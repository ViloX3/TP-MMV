#include "box2.h"

Box2::Box2()
{
    x_min = 0;
    x_max = 0;
    y_min = 0;
    y_max = 0;
}

Box2::Box2(double m_x_min, double m_x_max, double m_y_min, double m_y_max)
{
    x_min = m_x_min;
    x_max = m_x_max;
    y_min = m_y_min;
    y_max = m_y_max;
}

bool Box2::Inside(Vec2 vec2)
{
    if(x_min <= vec2.x && vec2.x <= x_max && y_min <= vec2.y && vec2.y <= y_max)
    {
        return true;
    }
    return false;
}


bool Box2::Intersect(Box2 box2)
{
    Vec2 vecTestSommet = Vec2();
    vecTestSommet.x = box2.x_min;
    vecTestSommet.y = box2.y_min;
    if(Inside(vecTestSommet))
    {
        return true;
    }
    vecTestSommet.y = box2.y_max;
    if(Inside(vecTestSommet))
    {
        return true;
    }
    vecTestSommet.x = box2.x_max;
    if(Inside(vecTestSommet))
    {
        return true;
    }
    vecTestSommet.y = box2.y_min;
    if(Inside(vecTestSommet))
    {
        return true;
    }
    return false;
}
