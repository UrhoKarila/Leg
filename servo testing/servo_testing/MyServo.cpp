#include <Arduino.h>
#include <Math.h>

#include <Adafruit_PWMServoDriver.h>

#include "ServoUtils.h"
#include "MyServo.h"


// int myIndex;
// int myPosition;
// int myOldPosition;
// unsigned long moveStartTime;
// unsigned int moveLifeTime;

// Adafruit_PWMServoDriver* myDriver;

MyServo::MyServo(int Index, int Position, Adafruit_PWMServoDriver *Driver){
    myIndex = Index;
    myPosition = Position;
    myDriver = Driver;
}

 void MyServo::setPosition(int angle){
   myDriver->writeMicroseconds(myIndex, getMicrosecondFromAngle(angle));
 }

 void MyServo::setServoPosition(int newPos, long startTime, int endTime){
   myOldPosition = myPosition;
   moveStartTime = startTime;
   moveLifeTime = endTime;
   myPosition = newPos;
 }

 void MyServo::updateServoPositionLinear(){
   setPosition(getServoPositionLinear(moveStartTime, moveLifeTime, myPosition, myOldPosition));
 }

 void MyServo::updateServoPositionSin(){
     setPosition(getServoPositionSin(moveStartTime, moveLifeTime, myPosition, myOldPosition));
 }
