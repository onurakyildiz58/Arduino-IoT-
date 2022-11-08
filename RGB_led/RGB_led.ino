int RedPin = 9; 
int GreenPin = 10;// Öncelikli olarak pinlerimizi belirliyoruz.
int Bluepin = 11;
void setup()
{
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(Bluepin, OUTPUT);
}
void loop()
{
  // Kırmızı ışık için
  analogWrite(RedPin,255); // kırmızı max düzeyde yanıyor
  analogWrite(GreenPin,0); // Yeşil Sönük
  analogWrite(Bluepin,0);  // Mavi Sönük
  delay(2000);
  // Yeşil ışık için
  analogWrite(RedPin,0);     // Kırmızı sönük
  analogWrite(GreenPin,255); // Yeşil max düzeyde yanıyor
  analogWrite(Bluepin,0);    // Mavi Sönük
  delay(2000);
  // Mavi ışık için
  analogWrite(RedPin,0);    // Kırmızı sönük
  analogWrite(GreenPin,0);  // Yeşil sönük
  analogWrite(Bluepin,255); // Mavi max düzeyde yanıyor
  delay(2000);
  // RGB(122,68,45) rengi için
  analogWrite(RedPin,122); 
  analogWrite(GreenPin,68); 
  analogWrite(Bluepin,45);  
  delay(2000);
  // RGB(55,61,117) rengi için
  analogWrite(RedPin,55); 
  analogWrite(GreenPin,61); 
  analogWrite(Bluepin,117);  
  delay(2000);
 
}
