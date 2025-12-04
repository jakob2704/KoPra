/*

  Fahren.h - Library for fahren das Fahrzeug.

  Created by Jakob Hawlat, November 24 2025.

  Not released into the public domain.

*/

#include "Fahren.h"

Fahren::Fahren() {
  pinLinksVor = 30;
  pinRechtsVor = 31;
  pinLinksRueck = 32;
  pinRechtsRueck = 33;
}

//true -> vorwärts || false -> rückwärts (sollte man aber nicht verwenden)
void Fahren::moveGerade(bool direction) {
  int vor = direction ? HIGH : LOW;
  int rueck = direction ? LOW : HIGH;

  digitalWrite(pinLinksVor, vor);
  digitalWrite(pinRechtsVor, vor);
  digitalWrite(pinLinksRueck, rueck);
  digitalWrite(pinRechtsRueck, rueck);
}


//true -> links || false -> rechts
//schaltet eines der Räder am um zu steuern
void Fahren::turn(bool direction) {
  int rechts = direction ? HIGH : LOW;
  int links = direction ? LOW : HIGH;

  digitalWrite(pinLinksVor, links);
  digitalWrite(pinRechtsVor, rechts);
  digitalWrite(pinLinksRueck, LOW);
  digitalWrite(pinRechtsRueck, LOW);
}

//true -> links || false -> rechts
//dreht die Räder in entgegengesetzte Richtungen um auf der Stelle zu drehen
void Fahren::rotate(bool direction) {
  int rechts = direction ? HIGH : LOW;
  int links = direction ? LOW : HIGH;

  digitalWrite(pinLinksVor, links);
  digitalWrite(pinRechtsVor, rechts);
  digitalWrite(pinLinksRueck, rechts);
  digitalWrite(pinRechtsRueck, links);
}

void Fahren::stop() {
  digitalWrite(pinLinksVor, LOW);
  digitalWrite(pinRechtsVor, LOW);
  digitalWrite(pinLinksRueck, LOW);
  digitalWrite(pinRechtsRueck, LOW);
}