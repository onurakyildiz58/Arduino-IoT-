#define led 8
#define btn 7
const int btnstate = 0;


void setup() 
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
}

void loop() 
{
  Serial.println(digitalRead(btn));
  int btnstate = digitalRead(btn);
  
    if (btnstate == 1) 
    {
      digitalWrite(led, HIGH);
    }
    else 
    {
      digitalWrite(led, LOW);
    }
  
 
}
