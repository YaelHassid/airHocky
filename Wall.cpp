#include "Wall.h"

Wall::Wall(double x1, double y1, double x2, double y2) {
    right_border = new Vector2D(x1, y1);
    left_border = new Vector2D(x2, y2);
}

void Wall::print() const{
    cout << *left_border << "," << *right_border << endl;
}
