#ifndef TOF_H
#define TOF_H
#include <Arduino.h>
#include <ToFFilter.h>
#include <Adafruit_VL53L0X.h>
#include <Wire.h>
#define TCA_ADDR 0x70//add pin
#define CH_TOF_FRONT 1//add pin
#define CH_TOF_LEFT  2//add pin
#define CH_TOF_RIGHT 3//add pin
#define CH_TOF_BACK  4//add pin
extern Adafruit_VL53L0X tofFront;
extern Adafruit_VL53L0X tofLeft;
extern Adafruit_VL53L0X tofRight;
extern Adafruit_VL53L0X tofBack;
extern float distFront, distLeft, distRight, distBack;
extern ToFFilter filterFront, filterLeft, filterRight, filterBack;
void tcaSelect(uint8_t channel);
void change();
void readTOF();



#endif