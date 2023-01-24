#include "Vector2D.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(): x(0), y(0) {}

double Vector2D::norm() const{
    return sqrt(pow(this->x,2) + pow(this->y,2));
}
double Vector2D::dotProduct(Vector2D other) const{
    return this->x*other.x + this->y*other.y;
}
Vector2D Vector2D::closest_Point(Vector2D p1, Vector2D p2) const{
    if((p1.x == p2.x) && (p1.y == p2.y)) return p1;// segment has length zero
    else {
        Vector2D p3 = *this - p1;
        Vector2D p4 = p2 - p1;
        double a = p3.dotProduct(p4)/pow((p1-p2).norm(),2);
        if(a < 0) return p1;
        else if(a > 1) return p2;
        else return p1 + a*(p2 - p1);
    }
}
Vector2D Vector2D::operator+(const Vector2D other) const {
    return Vector2D(x + other.x, y + other.y);
}
Vector2D Vector2D::operator-(const Vector2D other) const {
    return Vector2D(x - other.x, y - other.y);
}
Vector2D Vector2D::operator*(double c) const {
    return Vector2D(c* this->x, c* this->y);
}
Vector2D Vector2D::operator/(double scalar) const {
    return Vector2D(this->x / scalar, this->y / scalar);
}
ostream& operator<<(ostream& os, const Vector2D& pos) {
    os << setprecision(4) << fixed << "(" << pos.x << "," << pos.y << ")";
    return os;
}
Vector2D operator*(double c, const Vector2D& pos){
    return pos*c;
}
Vector2D operator/(double c, const Vector2D& pos){
    return pos/c;
}
