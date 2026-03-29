#include <Arduino.h>
#ifndef ENCODER_H
#define ENCODER_H


extern const int clkLEFT  ;
extern const int dtLEFT   ;
extern const int clkRIGHT ;
extern const int dtRIGHT  ;

extern volatile int counterLEFT ;
extern volatile int counterRIGHT;

extern float dia ; 
extern int   i   ; 

extern float Kp , Ki , Kd ;

extern float filter     ;
extern float dt;
extern float lasterror  ;
extern float integral   ;
extern float Xderivative , Yderivative ;

extern bool  moving          ;
extern float targetDistance  ;
extern float d               ;    

extern float encoderCorrection;

extern unsigned long currenttime, lasttime;

void isrLeft();
void isrRight();
void setuppp();
void iniit();
void loopp();

#endif
