const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const int delayTime = 20;
const int stepSize = 5;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i += stepSize) {
    analogWrite(redPin, 255 - i);
    analogWrite(greenPin, 0 + i);
    analogWrite(bluePin, 0);
    delay(delayTime);
  }
  for (int i = 0; i <= 255; i += stepSize) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255 - i);
    analogWrite(bluePin, 0 + i);
    delay(delayTime);
  }
  for (int i = 0; i <= 255; i += stepSize) {
    analogWrite(redPin, 0 + i);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255 - i);
    delay(delayTime);
  }
}