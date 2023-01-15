#include "scalarfield.h"
#include <QtGui/QImage>
#include <QString>>
#include <iostream>>


ScalarField::ScalarField() : Grille()
{
    height = std::vector<double>(0);
    roadFromAtoB = std::vector<int>(0);
}

ScalarField::ScalarField(double x_min, double x_max, double y_min, double y_max, int x_n, int y_n) : Grille(x_min, x_max, y_min, y_max, x_n, y_n)
{
    height = std::vector<double>(x_n*y_n);
    roadFromAtoB = std::vector<int>(0);
}


double ScalarField::maxHeight()
{
    double value = 0;
    double max = 0;
    for(int i=0; i<x_n; i++)
    {
        for(int j=0; j<y_n; j++)
        {
            value = height[Index(i, j)];
            if(value > max)
            {
                max = value;
            }
        }
    }
    return max;
}


void ScalarField::SaveAsImg(QString fileName)
{
    fileName+=".png";
    QImage image(y_n, x_n, QImage::Format_Grayscale8);
    //double maxH = maxHeight();
    double value = 0;

    for (int y = 0; y < y_n; y++) {
        for (int x = 0; x < x_n; x++) {
            value = height[Index(x, y)];
            image.setPixel(y, x, value);
        }
    }

    for(int i=0; i<roadFromAtoB.size(); i++)
    {
        int x = roadFromAtoB[i]/y_n;
        int y = roadFromAtoB[i]%y_n;
        value = height[roadFromAtoB[i]];
        image.setPixel(y, x, 0);
    }

    image.save(fileName, "PNG");
}

void ScalarField::ReadImg(QString fileName)
{
    QImage image;
    if(image.load(fileName)){
        std::cout << "loaded" << std::endl;;
    }
    image.convertTo(QImage::Format_Grayscale8);
    x_n = image.height();
    y_n = image.width();
    x_min = 0;
    y_min = 0;
    x_max = x_n-1;
    y_max = y_n-1;
    height = std::vector<double>(x_n*y_n);
    x_step = (x_max-x_min)/x_n;
    y_step = (y_max-y_min)/y_n;
    for(int i=0; i<x_n; i++)
    {
        for(int j=0; j<y_n; j++)
        {
            height[Index(i, j)] = image.pixel(j,i);
        }
    }
    image.save("currentImg.png", "PNG");
}



void ScalarField::blur() {
    std::vector<double> height_bis = height;
    for (int i = 1; i < x_n - 1; i++) {
        for (int j = 1; j < y_n - 1; j++) {
            height[i * y_n + j] =
                    (height_bis[i * y_n + j] + height_bis[(i + 1) * y_n + j] + height_bis[(i - 1) * y_n + j] +
                     height_bis[i * y_n + j + 1] + height_bis[(i + 1) * y_n + j + 1] +
                     height_bis[(i - 1) * y_n + j + 1] + height_bis[i * y_n + j - 1] +
                     height_bis[(i + 1) * y_n + j - 1] + height_bis[(i - 1) * y_n + j - 1]) / 9;
        }
    }
}

float ScalarField::Laplacien(int i, int j)
{
    float l = 0;
    if(i>0) l += height[i*y_n+j] - height[(i-1)*y_n+j];
    if(i<x_n-1) l += height[i*y_n+j] - height[(i+1)*y_n+j];
    if(j>0) l += height[i*y_n+j] - height[i*y_n+j-1];
    if(j<y_n-1) l += height[i*y_n+j] - height[i*y_n+j+1];
    l /= pow(x_step, 2);
    return l;
}

Vec2 ScalarField::Gradient(int i, int j)
{
    Vec2 grad = Vec2();
    if(i>0){
        if(i<x_n-1){
           grad.x = (height[(i+1)*y_n+j]-height[(i-1)*y_n+j])/(2*x_n);
        }
        else{
            grad.x = (height[i*y_n+j]-height[(i-1)*y_n+j])/(x_n);
        }
    }
    else{
        grad.x = (height[(i+1)*y_n+j]-height[(i)*y_n+j])/(x_n);
    }

    if(j>0){
        if(j<y_n-1){
            grad.y = (height[i*y_n+j+1]-height[i*y_n+j-1])/(2*y_n);
        }
        else{
            grad.y = (height[i*y_n+j]-height[i*y_n+j-1])/(y_n);
        }
    }
    else{
        grad.y = (height[i*y_n+j+1]-height[i*y_n+j])/(y_n);
    }
    return grad;
}
