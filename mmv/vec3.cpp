#include "vec3.h"

Vec3::Vec3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vec3::Vec3(double m_x, double m_y, double m_z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

Vec3 operator+(Vec3 a, Vec3 b)
{
    Vec3 res = Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
    return res;
}
