#ifndef GRILLE_H
#define GRILLE_H

#include "box2.h"

class Grille : public Box2
{
public:
    Grille();
    Grille(double x_min, double x_max, double y_min, double y_max, int x_n, int y_n);
    double x_step, y_step;
    int x_n, y_n;
    int Index(int i, int j);
    bool Inside(int i, int j);
};

#endif // GRILLE_H
