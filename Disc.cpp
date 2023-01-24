#include "Disc.h"
#include <iostream>
#include <iomanip>

using namespace std;

Disc::Disc(double x, double y, double vx, double vy, double radius) {
    this->c = 1;
    this->position = new Vector2D(x, y);
    this->speed  = new Vector2D(vx, vy);
    this->radius = radius;
    this->mass = this->c * radius * radius;
    this->clashed = false;
}
void Disc::print() const {
    cout << *this->position << "/"<< setprecision(4) << fixed << this->radius << " ";
}

