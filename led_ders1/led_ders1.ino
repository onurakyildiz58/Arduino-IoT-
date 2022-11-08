
void setup()
{
  
  for(int i=8;i<13;i++)
  {
     pinMode(i, OUTPUT); // 8 9 10 11 12
  }
}
void loop()
{
  for(int i=8;i<13;i++)
  {
    digitalWrite(i, HIGH);   
    delay(200);                       
    digitalWrite(i, LOW);    
    delay(200); 
  }  
  for(int i=11;i>7;i--)
  {
    digitalWrite(i, HIGH);   
    delay(200);                       
    digitalWrite(i, LOW);    
    delay(200); 
  }   
}
