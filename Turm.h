
#include <Servo.h>
#include <Arduino.h>

#include "VL53L0X.h"
#include "fastop.h"

class Turm
{
  public:
    
  //Pin numbers on the board
<<<<<<< Updated upstream
  #define XSHUT_PIN 29
  #define SERVO_PIN 23
  #define PUMPE_PIN 28
=======
  #define XSHUT_PIN 52
  #define SERVO_PIN 5
  #define PUMP_PIN  27
  #define TANK_PIN  29

>>>>>>> Stashed changes

  //Constants
  #define G_EARTH   9.81
  #define Y_0       0

  //jiggle angle amount and speed
  #define SPRAY_ANGLE 2
  #define SPRAY_TIMES 4
  #define SPRAY_THROTTLE 10

  //max scanning angle
  #define SCAN_ANGLE 5

  //Intervall of valid target distances in mm
  #define VALID_MIN_DISTANCE 1200
  #define VALID_MAX_DISTANCE 700

  //muzzlevelocity in m/s
  #define MUZZLE_VEL  3

  //Servo parameters
  #define ZERO_PITCH  0
  #define MAX_PITCH   (90 - ZERO_PITCH)
  #define MIN_PITCH   (90 + ZERO_PITCH)

  struct ZielPosition {
    uint16_t range;
    uint8_t angle;
  };

  void      initTurm ();

  void      printTargetDistance();
  void      scanForTarget(ZielPosition &target, uint8_t zeroAngle);
  void      fireOnTarget (ZielPosition &target);
  void      jiggle (uint8_t firingAngle);
<<<<<<< Updated upstream
  uint8_t   calculateFiringAngle (ZielPosition &target, uint8_t muzzleVelocity);
=======
  uint16_t  calculateFiringAngle (ZielPosition &target, uint16_t muzzleVelocity);
>>>>>>> Stashed changes

  void      printSensorReadings();
  uint16_t  sensorGetDistance();
  void      turnSensorOn ();
  void      turnSensorOff ();

  void      servoTestDrive();
  void      printServoReadings();
  int       pitch(int targetPitch);

  void      pumpOn();
  void      pumpOff();
<<<<<<< Updated upstream
    VL53L0X TOFsensor;
=======
  void      refilling();
  
  VL53L0X TOFsensor;
>>>>>>> Stashed changes
  ZielPosition target;
  private:


  bool    TOFstateOn;

  Servo   myServo;
  uint8_t myServoPitch;
};