#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
 Serial.begin(9600);
 lcd.init();
 lcd.backlight();
 
}
  
void loop() {
  lcd.setCursor(1,0);
  lcd.print("batuu");

}
