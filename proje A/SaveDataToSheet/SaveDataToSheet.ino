#include <SPI.h>
#include <MFRC522.h>

// sheete gidicek verilerin tanımlanması
String student_id;

int blocks[] = {4,5,6,8,9};
#define total_blocks  (sizeof(blocks) / sizeof(blocks[0]))

#define RST_PIN  9 
#define SS_PIN   10
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
  //Serial.println('\n');
 
  SPI.begin();
}

void loop() 
{
  mfrc522.PCD_Init();
  /* kart tarama */
  /* kart algılandığında reset işlemi */
  if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}
  /* kartı seçme */
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  /* bloktan veriyi okuma */
  //Serial.println();
  //Serial.println(F("RFID okunuyor..."));  
 
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
  Serial.println(values);
 
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
    //Serial.print("okuma hatalı: ");
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    //Serial.println("okuma başarılı");
  }
  /* bloktan veri okuma */
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK) 
  {
    //Serial.print("okuma hatalı: ");
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else 
  {
    readBlockData[16] = ' ';
    readBlockData[17] = ' ';
    //Serial.println("başarılı");
      
  }
}
