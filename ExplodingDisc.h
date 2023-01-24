#ifndef AIRHOCKEY_EXPLODINGDISC_H
#define AIRHOCKEY_EXPLODINGDISC_H
#include "Disc.h"
#include "YaelLinkedListNode.h"
class ExplodingDisc: public Disc {
public:
    int clashCounter;
    //Constructor:
    ExplodingDisc(double x, double y, double vx, double vy, double radius);
    //creating three children to teh exploding disc:
    Triplet get_triplet();
};


#endif //AIRHOCKEY_EXPLODINGDISC_H
