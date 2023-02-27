int a = 0;
void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < 4; i++)
  {
        
        // 4 5 6 8 9
        a = i+4;
        if(a == 7){
          a == 8;
        }
        Serial.print("i : " + a);
        
  }
  
}
