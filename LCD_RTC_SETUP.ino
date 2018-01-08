#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"

// LCD setup:
// VSS - gnd
// VDD - 5V
// V0  - Wheel data (mid pin)
// RS  - 12
// RW  - gnd
// E   - 11
// D4  - 2
// D5  - 3
// D6  - 4
// D7  - 5
// A   - gnd
// K   - 5v (with 330Ω)

// Wheel setup
// pin1 - gnd
// mid  - v0 (LCD)
// pin3 - 5V 

// RTC setup
// SCL  - A5
// SDA  - A4
// VCC  - 5V
// GND  - GND



RTC_DS1307 RTC;

LiquidCrystal lcd( 12, 11, 2, 3, 4, 5);

void setup() {
  Serial.begin(9600);
  Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time 
    //this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("loading");
  delay(3000);
  lcd.clear();
  lcd.print("hallo World");
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = RTC.now(); 
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    lcd.print(' ');
    lcd.setCursor(0,1);
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
    lcd.println(); 
    delay(1000);
    lcd.clear();
}
