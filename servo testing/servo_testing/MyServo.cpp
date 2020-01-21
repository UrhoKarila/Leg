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

MyServo::MyServo(int Index, int Position, bool IsInverted, int Offset, Adafruit_PWMServoDriver *Driver, int LowMicro, int HighMicro){
    myIndex = Index;
    myPosition = Position;
    myDriver = Driver;
    isInverted = IsInverted;
    myOffset = Offset;
    myLowMicro = LowMicro;
    myHighMicro = HighMicro;
}

 void MyServo::setPosition(int angle){
   myDriver->writeMicroseconds(myIndex, getMicrosecondFromAngle(angle));
 }

 void MyServo::setServoPosition(int newPos, long startTime, int endTime){
  
   myOldPosition = myPosition;
   moveStartTime = startTime;
   moveLifeTime = endTime;
   if(isInverted){
    myPosition = constrain(180-newPos-myOffset, 0, 180);
  }
  else{myPosition = constrain(newPos+myOffset,0,180);}
//       Serial.print("Target angle: ");
//    Serial.println(newPos);
 }

 void MyServo::updateServoPositionLinear(){
   setPosition(getServoPositionLinear(moveStartTime, moveLifeTime, myPosition, myOldPosition));
 }

 void MyServo::updateServoPositionSin(){
     setPosition(getServoPositionSin(moveStartTime, moveLifeTime, myPosition, myOldPosition));
 }

 int MyServo::getMicrosecondFromAngle(int angle){
  return (map(angle, 0, 180, myLowMicro, myHighMicro));
}
