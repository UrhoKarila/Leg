#include "Leg.h"
#include <Math.h>
#include "ServoUtils.h"

//float pi = 3.14159;

Leg::Leg(MyServo *hipServo, MyServo *kneeServo, MyServo *ankleServo, int thigh, int shin, int foot){
    hip = hipServo;
    knee = kneeServo;
    ankle = ankleServo;

    thighLength = thigh;
    shinLength = shin;
    footLength = foot;

    myPosition = 50;
    myOldPosition = 50;

    moveStartTime = 0;
    moveLifeTime = 0;
}
        
void Leg::setLegDistance(int newPos, long startTime, int endTime){
   if(myOldPosition != myPosition){
       Serial.println(myPosition);
   }
   myOldPosition = myPosition;
   moveStartTime = startTime;
   moveLifeTime = endTime;
   myPosition = newPos;

}

void Leg::updateLegDistance(){
  DetermineDistance(interpolatePositionLinear(moveStartTime, moveLifeTime, myPosition, myOldPosition));

//  hip->updateServoPositionLinear();
//  knee->updateServoPositionLinear();
//  ankle->updateServoPositionLinear();
}


void Leg::DetermineDistance(int distance) //distance in mm
{
  // ride height:      60
  //shoulder distance: 42
  // Elbow distance:   36
  // Wrist distance:   54
  int rideHeight = 60;
//  int thigh = 42;
//  int shin = 36;
//  int jambe = 54;

  distance = constrain(distance, 0, 109);
  
  int elbowDistance = distance - thighLength;

  //Determine EW hypotenuse
  float hypotenuse = sqrt(sq(elbowDistance) + sq(rideHeight));

  //Determine elbow/wrist angle
  double elbowWristAngle = acos((sq(shinLength)+sq(footLength)-sq(hypotenuse))/(2*shinLength*footLength));

  //Determine Elbow angle
  //Find topmost angle
  double elbowAngleOffset = acos((float)rideHeight/hypotenuse);
   if(elbowDistance < 0){
    elbowAngleOffset *= -1;
  }
  //Find native angle
  double elbowAngle = acos((sq(shinLength)+sq(hypotenuse)-sq(footLength))/(shinLength*2*hypotenuse));

  elbowAngle += elbowAngleOffset;
  int elbowWristAngleDegrees = (toDegrees(elbowWristAngle)-90);
  if(elbowWristAngleDegrees < 0){
    elbowWristAngleDegrees *= -1;
  }

  Serial.print("2: ");Serial.println(toDegrees(elbowAngle));
  Serial.print("3: ");Serial.println(elbowWristAngleDegrees);
  

//  ankle->setPosition(elbowWristAngleDegrees);
//  knee->setPosition(toDegrees(elbowAngle));
}
