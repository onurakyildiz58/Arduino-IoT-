int xPin = A0; 
int yPin = A1; 
int butonPin = 7; 
 
int xPozisyon;
int yPozisyon;
int butonDurum;

#define led1 8;
#define led2 9;
#define led3 10;
#define led4 11;
#define led4 12;
#define led4 13;

void setup()
{
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(butonPin, INPUT_PULLUP);
  pinMode(8, OUTPUT);//0-200
  pinMode(9, OUTPUT);//200-400
  pinMode(10, OUTPUT);//400-600
  pinMode(11, OUTPUT);//600-800
  pinMode(12, OUTPUT);//800-1000
}
 
void loop()
{
  xPozisyon = analogRead(xPin);
  yPozisyon = analogRead(yPin);
  butonDurum = digitalRead(butonPin);
  // sadece x ekseni için 1 - 1000
  if(xPozisyon < 200)
  {
    digitalWrite(8, HIGH);   
    delay(500);                       
    digitalWrite(8, LOW);    
    delay(500);
  }
  if(xPozisyon > 200 && xPozisyon < 400)
  {
    digitalWrite(9, HIGH);   
    delay(500);                       
    digitalWrite(9, LOW);    
    delay(500);
  }
  if(xPozisyon > 400 && xPozisyon < 600)
  {
    digitalWrite(10, HIGH);   
    delay(500);                       
    digitalWrite(10, LOW);    
    delay(500);
  }
  if(xPozisyon > 600 && xPozisyon < 800)
  {
    digitalWrite(11, HIGH);   
    delay(500);                       
    digitalWrite(11, LOW);    
    delay(500);
  }
  if(xPozisyon > 800 && xPozisyon < 1000)
  {
    digitalWrite(12, HIGH);   
    delay(500);                       
    digitalWrite(12, LOW);    
    delay(500);
  }
}
