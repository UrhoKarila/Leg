//#include <Servo.h>
//#include <Math.h>
//#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include "MyServo.h"

// int myIndex;
// int myPosition;
// int myOldPosition;
// unsigned long moveStartTime;
// unsigned int moveLifeTime;

// Adafruit_PWMServoDriver* myDriver;

MyServo::MyServo(){
    myIndex = 4;
    myPosition = 90;
}

MyServo::MyServo(int Index){
    myIndex = Index;
}

MyServo::MyServo(int Index, int Position, Adafruit_PWMServoDriver *Driver){
    myIndex = Index;
    myPosition = Position;
    *myDriver = Driver;
}

void MyServo::setPosition(int servoNum, int angle){
  &myDriver.writeMicroseconds(servoNum, getMicrosecondFromAngle(angle));
}

void MyServo::setServoPos(int newPos, long startTime, int endTime){
  oldPos = servoPos;
  start = startTime;
  life = endTime;
  servoPos = newPos;
}

void MyServo::updateServoPosLinear(int servoNum){
  setPosition(servoNum, getServoPositionLinear(start, life, servoPos, oldPos));
}

void MyServo::updateServoPosSin(int servoNum){
    setPosition(servoNum, getServoPositionSin(start, life, servoPos, oldPos));
}