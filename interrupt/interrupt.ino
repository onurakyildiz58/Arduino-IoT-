int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  attachInterrupt(0, Yak, RISING);//ilk başta yakıcak ilk değer 0 yanı pin 2 button buraya bağlanıcak
  Serial.begin(9600);
}

void loop() {
  delay(1000);
}

void Yak(){
  digitalWrite(led, HIGH);
  attachInterrupt(0, Sondur, FALLING);//yandı sonra söndürücek 1 sn beklicek buton için
}

void Sondur(){
  digitalWrite(led, LOW);
  attachInterrupt(0, Yak, RISING);//söndürdü 1 sn bekleyip yakıcak 
}
