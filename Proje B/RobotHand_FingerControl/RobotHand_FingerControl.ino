#include <Servo.h>

Servo thumb;
Servo index;
Servo middle;
Servo ring;
Servo pinky;

#define numOfValsRec 5
#define digitsPerValRec 1

int valsRec[numOfValsRec];

//gelen veri şu şekildedir $00000 = parmaklar kapalı
//gelen veri şu şekildedir $11111 = parmaklar açık
int stringLength = (numOfValsRec * digitsPerValRec) + 1;
int counter = 0;

//$ işaretini görünce true dönücek ve gelen veriyi degerUzunlugu kadar okumaya başlıcak 
bool counterStart = false;
String recievedString;

void setup() 
{
  Serial.begin(9600);
  
  thumb.attach(2);
  index.attach(3);
  middle.attach(4);
  ring.attach(5);
  pinky.attach(6);

}
void receieveData()
{
  while(Serial.available())
  {
    char c = Serial.read(); 
    if(c == '$')
    {
      counterStart = true;
    }
    if(counterStart)
    {
      if(counter < stringLength)
      {
        recievedString = String(recievedString + c);
        counter++;
      }
      if(counter >= stringLength)
      {
        for(int i = 0; i < numOfValsRec; i++)
        {
          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = recievedString.substring(num, num + digitsPerValRec).toInt();
        }
        recievedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}


void loop() 
{
  receieveData();
  
  //baş parmak
  if(valsRec[0] == 1){ thumb.write(180); Serial.println("baş açık");}else{ thumb.write(0); Serial.println("baş kapalı");}

  //işaret parmak
  if(valsRec[1] == 1){ index.write(180); Serial.println("işaret açık");}else{ index.write(0); Serial.println("işaret kapalı");}
  
  //orta parmak
  if(valsRec[2] == 1){ middle.write(180); Serial.println("orta açık");}else{ middle.write(0); Serial.println("orta kapalı");}
  
  //yüzük parmak
  if(valsRec[3] == 1){ ring.write(180); Serial.println("yüzük açık");}else{ ring.write(0); Serial.println("yüzük kapalı");}

   //küçük parmak
  if(valsRec[4] == 1){ pinky.write(180); Serial.println("küçük açık");}else{ pinky.write(0); Serial.println("küçük kapalı");}
}
