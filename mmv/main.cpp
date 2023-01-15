#include <QCoreApplication>
#include "heightfield.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HeightField test = HeightField(0, 500, 0, 500, 500, 500);

    test.ReadImg("img.png");
    test.SaveAsImg("test1");

    test.fluidErosion();
    test.SaveAsImg("fluide");

    test.createRoadFromAtoB(20, 20, 60, 60);
    test.SaveAsImg("road");

    test.ReadImg("img.png");

    test.blur();
    test.SaveAsImg("blur1");

    //test.fillHeightWithPerlinNoise();
    //test.SaveAsImg("afterPerlin");

    test.thermiqueErosion();

    test.SaveAsImg("1erosion");
    std::cout << "save 1 erosions" << std::endl;

    for(int i=0; i<10; i++)
    {
        std::cout << i << std::endl;
        test.thermiqueErosion();
    }

    test.SaveAsImg("11erorion");
    std::cout << "save 11 erosions" << std::endl;


    //for(int i=0; i<100; i++)
    //{
    //    std::cout << i << std::endl;
    //    test.thermiqueErosion();
    //}

    //test.SaveAsImg("111erosion");
    //std::cout << "save 111 erosions" << std::endl;


    std::cout << "end" << std::endl;

    return a.exec();
}
