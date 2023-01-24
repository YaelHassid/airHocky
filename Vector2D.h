#ifndef AIRHOCKEY_VECTOR2D_H
#define AIRHOCKEY_VECTOR2D_H
#include <iostream>
using namespace std;
class Vector2D {
public:
    double x;
    double y;
    Vector2D(double x, double y);
    Vector2D();


    double norm() const;
    double dotProduct(Vector2D other) const;
    Vector2D closest_Point(Vector2D p1, Vector2D p2) const;
    Vector2D operator+(Vector2D other) const;
    Vector2D operator-(Vector2D other)const;
    Vector2D operator*(double c)const;
    Vector2D operator/(double scalar)const;

};
ostream& operator<<(ostream& os, const Vector2D& pos);
Vector2D operator*(double c, const Vector2D& pos);
Vector2D operator/(double c, const Vector2D& pos);
#endif //AIRHOCKEY_VECTOR2D_H