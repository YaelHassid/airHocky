#include "ShrinkingDisc.h"

ShrinkingDisc::ShrinkingDisc(double x, double y, double vx, double vy, double radius) : Disc(x, y, vx, vy, radius) {
    this->clashCounter = 0;
}