#ifndef _Leg_H
#define _Leg_H

#include <Arduino.h>
#include <Math.h>

#include "ServoUtils.h"
#include "MyServo.h"

class Leg {
    public:
        Leg(MyServo *hipServo, MyServo *kneeServo, MyServo *ankleServo, int thigh, int shin, int foot);

        void DetermineDistance(int distance, bool isTest = false);

        void SetPolarPosition(int angle, int distance, bool isTest = false);
        void SetCartesianPosition(int xPos, int yPos, bool isTest = false);

        void SetCartesianTarget(int newX, int newY, long startTime, int endTime);
        void UpdateCartesianMove();
        
        void setLegDistance(int newPos, long startTime, int endTime);
        void updateLegDistance();


        MyServo* hip;
        MyServo* knee;
        MyServo* ankle;

        int thighLength;
        int shinLength;
        int footLength;

        int myPosition;
        int myOldPosition;
    
        int myXTarget;
        int myYTarget;
    
        int myOldXTarget;
        int myOldYTarget;
        
        unsigned long moveStartTime;
        unsigned int moveLifeTime;
        
        //int myIndex;
//         bool isInverted;
//         int myOffset;
//         int myPosition;
//         int myOldPosition;
//         int myLowMicro;
//         int myHighMicro;
//         unsigned long moveStartTime;
//         unsigned int moveLifeTime;
//
//         Adafruit_PWMServoDriver *myDriver;
//
//         void setServoPosition(int newPos, long startTime, int endTime);
//         void setPosition(int angle);
//         void updateServoPositionLinear();
//         void updateServoPositionSin();
//
//         int getMicrosecondFromAngle(int angle);

     private:
//        int myIndex;
};

#endif
