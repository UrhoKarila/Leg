#include <Servo.h>
#include <Math.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

int myIndex;
int myPosition;
int myOldPosition;
unsigned long moveStartTime;
unsigned int moveLifeTime;

Adafruit_PWMServoDriver* myDriver;

void MyServo(int Index, int Position, Adafruit_PWMServoDriver* Driver){
    myIndex = Index;
    myPosition = Position;
    myDriver = Driver;
}

void updateServoPositionLinear();
void updateServoPositionSin();