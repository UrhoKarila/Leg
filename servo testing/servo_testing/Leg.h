#ifndef _Leg_H
#define _Leg_H

#include <Arduino.h>
#include <Math.h>

#include "ServoUtils.h"
#include "MyServo.h"

class Leg {
    public:
        Leg(MyServo *hipServo, MyServo *kneeServo, MyServo *ankleServo, int thigh, int shin, int foot);

        void DetermineDistance(int distance, int zOffset = 0, bool isTest = false);

        void SetRideHeight(int newHeight);
 
        void SetPolarPosition(int angle, int distance, int zOffset = 0, bool isTest = false);
        void SetCartesianPosition(int xPos, int yPos, int zOffset = 0, bool isTest = false);

        void SetCartesianTarget(int newX, int newY, long startTime, int endTime, bool isStep);
        void UpdateCartesianMove();
        
        void SetLegDistance(int newPos, long startTime, int endTime);
        void UpdateLegDistance();


        MyServo* hip;
        MyServo* knee;
        MyServo* ankle;

        int thighLength;
        int shinLength;
        int footLength;

        int rideHeight;

        int myPosition;
        int myOldPosition;
    
        int myXTarget;
        int myYTarget;
    
        int myOldXTarget;
        int myOldYTarget;
        
        unsigned long moveStartTime;
        unsigned int moveLifeTime;

        bool isStepping;
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
