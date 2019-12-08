#include "SBUS.h"
#include <Servo.h>

// a SBUS object, which is on hardware
// serial port 1
SBUS xmp(Serial);

// channel, fail safe, and lost frames data
float channels[16];
bool failSafe;
bool lostFrame;

Servo servo;
int servoPos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Hello world!");
  xmp.begin();
  servo.attach(9);

  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH);
  servo.write(45);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW); 
  servo.write(0);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
    // look for a good SBUS packet from the receiver
  if(xmp.readCal(&channels[0], &failSafe, &lostFrame)){
    //servo.write(channels[0]);
    setServo(channels[0]);

    digitalWrite(LED_BUILTIN, HIGH);
    //servo.writeMicroseconds(*(channels+0));
  }
  else{
    digitalWrite(LED_BUILTIN, LOW); 
  }
  //Serial.println("looped");
}

void setServo(float pos){
    Serial.println(pos);

  servo.write(90+(90*pos));
}
