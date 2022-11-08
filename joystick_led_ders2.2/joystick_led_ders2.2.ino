int xPin = A0; 
int yPin = A1; 
int butonPin = 7; 
 
int xPozisyon;
int yPozisyon;
int butonDurum;

#define ledust 10;
#define ledsag 9;
#define ledalt 8;
#define ledsol 11;

void setup()
{
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(butonPin, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}
 
void loop()
{
  xPozisyon = analogRead(xPin);
  yPozisyon = analogRead(yPin);
  butonDurum = digitalRead(butonPin);
 
  Serial.print("X Pozisyonu: ");
  Serial.print(xPozisyon);
  Serial.print(" | Y Pozisyonu: ");
  Serial.print(yPozisyon);
  Serial.print(" | Buton Durum: ");
  Serial.println(butonDurum);
  delay(500);

  if(xPozisyon > 900)
  {
    digitalWrite(8, HIGH);   
    delay(500);                       
    digitalWrite(8, LOW);    
    delay(500);
  }
  else if(xPozisyon < 200)
  {
    digitalWrite(10, HIGH);   
    delay(500);                       
    digitalWrite(10, LOW);    
    delay(500);
  }
  else if(yPozisyon > 900)
  {
    digitalWrite(11, HIGH);   
    delay(500);                       
    digitalWrite(11, LOW);    
    delay(500);
  }
  else if(yPozisyon < 200)
  {
    digitalWrite(9, HIGH);   
    delay(500);                       
    digitalWrite(9, LOW);    
    delay(500);
  }
  else if(butonDurum == 0)
  {
    digitalWrite(8, HIGH);                            
    digitalWrite(9, HIGH);        
    digitalWrite(10, HIGH);                     
    digitalWrite(11, HIGH);    
  }
  else if(butonDurum == 1)
  {
    digitalWrite(8, LOW);                            
    digitalWrite(9, LOW);        
    digitalWrite(10, LOW);                     
    digitalWrite(11, LOW);    
  }
}
