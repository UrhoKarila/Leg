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

    myXTarget = 20;
    myYTarget = 20;

    myOldXTarget = 20;
    myOldYTarget = 20;

    moveStartTime = 0;
    moveLifeTime = 0;
}


void Leg::SetPolarPosition(int angle, int distance, bool isTest = false)
{
  angle += 45;
  hip->setPosition(angle);
  DetermineDistance(distance);
}

void Leg::SetCartesianPosition(int xPos, int yPos, bool isTest = false)
{
  float hypotenuse = sqrt(sq(xPos) + sq(yPos));
  float angle = atan2(yPos, xPos);

  if(isTest)
  {
    Serial.print("distance: ");Serial.println(hypotenuse);
    Serial.print("angle (degrees): ");Serial.println(toDegrees(angle));
  }
  else
  {
      SetPolarPosition(toDegrees(angle), hypotenuse);
  
  }
}

void Leg::SetCartesianTarget(int newX, int newY, long startTime, int endTime)
{
  myOldXTarget = myXTarget;
  myOldYTarget = myYTarget;

  moveStartTime = startTime;
  moveLifeTime = endTime;

  myXTarget = newX;
  myYTarget = newY;
}

void Leg::UpdateCartesianMove(){
//  Serial.println("UpdateCartesianMove");
    int xPos = interpolatePositionLinear(moveStartTime, moveLifeTime, myXTarget, myOldXTarget);
    int yPos = interpolatePositionLinear(moveStartTime, moveLifeTime, myYTarget, myOldYTarget);
//  Serial.print("xPos: ");Serial.println(xPos);
//  Serial.print("yPos: ");Serial.println(yPos);

    SetCartesianPosition(xPos, yPos);
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
  int ratio = interpolatePositionLinear(moveStartTime, moveLifeTime, myPosition, myOldPosition); 
    DetermineDistance(ratio, false);
  
  //hip->updateServoPositionLinear();
  //knee->updateServoPositionLinear();
  //ankle->updateServoPositionLinear();
}

//Seems to be acting up
// Add debug mode to help determine if correct commands are making their way to the servos
void Leg::DetermineDistance(int distance, bool isTest = false) //distance in mm
{
  // ride height:      60
  //shoulder distance: 42
  // Elbow distance:   36
  // Wrist distance:   54
  int rideHeight = 60;
//  int thigh = 42;
//  int shin = 36;
//  int jambe = 54;
  int maxDistance = acos(rideHeight/(shinLength+footLength));
  distance = constrain(distance, 0, maxDistance);
  
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
//  if(elbowWristAngleDegrees < 0){
//    elbowWristAngleDegrees *= -1;
//  }

  if(isTest)
  {
    Serial.println("Targeted distance is: ");Serial.println(distance);
    Serial.print("knee, set to 2: ");Serial.println(toDegrees(elbowAngle));
    Serial.print("ankle, set to 3: ");Serial.println(elbowWristAngleDegrees);
  }
  
  knee->setPosition(toDegrees(elbowAngle));
  ankle->setPosition(elbowWristAngleDegrees);
}
