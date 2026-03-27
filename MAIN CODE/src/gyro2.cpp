#include <Arduino.h>
#include "gyro2.h"
#include "TOF.h" 
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setupGyro() {
  tcaSelect(4);
  if(!bno.begin()) {
    Serial.println("gyro not detected");
    while(1);
  }
  delay(1000);
}

float gyro() {
  tcaSelect(4);
  sensors_event_t event;
  bno.getEvent(&event);
  return event.orientation.x;
}

float gyroError(float target, float current) {
  float error = target - current;
  if (error > 180)  error -= 360;
  if (error < -180) error += 360;
  return error;
}