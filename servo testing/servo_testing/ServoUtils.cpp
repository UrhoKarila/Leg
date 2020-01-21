#include "ServoUtils.h"

#include <Math.h>




int interpolatePosition(unsigned long startTime, int lifeTime){
  //int ratioThru;
  //int timeThru = (100*(millis() - startTime));

  return constrain(((100*(millis() - startTime) / (lifeTime))), 0, 100);
}

int getServoPositionLinear(unsigned long startTime, int lifeTime, int newPosition, int oldPosition){
  
  int ratioThru = interpolatePosition(startTime, lifeTime);
//
//  if(millis() %250 == 0){
//    Serial.println(ratioThru);
//  }
  
  return(oldPosition + (int)(ratioThru * (newPosition - oldPosition)) / 100);

  //servo.write(oldPos + (int)((ratioThru * (servoPos - oldPos)) / 100));

}

int getServoPositionSin(unsigned long startTime, int lifeTime, int newPosition, int oldPosition){
  int ratioThru = interpolatePosition(startTime, lifeTime);

  float mappedRatio = (map(ratioThru, 0, 100, -157, 157))/100.0;

  float test = (sin(mappedRatio) + 1)/2.0;
    
  return(oldPosition + (int)(((sin(mappedRatio) + 1)/2.0) * (newPosition - oldPosition)));


  //Serial.print("relative position: "); Serial.println(relativePosition);
  //Serial.println((oldPos + (int)(relativePosition * (servoPos - oldPos))));
}
