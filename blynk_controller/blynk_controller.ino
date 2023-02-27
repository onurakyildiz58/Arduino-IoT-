#define BLYNK_TEMPLATE_ID "TMPLV56TSoWg"
#define BLYNK_DEVICE_NAME "rc controller"
#define BLYNK_AUTH_TOKEN "G1NgVMgCXcVv7JYh1NE7l0qKZPgVxQ4t"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Servo.h>
Servo steer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "FiberHGW_ZT2Y7A_2.4GHz";
char pass[] = "pjCeU4xeTa";

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  steer.attach(16);
}

void loop() {
 Blynk.run();

}

BLYNK_WRITE(V1){
  steer.write(param.asInt());
}
