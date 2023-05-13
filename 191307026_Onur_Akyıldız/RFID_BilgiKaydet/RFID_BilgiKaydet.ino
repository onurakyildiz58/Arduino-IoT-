#include <SPI.h>
#include <MFRC522.h>

const uint8_t RST_PIN = 9;
const uint8_t SS_PIN = 10;

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;        

/* blok numara başlangıcı */
int blockNum = 4;
byte block_data[16];
/* karttaki verileri dizi şeklinde okuyup yazma için */
byte bufferLen = 18;
byte readBlockData[18];

MFRC522::StatusCode status;

void setup() 
{
  /* seri haberleşme */
  Serial.begin(9600);
  SPI.begin();
  
  mfrc522.PCD_Init();
  Serial.println("kartı okutup işlem bitene kadar kaldırmayınız ...");
}


void loop()
{
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
  toBlockDataArray("191307058");
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
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else 
  {
    Serial.println("başarılı");
  }
  
  /* bloka verileri yazma */
  status = mfrc522.MIFARE_Write(blockNum, blockData, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.println("başarısız: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("yazma başarılı");
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
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("başarılı");
  }

  /* bloktan veri okuma */
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.println("başarısız: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else {
    Serial.println("okuma başarılı");
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
