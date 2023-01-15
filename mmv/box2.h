#ifndef BOX2_H
#define BOX2_H

#include "vec2.h"

class Box2
{
public:
    Box2();
    Box2(double x_min, double x_max, double y_min, double y_max);
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    bool Inside(Vec2 vec2);
    bool Intersect(Box2 box2);
};

#endif // BOX2_H
