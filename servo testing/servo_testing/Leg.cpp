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

    isStepping = false;
}


void Leg::SetPolarPosition(int angle, int distance, int zOffset = 0, bool isTest = false)
{
  angle += 45;
  hip->SetPosition(angle);
  DetermineDistance(distance, zOffset);
}

void Leg::SetCartesianPosition(int xPos, int yPos, int zOffset = 0, bool isTest = false)
{
  float hypotenuse = sqrt(sq(xPos) + sq(yPos));
  float angle = atan2(yPos, xPos);

  
  if(isTest)
  {
    Serial.print("distance: ");Serial.println(hypotenuse);
    Serial.print("angle (degrees): ");Serial.println(toDegrees(angle));
    Serial.print("zOffset: ");Serial.println(zOffset);
  }
  else
  {
      SetPolarPosition(toDegrees(angle), hypotenuse, zOffset);
  
  }
}

void Leg::SetCartesianTarget(int newX, int newY, long startTime, int endTime, bool isStep = false)
{
  myOldXTarget = myXTarget;
  myOldYTarget = myYTarget;

  moveStartTime = startTime;
  moveLifeTime = endTime;

  myXTarget = newX;
  myYTarget = newY;

  isStepping = isStep;
}

void Leg::SetRideHeight(int newHeight){
  rideHeight = newHeight;
}

void Leg::UpdateCartesianMove(){
//  Serial.println("UpdateCartesianMove");
    int xPos = interpolatePositionLinear(moveStartTime, moveLifeTime, myXTarget, myOldXTarget);
    int yPos = interpolatePositionLinear(moveStartTime, moveLifeTime, myYTarget, myOldYTarget);


  int zOffset = 0;
  if(isStepping)
  {
    zOffset = sinusoidalArc(moveStartTime, moveLifeTime, 20);
  }
    
//  Serial.print("xPos: ");Serial.println(xPos);
//  Serial.print("yPos: ");Serial.println(yPos);

    SetCartesianPosition(xPos, yPos, zOffset);
}
        
void Leg::SetLegDistance(int newPos, long startTime, int endTime){
   if(myOldPosition != myPosition){
       Serial.println(myPosition);
   }
   myOldPosition = myPosition;
   moveStartTime = startTime;
   moveLifeTime = endTime;
   myPosition = newPos;

}

void Leg::UpdateLegDistance(){
  int ratio = interpolatePositionLinear(moveStartTime, moveLifeTime, myPosition, myOldPosition); 
    DetermineDistance(ratio, false);
}

//Seems to be acting up
// Add debug mode to help determine if correct commands are making their way to the servos
void Leg::DetermineDistance(int distance, int zOffset = 0, bool isTest = false) //distance in mm
{
  // ride height:      60
  //shoulder distance: 42
  // Elbow distance:   36
  // Wrist distance:   54
  int stepHeight = 60 - zOffset;
//  int thigh = 42;
//  int shin = 36;
//  int jambe = 54;
  int maxDistance = sqrt(sq(shinLength+footLength)-sq(stepHeight))+thighLength;
  
  distance = constrain(distance, 0, maxDistance);
  
  int elbowDistance = distance - thighLength;

  //Determine EW hypotenuse
  float hypotenuse = sqrt(sq(elbowDistance) + sq(stepHeight));

  //Determine elbow/wrist angle
  double elbowWristAngle = acos((sq(shinLength)+sq(footLength)-sq(hypotenuse))/(2*shinLength*footLength));

  //Determine Elbow angle
  //Find topmost angle
  double elbowAngleOffset = acos((float)stepHeight/hypotenuse);
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
    Serial.print("Max distance is: ");Serial.println(maxDistance);
    Serial.println("Targeted distance is: ");Serial.println(distance);
    Serial.print("knee, set to 2: ");Serial.println(toDegrees(elbowAngle));
    Serial.print("ankle, set to 3: ");Serial.println(elbowWristAngleDegrees);
    Serial.print("zOffset, set to: ");Serial.println(zOffset);
  }
  
  knee->SetPosition(toDegrees(elbowAngle));
  ankle->SetPosition(elbowWristAngleDegrees);
}
