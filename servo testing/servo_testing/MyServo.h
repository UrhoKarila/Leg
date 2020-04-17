#ifndef _MyServo_H
#define _MyServo_H

#include <Arduino.h>
#include <Math.h>

#include <Adafruit_PWMServoDriver.h>

#include "ServoUtils.h"


class MyServo {
    public:
        MyServo(int Index, int Position, bool IsInverted, int Offset, Adafruit_PWMServoDriver *Driver, int LowMicro, int HighMicro);

        //int myIndex;
         bool isInverted;
         int myOffset;
         int myPosition;
         int myOldPosition;
         int myLowMicro;
         int myHighMicro;
         unsigned long moveStartTime;
         unsigned int moveLifeTime;

         Adafruit_PWMServoDriver *myDriver;

        void setRadianServoPosition(double newPos, long startTime, int endTime);

         void setServoPosition(int newPos, long startTime, int endTime);
         void setPosition(int angle);
         void updateServoPositionLinear();
         void updateServoPositionSin();

         int getMicrosecondFromAngle(int angle);

     private:
        int myIndex;
};

#endif
