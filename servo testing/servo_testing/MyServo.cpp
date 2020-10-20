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

MyServo::MyServo(int Index, int Position, bool IsInverted, int SoftOffset, int HardOffset, Adafruit_PWMServoDriver *Driver, int LowMicro, int HighMicro){
    myIndex = Index;
    myPosition = Position;
    myDriver = Driver;
    isInverted = IsInverted;
    mySoftOffset = SoftOffset;
    myHardOffset = HardOffset;
    myLowMicro = LowMicro;
    myHighMicro = HighMicro;
}

 void MyServo::SetPosition(int angle){
  //Serial.print("Position set to: ");Serial.println(angle);
     if(isInverted){
    angle = constrain(180-angle-mySoftOffset, 0, 180);
  }
  else{angle = constrain(angle+mySoftOffset,0,180);}
   myDriver->writeMicroseconds(myIndex, GetMicrosecondFromAngle(angle));
 }

void MyServo::SetRadianServoPosition(double newPos, long startTime, int endTime){
  SetPosition(toDegrees(newPos));
}

void MyServo::SetJointPosition(int newPos, long startTime, int endTime){
  
}

 void MyServo::SetServoPosition(int newPos, long startTime, int endTime){
  
   myOldPosition = myPosition;
   moveStartTime = startTime;
   moveLifeTime = endTime;
   if(isInverted){
    myPosition = constrain(180-newPos-mySoftOffset, 0, 180);
  }
  else{myPosition = constrain(newPos+mySoftOffset,0,180);}
//       Serial.print("Target angle: ");
//    Serial.println(newPos);
 }

 void MyServo::UpdateServoPositionLinear(){
   SetPosition(interpolatePositionLinear(moveStartTime, moveLifeTime, myPosition, myOldPosition));
 }

 void MyServo::UpdateServoPositionSin(){
     SetPosition(interpolatePositionSin(moveStartTime, moveLifeTime, myPosition, myOldPosition));
 }

 int MyServo::GetMicrosecondFromAngle(int angle){
  return (map(angle, 0, 180, myLowMicro, myHighMicro));
}
