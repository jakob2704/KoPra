  //libraries
  //-------------------------------------------------------------------------
  #include <Arduino.h>
  #include <SoftwareSerial.h>
  #include <SPI.h>
  #include <Pixy2.h>
  #include <Wire.h>
  #include <Servo.h>
  #include <stdio.h>

  #include "Fahren.h"
  #include "Turm.h"

  Fahren fahren;
  Pixy2 myPixy;
  Turm myTurm;
  int angle = 86;
  uint8_t r, g, b, pixyDistance, soundCounter, soundCounter2;
  uint8_t width, height, scanWidthStart, scanWidthEnd, scanHeightStart, scanHeightEnd;
  uint16_t addingr, addingg, addingb, pixyCounter;
  bool sound;

  #define LED_PIN_R 13
  #define LED_PIN_L 12

  #define redr 246
  #define redg 17
  #define redb 16

  #define kiesr 194
  #define kiesg 246
  #define kiesb 186

  #define TARGET_ANGLE 80
  #define SPRAY_ANGLE 4
  #define SPRAY_TIMES 30
  #define SPRAY_THROTTLE 200

  //Variablen
  //-------------------------------------------------------------------------
  //Längenangaben in mm

  static short radAbstand = 250;
  static short radUmfang = 200;

  short speed;

  unsigned long tempTime1;
  unsigned long tempTime2;
  unsigned long LEDTime;

  /* --Fire jiggle--
  bool    autoU;
  short   autoPitch;
  short   autoPtimes;
  */

  bool    saveMode;
  short   autoL;
  uint8_t autoState;

  uint16_t sensorDistance;
  bool LED_L_ON;

  void setup() {

    autoL = false;

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
    pinMode(10, OUTPUT);
    //Motoren
    fahren.setup();
    //Sensoren
    myPixy.init();
    myTurm.initTurm();
    //myTurm.turnSensorOn();

    Serial1.println("initSuccesfull");

    myPixy.setLamp(1, 0);
    myPixy.changeProg("video");

    width = myPixy.frameWidth;
    height = myPixy.frameHeight;

    scanWidthStart = width * 0.3;
    scanWidthEnd = width * 0.7;
    scanHeightStart = height * 0.1;
    scanHeightEnd = height * 0.2;

    pixyCounter = 0;
    pixyDistance = 10;

    myPixy.setLamp(1, 0);
    myPixy.setCameraBrightness(65);

    /* --FIRE JIGGLE--
    autoU     = true;
    autoPitch = 0;
    autoPtimes = 0;
    */

    saveMode  = false;
    autoL     = 0;
    autoState = 0;

    tempTime1 = millis();
    tempTime2 = millis();
    LEDTime   = millis();

    speed     = 255;

    Serial1.println("stateSuccesfull");
  }

  void loop() 
  {
    //getimete funktionen werden nicht über delay() sondern über eine Abfrage der timer Variable ausgesetzt, um multitasking zu ermöglichen

    // LOOP GENERAL --------------------------------------------------------------------
    //Serial1.println(myTurm.sensorGetDistance());
    //LED
    if(!saveMode){
      if(fastop::delayMillis(LEDTime, 300))
      {
        if(LED_L_ON){
          digitalWrite(LED_PIN_L, LOW);
          digitalWrite(LED_PIN_R, HIGH);
          LED_L_ON = false;
        }else{
          digitalWrite(LED_PIN_L, HIGH);
          digitalWrite(LED_PIN_R, LOW);
          LED_L_ON = true;
        }
      }
      myPixy.setLamp(1, 0);
    }else{
      digitalWrite(LED_PIN_L, LOW);
      digitalWrite(LED_PIN_R, LOW);
      myPixy.setLamp(0, 0);
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
        case 'c':
          fahren.rotate(true, speed);
          break;
        case 'y':
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
          saveMode = true;
          break;
        case 'h':
          myTurm.pumpOff();
          Serial1.println("---PUMPE AUS---");
          saveMode = false;
          myPixy.setLamp(1,0);
          break;
        case 'u':
          //autoT
          autoState = 10;
          Serial1.println("Automatische Betankung an. ---- CASE 10 REFUEL FIND MARKER ----");
          break;
        case 'b':
          autoState = 12;
          Serial1.println("Automatische Kiesdetektion an. ---- CASE 12 FIND GRAVEL ----");
          break;
        case 'j':
          //autoL
          Serial1.println("Automatisches Löschen an. ---- CASE 20 LÖSCHEN FIND MARKER ----");
          autoState = 20;
          break;
        case 'n':
          //autoOff
          Serial1.println("Autonom aus.");
          autoState = 0;
          break;
        case 'e':
          //Ventil auf
          Serial1.println("Ventil Auf");
          myTurm.tankOn();
          break;
        case 'i':
          Serial1.println("Ventil Zu");
          myTurm.tankOff();
          break;
        case 'k':
          Serial1.println("Sound On");
          autoState = 13;
          break;
      }
    }
    
    // Autonom --------------------------------------------------------------------
    
    if(autoState > 0)
    {
      switch(autoState)
      {
        case 10: //CASE REFUEL FIND MARKER

          if(myTurm.sensorGetDistance() < 200) fahren.moveGerade(true, SLOW);

          if(bodenerkennung() == 1)
          {
            fahren.stop();
            autoState = 11;
            Serial1.println("Bodenmaker erkannt. ----> CASE 11 REFUEL");
            tempTime1 = millis();
            tempTime2 = millis();
          }

          break;

        case 11: //CASE REFUEL
        
          fahren.stop();
          if(fastop::delayMillis(tempTime1, 1000))
          {
            myTurm.tankOn();
          }
          if(fastop::delayMillis(tempTime2, 26000))
          {
            myTurm.tankOff();
            Serial1.println("Autonome Betankung beendet. ----> CASE 12 DETECT GRAVEL");
            tempTime1 = millis();
            break;
          }
          
        case 12: //CASE DETECT GRAVEL

          if(fastop::delayMillis(tempTime1, 500))
          {
            fahren.moveGerade(true, FAST);
          }
          if(bodenerkennung() == 2)
          {
            autoState = 13; 
            Serial1.println("Kies detektiert! ----> CASE 13 GRAVEL FOUND");
            fahren.stop();
          }
          break;

        case 13: // CASE GRAVEL FOUND 

          if(tempTime1 + 200 < millis()){
            tempTime1 = millis();
            sound = !sound;
            soundCounter++;
          }
          if(sound) {
            analogWrite(10, 200);
          }
          else {
            analogWrite(10, 0);
          }
          if(soundCounter > 5) {
            autoState = 0;
            soundCounter = 0;
            Serial1.println("Autonom aus. ----> CASE 0 ");
          }
          break;

        case 20: //CASE LÖSCHEN FIND MARKER

          if(bodenerkennung() == 1) {
            autoState = 21;
            Serial1.println("Marker detektiert! Ziel suchen. ----> CASE 21 LÖSCHEN ZIELSUCHEN");
            myTurm.pitch(TARGET_ANGLE);
          }
          else {
            fahren.moveGerade(true, SLOW);
          }
          break;
        case 201: //CASE LÖSCHEN VERZÖRGERT ZIELSUCHEN

          if(fastop::delayMillis(tempTime1, 700))
          {
            autoState = 21;
            Serial1.println("Ziel suchen. ----> CASE 21 LÖSCHEN ZIELSUCHEN");
          }
          break;

        case 21: //CASE LÖSCHEN ZIELSUCHEN

          sensorDistance = myTurm.sensorGetDistance();
          Serial1.println(sensorDistance);
          if(sensorDistance >= 800 && sensorDistance <= 1300)
          {
            fahren.stop();
            autoState = 211;
            Serial1.println("Ziel detektiert! ----> CASE 211 ZIEL FOUND");
            tempTime1 = millis();
          }
          break;

        case 211: //CASE ZIEL FOUND

          if(tempTime1 + 200 < millis()){
            tempTime1 = millis();
            sound = !sound;
            soundCounter2++;
          }
          if(sound) {
            analogWrite(10, 200);
          }
          else {
            analogWrite(10, 0);
          }
          if(soundCounter2 > 5) {
            autoState = 22;
            Serial1.println("FEUER FREI! ---> CASE 22 LÖSCHEN FEUERN");
            tempTime1 = millis();
            tempTime2 = millis();
          }
          break;

        case 22: //CASE LÖSCHEN FEUERN

          Serial1.println("Fire");
          myTurm.pitch(160);
          saveMode = true;
          if(fastop::delayMillis(tempTime1, 500))
          {
            Serial1.println("FEUER");
            myTurm.pumpOn();
          }
          if(fastop::delayMillis(tempTime2, 5500))
          {
            saveMode = false;
            myPixy.setLamp(1,0);
            myTurm.pumpOff();
            myTurm.pitch(TARGET_ANGLE);
            Serial1.println("FEUER STOP");
            if(autoL > 3){
              autoState = 0;
              Serial1.println ("Alle Ziele gelöscht! ----> CASE 0");
              break;
            }
            autoL++;
            myTurm.pitch(TARGET_ANGLE);
            Serial1.println("Ziel gelöscht! ----> CASE 201 ZIEL VERZÖGERT SUCHEN");
            tempTime1 = millis();
            autoState = 201;
          }
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

  pixyCounter = 0;

  /*Serial1.print(addingr);
  Serial1.print(" ");
  Serial1.print(addingg);
  Serial1.print(" ");
  Serial1.println(addingb);*/

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
}

//CODE BUNKER
/*

if(fastop::delayMillis(tempTime1, SPRAY_THROTTLE))
          {
            myTurm.pumpOn();
            
            Serial1.print("\n FIRE PITCH ANGLE: ");
            Serial1.print(autoPitch);
            
            if(autoU){
              if(autoPitch < SPRAY_ANGLE){
                myTurm.pitch(90 + autoPitch);
                autoPitch++;
              }else{
                autoPtimes++;
                autoU = false;
              }
            }else{
              if(autoPitch > -SPRAY_ANGLE){
                myTurm.pitch(90 + autoPitch);
                autoPitch--;
              }else{
                autoPtimes++;
                autoU = true;
              }
            }
          }
          if(autoPtimes < SPRAY_TIMES) break;

          autoU       = true;
          autoPitch   = 0;
          autoPtimes  = 0;
          myTurm.pumpOff();
          
          if(autoL > 3) {
            autoL++;
            autoState = 20;
            break;
          }
          autoState = 0;
          break;
        }
*/

