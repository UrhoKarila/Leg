#include <Math.h>
#include <Adafruit_PWMServoDriver.h>

#include "MyServo.h"
#include "ServoUtils.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

MyServo shoulder = MyServo(0, 90, false, &pwm);
MyServo elbow = MyServo(1, 90, true, &pwm);
MyServo wrist = MyServo(2, 90, false, &pwm);
MyServo testServo = MyServo(4, 90, false, &pwm);

#define SERVO_FREQ 60 // Analog servos run at ~60 Hz updates

int servoPos = 45;
bool hasWritten;

float pi = 3.1415;

unsigned long start;
long life = 0;
int oldPos;

void setup() {

  Serial.begin(9600);
  Serial.print("Hello world!");
  pwm.begin();  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~60 Hz updates

  testServo.setPosition(90);
  delay(1500);
  
  start = millis();
  
  shoulder.setServoPosition(135, start, 1000);
  elbow.setServoPosition(55, start, 500);
  wrist.setServoPosition(30, start, 500);

  delayUntil(start + 1000);
//
//  testServo.setPosition(60);
//  delay(1500);
//  
//  testServo.setPosition(120);
//  delay(1500);
//
//  testServo.setPosition(90);
//  delay(1500);

//  pwm.writeMicroseconds(4, 1500);
//  delay(1000);
//
//      pwm.writeMicroseconds(4, 620);
//      delay(3000);
//
//
//  for(int i = 620; i < 2500; i+=10){
//      pwm.writeMicroseconds(4, i);
//      Serial.println(i);
//      delay(5);
//  }      
//  delay(500);
  Serial.println("index, position, lifetime");

}

void loop() {
  // put your main code here, to run repeatedly:
//  if(millis() % 2000 == 0){
//    if(!hasWritten){
////        servoPos = (servoPos += 45)%180;
////
////        Serial.print("Target angle: ");
////        Serial.println(servoPos);
////        hasWritten = true;
////        testServo.setServoPosition(servoPos, millis(), 2000);
//
//    }
//    
//  }
//  else{
//    hasWritten = false;
//  }

//  if(Serial.available()){
//    parseSerial(Serial.readString());
//  }
//      updateMotors();


  start = millis();
  
  shoulder.setServoPosition(45, start, 1000);
  elbow.setServoPosition(100, start, 500);
  wrist.setServoPosition(-10, start, 500);

  delayUntil(start + 500);
  
  start = millis();
  elbow.setServoPosition(55, start, 500);
  wrist.setServoPosition(30, start, 500);
  delayUntil(start + 500);
  
  start = millis();
  shoulder.setServoPosition(135, start, 1000);
  delayUntil(start + 1000);

}

void delayUntil(long endTime){
  while(millis() < endTime){
    updateMotors();

    delay(10);
  }
}

void updateMotors(){
  shoulder.updateServoPositionSin();
  elbow.updateServoPositionSin();
  wrist.updateServoPositionSin();
  
}

void parseSerial(String input){
  String sPosition = getValue(input, ':', 1);
  String lTime = getValue(input, ':', 2);
  String servoIdx = getValue(input, ':', 0);

  switch(servoIdx.toInt()){
    case 1:
      shoulder.setServoPosition(sPosition.toInt(), millis(), lTime.toInt()); 
      break;
    case 2:
      elbow.setServoPosition(sPosition.toInt(), millis(), lTime.toInt()); 
      break;
    case 3:
      wrist.setServoPosition(sPosition.toInt(), millis(), lTime.toInt()); 
      break;
    case 4:
      testServo.setServoPosition(sPosition.toInt(), millis(), lTime.toInt());  
      break;
  }


  Serial.print(shoulder.myPosition);Serial.print(" ");
  Serial.print(elbow.myPosition);Serial.print(" ");
  Serial.print(wrist.myPosition);Serial.println(" ");
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
