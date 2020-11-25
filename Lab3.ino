#include <LiquidCrystal.h>
#include <Wire.h>
#include "DS1307.h"

#define ENABLE 5
#define DIRA 3
#define DIRB 4

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
DS1307 clock;

int button = 13;
int count = 0;
int i;

void setup() {
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);

  pinMode(button, INPUT_PULLUP);

  lcd.begin(16, 2);

  clock.begin();
  clock.fillByHMS(3, 42, 00); 
  clock.setTime();//write time to the RTC chip
}

void loop() {

  clock.getTime();
  lcd.setCursor(0,0);
  lcd.print(clock.hour, DEC);
  lcd.print(":");
  lcd.print(clock.minute, DEC);
  
  if(digitalRead(button) == LOW && count%2 == 1) {
    analogWrite(ENABLE,128);
    digitalWrite(DIRA,HIGH); 
    digitalWrite(DIRB,LOW);
    lcd.setCursor(0, 1);
    lcd.print("C  1/2");
    count++;
  }
  else if (digitalRead(button) == LOW) {
    analogWrite(ENABLE,128);
    digitalWrite(DIRA,LOW); 
    digitalWrite(DIRB,HIGH);
    lcd.setCursor(0, 1);
    lcd.print("CC 1/2");
    count++;
  }
}
