/*

  Kieserkennung.h - Library for erkennen das Kies.

  Created by Jakob Hawlat, December 04 2025.

  Not released into the public domain.

*/

#ifndef KIESERKENNUNG_H
#define KIESERKENNUNG_H

#include <Arduino.h>

class Kieserkennung
{
  public:
    //Constructor
    Kieserkennung();
    //Methoden
    bool weichtBodenAb(uint8_t currentR, uint8_t currentG, uint8_t currentB, uint8_t sollR, uint8_t sollG, uint8_t sollB);
  private:
    int abweichung;
};

#endif