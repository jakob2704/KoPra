//libraries
//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Pixy2.h>
#include <Wire.h>
#include <Servo.h>

#include "Fahren.h"

Pixy2 mypixy;
Servo myservo;

//Variablen
//-------------------------------------------------------------------------
  //Längenangaben in mm

static short radAbstand = 250;
static short radUmfang = 200;
unsigned long boardTime;
unsigned long moveTime;
bool kiesErkennung;
bool kiesErkannt;
bool autoL;
bool autoSuchen;


void setup() {

  kiesErkennung = false;
  kiesErkannt = false;
  autoL = false;
  autoSuchen = false;

  //Wire
  Wire.begin();
  Wire.setClock(100000);

  //Serial
  Serial1.begin(9600);
  Serial1.println("Serial Started");
  Serial.begin(9600);
  Serial.println("Serial Started");
  Serial.println(Serial1.available());

  //PinModes
    //LED
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    //Motoren
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(33, OUTPUT);
    //Sensoren
    mypixy.init();
  
  //Servomotor
  myservo.attach(6);

}

void loop() {
  //getimete funktionen werden nicht über delay() sondern über eine Abfrage der timer Variable ausgesetzt, um multitasking zu ermöglichen

  //SerialBluetooth
  if(Serial1.available() > 0) {
    char DATA = Serial1.read();
    switch(DATA) {
      case 'w':
        stop();
        moveGerade(true);
        break;
      case 'a':
        stop();
        turn(true);
        break;
      case 'd':
        stop();
        turn(false);
        break;
      case 's':
        stop();
        break;
    }
  }

  //Kieserkennung
  //-----------------------------------------------------------------------
    //Kies wird von Sensoren: Gyro, Pixycam erkannt
  if(kiesErkennung) {
    if(kiesErkannt) {
      stop();
    }
    else {
      moveGerade(true);
    }
  }

  //Slalom
  //-----------------------------------------------------------------------
    //Motorsteuerung manuell

  //AutoLöschen
  //-----------------------------------------------------------------------
  if(autoL) {
    //vier Phasen
    //Suchen || Zielen || Schießen || Fahren
    if(autoSuchen) {
    //Suchen
      //sweeping von links nach rechts
      //aufzeichnung der Daten des Ultraschallsensors
      //Auswerten der Daten
      //zurückschwenken bis zu maximalem ausschlag
    //Zielen
      //kleiner Schwenk mit tof sensor
      //Bis maximaler Wert gefunden
    //Schießen
      //auwertung der Distanz
      //ausrichten der Düse
      //Schießen
    //Fahren
      //ausrichten an evtl Bodenmarkierungen
      //Fahren bis zum nächsten markierungspunkt
      //Suchen starten
    }
  }
}

//true -> vorwärts || false -> rückwärts (sollte man aber nicht verwenden)
void moveGerade(bool dir) {
  if(dir) {
    digitalWrite(30, LOW);
    digitalWrite(31, HIGH);
    digitalWrite(31, LOW);
    digitalWrite(31, HIGH);
  }
  else {
    digitalWrite(30, HIGH);
    digitalWrite(31, LOW);
    digitalWrite(31, HIGH);
    digitalWrite(31, LOW);
  }
}

//true -> links || false -> rechts
//schaltet eines der Räder am um zu steuern
void turn(bool dir) {
  if(turn) {
    digitalWrite(30, HIGH);
    digitalWrite(31, LOW);
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
  }
  else {
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
    digitalWrite(32, HIGH);
    digitalWrite(33, LOW);
  }
}

//true -> links || false -> rechts
//dreht die Räder in entgegengesetzte Richtungen um auf der Stelle zu drehen
void rotate(bool dir) {
  if(dir) {
    digitalWrite(30, LOW);
    digitalWrite(31, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(33, LOW);
  }
  else {
    digitalWrite(30, HIGH);
    digitalWrite(31, LOW);
    digitalWrite(32, LOW);
    digitalWrite(33, HIGH);
  }
}

void stop() {
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);
}
