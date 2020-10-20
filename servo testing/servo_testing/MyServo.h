#ifndef _MyServo_H
#define _MyServo_H

#include <Arduino.h>
#include <Math.h>

#include <Adafruit_PWMServoDriver.h>

#include "ServoUtils.h"


class MyServo {
    public:
        MyServo(int Index, int Position, bool IsInverted, int SoftOffset, int HardOffset, Adafruit_PWMServoDriver *Driver, int LowMicro, int HighMicro);

        //int myIndex;
         bool isInverted;
         //intended for adjustments to neutral position when leg is assembled - if more than a few degrees, consider using HardOffset instead
         int mySoftOffset;
         //intended to account for mounting position, usually something like 45 or 90 degrees
         int myHardOffset;
         int myPosition;
         int myOldPosition;
         int myLowMicro;
         int myHighMicro;
         unsigned long moveStartTime;
         unsigned int moveLifeTime;

         Adafruit_PWMServoDriver *myDriver;

        void SetRadianServoPosition(double newPos, long startTime, int endTime);

         void SetJointPosition(int newPos, long startTime, int endTime);
         void SetServoPosition(int newPos, long startTime, int endTime);
         void SetPosition(int angle);
         void UpdateServoPositionLinear();
         void UpdateServoPositionSin();

         int GetMicrosecondFromAngle(int angle);

     private:
        int myIndex;
};

#endif
