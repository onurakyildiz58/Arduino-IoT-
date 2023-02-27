#define role1 D0


void setup() 
{
  Serial.begin(9600);
  pinMode(role1, OUTPUT);

}

void loop() {
  
  digitalWrite(role1, HIGH);
  delay(1000);
  digitalWrite(role1, LOW);
  delay(1000);
}
