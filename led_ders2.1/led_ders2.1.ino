const int button = 7;            
const int led1 = 8;   
const int led2 = 9;
const int led3 = 10;             
int ledflag = 0;  
int ledsira = 0;                 

void setup() {
  pinMode(button,INPUT);        
  pinMode(led1,OUTPUT);           
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);      
}

void loop() {  
  if(ledsira == 0)
  {
    
    if (ledflag==0)
    {             
      ledflag=1;
      ledsira++;                 
      digitalWrite(led1,HIGH);     
    }                           
    else 
    {                        
      ledflag=0;                  
      digitalWrite(led1,LOW);     
    }
    delay(500);
  }
  if(ledsira == 1)
  {
   
    if (ledflag==0)
    {             
      ledflag=1;  
      ledsira++;              
      digitalWrite(led2,HIGH);     
    }                           
    else 
    {                        
      ledflag=0;                  
      digitalWrite(led2,LOW);     
    }
    delay(500);
  }
  if(ledsira == 2)
  {
    
    if (ledflag==0)
    {             
      ledflag=1;
      ledsira = 0;                
      digitalWrite(led3,HIGH);     
    }                           
    else 
    {                        
      ledflag=0;                  
      digitalWrite(led3,LOW);     
    }
    delay(500);
  }
                           
}                                 
