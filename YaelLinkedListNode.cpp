#include "YaelLinkedListNode.h"
#include "ExplodingDisc.h"
#include "ShrinkingDisc.h"
#include <iostream>
using namespace std;

YaelLinkedListNode::YaelLinkedListNode(double x, double y, double vx, double vy, double radius, int type){
    // type 0 = basic disc, type 1 = exploding disc, type 2 = shrinking disc
    this->init();
    if (type == 0) {
        this->disc = new Disc(x, y, vx, vy, radius);
    } else if (type == 1) {
        this->explodingDisc = new ExplodingDisc(x, y, vx, vy, radius);
    } else {
        this->shrinkingDisc = new ShrinkingDisc(x, y, vx, vy, radius);
    }
}
YaelLinkedListNode::YaelLinkedListNode(double x1, double y1, double x2, double y2) {
    this->init();
    this->wall = new Wall(x1, y1, x2, y2);
}
void YaelLinkedListNode::init() {
    this->disc = NULL;
    this->explodingDisc = NULL;
    this->shrinkingDisc = NULL;
    this->wall = NULL;
    this->next = NULL;

}
YaelLinkedListNode::~YaelLinkedListNode() {
    if(this->disc != NULL) delete this->disc;
    if(this->shrinkingDisc != NULL) delete this->shrinkingDisc;
    if(this->explodingDisc != NULL) delete this->explodingDisc;
    if(this->wall != NULL) delete this->wall;
}
bool YaelLinkedListNode::check_collision(YaelLinkedListNode *other) const {
    if (this->disc != NULL) {
        if (other->disc != NULL) { //checking collision between two normal discs
            Vector2D p1(this->disc->position->x, this->disc->position->y);
            Vector2D p2(other->disc->position->x, other->disc->position->y);
            return (p1-p2).norm() <= this->disc->radius + other->disc->radius;
        } else if (other->explodingDisc != NULL) { //checking collision between a normal disc and an exploding disc
            Vector2D p1(this->disc->position->x, this->disc->position->y);
            Vector2D p2(other->explodingDisc->position->x, other->explodingDisc->position->y);
            return (p1-p2).norm() <= this->disc->radius + other->explodingDisc->radius;
        } else if (other->shrinkingDisc != NULL) { //checking collision between a normal disc and an shrinking disc
            Vector2D p1(this->disc->position->x, this->disc->position->y);
            Vector2D p2(other->shrinkingDisc->position->x, other->shrinkingDisc->position->y);
            return (p1-p2).norm() <= this->disc->radius + other->shrinkingDisc->radius;
        } else { //checking collision between a normal disc and a wall
            Vector2D p(this->disc->position->x, this->disc->position->y);
            Vector2D q = this->disc->position->closest_Point(*other->wall->left_border, *other->wall->right_border);
            if((p-q).norm() <= this->disc->radius) return true;
            else return false;
        }
    } else if (this->explodingDisc != NULL) {
        if (other->disc != NULL) { //checking collision between an exploding disc and a normal disc
            Vector2D p1(this->explodingDisc->position->x, this->explodingDisc->position->y);
            Vector2D p2(other->disc->position->x, other->disc->position->y);
            return (p1-p2).norm() <= this->explodingDisc->radius + other->disc->radius;
        } else if (other->explodingDisc != NULL) { //checking collision between two exploding discs
            Vector2D p1(this->explodingDisc->position->x, this->explodingDisc->position->y);
            Vector2D p2(other->explodingDisc->position->x, other->explodingDisc->position->y);
            return (p1-p2).norm() <= this->explodingDisc->radius + other->explodingDisc->radius;
        } else if (other->shrinkingDisc != NULL) { //checking collision between an exploding disc and a shrinking disc
            Vector2D p1(this->explodingDisc->position->x, this->explodingDisc->position->y);
            Vector2D p2(other->shrinkingDisc->position->x, other->shrinkingDisc->position->y);
            return (p1-p2).norm() <= this->explodingDisc->radius + other->shrinkingDisc->radius;
        } else { //checking collision between an exploding disc and a wall
            Vector2D p(this->explodingDisc->position->x, this->explodingDisc->position->y);
            Vector2D q = this->explodingDisc->position->closest_Point(*other->wall->left_border, *other->wall->right_border);
            if((p-q).norm() <= this->explodingDisc->radius) return true;
            else return false;
        }
    } else if (this->shrinkingDisc != NULL) {
        if (other->disc != NULL) { //checking collision between a shrinking disc and a normal disc
            Vector2D p1(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
            Vector2D p2(other->disc->position->x, other->disc->position->y);
            return (p1-p2).norm() <= this->shrinkingDisc->radius + other->disc->radius;
        } else if (other->explodingDisc != NULL) { //checking collision between a shrinking disc and a exploding disc
            Vector2D p1(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
            Vector2D p2(other->explodingDisc->position->x, other->explodingDisc->position->y);
            return (p1-p2).norm() <= this->shrinkingDisc->radius + other->explodingDisc->radius;
        } else if (other->shrinkingDisc != NULL) { //checking collision between a shrinking disc and a shrinking disc
            Vector2D p1(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
            Vector2D p2(other->shrinkingDisc->position->x, other->shrinkingDisc->position->y);
            return (p1-p2).norm() <= this->shrinkingDisc->radius + other->shrinkingDisc->radius;
        } else { //checking collision between a normal disc and a wall
            Vector2D p(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
            Vector2D q = this->shrinkingDisc->position->closest_Point(*other->wall->left_border, *other->wall->right_border);
            if ((p-q).norm() <= this->shrinkingDisc->radius) return true;
            else return false;
        }
    }
}
void YaelLinkedListNode::update_collision_speed(YaelLinkedListNode &against) {
    if (this->disc != NULL) {
        if (against.disc != NULL) { //updating the speeds of two normal discs
            Vector2D p1(this->disc->position->x, this->disc->position->y);
            Vector2D p2(against.disc->position->x, against.disc->position->y);
            Vector2D v1(this->disc->speed->x, this->disc->speed->y);
            Vector2D v2(against.disc->speed->x, against.disc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->disc->mass;
            double m2 = against.disc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->disc->speed->x = newV1.x;
            this->disc->speed->y = newV1.y;
            against.disc->speed->x = newV2.x;
            against.disc->speed->y = newV2.y;
        } else if (against.explodingDisc != NULL) { //updating the speeds of a normal disc and a exploding disc
            Vector2D p1(this->disc->position->x, this->disc->position->y);
            Vector2D p2(against.explodingDisc->position->x, against.explodingDisc->position->y);
            Vector2D v1(this->disc->speed->x, this->disc->speed->y);
            Vector2D v2(against.explodingDisc->speed->x, against.explodingDisc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->disc->mass;
            double m2 = against.explodingDisc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->disc->speed->x = newV1.x;
            this->disc->speed->y = newV1.y;
            against.explodingDisc->speed->x = newV2.x;
            against.explodingDisc->speed->y = newV2.y;
        } else if (against.shrinkingDisc != NULL) { //updating the speeds of a normal disc and a shrinking disc
            Vector2D p1(this->disc->position->x, this->disc->position->y);
            Vector2D p2(against.shrinkingDisc->position->x, against.shrinkingDisc->position->y);
            Vector2D v1(this->disc->speed->x, this->disc->speed->y);
            Vector2D v2(against.shrinkingDisc->speed->x, against.shrinkingDisc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->disc->mass;
            double m2 = against.shrinkingDisc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->disc->speed->x = newV1.x;
            this->disc->speed->y = newV1.y;
            against.shrinkingDisc->speed->x = newV2.x;
            against.shrinkingDisc->speed->y = newV2.y;
        } else { //updating the speed of a normal disc
            Vector2D p(this->disc->position->x, this->disc->position->y);
            Vector2D q = this->disc->position->closest_Point(*against.wall->left_border, *against.wall->right_border);
            Vector2D direction_vector = (p - q)/(p-q).norm();
            Vector2D v(this->disc->speed->x, this->disc->speed->y);
            *(this->disc->speed) = v - 2*((v.dotProduct(direction_vector))*direction_vector);
        }
    } else if (this->explodingDisc != NULL) {
        if (against.disc != NULL) { //updating the speeds of a exploding disc and a normal disc
            Vector2D p1(this->explodingDisc->position->x, this->explodingDisc->position->y);
            Vector2D p2(against.disc->position->x, against.disc->position->y);
            Vector2D v1(this->explodingDisc->speed->x, this->explodingDisc->speed->y);
            Vector2D v2(against.disc->speed->x, against.disc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->explodingDisc->mass;
            double m2 = against.disc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->explodingDisc->speed->x = newV1.x;
            this->explodingDisc->speed->y = newV1.y;
            against.disc->speed->x = newV2.x;
            against.disc->speed->y = newV2.y;
        } else if (against.explodingDisc != NULL) { //updating the speeds of two exploding discs
            Vector2D p1(this->explodingDisc->position->x, this->explodingDisc->position->y);
            Vector2D p2(against.explodingDisc->position->x, against.explodingDisc->position->y);
            Vector2D v1(this->explodingDisc->speed->x, this->explodingDisc->speed->y);
            Vector2D v2(against.explodingDisc->speed->x, against.explodingDisc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->explodingDisc->mass;
            double m2 = against.explodingDisc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->explodingDisc->speed->x = newV1.x;
            this->explodingDisc->speed->y = newV1.y;
            against.explodingDisc->speed->x = newV2.x;
            against.explodingDisc->speed->y = newV2.y;
        } else if (against.shrinkingDisc != NULL) { //updating the speeds of a exploding disc and a shrinking disc
            Vector2D p1(this->explodingDisc->position->x, this->explodingDisc->position->y);
            Vector2D p2(against.shrinkingDisc->position->x, against.shrinkingDisc->position->y);
            Vector2D v1(this->explodingDisc->speed->x, this->explodingDisc->speed->y);
            Vector2D v2(against.shrinkingDisc->speed->x, against.shrinkingDisc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->explodingDisc->mass;
            double m2 = against.shrinkingDisc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->explodingDisc->speed->x = newV1.x;
            this->explodingDisc->speed->y = newV1.y;
            against.shrinkingDisc->speed->x = newV2.x;
            against.shrinkingDisc->speed->y = newV2.y;
        } else { //updating the speed of a exploding disc
            Vector2D p(this->explodingDisc->position->x, this->explodingDisc->position->y);
            Vector2D q = this->explodingDisc->position->closest_Point(*against.wall->left_border, *against.wall->right_border);
            Vector2D direction_vector = (p - q)/(p-q).norm();
            Vector2D v(this->explodingDisc->speed->x, this->explodingDisc->speed->y);
            *(this->explodingDisc->speed) = v - 2*((v.dotProduct(direction_vector))*direction_vector);
        }
    } else if (this->shrinkingDisc != NULL) {
        if (against.disc != NULL) { //updating the speeds of a shrinking disc and a normal disc
            Vector2D p1(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
            Vector2D p2(against.disc->position->x, against.disc->position->y);
            Vector2D v1(this->shrinkingDisc->speed->x, this->shrinkingDisc->speed->y);
            Vector2D v2(against.disc->speed->x, against.disc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->shrinkingDisc->mass;
            double m2 = against.disc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->shrinkingDisc->speed->x = newV1.x;
            this->shrinkingDisc->speed->y = newV1.y;
            against.disc->speed->x = newV2.x;
            against.disc->speed->y = newV2.y;
        } else if (against.explodingDisc != NULL) { //updating the speeds of a shrinking disc and a exploding disc
            Vector2D p1(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
            Vector2D p2(against.explodingDisc->position->x, against.explodingDisc->position->y);
            Vector2D v1(this->shrinkingDisc->speed->x, this->shrinkingDisc->speed->y);
            Vector2D v2(against.explodingDisc->speed->x, against.explodingDisc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->shrinkingDisc->mass;
            double m2 = against.explodingDisc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->shrinkingDisc->speed->x = newV1.x;
            this->shrinkingDisc->speed->y = newV1.y;
            against.explodingDisc->speed->x = newV2.x;
            against.explodingDisc->speed->y = newV2.y;
        } else if (against.shrinkingDisc != NULL) { //updating the speeds of two shrinking discs
            Vector2D p1(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
            Vector2D p2(against.shrinkingDisc->position->x, against.shrinkingDisc->position->y);
            Vector2D v1(this->shrinkingDisc->speed->x, this->shrinkingDisc->speed->y);
            Vector2D v2(against.shrinkingDisc->speed->x, against.shrinkingDisc->speed->y);
            Vector2D direction_vector = (p1 - p2)/(p1-p2).norm();
            Vector2D delta = ((v1-v2).dotProduct(direction_vector))*direction_vector;
            double m1 = this->shrinkingDisc->mass;
            double m2 = against.shrinkingDisc->mass;
            Vector2D newV1 = (v1 - ((2*m2)/(m1+m2))*delta);
            Vector2D newV2 = (v2 + ((2*m1)/(m1+m2))*delta);
            this->shrinkingDisc->speed->x = newV1.x;
            this->shrinkingDisc->speed->y = newV1.y;
            against.shrinkingDisc->speed->x = newV2.x;
            against.shrinkingDisc->speed->y = newV2.y;
        } else { //updating the speed of a shrinking disc
            Vector2D p(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
            Vector2D q = this->shrinkingDisc->position->closest_Point(*against.wall->left_border, *against.wall->right_border);
            Vector2D direction_vector = (p - q)/(p-q).norm();
            Vector2D v(this->shrinkingDisc->speed->x, this->shrinkingDisc->speed->y);
            *(this->shrinkingDisc->speed) = v - 2*((v.dotProduct(direction_vector))*direction_vector);
        }
    }
}

void YaelLinkedListNode::print() {
    if (this->disc != NULL) {
        this->disc->print();
    } else if (this->explodingDisc != NULL) {
        this->explodingDisc->print();
    } else if (this->shrinkingDisc != NULL) {
        this->shrinkingDisc->print();
    } else {
        this->wall->print();
    }
}
Vector2D YaelLinkedListNode::getPosition(){
    if(this->disc != NULL) {
        return Vector2D(this->disc->position->x, this->disc->position->y);
    } else if (this->explodingDisc != NULL) {
        return Vector2D(this->explodingDisc->position->x, this->explodingDisc->position->y);
    } else {
        return Vector2D(this->shrinkingDisc->position->x, this->shrinkingDisc->position->y);
    }
}
void YaelLinkedListNode::setPosition(double x, double y){
    if(this->disc != NULL) {
        this->disc->position->x = x;
        this->disc->position->y = y;
    } else if (this->explodingDisc != NULL) {
       this->explodingDisc->position->x = x;
       this->explodingDisc->position->y = y;
    } else {
       this->shrinkingDisc->position->x = x;
       this->shrinkingDisc->position->y = y;
    }
}
Vector2D YaelLinkedListNode::getSpeed(){
    if(this->disc != NULL) {
        return Vector2D(this->disc->speed->x, this->disc->speed->y);
    } else if (this->explodingDisc != NULL) {
        return Vector2D(this->explodingDisc->speed->x, this->explodingDisc->speed->y);
    } else {
        return Vector2D(this->shrinkingDisc->speed->x, this->shrinkingDisc->speed->y);
    }
}
void YaelLinkedListNode::setSpeed(double x, double y) {
    if(this->disc != NULL) {
        this->disc->speed->x = x;
        this->disc->speed->y = y;
    } else if (this->explodingDisc != NULL) {
        this->explodingDisc->speed->x = x;
        this->explodingDisc->speed->y = y;
    } else {
        this->shrinkingDisc->speed->x = x;
        this->shrinkingDisc->speed->y = y;
    }
}
void YaelLinkedListNode::updateClashedFlag(bool state) {
    if (this->disc != NULL) {
        this->disc->clashed = state;
    } else if (this->explodingDisc != NULL) {
        this->explodingDisc->clashed = state;
    } else {
        this->shrinkingDisc->clashed = state;
    }
}