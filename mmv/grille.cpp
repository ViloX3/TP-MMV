#include "grille.h"

Grille::Grille() : Box2(), x_n(0), y_n(0), x_step(0), y_step(0) {}

Grille::Grille(double x_min, double x_max, double y_min, double y_max, int x_n, int y_n) : Box2(x_min, x_max, y_min, y_max), x_n(x_n), y_n(y_n)
{
    x_step = (x_max-x_min)/x_n;
    y_step = (y_max-y_min)/y_n;
}

int Grille::Index(int i, int j)
{
    return i*y_n + j;
}

bool Grille::Inside(int i, int j)
{
    if(i>=0 && i<x_n && j>=0 && j<y_n)
    {
        return true;
    }
    return false;
}
