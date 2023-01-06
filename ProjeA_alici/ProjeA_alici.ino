/*-----( kütüphaneleri yükleyelim )-----*/ 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//RF modülün pinleri
#define CE_PIN 9
#define CSN_PIN 10
 
const int kanal = 111;
 
/*-----( radio nesnesi yaratılıyor)-----*/
RF24 radio(CE_PIN, CSN_PIN); // 
/*-----( değişkenler tanımlanıyor )-----*/

int data[2];

// Motor sağ
const int enA = 5;
const int in1 = 7;    // sağ Motor (-)
const int in2 = 4;    // sağ Motor (+)

//motor sol
const int enB = 6;
const int in3 = 3;   // sol Motor (+)
const int in4 = 2;    // sol Motor (-)

int hiz;
void setup()   
{
  Serial.begin(9600);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(1000);
  
  //radio ile iletişim kuruyoruz
  Serial.println("Nrf24L01 Alıcı Başlatılıyor");
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, kanal);
  radio.startListening();
}
 
 
void loop()
{
  if ( radio.available() ) //eğer radyo ile temas kurabilmişse
    {
      Serial.println("nrf aktif");
      // done değişkeni false yapıyoruz ve while içinde sonsuz döngü oluşturarak verileri toplayacağız
      bool done = false;
      while (!done) 
      {
        radio.read(&data, sizeof(data));
        Serial.println("veriler geldi");
        delay(1000);
        /*
         * stabil değerler    ileri     geri      sağ       sol       dur
         * ax = 520-530       ax>530    ax<520    ay>510    ay<520    520<ax<530  510<ay<520
         * ay = 510-520
        */
        if(data[0] > 530)//ileri
        {
          Serial.print("ileri : ");
          Serial.println(data[0]);
          hiz = map(data[0], 530, 1024, 0, 255);
          digitalWrite(enA, hiz);
          digitalWrite(enB, hiz);
          digitalWrite(in1, HIGH);
          digitalWrite(in2, LOW);
          digitalWrite(in3, HIGH);
          digitalWrite(in4, LOW);
        }
        if(data[0] < 520)//geri
        {
          Serial.print("geri : ");
          Serial.println(data[0]);
          hiz = map(data[0], 0, 520, 0, 255);
          digitalWrite(enA, hiz);
          digitalWrite(enB, hiz);
          digitalWrite(in1, LOW);
          digitalWrite(in2, HIGH);
          digitalWrite(in3, LOW);
          digitalWrite(in4, HIGH);
        }
        if(data[1] < 510)//sol
        {        
          Serial.print("sol : ");
            Serial.println(data[1]);
              hiz = map(data[1], 0, 510, 0, 255);
              digitalWrite(enA, hiz);
              digitalWrite(enB, hiz);
              digitalWrite(in1, HIGH);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, HIGH);
        }
        if(data[1] > 520)//sağ
        {
          Serial.print("sağ : ");
              Serial.println(data[1]);
              hiz = map(data[1], 520, 1024, 0, 255);
              digitalWrite(enA, hiz);
              digitalWrite(enB, hiz);
              digitalWrite(in1, LOW);
              digitalWrite(in2, HIGH);
              digitalWrite(in3, HIGH);
              digitalWrite(in4, LOW);
        }
        if(data[0]>520 && data[0]<530 && data[1]>510 && data[1]<520)
        {
          Serial.print("dur : x ");
              Serial.print(data[0]);
              Serial.println(" y : ");
              Serial.println(data[1]);
              digitalWrite(enA, 0);
              digitalWrite(enB, 0);
        }
      }
    }
    else
    {
      Serial.println("Verici Bulunamadı");
      data[0] = 0;
      data[1] = 0;
      digitalWrite(enA, 0);
      digitalWrite(enB, 0);
    }
}
