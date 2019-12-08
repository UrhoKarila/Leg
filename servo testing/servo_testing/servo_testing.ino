#include <Math.h>
#include <Adafruit_PWMServoDriver.h>

#include "MyServo.h"
#include "ServoUtils.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
MyServo testServo = MyServo(4, 90, &pwm);

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

  testServo.setPosition(60);
  delay(1500);
  
  testServo.setPosition(120);
  delay(1500);

  testServo.setPosition(90);
  delay(1500);

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

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() % 2000 == 0){
    if(!hasWritten){
      hasWritten = true;
        //testServo.setServoPosition(servoPos, millis(), 2000);

    }
    servoPos += 45;
  }
  else{
    hasWritten = false;
  }

  testServo.updateServoPositionLinear();

//  if(Serial.available()){
//    parseSerial(Serial.readString());
//  }
  
}

void parseSerial(String input){
  String sPosition = getValue(input, ':', 0);
  String lTime = getValue(input, ':', 1);

  Serial.println("Y:" + lTime);
  Serial.print("X:" + sPosition);

  testServo.setServoPosition(sPosition.toInt(), millis(), lTime.toInt());
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
