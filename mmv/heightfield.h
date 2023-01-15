#ifndef HEIGHTFIELD_H
#define HEIGHTFIELD_H

#include "scalarfield.h"
#include <cmath>
#include <fstream>
#include <iostream>

class HeightField : public ScalarField
{
public:
    HeightField();
    HeightField(double x_min, double x_max, double y_min, double y_max, int x_n, int y_n);

    void thermiqueErosion();
    void TErosionPoint(int i, int j);

    double hillSlopErosion(int i, int j);
    double tectErosion(int i, int j);

    std::vector<int> mergeSortForHeight();

    void fillHeightWithPerlinNoise();

    void save2DArrayToOBJ(std::vector<std::vector<int>>& array, const std::string& filename);

    std::vector<double> slopes(int i, int j);

    void createRoadFromAtoB(int i1, int j1, int i2, int j2);

    void calculateDrainage(std::vector<double> &drain, std::vector<int> &indexSortedByHeightVector);

    double streamPowerErosion(int i, int j, std::vector<double> &drain);

    void fluidErosion();

private:
    void merge(std::vector<int>& arr, int l, int m, int r);
    void mergeSort(std::vector<int>& arr, int l, int r);
    double matToWithdraw(int i, int j, double theta);

    void initPerlinNoise(int TABLE_SIZE, std::vector<int>& permutationTable, std::vector<double>& gradientTable);
    double perlinNoise(double x, double y, std::vector<int> permutationTable, std::vector<double> gradientTable);
};

#endif // HEIGHTFIELD_H
