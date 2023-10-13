#include "PTTransform.h"

int main()
{

    genPointSet(3.0, 4.0, 7.0, 13.0, 15.0, 2.0);

    interpolate2D(&getGenPts()[0], &getGenPts()[1], &getGenPts()[2], 0.5, 1.0);


    printf("%f,%f", getCalculated2D()->x, getCalculated2D()->y);

    freeAll();
}