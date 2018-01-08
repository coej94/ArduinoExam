#include <Servo.h>
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
Servo doorServo;
Servo fingerServo;

int swPin = 2;               //switch on pin 2

int pos = 0;

int selectedMove = 0;             //move selector

void setup()
{
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

  pinMode(swPin, INPUT);
  doorServo.attach(9);           //set door servo on Pin 9 pwm
  fingerServo.attach(10);          //set finger servo on Pin 10 pwm
  doorServo.write(80);           //set door to hiding position
  fingerServo.write(270);            //set finger to hiding position
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
  lcd.setCursor(0, 1);
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  lcd.println();
  delay(1000);
  lcd.clear();

  //if the switch is on, move door and finger to switch it off
  if (digitalRead(swPin) == HIGH)
  {

    if (selectedMove > 2) {
      selectedMove = 0;
    } //when all moves are played, repeat the moves from beginning

    if (selectedMove == 0) {
      simpleClose();
    }
    else if (selectedMove == 1) {
      simpleClose();
    }
    selectedMove += 1;         //swith to next move
  }
}



// Moves

// basic move
void simpleClose()
{
  //Moving door
  for (pos = 80; pos < 155; pos += 3)
  {
    doorServo.write(pos);
    delay(15);
  }

  //Moving hand
  for (pos = 270; pos > 0; pos -= 15)
  {
    fingerServo.write(pos);
    delay(15);
  }

  //hiding hand
  for (pos = 0; pos <= 270; pos += 15)
  {
    fingerServo.write(pos);
    delay(15);
  }

  //hiding door
  for (pos = 155; pos >= 80; pos -= 3)
  {
    doorServo.write(pos);
    delay(15);
  }
}
