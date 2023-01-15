#include "vec2.h"

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(double m_x, double m_y)
{
    x = m_x;
    y = m_y;
}

Vec2 operator+(Vec2 a, Vec2 b)
{
    Vec2 res = Vec2(a.x + b.x, a.y + b.y);
    return res;
}
