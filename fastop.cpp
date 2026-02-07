
#include <Arduino.h>
#include "fastop.h"

//assembly delay function
static void fastop::delay(int times)
{
  while (times > 0)
  {
    __asm__ __volatile__ ("nop");
    times--;
  }
}

static bool fastop::delayMillis(unsigned long &timestamp, unsigned int time)
{
  unsigned long current = millis();
  if(current-timestamp >= time)
  {
    timestamp = current;
    return true;
  }

  return false;
}

static bool fastop::delayMillisBlock(unsigned long time)
{
  unsigned long last = millis();
  
  while(millis() - last <= time){}

  return true;
}