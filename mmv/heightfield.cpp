#include "heightfield.h"


HeightField::HeightField() : ScalarField() {}

HeightField::HeightField(double x_min, double x_max, double y_min, double y_max, int x_n, int y_n) : ScalarField(x_min, x_max, y_min, y_max, x_n, y_n) {}

double HeightField::hillSlopErosion(int i, int j)
{
    double l = 0.8;
    return l*Laplacien(i,j);
}

double HeightField::tectErosion(int i, int j)
{
    double uplift = 3;
    return uplift - hillSlopErosion(i, j) - Laplacien(i, j);
}


std::vector<double> HeightField::slopes(int i, int j)
{

    std::vector<double> slope = std::vector<double>(8);
    if(i>0 && i<x_max-1 && j>0 && j<y_max-1)
    {
        double currentH = height[Index(i, j)];

        std::vector<int> indexs = std::vector<int>(8);
        indexs[0] = Index(i-1,j-1);
        indexs[1] = Index(i-1,j);
        indexs[2] = Index(i-1,j+1);
        indexs[3] = Index(i,j-1);
        indexs[4] = Index(i,j+1);
        indexs[5] = Index(i+1,j-1);
        indexs[6] = Index(i+1,j);
        indexs[7] = Index(i+1,j+1);


        for(int i = 0; i<8; i++)
        {
            double HeightI = height[indexs[i]];
            slope[i] = HeightI - currentH;
        }

        slope[0] = slope[0]/sqrt(x_step*x_step+y_step*y_step);
        slope[1] = slope[1]/(y_step);
        slope[2] = slope[2]/sqrt(x_step*x_step+y_step*y_step);
        slope[3] = slope[3]/(x_step);
        slope[4] = slope[4]/(x_step);
        slope[5] = slope[5]/sqrt(x_step*x_step+y_step*y_step);
        slope[6] = slope[6]/(y_step);
        slope[7] = slope[7]/sqrt(x_step*x_step+y_step*y_step);
    }
    return slope;
}

double HeightField::matToWithdraw(int i, int j, double theta)
{
    double withdraw = 0;
    double currentH = height[Index(i, j)];
    if(i>0 && i<x_max-1 && j>0 && j<y_max-1)
    {
        withdraw = currentH - height[Index(i-1,j-1)] - sqrt(x_step*x_step+y_step*y_step)/std::tan(theta);

        double withdraw2 = currentH - height[Index(i-1,j)] - y_step/std::tan(theta);
        if(withdraw2 < withdraw && 0<withdraw2)
        {
            withdraw = withdraw2;
        }

        withdraw2 = currentH - height[Index(i-1,j+1)] - sqrt(x_step*x_step+y_step*y_step)/std::tan(theta);
        if(withdraw2 < withdraw && 0<withdraw2)
        {
            withdraw = withdraw2;
        }

        withdraw2 = currentH - height[Index(i,j-1)] - x_step/std::tan(theta);
        if(withdraw2 < withdraw && 0<withdraw2)
        {
            withdraw = withdraw2;
        }

        withdraw2 = currentH - height[Index(i,j+1)] - x_step/std::tan(theta);
        if(withdraw2 < withdraw && 0<withdraw2)
        {
            withdraw = withdraw2;
        }

        withdraw2 = currentH - height[Index(i+1,j-1)] - sqrt(x_step*x_step+y_step*y_step)/std::tan(theta);
        if(withdraw2 < withdraw && 0<withdraw2)
        {
            withdraw = withdraw2;
        }

        withdraw2 = currentH - height[Index(i+1,j)] - y_step/std::tan(theta);
        if(withdraw2 < withdraw && 0<withdraw2)
        {
            withdraw = withdraw2;
        }

        withdraw2 = currentH - height[Index(i+1,j+11)] - sqrt(x_step*x_step+y_step*y_step)/std::tan(theta);
        if(withdraw2 < withdraw && 0<withdraw2)
        {
            withdraw = withdraw2;
        }

    }
    return withdraw;
}

void HeightField::TErosionPoint(int i, int j)
{
    double theta = 3.14/180. * 30.;
    int index = Index(i, j);
    double numberAdj = 0;
    std::vector<double> slope = slopes(i, j);
    double withdraw = matToWithdraw(i, j, theta);

    for(int i0=0; i0<8; i0++)
    {
        if(slope[i0] < -std::tan(theta))
        {
            numberAdj += slope[i0];
        }
    }

    for(int i0=0; i0<8; i0++)
    {
        if(slope[i0] < -std::tan(theta))
        {
            // le fait de ne pas inclure le point central dans slopes fait qu'il faut séparer la formule pour l'aglorithme en deux
            if(i0<4)
            {
                height[Index(i-1+i0/3,j-1+i0%3)] += withdraw*slope[i0]/numberAdj;
            }
            else
            {
                height[Index(i-1+(i0+1)/3,j+(i0+1)%3)] += withdraw*slope[i0]/numberAdj;
            }
        }
    }
}

void HeightField::thermiqueErosion()
{
    std::vector<int> indexSortedByHeightVector = mergeSortForHeight();
    for(int index=0; index<height.size(); index++)
    {
        int currentIndex = indexSortedByHeightVector[index];
        int i = currentIndex/y_n;
        int j = currentIndex%y_n;
        TErosionPoint(i, j);
    }
}


void HeightField::createRoadFromAtoB(int i1, int j1, int i2, int j2)
{
    std::cout << "test"<< std::endl;
    std::vector<int> pileTraj;
    std::vector<double> couts = std::vector<double>(x_n*y_n, -1);
    couts[Index(i1,j1)] = 0;
    pileTraj.push_back(Index(i1, j1));

    int valBox = 0;
    int imin = std::min(i1-valBox, i2-valBox);
    int jmin = std::min(j1-valBox, j2-valBox);
    int imax = std::max(i1+valBox, i2+valBox);
    int jmax = std::max(j1+valBox, j2+valBox);

    //remplissage de la matrice des couts
    while(pileTraj.size()>0)
    {
        std::cout << "first " << pileTraj.size()<< std::endl;
        int index = pileTraj.back();
        pileTraj.pop_back();
        int i = index/y_n;
        int j = index%y_n;
        std::vector<double> fullSlopes = slopes(i, j);
        if(imin < i && i < imax && jmin < j && j < jmax)
        {
            for(int k=0; k<fullSlopes.size(); k++)
            {
                int currentIndex = 0;
                double distance = 0;
                // le fait de ne pas inclure le point central dans slopes fait qu'il faut séparer la formule pour l'aglorithme en deux
                if(k<4)
                {

                    currentIndex = Index(i-1+k/3,j-1+k%3);
                }
                else
                {
                    currentIndex = Index(i-1+(k+1)/3,j+(k+1)%3);
                }
                if(k == 1 || k == 6)
                {
                    distance = y_step;
                }
                else
                {
                    if(k == 3 || k == 4)
                    {
                        distance = x_step;
                    }
                    else
                    {
                        distance = sqrt(x_step*x_step+y_step*y_step);
                    }
                }

                double currentCost = abs(fullSlopes[k])+couts[Index(i,j)]+distance;

                if(couts[currentIndex]==-1)
                {
                    couts[currentIndex] = currentCost;
                    pileTraj.push_back(currentIndex);
                }
                else
                {
                    if(currentCost<couts[currentIndex])
                    {
                        couts[currentIndex] = currentCost;
                        if (std::find(pileTraj.begin(), pileTraj.end(), currentIndex) == pileTraj.end())
                        {
                                pileTraj.push_back(currentIndex);
                        }
                    }
                }
            }
        }
    }

    // recherche du plus court chemin étant donné la matrice des coûts
    roadFromAtoB.push_back(Index(i2, j2));
    while(roadFromAtoB.back() != Index(i1, j1))
    {
        int index = roadFromAtoB.back();
        std::cout << "second " << index << std::endl;
        int i = index/y_n;
        int j = index%y_n;
        double cost = couts[index];
        std::vector<double> fullSlopes = slopes(i, j);
        int nextIndex = 0;
        for(int k=0; k<fullSlopes.size(); k++)
        {
            int currentIndex = 0;
            double distance = 0;
            // le fait de ne pas inclure le point central dans slopes fait qu'il faut séparer la formule pour l'aglorithme en deux
            if(k<4)
            {

                currentIndex = Index(i-1+k/3,j-1+k%3);
            }
            else
            {
                currentIndex = Index(i-1+(k+1)/3,j+(k+1)%3);
            }
            if(k == 1 || k == 6)
            {
                distance = y_step;
            }
            else
            {
                if(k == 3 || k == 4)
                {
                    distance = x_step;
                }
                else
                {
                    distance = sqrt(x_step*x_step+y_step*y_step);
                }
            }

            double currentCost = abs(fullSlopes[k])+couts[Index(i,j)]+distance;

            if(cost-couts[currentIndex]==currentCost)
            {
                nextIndex = currentIndex;
            }
        }
        roadFromAtoB.push_back(nextIndex);
        if(index == roadFromAtoB.back())
        {
            return;
        }
    }
}

// Function to merge two sorted vectors
void HeightField::merge(std::vector<int>& arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    // Create temp vectors
    std::vector<int> L(n1), R(n2);

    // Copy data to temp vectors L and R
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp vectors back into arr
    i = 0; // Initial index of first vector
    j = 0; // Initial index of second vector
    k = l; // Initial index of merged vector
    while (i < n1 && j < n2)
    {
        if (height[L[i]] <= height[R[j]])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L, if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R, if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to sort a vector using Tri Fusion
void HeightField::mergeSort(std::vector<int>& arr, int l, int r)
{
    if (l < r)
    {
        // Find the middle point
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

std::vector<int> HeightField::mergeSortForHeight()
{
    std::vector<int> arr;
    for(int i = 0; i< height.size(); i++)
    {
        arr.push_back(i);
    }

    mergeSort(arr, 0, height.size()-1);

    return arr;
}

void HeightField::fluidErosion()
{
    std::vector<double> heightBis;
    for(int index=0; index<height.size(); index++)
    {
        heightBis.push_back(height[index]);
    }
    std::vector<double> drain;
    std::vector<int> indexSortedByHeightVector = mergeSortForHeight();
    double uplift = 0;
    calculateDrainage(drain, indexSortedByHeightVector);
    for(int k=0; k< indexSortedByHeightVector.size(); k++)
    {
        int index = indexSortedByHeightVector[k];
        int i = index/y_n;
        int j = index%y_n;
        heightBis[index] += streamPowerErosion(i, j, drain) + uplift - Laplacien(i, j);
    }
    for(int index=0; index<height.size(); index++)
    {
        height[index] = heightBis[index];
    }
}

double HeightField::streamPowerErosion(int i, int j, std::vector<double> &drain)
{
    int index = Index(i, j);
    double k = 0.8;

    std::vector<double> fullSlopes = slopes(i, j);
    double slope = 0;
    for(int i=0; i<8; i++)
    {
        slope += fullSlopes[i];
    }
    return -k*slope*drain[index];
}


void HeightField::calculateDrainage(std::vector<double> &drain, std::vector<int> &indexSortedByHeightVector)
{
    drain = std::vector<double>(x_n*y_n, 1);
    //std::vector<int> indexSortedByHeightVector = mergeSortForHeight();

    // after sorted the index by height, calculate the area drainage
    for(int index=0; index<height.size(); index++)
    {
        int currentIndex = indexSortedByHeightVector[index];
        int i = currentIndex/y_n;
        int j = currentIndex%y_n;

        double currentH = height[currentIndex];
        std::vector<double> neighborsHeight = slopes(i, j);

        // std::vector<int> neighbors = std::vector<int>(9, -1);

        // if(currentIndex>=a)
        // {
        //     neighbors[1] = currentH-height[currentIndex-a];
        //     if(currentIndex % a > 0)
        //     {
        //         neighbors[0] = currentH-height[currentIndex-a-1];
        //     }
        //     if(currentIndex % a < b)
        //     {
        //         neighbors[2] = currentH-height[currentIndex-a+1];
        //     }
        // }
        // if(currentIndex % a > 0)
        // {
        //     neighbors[3] = currentH-height[currentIndex-a];
        // }
        // if(currentIndex % a < b)
        // {
        //     neighbors[5] = currentH-height[currentIndex-a];
        // }
        // if(currentIndex<=a*b-1)
        // {
        //     neighbors[7] = currentH-height[currentIndex+a];
        //     if(currentIndex % a > 0)
        //     {
        //         neighbors[6] = currentH-height[currentIndex+a-1];
        //     }
        //     if(currentIndex % a < b)
        //     {
        //         neighbors[8] = currentH-height[currentIndex+a+1];
        //     }
        // }
        double sum = 0;
        for(int i = 0; i<8; i++)
        {
            if(neighborsHeight[i]>0)
            {
                sum += pow(neighborsHeight[i],2);
            }
        }
        for(int i = 0; i<8; i++)
        {
            if(neighborsHeight[i]>0)
            {
                drain[currentIndex+(i%3-1)*x_n+(i-i%3*3-1)] += pow(neighborsHeight[i],2)/sum;
            }
        }

    }

}




void HeightField::fillHeightWithPerlinNoise()
{
    const int TABLE_SIZE = x_max*y_max;
    std::vector<int> permutationTable = std::vector<int>(TABLE_SIZE);
    std::vector<double> gradientTable = std::vector<double>(TABLE_SIZE);
    std::cout << "init perlin noise" << std::endl;
    initPerlinNoise(TABLE_SIZE, permutationTable, gradientTable);
    std::cout << "end init perlin noise" << std::endl;
    for(int i=0; i<x_max; i++)
    {
        std::cout << i << std::endl;
        for(int j=0; j<y_max; j++)
        {
            height[Index(i, j)] = perlinNoise(i, j, permutationTable, gradientTable);
        }
    }
}



// Fonction qui initialise les tables de permutation et de gradient
void HeightField::initPerlinNoise(int TABLE_SIZE, std::vector<int>& permutationTable, std::vector<double>& gradientTable) {

    // Remplissage de la table de permutation avec des valeurs aléatoires
    for (int i = 0; i < TABLE_SIZE; i++) {
        permutationTable[i] = i;
    }


    // Mélange des valeurs de la table de permutation
    for (int i = 0; i < TABLE_SIZE; i++) {
        int j = rand() % TABLE_SIZE;
        int temp = permutationTable[i];
        permutationTable[i] = permutationTable[j];
        permutationTable[j] = temp;
    }


    // Remplissage de la table de gradient avec des vecteurs unitaires aléatoires
    for (int i = 0; i < TABLE_SIZE; i++) {
        double angle = 2 * M_PI * rand() / RAND_MAX;
        gradientTable[i] = cos(angle);
    }
}

// Fonction qui calcule le bruit de Perlin en un point (x, y)
double HeightField::perlinNoise(double x, double y, std::vector<int> permutationTable, std::vector<double> gradientTable) {
    // Calcul des indices des cellules de grille qui entourent le point (x, y)
    int x0 = (int)floor(x);
    int y0 = (int)floor(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Calcul des vecteurs de gradient associés aux quatre coins de la cellule de grille
    double n00 = gradientTable[permutationTable[permutationTable[x0] + y0]];
    double n01 = gradientTable[permutationTable[permutationTable[x0] + y1]];
    double n10 = gradientTable[permutationTable[permutationTable[x1] + y0]];
    double n11 = gradientTable[permutationTable[permutationTable[x1] + y1]];

    // Calcul des coefficients de lissage
    double sx = x - x0;
    double sy = y - y0;
    double u = sx * sx * (3 - 2 * sx);
    double v = sy * sy * (3 - 2 * sy);

    // Calcul du bruit de Perlin en utilisant les coefficients de lissage et les vecteurs de gradient
    double nx0 = n00 + u * (n10 - n00);
    double nx1 = n01 + u * (n11 - n01);

    // Calcul du bruit de Perlin en un point (x, y)
    return nx0 + v * (nx1 - nx0);
}


void HeightField::save2DArrayToOBJ(std::vector<std::vector<int>>& array, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
      std::cerr << "Error opening file\n";
      return;
    }

    for (const auto& row : array) {
      for (const auto& element : row) {
        file << "v " << element << '\n';
      }
    }

    file << "# " << array.size() << "x" << array[0].size() << '\n';
    file.close();
  }
