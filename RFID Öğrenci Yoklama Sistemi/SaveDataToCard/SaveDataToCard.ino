#include <SPI.h>
#include <MFRC522.h>

//GPIO 0 --> D3
//GPIO 2 --> D4
const uint8_t RST_PIN = D3;
const uint8_t SS_PIN = D4;

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;        

/* blok numara başlangıcı */
int blockNum = 4;
byte block_data[16];
/* karttaki verileri dizi şeklinde okuyup yazma için */
byte bufferLen = 18;
byte readBlockData[18];

MFRC522::StatusCode status;

int red = D0;
int green = D1;
int blue = D2;

void setup() 
{
  /* seri haberleşme */
  Serial.begin(9600);
  SPI.begin();
  
  mfrc522.PCD_Init();
  Serial.println("kartı okutup işlem bitene kadar kaldırmayınız ...");
  
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}


void loop()
{
  b();
  
  /* doğrulama */
  for (byte i = 0; i < 6; i++){
    key.keyByte[i] = 0xFF;
  }
  
  /* yeni kart tarama */
  /* yeni kart okutulunca reset işlemi */
  if ( ! mfrc522.PICC_IsNewCardPresent()){return;}
  
  /* okunan kartı seçme */
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  Serial.print("\n");
  Serial.println("**kart algılandı**");
  
  /* kart UID  */
  Serial.print(F("Kart UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.print("\n");

  /* kart tipi */
  Serial.print(F("PICC tip: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  /* bloklara yazılan veriler */
  blockNum = 4;
  toBlockDataArray("191307026"); //Student ID
  WriteDataToBlock(blockNum, block_data);
  ReadDataFromBlock(blockNum, readBlockData);
  dumpSerial(blockNum, readBlockData);

  blockNum = 5;
  toBlockDataArray("Onur Akyıldız"); //First Name
  WriteDataToBlock(blockNum, block_data);
  ReadDataFromBlock(blockNum, readBlockData);
  dumpSerial(blockNum, readBlockData);

  blockNum = 6;
  toBlockDataArray("Kocaeli Uni"); //Last Name
  WriteDataToBlock(blockNum, block_data);
  ReadDataFromBlock(blockNum, readBlockData);
  dumpSerial(blockNum, readBlockData);

  blockNum = 8;
  toBlockDataArray("Teknoloji fak"); //Faculty Name
  WriteDataToBlock(blockNum, block_data);
  ReadDataFromBlock(blockNum, readBlockData);
  dumpSerial(blockNum, readBlockData);

  blockNum = 9;
  toBlockDataArray("Bil Sis Müh"); //Department Name
  WriteDataToBlock(blockNum, block_data);
  ReadDataFromBlock(blockNum, readBlockData);
  dumpSerial(blockNum, readBlockData);
  
}

void WriteDataToBlock(int blockNum, byte blockData[]) 
{
  Serial.println("bloklara veri yazılıyor ... ");
  Serial.println("blok numrası : "+blockNum);
  /* yazma erişimi için istenen veri bloğunun kimliğinin doğrulanması */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.println("başarısız: ");
    r();
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else 
  {
    Serial.println("başarılı");
    g();
  }
  
  /* bloka verileri yazma */
  status = mfrc522.MIFARE_Write(blockNum, blockData, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.println("başarısız: ");
    r();
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("yazma başarılı");
    g();
  }
}


void ReadDataFromBlock(int blockNum, byte readBlockData[]) 
{
   Serial.println("bloktan veri okunuyor... ");
   Serial.println("blok numarası: "+blockNum);

  /* Okuma erişimi için istenen veri bloğunun kimliğinin doğrulanması */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.println("başarısız: ");
    r();
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("başarılı");
    g();
  }

  /* bloktan veri okuma */
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.println("başarısız: ");
    r();
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else {
    Serial.println("okuma başarılı");
    g(); 
  }
}

void dumpSerial(int blockNum, byte blockData[]) 
{
   Serial.print("\n");
   Serial.print("bloktaki veri:");
   Serial.print(blockNum);
   Serial.print(" --> ");
   for (int j=0 ; j<16 ; j++)
   {
     Serial.write(readBlockData[j]);
   }
   Serial.print("\n");
   Serial.print("\n");
}

void toBlockDataArray(String str) 
{
  byte len = str.length();
  if(len > 16) len = 16;
  for (byte i = 0; i < len; i++) block_data[i] = str[i];
  for (byte i = len; i < 16; i++) block_data[i] = ' ';
}

void r(){
  analogWrite(red,255);
  analogWrite(green,0);
  analogWrite(blue,0);
  delay(100); 
}
void g(){
  analogWrite(red,0);
  analogWrite(green,255);
  analogWrite(blue,0);
  delay(100); 
}
void b(){
  analogWrite(red,0);
  analogWrite(green,0);
  analogWrite(blue,255);
  delay(100); 
}
