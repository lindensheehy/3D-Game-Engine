/*
    Note: Im very aware that there are several libraries which have most if not all of these functions, but I wanted to write it myself
*/

#include <cmath>

#include "math.h"


double inRange(double num, double from, double to) {
    if ( (num >= from) && (num <= to) )
        return ( (num - from) / (to - from) );
    return -1;
}

double outRange(double num, double from, double to) {
    /*
        Function is similar to inRange, but it allows values to be outside the range and will return a value accordingly.
        Will return a value between 0-1 if the num is in the range, and can be bigger or smaller depending how far outside the range is lies
    */

    return -1;

}

void swap(int* var1, int* var2) {
    int temp = *var1;
    *var1 = *var2;
    *var2 = temp;
    return;
}

double quickArctan(double x) {
    // Returns degrees

    double a = 90;
    double b = 0.3;

    // a * (bx / sqrt(1 + (bx)^2))
    return (a * ( (b * x) / sqrt(1 + ((b * x) * (b * x)) ) ));
}

double getAngle(double x1, double y1, double x2 /* default value = 0 */, double y2 /* default value = 0 */) {
    /*
        Returns the angle made between the y axis and (x1, y1) relative to (x2, y2)
        so this means that the 'y-axis' will be shifted to one side depending on where x2 lies
    */

    // If the x coordinates are the same, the point is either right above, below or on top of the other
    if (x1 == x2) {
        if (y1 >= y2) return 0;
        return 180;
    }

    if (y1 == y2) {
        if (x1 >= x2) return 90;
        return 270;
    }

    double angle;
    if (x1 != x2) {
        double m = abs( (x1 - x2) / (y1 - y2) );
        angle = toDegrees(atan(m));
    } else
        angle = 0;

    // Adjust angle based on quadrant
    if (y1 < y2) angle = (double) 180 - angle;
    if (x1 < x2) angle = (double) 360 - angle;

    return angle;

}