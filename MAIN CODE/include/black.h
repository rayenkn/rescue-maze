#include <Arduino.h>
#ifndef BLACK_H
#define BLACK_H

#define IR_PIN 35//add pin

extern bool onblack;
extern unsigned long blackstart;
extern const unsigned long howlongback;

void onblackk();
void backwards();

#endif