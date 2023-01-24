#ifndef AIRHOCKEY_DISC_H
#define AIRHOCKEY_DISC_H
#include "Vector2D.h"
#include "Wall.h"
class Wall;

class Disc {
public:
    double radius;
    double mass;
    double c;
    bool clashed;
    Vector2D* speed;
    Vector2D* position;
    Disc(double x, double y, double vx, double vy, double radius);
    void print() const;
};
ostream& operator<<(ostream& os, const Disc& d);


#endif //AIRHOCKEY_DISC_H
