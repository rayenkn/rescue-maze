#include <Arduino.h>
#include "black.h"

bool onblack = false;
unsigned long blackstart = 0;
const unsigned long howlongback = 8; 

extern void setMotors(int l, int r);
extern void stopMotors();

void onblackk() {
  if (digitalRead(IR_PIN) == HIGH && !onblack) {
    onblack    = true;
    blackstart = millis();
  }

  if (onblack && millis() - blackstart >= howlongback) {
    onblack = false;
    stopMotors();
  }
}

void backwards() {
  setMotors(-150, -150);
}