#ifndef TOF_H
#define TOF_H
#include <ToFFilter.h>
#include <Adafruit_VL53L0X.h>
#include <Wire.h>
#define XSHUT_FRONT 3 //add pins
#define XSHUT_LEFT  4//add pins
#define XSHUT_RIGHT 5//add pins
#define XSHUT_BACK  6//add pins
extern Adafruit_VL53L0X tofFront;
extern Adafruit_VL53L0X tofLeft;
extern Adafruit_VL53L0X tofRight;
extern Adafruit_VL53L0X tofBack;
extern float distFront, distLeft, distRight, distBack;
extern ToFFilter filterFront, filterLeft, filterRight, filterBack;
void  change();
void readTOF();



#endif