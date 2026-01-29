  //libraries
  //-------------------------------------------------------------------------
  #include <Arduino.h>
  #include <SoftwareSerial.h>
  #include <SPI.h>
  #include <Pixy2.h>
  #include <Wire.h>
  #include <Servo.h>
  #include <stdio.h>

<<<<<<< Updated upstream
#include "Fahren.h"
#include "Kieserkennung.h"
#include "Turm.h"

Fahren fahren;
Pixy2 mypixy;
Kieserkennung kieserkennung;
Turm myTurm;
int angle = 86;
=======
  #include "Fahren.h"
  #include "Turm.h"

  Fahren fahren;
  Pixy2 myPixy;
  Turm myTurm;
  int angle = 86;
  uint8_t r, g, b, pixyDistance;
  uint8_t width, height, scanWidthStart, scanWidthEnd, scanHeightStart, scanHeightEnd;
  uint16_t addingr, addingg, addingb, pixyCounter;
>>>>>>> Stashed changes

  #define LED_PIN_R 13
  #define LED_PIN_L 12

  #define redr 246
  #define redg 20
  #define redb 50

  #define kiesr 100
  #define kiesg 100
  #define kiesb 100

  //Variablen
  //-------------------------------------------------------------------------
  //Längenangaben in mm

  static short radAbstand = 250;
  static short radUmfang = 200;

  short speed;

  unsigned long tempTime1;
  unsigned long LEDTime;

  uint8_t autoL;
  uint8_t autoState;
  uint16_t sensorDistance;
  bool LED_L_ON;

  void setup() {

    autoL = false;

<<<<<<< Updated upstream
  //PinModes
  //LED
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  //Motoren
  fahren.setup();
  //Sensoren
  mypixy.init();
  myTurm.initTurm();
  myTurm.turnSensorOn();
}

void loop() {
  //getimete funktionen werden nicht über delay() sondern über eine Abfrage der timer Variable ausgesetzt, um multitasking zu ermöglichen
  //myTurm.pitch(86);
  //myTurm.printSensorReadings();
  //myTurm.scanForTarget(myTurm.target, 86);
  //myTurm.servoTestDrive();

  if(Serial.available() > 0) {
    char cmd = Serial.read();
    switch(cmd){
      case 'w':
        angle++;
        myTurm.pitch(angle);
        Serial.print("\nUP: ");
        myTurm.printServoReadings();
        break;
      case 's':
        angle--;
        myTurm.pitch(angle);
        Serial.print("\nDOWN: ");
        myTurm.printServoReadings();
        break;
    }
  }
  myTurm.printSensorReadings();
  delay(500);
  /*
  //SerialBluetooth
  if(Serial1.available() > 0) {
    char DATA = Serial1.read();
    switch(DATA) {
      case 'w':
        fahren.moveGerade(true, 255);
        //Serial1.println("w");
        break;
      case 'a':
        fahren.turn(true, 255);
        //Serial1.println("a");
        break;
      case 'd':
        fahren.turn(false, 255);
        //Serial1.println("d");
        break;
      case 's':
        fahren.stop();
        //Serial1.println("s");
        break;
      case 'l':
        fahren.rotate(true, 255);
        break;
      case 'r':
        fahren.rotate(false, 255);
        break;
    }
  }*/
  /*
  //Kieserkennung
  //-----------------------------------------------------------------------
    //Kies wird von Sensoren: Gyro, Pixycam erkannt
  if(kiesErkennung) {
    if(kiesTime - millis() < -200) {
      //kies erkennen
      mypixy.changeProg("video");
      if(mypixy.video.getRGB(mypixy.frameWidth / 2, mypixy.frameHeight / 2, &r, &g, &b)) {
        kiesTime = millis();
=======
    //Wire
    Wire.begin();
    Wire.setClock(100000);

    //Serial
    Serial1.begin(9600);
    Serial1.println("Serial Started");
    Serial.begin(115200);
    Serial.println("Serial Started");
    Serial.println(Serial1.available());

    //PinModes
    //LED
    pinMode(LED_PIN_L, OUTPUT);
    pinMode(LED_PIN_R, OUTPUT);
    //Motoren
    fahren.setup();
    //Sensoren
    myPixy.init();
    myTurm.initTurm();
    myTurm.turnSensorOn();

    Serial.println("initSuccesfull");

    myPixy.setLamp(1, 0);
    myPixy.changeProg("video");

    width = myPixy.frameWidth;
    height = myPixy.frameHeight;

    scanWidthStart = width * 0.1;
    scanWidthEnd = width * 0.9;
    scanHeightStart = height * 0.1;
    scanHeightEnd = height * 0.3;

    pixyCounter = 0;
    pixyDistance = 10;

    myPixy.setLamp(1, 0);
    myPixy.setCameraBrightness(40);
    
    autoState = 0;
    autoL     = 0;
    autoState = 0;
    LEDTime   = millis();

    speed     = 255;

    Serial.println("stateSuccesfull");
  }

  void loop() 
  {
    //getimete funktionen werden nicht über delay() sondern über eine Abfrage der timer Variable ausgesetzt, um multitasking zu ermöglichen

    // LOOP GENERAL --------------------------------------------------------------------
    Serial1.println(myTurm.sensorGetDistance());
    //LED
    if(fastop::delayMillis(LEDTime, 200))
    {
      if(LED_L_ON){
        digitalWrite(LED_PIN_L, LOW);
        digitalWrite(LED_PIN_R, HIGH);
        LED_L_ON = false;
      }else{
        digitalWrite(LED_PIN_L, HIGH);
        digitalWrite(LED_PIN_R, LOW);
        LED_L_ON = true;
>>>>>>> Stashed changes
      }
    }

    //SerialBluetooth
    if(Serial1.available() > 0) {
      char DATA = Serial1.read();
      switch(DATA) {
        case 'w':
          fahren.moveGerade(true, speed);
          Serial1.println("w");
          break;
        case 'a':
          fahren.turn(false, speed);
          Serial1.println("a");
          break;
        case 'd':
          fahren.turn(true, speed);
          Serial1.println("d");
          break;
        case 's':
          fahren.stop();
          Serial1.println("s");
          break;
        case 'x':
          fahren.moveGerade(false, speed);
          Serial.println("x");
          break;
        case 'y':
          fahren.rotate(true, speed);
          break;
        case 'c':
          fahren.rotate(false, speed);
          break;
        case 'f':
          speed = SLOW;
          Serial1.println("SLOW");
          break;
        case 'r':
          speed = FAST;
          Serial1.println("FAST");
          break;
        case 't':
          angle++;
          myTurm.pitch(angle);
          Serial1.print("\nUP: ");
          myTurm.printServoReadings();
          break;
        case 'g':
          angle--;
          myTurm.pitch(angle);
          Serial1.print("\nDOWN: ");
          myTurm.printServoReadings();
          break;
        case 'z':
          myTurm.pumpOn();
          Serial1.println("---PUMPE AN---");
          break;
        case 'h':
          myTurm.pumpOff();
          Serial1.println("---PUMPE AUS---");
          break;
        case 'u':
          //autoT
          autoState = 10;
          Serial1.println("Automatische Betankung an.");
          break;
        case 'b':
          autoState = 13;
          Serial1.println("Automatische Kiesdetektion an.");
          break;
        case 'j':
          //autoL
          Serial1.println("Automatisches Löschen an.");
          autoState = 20;
          break;
        case 'n':
          //autoOff
          Serial1.println("Autonom aus.");
          autoState = 0;
          break;
      }
    }
    
    // Autonom --------------------------------------------------------------------
    
    if(autoState > 0)
    {
      switch(autoState)
      {
        case 10: //CASE REFUEL FIND MARKER
          //Serial1.print("CASE REFUEL FIND MARKER");
          //Serial1.print("ALLO");
          //if(myTurm.sensorGetDistance() < 200) fahren.moveGerade(true, SLOW);
          if(bodenerkennung() == 1)
          {
            fahren.stop();
            autoState = 11;
            //Serial1.println("STOP");
            tempTime1 = millis();
          }

          //Serial1.println("END CASE");
          break;

        case 11: //CASE REFUEL

          //Serial1.println("CASE REFUEL");
          fahren.stop();
          if(fastop::delayMillis(tempTime1, 25000))
          {
            digitalWrite(TANK_PIN, HIGH); 
            break;
          }else{
            digitalWrite(TANK_PIN, LOW);
            break;
          }
          
        case 12: //CASE DETECT GRAVEL
          //Serial1.println("CASE DETECT GRAVEL");
          fahren.moveGerade(true, FAST);
          if(bodenerkennung() == 2)
          {
            autoState = 0; 
            fahren.stop();
          }
          break;

        case 20: //CASE LÖSCHEN FIND MARKER
          Serial1.println("Find Marker");
          if(bodenerkennung() == 1) {
            autoState = 21;
          }
          else {
            fahren.moveGerade(true, SLOW);
          }
          break;

        case 21: //CASE LÖSCHEN ZIELSUCHEN
        Serial1.println("Find Distance");
          sensorDistance = myTurm.sensorGetDistance();
          Serial1.println(sensorDistance);
          if(sensorDistance >= 800 && sensorDistance <= 1300)
          {
            fahren.stop();
            autoState = 22;
          }
          break;
        case 22: //CASE LÖSCHEN FEUERN
        Serial1.println("Fire");
          myTurm.pitch(90);
          myTurm.pumpOn();
          myTurm.jiggle(90);
          myTurm.pumpOff();
          if(autoL < 3) {
            autoL++;
            autoState = 20;
            break;
          }
          autoState = 0;
          break;
      }
    }

}

int bodenerkennung(){
  addingr = 0;
  addingg = 0;
  addingb = 0;

  // Getting values
  for (int i = scanWidthStart; i < scanWidthEnd; i = i + 5) {
    for (int j = scanHeightStart; j < scanHeightEnd; j = j + 5) {
      if (myPixy.video.getRGB(i, j, &r, &g, &b) == 0) {
        addingr = addingr + r;
        addingg = addingg + g;
        addingb = addingb + b;
        pixyCounter++;
      }
    }
  }

  // Equalizing values (calculate averages)
  if (pixyCounter > 0) {
    addingr = addingr / pixyCounter;
    addingg = addingg / pixyCounter;
    addingb = addingb / pixyCounter;
  }
<<<<<<< Updated upstream
  */
=======

  pixyCounter = 0;

  Serial1.print(addingr);
  Serial1.print(" ");
  Serial1.print(addingg);
  Serial1.print(" ");
  Serial1.println(addingb);

  // Checking for color matches
  if (abs((int)addingr - (int)redr) <= pixyDistance &&
      abs((int)addingg - (int)redg) <= pixyDistance &&
      abs((int)addingb - (int)redb) <= pixyDistance) {
    Serial.println("Red found");
    return 1;
    }
    else if (abs((int)addingr - (int)kiesr) <= pixyDistance &&
      abs((int)addingg - (int)kiesg) <= pixyDistance &&
      abs((int)addingb - (int)kiesb) <= pixyDistance) {
    Serial.println("Kies found");
    return 2;
    }
    else{return 0;}
>>>>>>> Stashed changes
}



