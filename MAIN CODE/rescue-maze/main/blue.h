#ifndef BLUE_H
#define BLUE_H
#include "PID_30cm.h"
#include "colour_sensor.h"

extern bool onblue;
extern unsigned long bluestart;
extern float correctionleft;
extern float correctionright;
extern const unsigned long howlongblue;
extern unsigned long holdlasttime;
extern float nKp , nKi, nKd ;

extern float errorleft,  lasterrorleft , integralleft  ;
extern float errorright, lasterrorright , integralright;
extern float Xderivativeleft,  Yderivativeleft  ;
extern float Xderivativeright, Yderivativeright ;
extern float ndt;



void onbluee();

#endif
