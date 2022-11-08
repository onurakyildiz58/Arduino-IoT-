#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

const int  trigPin = 6;
const int   echoPin = 7;
int duration; 
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();                     
  lcd.backlight();
}


void loop() 
{
  lcd.clear();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  lcd.setCursor(1, 0);
  lcd.print("Boyunuz");
  lcd.setCursor(1, 1);
  lcd.print(abs(distance));  
}

 
