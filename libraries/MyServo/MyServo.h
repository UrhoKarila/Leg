#ifndef _MyServo_H
#define _MyServo_H

#include <Arduino.h>

#include <Adafruit_PWMServoDriver.h>

class MyServo {
    public:
        MyServo();
        MyServo(int Index);
        MyServo(int Index, int Position, Adafruit_PWMServoDriver *Driver);

        //int myIndex;
         int myPosition;
        int myOldPosition;
        unsigned long moveStartTime;
        unsigned int moveLifeTime;

        Adafruit_PWMServoDriver *myDriver;

        void updateServoPositionLinear();
        void updateServoPositionSin();
    private:
        int myIndex;
};

#endif