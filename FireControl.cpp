
#include "Turm_servo.h"
#include "TOF_sensor.h"
#include "fastop.h"

struct zielPos{
  int    x;
  short  phi;
};


void Zielerfassung(TOF_sensor sensor, Turm_servo servo /*, Pumpe*/) //Sensor ausrichten und Scannen
{
  
  //Servo auf Startposition ausrichten
  servo.pitch(0);
  
  //Scanning 
  for(int i = 0; i < 180; i++){
    servo.myServo.write(i);
    sensor.readDistance(); // <- speichern und vergleichen noch benötigt
    fastop::delay(1);
  }

  //Servo auf Neutraleposition ausrichten
  servo.pitch(90);
}

void sprayNPray(short* firingAngle, Turm_servo servo /*, Pumpe*/){

  for (int i = 2; i > -2; i--){
    servo.myServo.write(&firingAngle + i);
    fastop::delay(10);
  }

  for (int i = -2; i < 2; i++){
    servo.myServo.write(&firingAngle + i);
    fastop::delay(10);
  }

}

void Feuern(short firingAngle, Turm_servo servo /*, Pumpe*/) //Düse ausrichten und feuern
{

  //Servo auf Feuerposition
  servo.pitch(firingAngle);

  //JIGGLE!
  for(int i = 0; i < 10; i++){
    sprayNPray(firingAngle, servo);
  }
  
}

uint_16_t calculateFiringAngle(uint_16_t distance; uint_8_t phi; uint_16_t muzzle_vel)
{
  uint_16_t alpha;
  
  uint_16_t x_z = distance * cos(phi);
  uint_16_t y_z = distance * sin(phi);
  uint_16_t gxz = G_EARTH*pow(x_z, 2)/(2*pow(muzzle_vel, 2));

  alpha = (uint_16_t)atan((x_z - sqrt(pow(x_z, 2), - 4*gxz*(Y_0 - y_z - gxz)))*1/gxz); //Winkelberechnung

  return alpha;
}

