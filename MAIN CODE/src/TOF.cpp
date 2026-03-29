#include <Arduino.h>
#include "TOF.h"
Adafruit_VL53L0X tofFront;
Adafruit_VL53L0X tofLeft;
Adafruit_VL53L0X tofRight;
Adafruit_VL53L0X tofBack;

float distFront, distLeft, distRight, distBack; 
ToFFilter filterFront, filterLeft, filterRight, filterBack; 
void tcaSelect(uint8_t channel) {
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}
void  change(){
  tcaSelect(CH_TOF_FRONT); tofFront.begin();
  tcaSelect(CH_TOF_LEFT);  tofLeft.begin();
  tcaSelect(CH_TOF_RIGHT); tofRight.begin();
  tcaSelect(CH_TOF_BACK);  tofBack.begin();


  
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

  tcaSelect(CH_TOF_FRONT);
  tofFront.rangingTest(&measure, false);
  distFront = filterFront.filter(measure.RangeMilliMeter) * 100;

  tcaSelect(CH_TOF_LEFT);
  tofLeft.rangingTest(&measure, false);
  distLeft = filterLeft.filter(measure.RangeMilliMeter) * 100;

  tcaSelect(CH_TOF_RIGHT);
  tofRight.rangingTest(&measure, false);
  distRight = filterRight.filter(measure.RangeMilliMeter) * 100;

  tcaSelect(CH_TOF_BACK);
  tofBack.rangingTest(&measure, false);
  distBack = filterBack.filter(measure.RangeMilliMeter) * 100;

}