#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H
#include <Wire.h>
#include "Adafruit_TCS34725.h"
 
extern int threshold;
extern Adafruit_TCS34725 tcs;
 
struct ColorData {
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t c;
};
void setupp();
ColorData colour_sensor();
 
#endif