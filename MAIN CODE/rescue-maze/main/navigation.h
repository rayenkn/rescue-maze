#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "gyro2.h"
#include "TOF.h"
#include "PID_30cm.h"


extern float Kp1, Ki1, Kd1;
extern float error1, lasterror1, integral1;
extern float Xderivative1, Yderivative1;
extern float correction1; 

extern float Kp2, Ki2, Kd2;
extern float error2, lasterror2, integral2;
extern float Xderivative2 , Yderivative2;
extern float correction2;

extern float Kp3, Ki3, Kd3;

extern int x ; // distLeft > x means left is open

extern bool turning      ;
extern float turnTarget  ;
extern float turnIerror  ;
extern float turnLasterr ;
extern float turnXderiv  ;
extern float turnYderiv  ;

bool turnUpdate();
void turnLeft();
void turnRight();
void turnAround();
void nav();

#endif
