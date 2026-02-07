
#include <Servo.h>
#include <Arduino.h>

#include "VL53L0X.h"
#include "fastop.h"

class Turm
{
  public:
    
  //Pin numbers on the board
  #define XSHUT_PIN 0
  #define SERVO_PIN 5
  #define PUMP_PIN  27
  #define TANK_PIN  29

  //max scanning angle
  #define SCAN_ANGLE 10

  //SERVO MIN MAX
  #define MIN_PITCH 50
  #define MAX_PITCH 160
  #define ZERO_PITCH 86

  struct ZielPosition {
    uint16_t range;
    uint8_t angle;
  };

  void      initTurm ();

  void      printSensorReadings();
  uint16_t  sensorGetDistance();
  void      turnSensorOn ();
  void      turnSensorOff ();

  void      servoTestDrive();
  void      printServoReadings();
  int       pitch(int targetPitch);

  void      pumpOn();
  void      pumpOff();
  void      tankOn();
  void      tankOff();
  
  VL53L0X TOFsensor;
  ZielPosition target;
  private:


  bool    TOFstateOn;

  Servo   myServo;
  uint8_t myServoPitch;
};