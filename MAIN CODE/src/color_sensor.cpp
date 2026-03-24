#include <Arduino.h>
#include "colour_sensor.h"
#include "TOF.h" 
int threshold = 50;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

 
void setupp() {
  tcaSelect(5);
  Serial.begin(115200);
  if (!tcs.begin()) {
    Serial.println("colour sensor not found");
    while (1);
  }
}
 
ColorData colour_sensor() {
  tcaSelect(4);
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  return {r, g, b, c};
}