#include "ExplodingDisc.h"
#include <cmath>
class YaelLinkedListNode;

ExplodingDisc::ExplodingDisc(double x, double y, double vx, double vy, double radius) : Disc(x, y, vx, vy, radius) {
    this->clashCounter = 0;
}

Triplet ExplodingDisc::get_triplet() {
    Triplet triplet;
    double c = 0.99; //to make sure the new discs are not touching
    double r = (2.0* sqrt(3.0)-3.0)*c*this->radius;
    double a = (4.0-2.0* sqrt(3.0))*this->radius;
    //first child:
    Vector2D p0 = *this->position + Vector2D(0,a);
    Vector2D v0 = *this->speed + Vector2D(0,1);
    //second child:
    Vector2D p1 = *this->position + Vector2D(this->radius-a, -(a/2.0));
    Vector2D v1 = *this->speed + Vector2D(sqrt(3.0)/2.0,-0.5);
    //third child:
    Vector2D p2 = *this->position + Vector2D(-(this->radius-a), -(a/2.0));
    Vector2D v2 = *this->speed + Vector2D(-(sqrt(3.0)/2.0),-0.5);
    triplet.child_one = new YaelLinkedListNode(p0.x, p0.y, v0.x, v0.y, r, 1);
    triplet.child_one->explodingDisc->mass = this->mass/3.0;
    triplet.child_one->explodingDisc->clashCounter = this->clashCounter;
    triplet.child_two =  new YaelLinkedListNode(p1.x, p1.y, v1.x, v1.y, r, 1);
    triplet.child_two->explodingDisc->mass = this->mass/3.0;
    triplet.child_two->explodingDisc->clashCounter = this->clashCounter;
    triplet.child_three = new YaelLinkedListNode(p2.x, p2.y, v2.x, v2.y, r, 1);
    triplet.child_three->explodingDisc->mass = this->mass/3.0;
    triplet.child_three->explodingDisc->clashCounter = this->clashCounter;

    return triplet;
}
