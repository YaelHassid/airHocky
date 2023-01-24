#ifndef AIRHOCKEY_YAELLINKEDLISTNODE_H
#define AIRHOCKEY_YAELLINKEDLISTNODE_H
#include <iostream>
#include "Disc.h"
#include "Wall.h"
#include "ShrinkingDisc.h"

class ExplodingDisc;
class YaelLinkedListNode;
struct Triplet {
    YaelLinkedListNode *child_one;
    YaelLinkedListNode *child_two;
    YaelLinkedListNode *child_three;
};
class YaelLinkedListNode {
public:
    Disc* disc;
    ExplodingDisc* explodingDisc;
    ShrinkingDisc* shrinkingDisc;
    Wall* wall;
    void init();
    Vector2D getPosition();
    void setPosition(double x, double y);
    Vector2D getSpeed();
    void setSpeed(double x, double y);
    YaelLinkedListNode(double x, double y, double vx, double vy, double radius, int type);
    YaelLinkedListNode(double x1, double y1, double x2, double y2);
    ~YaelLinkedListNode();
    bool check_collision(YaelLinkedListNode* other) const;
    void update_collision_speed(YaelLinkedListNode &against);
    YaelLinkedListNode* next;
    void print();
    void updateClashedFlag(bool state);
};



#endif //AIRHOCKEY_YAELLINKEDLISTNODE_H
