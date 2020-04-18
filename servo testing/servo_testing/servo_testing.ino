#include <Math.h>
#include <Adafruit_PWMServoDriver.h>

#include "Leg.h"
#include "MyServo.h"
#include "ServoUtils.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

  // ride height:      60
  //shoulder distance: 42
  // Elbow distance:   36
  // Wrist distance:   54

MyServo shoulder = MyServo(0, 90, false, 0, &pwm, 500, 2600);
MyServo elbow = MyServo(1, 90, true, 45, &pwm, 500, 2600);
MyServo wrist = MyServo(2, 90, false, 45, &pwm, 500, 2600);
//MyServo testServo = MyServo(4, 90, 0, false, &pwm, 500, 2600);

Leg myLeg = Leg(&shoulder, &elbow, &wrist, 42, 36, 54);

#define SERVO_FREQ 60 // Analog servos run at ~60 Hz updates

int servoPos = 45;
//float pi = 3.1415;
bool hasWritten;

unsigned long start;
long life = 0;
int oldPos;

bool controlWholeLeg = true;

void setup() {

  Serial.begin(9600);
  Serial.println("Testing values!");

Serial.println(109);
  myLeg.DetermineDistance(109, true);
  
  Serial.println(100);
  myLeg.DetermineDistance(100, true);
  
  Serial.println(82);
  myLeg.DetermineDistance(82, true);
  
  Serial.println(55);
  myLeg.DetermineDistance(55, true);  
  
  Serial.println(32);
  myLeg.DetermineDistance(32, true);


  pwm.begin();  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~60 Hz updates

//  testServo.setPosition(90);
  delay(1500);
  
  start = millis();
  
  shoulder.setServoPosition(90, start, 1000);
  elbow.setServoPosition(90, start, 500);
  wrist.setServoPosition(90, start, 500);

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
//  if(millis() % 25 == 0){
    updateMotors();
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

  if(Serial.available()){
    parseSerial(Serial.readString());
  }
      //updateMotors();

}

void delayUntil(long endTime){
  while(millis() < endTime){
    updateMotors();

    delay(100);
  }
}

void updateMotors(){
  if(controlWholeLeg){
    myLeg.updateLegDistance();
  }
  else
  {
    shoulder.updateServoPositionSin();
    elbow.updateServoPositionSin();
    wrist.updateServoPositionSin();
  }
//  testServo.updateServoPositionSin();
}

void parseSerial(String input){
  String sPosition = getValue(input, ':', 1);
  String lTime = getValue(input, ':', 2);
  String servoIdx = getValue(input, ':', 0);

  int parsedPosition = 0;

  if(lTime.length() == 0)
    {
      //myLeg.DetermineDistance(servoIdx.toInt());
      myLeg.setLegDistance(servoIdx.toInt(), millis(), 1000);
      Serial.print("Setting distance to :");Serial.println(servoIdx);
    }
    else{
          
        
      if(sPosition.startsWith("-")){
        String subPosition = sPosition.substring(1);
        
        parsedPosition = 0-(subPosition.toInt());
        Serial.print("Parsed position: ");Serial.println(parsedPosition);
      }
      else{
        parsedPosition = sPosition.toInt();
      }
    
      switch(servoIdx.toInt()){
        case 1:
          shoulder.setServoPosition(parsedPosition, millis(), lTime.toInt()); 
          break;
        case 2:
          elbow.setServoPosition(parsedPosition, millis(), lTime.toInt()); 
          break;
        case 3:
          wrist.setServoPosition(parsedPosition, millis(), lTime.toInt()); 
          break;
//        case 4:
//          testServo.setServoPosition(parsedPosition, millis(), lTime.toInt());  
//          break;
      }
    
    
      Serial.print(shoulder.myPosition);Serial.print(" ");
      Serial.print(elbow.myPosition);Serial.print(" ");
      Serial.print(wrist.myPosition);Serial.println(" ");
    }
}


inline double to_degrees(double radians) {
    return radians * (180.0 / pi);
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
