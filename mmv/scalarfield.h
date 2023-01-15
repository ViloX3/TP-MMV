#ifndef SCALARFIELD_H
#define SCALARFIELD_H

#include "grille.h"
#include <vector>
#include <QString>

class ScalarField : public Grille
{
public:
    ScalarField();

    ScalarField(double x_min, double x_max, double y_min, double y_max, int x_n, int y_n);

    std::vector<double> height;

    std::vector<int> roadFromAtoB;

    void blur();

    void SaveAsImg(QString filename);

    void ReadImg(QString Filename);

    float Laplacien(int i, int j);

    Vec2 Gradient(int i, int j);

protected:
    double maxHeight();
};

#endif // SCALARFIELD_H
