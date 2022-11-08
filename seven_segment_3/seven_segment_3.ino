int veri[] = {0xc0, 0xf9, 0xA4};

void setup() {
 pinMode(1,OUTPUT);
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
}

void loop() {
  for(int i=0;i<8;i++){
    digitalWrite(i+1, bitRead(veri[i], i))
  }
}
