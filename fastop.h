<<<<<<< Updated upstream

#ifndef FASTOP_H
#define FASTOP_H

class fastop
{
  public:
    static void delay (int times);
};

=======

#ifndef FASTOP_H
#define FASTOP_H

class fastop
{
  public:
    static void delay             (int times);
    static bool delayMillis       (unsigned long &global, unsigned int time);
    static bool delayMillisBlock  (unsigned long time);
};

>>>>>>> Stashed changes
#endif