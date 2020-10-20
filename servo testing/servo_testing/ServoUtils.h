#ifndef SERVO_UTILS_H
#define SERVO_UTILS_H

#include <Arduino.h>

    //void setPosition(int servoNum, int angle);

    const float pi = 3.14159;

    int sinusoidalArc(unsigned long startTime, int lifeTime, int maxDeflection);

    int interpolatePosition(unsigned long startTime, int lifeTime);

    int interpolatePositionLinear(unsigned long startTime, int lifeTime, int oldPosition, int newPosition);
    int interpolatePositionSin(unsigned long startTime, int lifeTime, int oldPosition, int newPosition); 
    double toDegrees(double rads);

#endif
