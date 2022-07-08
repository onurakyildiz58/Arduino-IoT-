#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int RST_PIN = 9;
int SS_PIN = 10;
int servoPin = 8;

Servo motor;                          
MFRC522 rfid(SS_PIN, RST_PIN);
byte IDAc[4] = {80, 0, 64, 29};
byte IDKapa[4] = {192, 204, 186, 26};

void setup()
{
  motor.attach(servoPin);
  Serial.begin(9600);
  SPI.begin();
  lcd.init();
  lcd.backlight();
  rfid.PCD_Init();
  pinMode(7, OUTPUT);
}

void loop()
{

  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  if ( ! rfid.PICC_ReadCardSerial())
    return;

  if (rfid.uid.uidByte[0] == IDAc[0] &&
    rfid.uid.uidByte[1] == IDAc[1] &&
    rfid.uid.uidByte[2] == IDAc[2] &&
    rfid.uid.uidByte[3] == IDAc[3] )
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("kapi acik");
        lcd.setCursor(0,1);
        lcd.print("Hosgeldin");
        ekranaYazdir();
        motor.write(180);
        digitalWrite(7, HIGH);
        delay(100);
        digitalWrite(7, LOW);
        delay(100);
        digitalWrite(7, HIGH);
        delay(100);
        digitalWrite(7, LOW);
    }
    else if(rfid.uid.uidByte[0] == IDKapa[0] &&
    rfid.uid.uidByte[1] == IDKapa[1] &&
    rfid.uid.uidByte[2] == IDKapa[2] &&
    rfid.uid.uidByte[3] == IDKapa[3] )
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("kapi kapali");
        lcd.setCursor(0,1);
        lcd.print("gule gule");
        motor.write(0);
        ekranaYazdir();
        digitalWrite(7, HIGH);
        delay(800);
        digitalWrite(7, LOW);
    }
    else{                                
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("izinsiz giris");
      lcd.setCursor(0,1);
      lcd.print("polisi ararim");
      motor.write(0);
      ekranaYazdir();
      digitalWrite(7, HIGH);
      delay(800);
      digitalWrite(7, LOW);
    }
  rfid.PICC_HaltA();
}
void ekranaYazdir(){
  Serial.print("ID Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++){
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println("");
}
