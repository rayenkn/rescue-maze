#include <Arduino.h>
#include "navigation.h"
#include "blue.h"
float Kp1 = 0, Ki1 = 0, Kd1 = 0;
float error1, lasterror1 = 0, integral1 = 0;
float Xderivative1 = 0, Yderivative1 = 0;
float correction1 = 0; 

float Kp2 = 0, Ki2 = 0, Kd2 = 0;
float error2, lasterror2 = 0, integral2 = 0;
float Xderivative2 = 0, Yderivative2 = 0;
float correction2 = 0;

float Kp3 = 0, Ki3 = 0, Kd3 = 0;

int x ; // distLeft > x means left is open

bool turning       = false;
float turnTarget   = 0;
float turnIerror   = 0;
float turnLasterr  = 0;
float turnXderiv   = 0;
float turnYderiv   = 0;
bool turnUpdate() {
  if (!turning) return true;

  if (onblue) {
    
    return false;
  }

  currenttime = micros();
  dt = (currenttime - lasttime) / 1000000.0;
  if (dt <= 0.001) dt = 0.001;
  lasttime = currenttime;

  float err = gyroError(turnTarget, gyro());

  // turn done
  if (abs(err) <= 1.5) {
    turning      = false;
    turnIerror   = 0;
    turnLasterr  = 0;
    turnXderiv   = 0;
    turnYderiv   = 0;
    return true;
  }

  turnIerror += err * dt;
  turnIerror  = constrain(turnIerror, -100, 100);

  turnXderiv = (err - turnLasterr) / dt;
  turnYderiv = filter * turnXderiv + (1 - filter) * turnYderiv;
  turnLasterr = err;

  float speed = (err * Kp3) + (turnIerror * Ki3) + (turnYderiv * Kd3);
  speed = constrain(speed, -255, 255);


  return false;
}

void turnLeft()   { float t = gyro()+90;  if(t>=360) t-=360; turnTarget=t; turning=true; }
void turnRight()  { float t = gyro()-90;  if(t<0)    t+=360; turnTarget=t; turning=true; }
void turnAround() { float t = gyro()+180; if(t>=360) t-=360; turnTarget=t; turning=true; }


