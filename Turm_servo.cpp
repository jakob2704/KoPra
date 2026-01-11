#include <Servo.h>
#include "fastop.h"

Servo   myServo;
short   currentPos;

void initServo (short ServoPin){

  myServo.attach(ServoPin);

}

short pitch (short pitch){

  if(currentPos - pitch >= 0){
    while (currentPos != pitch){
      myServo.write(currentPos);
      currentPos++;
      fastop::delay(10);
    }
    return currentPos;
  }

  while (currentPos != pitch){
    myServo.write(currentPos);
    currentPos--;
    fastop::delay(10);
  }
  return currentPos;

}