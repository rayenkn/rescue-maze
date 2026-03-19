#include <Arduino.h>
#include "blue.h"
bool onblue = false;
unsigned long bluestart;
float correctionleft  = 0;
float correctionright = 0;
const unsigned long howlongblue = 5000;
unsigned long holdlasttime;
float nKp = 0, nKi = 0, nKd = 0;

float errorleft,  lasterrorleft  = 0, integralleft  = 0;
float errorright, lasterrorright = 0, integralright = 0;
float Xderivativeleft,  Yderivativeleft  = 0;
float Xderivativeright, Yderivativeright = 0;
float ndt;
void onbluee() {

  ColorData data = colour_sensor();


  if ((data.b > data.r) && (data.b > data.g) && (data.c > threshold) && !onblue) {
    onblue    = true;
    bluestart = millis();
    integralleft   = 0; integralright  = 0;
    lasterrorleft  = 0; lasterrorright = 0;
    correctionleft = 0; correctionright= 0;
    counterLEFT    = 0; counterRIGHT   = 0;
  }

  if (onblue) {
    if (millis() - bluestart >= howlongblue) {
      onblue = false; 
    } else {
    
      unsigned long currenttime = micros();
      ndt = (currenttime - holdlasttime) / 1000000.0;
      if (ndt <= 0 || ndt > 0.1) return;
      holdlasttime = currenttime;

      errorleft  = 0 - counterLEFT;
      errorright = 0 - counterRIGHT;

      if (abs(correctionleft)  < 255) integralleft  += errorleft  * ndt;
      if (abs(correctionright) < 255) integralright += errorright * ndt;

      integralleft  = constrain(integralleft,  -100, 100);
      integralright = constrain(integralright, -100, 100);

      Xderivativeleft  = (errorleft  - lasterrorleft)  / ndt;
      Xderivativeright = (errorright - lasterrorright) / ndt;

      Yderivativeleft  = filter * Xderivativeleft  + (1 - filter) * Yderivativeleft;
      Yderivativeright = filter * Xderivativeright + (1 - filter) * Yderivativeright;

      lasterrorleft  = errorleft;
      lasterrorright = errorright;

      correctionleft  = (errorleft  * nKp) + (integralleft  * nKi) + (Yderivativeleft  * nKd);
      correctionright = (errorright * nKp) + (integralright * nKi) + (Yderivativeright * nKd);
    }
  }
}