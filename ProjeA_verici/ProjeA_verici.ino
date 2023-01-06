#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

/*-----( Değişkenlerimizi tanımlıyoruz )-----*/
// Gyro ve Accelerometer'a erişmek ve onu hareket ettirmek için nesneyi tanımlayın (Gyro verilerini kullanmıyoruz)
#define MPU 0x68
int16_t ivmeX,ivmeY,ivmeZ,IsI,GyX,GyY,GyZ;

#define CE_PIN 9
#define CSN_PIN 10

const int kanal = 111; 

/*-----( RF24 kütüphanesi ile radio adında bir haberleşme nesnesi yaratıyoruz )-----*/
RF24 radio(CE_PIN, CSN_PIN); // radio yaratıldı
/*-----( Girdileri tutacağımız diziyi tanımlayalım )-----*/
int data[2];


void setup()
{
  Serial.begin(9600); 
  //kumandadaki gryo sensörü tanımlıyoruz
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);
  
  
  radio.begin(); //iletişimi başlattık
  radio.setDataRate( RF24_250KBPS );
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(kanal); //adrese bağlanıyoruz
}
 
void loop()
{ 
    verileriOku();
    data[0] = map(ivmeX, -17000, 17000, 0, 1024);
    data[1] = map(ivmeY, -17000, 17000, 0, 1024);
    Serial.print("x : ");
    Serial.println(data[0]);
    Serial.print("y : ");
    Serial.println(data[1]);
    radio.write( &data, sizeof(data) );
}

void verileriOku()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // mpu6050 nin ilk sensör verisinin adresi.
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true); //0X3B den başlayan 14 bitlik veri istendi. İçinde tüm değerlerimiz var.
  
  ivmeX=Wire.read()<<8|Wire.read();   
  ivmeY=Wire.read()<<8|Wire.read(); 
  ivmeZ=Wire.read()<<8|Wire.read(); 
  IsI=Wire.read()<<8|Wire.read(); 
  GyX=Wire.read()<<8|Wire.read(); 
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();
}
