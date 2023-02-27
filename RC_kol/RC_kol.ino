int speed = 0;
int direction = 0;

void setup() 
{
  Serial.begin(9600);  
}

void loop() 
{
  speed = analogRead(A0);//hız
  direction = analogRead(A1);//yön
  Serial.print("hız : ");
  Serial.println(speed);
  Serial.print("yön : ");
  Serial.println(direction);
  delay(500);
}
