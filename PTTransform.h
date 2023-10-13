#ifndef PTTH
#define PTTH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Point struct 2D
struct Point2D
{
    double x, y;
};


typedef struct Point2D Point2D;


// Frees memory at pointer calculated2D
bool freeCalculated2D();

// Frees memory at pointer calculated2DCurve
bool freeCalculated2DCurve();

// Frees memory at pointer genPts
bool freeGenPts();

// Frees all memory allocated in processing functions
bool freeAll();

// Returns calculated2D pointer
Point2D *getCalculated2D();

// Returns calculated2DCurve pointer
Point2D *getCalculated2DCurve();

// Returns genPts pointer
Point2D *getGenPts();

// 3-pt Bézier point interpolation for point posC. Curve fitting l (0<l<1). Returns Point2D and assigns pointer calculated2D to its address.
Point2D *interpolate2D(Point2D *p1, Point2D *p2, Point2D *p3, double l, double posC);

// 3-pt Bézier multi-point interpolation for point posC. Curve fitting l (0<l<1). Returns array of Point2D and assigns pointer calculated2DCurve to its address.
Point2D *interpolate2DCurve(Point2D *p1, Point2D *p2, Point2D *p3, double l, double posC, int dataPts);

// Generates array of 3 Point2D data structures. Returns the array and assigns pointer genPts to its starting address. 
Point2D *genPointSet(double x1, double y1, double x2, double y2, double x3, double y3);

// Writes 2-column csv file with specified x and y labels. 
void writeCSV(FILE *filePtr, char *xLabel, char *yLabel, Point2D **pointArray, int pointArrayLength);

#endif