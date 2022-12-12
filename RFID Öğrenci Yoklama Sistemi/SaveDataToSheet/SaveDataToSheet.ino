#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <HTTPSRedirect.h>


// Google Script deploy kimliği:
const char *GScriptId = "AKfycbyqQOre8jZbxRNB6tQLhefHS6rL98v2Cfq2Uk0SEZXH5ffxy1Ied22ubzr6sbp0DUnHRg";

// wifi bilgileri:
const char* ssid     = "FiberHGW_ZT2Y7A_2.4GHz";
const char* password = "pjCeU4xeTa";

String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"Sayfa1\", \"values\": ";
String payload = "";

// Google Sheets setup (do not edit)
const char* host        = "script.google.com";
const int   httpsPort   = 443;
const char* fingerprint = "";
String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

// sheete gidicek verilerin tanımlanması
String student_id;

int blocks[] = {4,5,6,8,9};
#define total_blocks  (sizeof(blocks) / sizeof(blocks[0]))

#define RST_PIN  D3  //D3
#define SS_PIN   D4  //D4
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;  
MFRC522::StatusCode status;

int blockNum = 2;  
/* verileri dizi şeklince okucağız*/
byte bufferLen = 18;
byte readBlockData[18];

void setup()
{
  /*seri haberleşme*/
  Serial.begin(9600);        
  delay(10);
  Serial.println('\n');
  
  SPI.begin();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);             
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  
  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  delay(5000);
  
  Serial.print("Connecting to ");
  Serial.println(host);
  
  bool flag = false;
  for(int i=0; i<5; i++)
  { 
    int retval = client->connect(host, httpsPort);
    if (retval == 1)
    {
      flag = true;
      String msg = "Connected. OK";
      Serial.println(msg);
      
      break;
    }
    else
    {
      Serial.println("Connection failed. Retrying...");
    }
  }
  if (!flag)
  {
    
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    delay(5000);
    return;
  }
  delete client;    
  client = nullptr;
}

void loop() 
{
  static bool flag = false;
  if (!flag)
  {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr)
  {
    if (!client->connected())
      {
        client->connect(host, httpsPort);
      }
  }
  else
  {
    Serial.println("Error creating client object!");
  }
 
  
  mfrc522.PCD_Init();
  /* kart tarama */
  /* kart algılandığında reset işlemi */
  if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}
  /* kartı seçme */
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  /* bloktan veriyi okuma */
  Serial.println();
  Serial.println(F("RFID okunuyor..."));  
 
  String values = "", data;

 
  //url oluşturma
  for (byte i = 0; i < total_blocks; i++)
  {
    ReadDataFromBlock(blocks[i], readBlockData);
    if(i == 0)
    {
      data = String((char*)readBlockData);
      data.trim();
      student_id = data;
      values = "\"" + data + ",";
    }
    else if(i == total_blocks-1)
    {
      data = String((char*)readBlockData);
      data.trim();
      values += data + "\"}";
    }
    else
    {
      data = String((char*)readBlockData);
      data.trim();
      values += data + ",";
    }
  }
  
  // json objesi oluşturup sheete yazma
  // values = "\"" + value0 + "," + value1 + "," + value2 + "\"}"
  payload = payload_base + values;
  
 
  
  // sheete göndeme
  Serial.println("veri gönderiliyor...");
  Serial.println(payload);
  if(client->POST(url, host, payload))
  { 
      //lcd kodları olucak
  }
  else
  {
    Serial.println("hata");
  }   
  delay(5000);
}

void ReadDataFromBlock(int blockNum, byte readBlockData[]) 
{ 
  for (byte i = 0; i < 6; i++) 
  {
    key.keyByte[i] = 0xFF;
  }
  /* Okuma erişimi için istenen veri bloğunun kimliğinin doğrulanması */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  
  if (status != MFRC522::STATUS_OK)
  {
     Serial.print("okuma hatalı: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    Serial.println("okuma başarılı");
  }
  /* bloktan veri okuma */
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK) 
  {
    Serial.print("okuma hatalı: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else 
  {
    readBlockData[16] = ' ';
    readBlockData[17] = ' ';
    Serial.println("başarılı");  
  }
}
