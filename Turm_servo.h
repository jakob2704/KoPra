#include <Servo.h>
#include "fastop.h"

class Turm_servo{
  public:
    Servo   myServo;
    void    initServo();
    short   pitch(short pitch);
  private:
    short   currentPos;
};