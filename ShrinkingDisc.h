#ifndef AIRHOCKEY_SHRINKINGDISC_H
#define AIRHOCKEY_SHRINKINGDISC_H


#include "Disc.h"

class ShrinkingDisc: public Disc {
public:
    int clashCounter;
    //Constructor:
    ShrinkingDisc(double x, double y, double vx, double vy, double radius);

};


#endif //AIRHOCKEY_SHRINKINGDISC_H
