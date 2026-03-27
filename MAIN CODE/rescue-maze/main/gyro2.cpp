#include "gyro2.h"
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
void setupGyro() {
  if(!bno.begin()) {
    Serial.println("gyro not detected");
    while(1);
  }
  delay(1000);
}

float gyro() {
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