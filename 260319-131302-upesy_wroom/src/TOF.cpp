#include "TOF.h"
Adafruit_VL53L0X tofFront;
Adafruit_VL53L0X tofLeft;
Adafruit_VL53L0X tofRight;
Adafruit_VL53L0X tofBack;

float distFront, distLeft, distRight, distBack; 
ToFFilter filterFront, filterLeft, filterRight, filterBack; 
void  change(){
  pinMode(XSHUT_FRONT,OUTPUT); digitalWrite(XSHUT_FRONT,LOW);
  pinMode(XSHUT_LEFT,OUTPUT); digitalWrite(XSHUT_LEFT,LOW);
  pinMode(XSHUT_RIGHT,OUTPUT); digitalWrite(XSHUT_RIGHT,LOW);
  pinMode(XSHUT_BACK,OUTPUT); digitalWrite(XSHUT_BACK,LOW);
  delay(5);
  digitalWrite(XSHUT_FRONT,HIGH);delay(5);
  tofFront.begin();

  digitalWrite(XSHUT_LEFT,HIGH);delay(5);
  tofLeft.begin();

  digitalWrite(XSHUT_RIGHT,HIGH);delay(5);
  tofRight.begin();

  digitalWrite(XSHUT_BACK,HIGH);delay(5);
  tofBack.begin();

  
  filterFront.setOffset(10);
  filterFront.setRangeLimits(15, 2000);
  filterFront.setAlpha(true, 0.05f, 0.8f);
  filterFront.setDeadband(true, 2);

  filterLeft.setOffset(10);
  filterLeft.setRangeLimits(15, 2000);
  filterLeft.setAlpha(true, 0.05f, 0.8f);
  filterLeft.setDeadband(true, 2);

  filterRight.setOffset(10);
  filterRight.setRangeLimits(15, 2000);
  filterRight.setAlpha(true, 0.05f, 0.8f);
  filterRight.setDeadband(true, 2);

  filterBack.setOffset(10);
  filterBack.setRangeLimits(15, 2000);
  filterBack.setAlpha(true, 0.05f, 0.8f);
  filterBack.setDeadband(true, 2);
}
void readTOF(){
  VL53L0X_RangingMeasurementData_t measure;

  tofFront.rangingTest(&measure, false);
  distFront = filterFront.filter(measure.RangeMilliMeter) * 100;

  tofLeft.rangingTest(&measure, false);
  distLeft = filterLeft.filter(measure.RangeMilliMeter) * 100;

  tofRight.rangingTest(&measure, false);
  distRight = filterRight.filter(measure.RangeMilliMeter) * 100;

  tofBack.rangingTest(&measure, false);
  distBack = filterBack.filter(measure.RangeMilliMeter) * 100;
}