#ifndef AIRHOCKEY_WALL_H
#define AIRHOCKEY_WALL_H
#include "Vector2D.h"
#include "Disc.h"

class Disc;

class Wall {
public:
    Vector2D* right_border;
    Vector2D* left_border;
    Wall(double x1, double y1, double x2, double y2);
    void print() const;
};

#endif //AIRHOCKEY_WALL_H
