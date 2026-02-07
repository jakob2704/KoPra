
//---------------------------------------------------------------------------------------------
//libraries
#include <Servo.h>
#include <Arduino.h>

#include "VL53L0X.h"
#include "fastop.h"
#include "Turm.h"


//Pin numbers on the board
#define XSHUT_PIN 53
#define SERVO_PIN 45
#define PUMP_PIN  49
#define TANK_PIN  47

//max scanning angle
#define SCAN_ANGLE 10

//Interval of valid target distances in mm
#define VALID_MIN_DISTANCE 1200
#define VALID_MAX_DISTANCE 700

//SERVO MIN MAX
#define MIN_PITCH 50
#define MAX_PITCH 160
#define ZERO_PITCH 86

//variables
VL53L0X TOFsensor;
bool    TOFstateOn;

Servo   myServo;
uint8_t myServoPitch;

//---------------------------------------------------------------------------------------------

//setup function
void Turm::initTurm(){
  pinMode(XSHUT_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(TANK_PIN, OUTPUT);

  myServo.attach(SERVO_PIN, 550, 2370);
  myServoPitch = ZERO_PITCH;

  digitalWrite(XSHUT_PIN, LOW);
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(TANK_PIN, LOW);
}

//Zielerfassung und Feuermechanismus ----------------------------------------------------------

//Sensor---------------------------------------------------------------------------------------

void Turm::printSensorReadings()
{
  int temp = sensorGetDistance();
  Serial1.print("\nTOFsensor distance: ");
  Serial1.print(temp);
  Serial1.print(" mm");
}

uint16_t Turm::sensorGetDistance()
{
  if(!TOFstateOn) {return -1;}
  uint16_t distance = TOFsensor.readRangeSingleMillimeters();
  if(TOFsensor.timeoutOccurred()) {return -1;}
  Serial1.print("\nSensorDistance: ");
  Serial1.print(distance);
  return distance;
}
void Turm::turnSensorOn()
{
  if (!TOFstateOn) {digitalWrite(XSHUT_PIN, HIGH); TOFsensor.initSensor(); TOFstateOn = true;}
}

void Turm::turnSensorOff()
{
  if (TOFstateOn) {digitalWrite(XSHUT_PIN, LOW);}
}

//Servo----------------------------------------------------------------------------------------

void Turm::servoTestDrive()
{
  pitch(160);
  printServoReadings();
  delay(1000);
  pitch(86);
  printServoReadings();
  delay(1000);
  pitch(0);
  printServoReadings();
  delay(1000);
}

void Turm::printServoReadings()
{
  Serial1.print("\nServo angle: ");
  Serial1.print(myServoPitch);
  Serial1.print("\n");
}

int Turm::pitch(int targetPitch)
{
  targetPitch = constrain(targetPitch, MIN_PITCH, MAX_PITCH);

  while (myServoPitch != targetPitch)
  {
    if (myServoPitch < targetPitch)
      myServoPitch++;
    else
      myServoPitch--;
    myServo.write(myServoPitch);
    fastop::delay(1000000);
  }
  return myServoPitch;
}

//Pumpe----------------------------------------------------------------------------------------

//Pumpe an.
void Turm::pumpOn()
{
  digitalWrite(PUMP_PIN, HIGH);
}

//Pumpe aus.
void Turm::pumpOff()
{
  digitalWrite(PUMP_PIN, LOW);
}

void Turm::tankOn()
{
  digitalWrite(TANK_PIN, HIGH);
}

void Turm::tankOff()
{
  digitalWrite(TANK_PIN, LOW);
}