<<<<<<< Updated upstream
<<<<<<< Updated upstream

#ifndef FASTOP_H
#define FASTOP_H

class fastop
{
  public:
    static void delay (int times);
};

=======
=======
>>>>>>> Stashed changes

#ifndef FASTOP_H
#define FASTOP_H

class fastop
{
  public:
    static void delay             (int times);
    static bool delayMillis       (unsigned long &global, unsigned int time);
    static bool delayMillisBlock  (unsigned long time);
};

<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
#endif