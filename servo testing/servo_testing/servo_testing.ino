#include <Servo.h>
#include <Math.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
//#include "C:\Users\Grant\Documents\Leg\libraries\MyServo\MyServo.h"
//#include "ServoUtilsRedirect.h"
#include "ServoUtils.h"


//ServoUtils util = ServoUtils();

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
#define SERVO_FREQ 60 // Analog servos run at ~60 Hz updates

//Servo servo;
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

  
  // put your setup code here, to run once:
  //servo.attach(9);

  //servo.write(135);
  //delay(500);
  //digitalWrite(LED_BUILTIN, LOW); 
  //servo.write(45);
  //delay(500);

  //servo.write(90);
  //writeMicroseconds(uint8_t num, uint16_t Microseconds);
  pwm.writeMicroseconds(4, 1500);
  delay(1000);
  Serial.print("wrote 1!");

  //pwm.writeMicroseconds(4, 1600);
  //delay(1500);
  //Serial.print("wrote 2!");
  //pwm.writeMicroseconds(4, 1400);
  //delay(1500);
  //Serial.print("wrote 3!");
  //pwm.writeMicroseconds(4, 1700);
  //delay(1500);
  //Serial.print("wrote 4!");
  //pwm.writeMicroseconds(4, 1300);
  //delay(1500);
  //Serial.print("wrote 5!");
  //servoPos = 30;
      pwm.writeMicroseconds(4, 620);
      delay(3000);


  for(int i = 620; i < 2500; i+=10){
      pwm.writeMicroseconds(4, i);
      Serial.println(i);
      delay(5);
  }      
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() % 2000 == 0){
    if(!hasWritten){
      //Serial.println(millis());
      //servoPos = (servoPos+15) % 180;

      //setServoPos(((servoPos+30) % 180), millis(), 2000);
      
      //Serial.println(servoPos);
      hasWritten = true;
    }
    
  }
  else{
    hasWritten = false;
  }

  updateServoPosLinear(4);

  if(Serial.available()){
    parseSerial(Serial.readString());
  }
  
}

void parseSerial(String input){
  String sPosition = getValue(input, ':', 0);
  String lTime = getValue(input, ':', 1);

  Serial.println("Y:" + lTime);
  Serial.print("X:" + sPosition);

  setServoPos(sPosition.toInt(), millis(), lTime.toInt());
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

void setServoPos(int newPos, long startTime, int endTime){
  oldPos = servoPos;
  start = startTime;
  life = endTime;
  servoPos = newPos;

  //Serial.println(oldPos);Serial.println(start); 
  //Serial.println(life); //Serial.println(servoPos);
}

void updateServoPosLinear(int servoNum){
  
  int ratioThru = interpolatePosition(start, life);

  setPosition(servoNum, (oldPos + (int)(ratioThru * (servoPos - oldPos)) / 100));

  //servo.write(oldPos + (int)((ratioThru * (servoPos - oldPos)) / 100));

}

void updateServoPosSin(int servoNum){
  int ratioThru =0; //0interpolatePosition(start, life);

  float mappedRatio = (map(ratioThru, 0, 100, -157, 157))/100.0;

  float test = (sin(mappedRatio) + 1)/2.0;
    
  setPosition(servoNum, oldPos + (int)(((sin(mappedRatio) + 1)/2.0) * (servoPos - oldPos)));


  //Serial.print("relative position: "); Serial.println(relativePosition);
  //Serial.println((oldPos + (int)(relativePosition * (servoPos - oldPos))));
}
