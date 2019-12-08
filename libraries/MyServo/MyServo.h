#ifndef _MyServo_H
#define _MyServo_H

#include <Servo.h>
#include <Math.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class MyServo{
    public:
        int myIndex;
        int myPosition;
        int myOldPosition;
        unsigned long moveStartTime;
        unsigned int moveLifeTime;

        Adafruit_PWMServoDriver* myDriver;

        void updateServoPositionLinear();
        void updateServoPositionSin();
};

#endif