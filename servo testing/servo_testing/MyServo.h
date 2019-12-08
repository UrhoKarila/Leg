#ifndef _MyServo_H
#define _MyServo_H

#include <Arduino.h>
#include <Math.h>

#include <Adafruit_PWMServoDriver.h>


class MyServo {
    public:
        MyServo(int Index, int Position, Adafruit_PWMServoDriver *Driver);

        //int myIndex;
         int myPosition;
         int myOldPosition;
         unsigned long moveStartTime;
         unsigned int moveLifeTime;

         Adafruit_PWMServoDriver *myDriver;

         void setServoPosition(int newPos, long startTime, int endTime);
         void setPosition(int angle);
         void updateServoPositionLinear();
         void updateServoPositionSin();
     private:
        int myIndex;
};

#endif
