#include <Arduino.h>
#include "TOF.h"
#include "colour_sensor.h"
#include "PID_40cm.h"
#include "blue.h"
#include "navigation.h"
#include "black.h"
#include "dfs.h"

#define MOTOR_LEFT_FWD  13//motor pins
#define MOTOR_LEFT_BWD  21//motor pins
#define MOTOR_RIGHT_FWD 24//motor pins
#define MOTOR_RIGHT_BWD 17//motor pins
#define BASE_SPEED      150

float currentTarget = 40.0;

void setMotors(int leftSpeed, int rightSpeed) {
  leftSpeed  = constrain(leftSpeed,  -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);
  if (leftSpeed  >= 0) { analogWrite(MOTOR_LEFT_FWD, leftSpeed);   analogWrite(MOTOR_LEFT_BWD,  0);           }
  else                 { analogWrite(MOTOR_LEFT_FWD, 0);           analogWrite(MOTOR_LEFT_BWD,  -leftSpeed);  }
  if (rightSpeed >= 0) { analogWrite(MOTOR_RIGHT_FWD, rightSpeed); analogWrite(MOTOR_RIGHT_BWD, 0);           }
  else                 { analogWrite(MOTOR_RIGHT_FWD, 0);          analogWrite(MOTOR_RIGHT_BWD, -rightSpeed); }
}

void stopMotors() {
  analogWrite(MOTOR_LEFT_FWD,  0); analogWrite(MOTOR_LEFT_BWD,  0);
  analogWrite(MOTOR_RIGHT_FWD, 0); analogWrite(MOTOR_RIGHT_BWD, 0);
}

void setup() {
  Serial.begin(115200);
  Wire.setClock(400000);
  pinMode(MOTOR_LEFT_FWD,  OUTPUT);
  pinMode(MOTOR_LEFT_BWD,  OUTPUT);
  pinMode(MOTOR_RIGHT_FWD, OUTPUT);
  pinMode(MOTOR_RIGHT_BWD, OUTPUT);
  change();
  iniitDfs();
  setupGyro();
  setupp();
  setuppp();
  holdlasttime = micros();
  lasttime     = micros();
}

void loop() {
  
  readTOF();
  onbluee(); 
  onblackk();

  if(onblack){
    backwards();
    delay(300);
    stopMotors();
    if(stackTop >= 0) stackTop--;
    turnAround();
    while(!turnUpdate());
  }
  if (onblue) {
    stopMotors();
    return;
  }

  if (!moving) {
    CalcMove();

    if (distFront >= 30) {
      currentTarget = 30.0;
      iniit();      
      moving = true;
    }


  } else {
    loopp(); 

    float remaining = currentTarget - d;

    
    if (distFront < (remaining + 6.0)) {

      if (distFront > 6.5) {
        
        setMotors(BASE_SPEED / 2, BASE_SPEED / 2);

      } else {
        
        stopMotors();
        moving = false;

        float finalRemaining = currentTarget - d;

        if (distLeft > 20) {
          turnLeft();
        } else if (distRight > 20) {
          turnRight();
        } else {
          turnAround();
        }

       
        if (finalRemaining > 1.5) {
          currentTarget = finalRemaining;
          iniit();
          moving = true;
        }
      }

    } else {

      bool leftWall  = distLeft  < WALL_THRESHOLD;
bool rightWall = distRight < WALL_THRESHOLD;

if(leftWall && rightWall){
    setMotors(BASE_SPEED + correction1, BASE_SPEED - correction1);
} else if(leftWall){
    setMotors(BASE_SPEED + correction1, BASE_SPEED - correction1);
} else if(rightWall){
    setMotors(BASE_SPEED + correction2, BASE_SPEED - correction2);
} else {
    setMotors(BASE_SPEED + encoderCorrection, BASE_SPEED - encoderCorrection);
}
    }
  }
}