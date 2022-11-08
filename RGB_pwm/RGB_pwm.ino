
int led1_R = 9;
int led1_G = 10;
int led1_B = 11;
char number='0';
int i;
void setup()
{
  pinMode(led1_R, OUTPUT);
  pinMode(led1_G, OUTPUT);
  pinMode(led1_B, OUTPUT);
}
void loop()
{
  switch(number)
  {
    case '0':
            for( i=0; i<255; i=i+5)
            {
              analogWrite(led1_R, i);
              delay(10);
            } 
            for( i=255; i>0; i=i-5)
            {
              analogWrite(led1_R, i);
              delay(10);
            } 
            number='1';
            
    break;
    case '1':
          for( i=0; i<255;i=i+5)
          {
            analogWrite(led1_G, i);
            delay(10);
          }
          for( i=250; i>0;i=i-5)
          {
            analogWrite(led1_G, i);
            delay(10);
          }
          number='2';
    break;
    case '2':
          for( i=0; i<255;i=i+5)
          {
            analogWrite(led1_B, i);
            delay(10);
          }
          for( i=255; i>0;i=i-5)
          {
            analogWrite(led1_B, i);
            delay(10);
          }
          number='0';
    break;
    default:
    break;
  }
  
}
