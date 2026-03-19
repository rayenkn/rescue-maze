#include <Arduino.h>
#ifndef GYRO_H
#define GYRO_H
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>

extern Adafruit_BNO055 bno;

void setupGyro();
float gyro();
float gyroError(float target, float current);
#endif