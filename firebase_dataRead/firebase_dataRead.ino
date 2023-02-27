#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <Servo.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "FiberHGW_ZT2Y7A_2.4GHz"
#define WIFI_PASSWORD "pjCeU4xeTa"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDdV6mSsSLhWeyzxZ2VmFS1YPDDB-l-FZY"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "rccontrol-9a429-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//some importent variables
String sValue, sValue2;
bool signupOK = false;
Servo myservo; 

void setup() {
  Serial.begin(115200);
  myservo.attach(16);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  // steer
  if (Firebase.ready() && signupOK ) 
  {
    if (Firebase.RTDB.getString(&fbdo, "/direction")) 
    {
      if (fbdo.dataType() == "string") 
      {
        sValue = fbdo.stringData();
        int a = sValue.toInt();
        Serial.println(a);
        int steer = map(a, 0, 1024, 45, 135);
        Serial.print("yön : ");
        Serial.println(steer);
        myservo.write(steer);  
      }
    }
    else
    {
      Serial.println(fbdo.errorReason());
    }
    
    //speed
    if (Firebase.RTDB.getString(&fbdo, "/speed")) 
    {
      if (fbdo.dataType() == "string") 
      {
        sValue2 = fbdo.stringData();
        int b = sValue2.toInt();
        Serial.println(b);
        int speed = map(b, 0, 1024, 0, 255);
        Serial.print("hız : ");
        Serial.println(speed);
        //apply speed
      }
    }
    else 
    {
      Serial.println(fbdo.errorReason());
    }
  }
}
