#include "fastop.h"

//assembly delay opperation

static void fastop::delay(int times){

  while (times > 0){
    __asm__ __volatile__ ("nop");
    times--;
  }
  
}