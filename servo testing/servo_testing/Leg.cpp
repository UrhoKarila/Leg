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
//  Serial.print("Hypotenuse: ");Serial.println(hypotenuse);

  //Determine elbow/wrist angle
  double elbowWristAngle = acos((sq(shinLength)+sq(footLength)-sq(hypotenuse))/(2*shinLength*footLength));
  //Serial.print("Elbow/Wrist Angle: ");Serial.println(toDegrees(elbowWristAngle));

  //Determine Elbow angle
  //Find topmost angle
  double elbowAngleOffset = acos((float)rideHeight/hypotenuse);
   if(elbowDistance < 0){
    Serial.println("Should be reflected");
    elbowAngleOffset *= -1;
  }
//  Serial.print("naive elbowangleoffset: ");Serial.println(elbowAngleOffset);
//  Serial.print("LoC EAO: ");

  //Find native angle
  double elbowAngle = acos((sq(shinLength)+sq(hypotenuse)-sq(footLength))/(shinLength*2*hypotenuse));


//  Serial.print("Native elbow angle: ");Serial.println(toDegrees(elbowAngle));
  elbowAngle += elbowAngleOffset;
//  Serial.print("Elbow angle offset: ");Serial.println(toDegrees(elbowAngleOffset));
  //int totalElbowAngle = toDegrees(elbowAngle) + 90;
//  Serial.print("Total elbow angle: ");Serial.println(totalElbowAngle);
//
//  Serial.println();
//
//  Serial.print("Angles to enter:");
  Serial.print("2: ");Serial.println(toDegrees(elbowAngle));
//  Serial.print("2: ");Serial.println(totalElbowAngle-90);
  //Serial.print("Raw EAW: ");Serial.println(toDegrees(elbowWristAngle));
  //Serial.print("3: ");Serial.println(toDegrees(elbowWristAngle)-90);
  

  //ankle->setPosition(toDegrees(elbowWristAngle)-90);
  //knee->setPosition(toDegrees(totalElbowAngle)-90);
}
