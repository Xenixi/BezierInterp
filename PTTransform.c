#include "PTTransform.h"
// Calculate points on bezier curve fit to 3 initial points.

static Point2D *calculated2D = NULL;
static Point2D *genPts = NULL;
static Point2D *calculated2DCurve = NULL;

// Frees memory at pointer calculated2D
bool freeCalculated2D()
{
    if (calculated2D != NULL)
    {
        free(calculated2D);
        calculated2D = NULL;
        return 1;
    }

    return 0;
}

// Frees memory at pointer calculated2DCurve
bool freeCalculated2DCurve()
{
    if (calculated2DCurve != NULL)
    {
        free(calculated2DCurve);
        calculated2DCurve = NULL;
        return 1;
    }

    return 0;
}

// Frees memory at pointer genPts
bool freeGenPts()
{
    if (genPts != NULL)
    {
        free(genPts);
        genPts = NULL;
        return 1;
    }

    return 0;
}

// Frees all memory allocated in processing functions
bool freeAll()
{
    return freeCalculated2D && freeGenPts && freeCalculated2DCurve;
}

// Returns calculated2D pointer
Point2D *getCalculated2D(){
    return calculated2D;
}

// Returns calculated2DCurve pointer
Point2D *getCalculated2DCurve(){
    return calculated2DCurve;
}

// Returns genPts pointer
Point2D *getGenPts(){
    return genPts;
}

// 3-pt Bézier point interpolation for point posC. Curve fitting l (0<l<1). Returns Point2D and assigns pointer calculated2D to its address.
Point2D *interpolate2D(Point2D *p1, Point2D *p2, Point2D *p3, double l, double posC)
{

    // Create pointers to each ordinate
    double *x1, *x2, *x3;
    double *y1, *y2, *y3;

    x1 = &p1->x;
    x2 = &p2->x;
    x3 = &p3->x;

    y1 = &p1->y;
    y2 = &p2->y;
    y3 = &p3->y;

    // Calculate second control point from p2s
    double xMid;
    xMid = ((*x2) - (1.0 - l) * (1.0 - l) * (*x1) - l * l * (*x3));
    xMid /= (2.0 * (1.0 - l) * l);

    double yMid;
    yMid = ((*y2) - (1.0 - l) * (1.0 - l) * (*y1) - l * l * (*y3));
    yMid /= (2.0 * (1.0 - l) * l);

    // Calculate point at posC on the curve
    Point2D *fnlPt = malloc(sizeof(struct Point2D));

    fnlPt->x = ((1.0 - posC) * (1.0 - posC) * *x1) + (2.0 * (1.0 - posC) * posC * xMid) + (posC * posC * *x3);
    fnlPt->y = ((1.0 - posC) * (1.0 - posC) * *y1) + (2.0 * (1.0 - posC) * posC * yMid) + (posC * posC * *y3);

    free(calculated2D);
    calculated2D = fnlPt; // Points to last value in case it's needed later.
    return calculated2D;
}

// 3-pt Bézier multi-point interpolation for point posC. Curve fitting l (0<l<1). Returns array of Point2D and assigns pointer calculated2DCurve to its address.
Point2D *interpolate2DCurve(Point2D *p1, Point2D *p2, Point2D *p3, double l, int dataPts)
{
  
    Point2D *arCurve = malloc(sizeof(Point2D) * dataPts);

    for (int i = 0; i < dataPts; i++)
    {
        interpolate2D(p1, p2, p3, l, (double)(i+1.0)/dataPts);
        arCurve[i] = *calculated2D;
    }

    freeCalculated2DCurve();
    calculated2DCurve = arCurve;
    return arCurve;
}

// Generates array of 3 Point2D data structures. Returns the array and assigns pointer genPts to its starting address. 
Point2D *genPointSet(double x1, double y1, double x2, double y2, double x3, double y3)
{
    Point2D *pts = malloc(sizeof(Point2D) * 3);

    pts[0].x = x1;
    pts[0].y = y1;
    pts[1].x = x2;
    pts[1].y = y2;
    pts[2].x = x3;
    pts[2].y = y3;

    freeGenPts();
    genPts = pts;
    return pts;
}

// Writes 2-column csv file with specified x and y labels. 
void writeCSV(FILE *filePtr, char *xLabel, char *yLabel, Point2D *pointArray, int pointArrayLength)
{
    
    fprintf(filePtr, "%s%s%s%s", xLabel, ",", yLabel, "\n");

    for (int i = 0; i < pointArrayLength; i++)
    {
        fprintf(filePtr, "%f,%f\n", pointArray[i].x, pointArray[i].y);
        
    }

    fclose(filePtr);
}

