#ifndef SERVO_UTILS_H
#define SERVO_UTILS_H

#include <Arduino.h>

    //void setPosition(int servoNum, int angle);


    int interpolatePosition(unsigned long startTime, int lifeTime);

    int getServoPositionLinear(unsigned long startTime, int lifeTime, int oldPosition, int newPosition);
    int getServoPositionSin(unsigned long startTime, int lifeTime, int oldPosition, int newPosition);

#endif
