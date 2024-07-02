/*
    Note: Im very aware that there are several libraries which have most of, if not all, of these functions, but I wanted to write it myself
          There are more function definitions in the header file (math.h), becuase they are inline functions
*/

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

double arctan(double x) {
    /*
        Returns radians
        This function is sort of complicated so heres the breakdown:

        1. This way of calculating only works if the value of x is in (-1, 1)
           If the value is outside that range, 1/x is used instead and the angle is given as (pi/2 - found angle)

        2. Im using powere series to calculate the angle, but for performance im only using the first 5 terms.
           This series is accurate until around |x| > 0.76

        3. When the value is outside that range, I am using linear functions which closely fit the graph of arctan
           I used desmos to find these functions and fine tuned the values, so they may seem arbitrary

        This method gives at most a 0.5% error, with the majority of inputs giving less than 0.05% error
        This function does not need to be perfectly accurate, so I am choosing to optimize performance over accuracy
    */

    double value = x;
    bool inverseFlag = false;

    // Fix value if its outside (-1, 1)
    if (abs(x) > 1) {
        value = 1 / value;
        inverseFlag = true;
    }

    // Linear Functions for values outside (-0.76, 0.76)
    if (value < -0.76) {
        return (0.55 * x) - 0.235;
    }

    if (value > 0.76) {
        return (0.55 * x) + 0.235;
    }

    // Power series for values inside (-0.76, 0.76)
    double returnValue = x;

    // Just defining these here for readability
    double xExp3 = x * x * x;
    double xExp5 = xExp3 * x * x;
    double xExp7 = xExp5 * x * x;
    double xExp9 = xExp7 * x * x;

    returnValue -= (xExp3) / 3;
    returnValue += (xExp5) / 5;
    returnValue -= (xExp7) / 7;
    returnValue += (xExp9) / 9;

    return returnValue;

}

double getAngle(double x1, double y1, double x2 /* default value = 0 */, double y2 /* default value = 0 */) {
    /*
        Returns the angle made between the y axis and (x1, y1) relative to (x2, y2)
        so this means that the 'y-axis' will be shifted to one side depending on where x2 lies
    */

    // If the x coordinates are the same, the point is either right above, below or on top of the other
    if (x1 == x2) {
        if (y1 >= y2) return 0;
        return pi;
    }

    if (y1 == y2) {
        if (x1 >= x2) return pi / 2;
        return (3 / 2) * pi;
    }

    double angle;
    if (x1 != x2) {
        double m = abs( (x1 - x2) / (y1 - y2) );
        angle = arctan(m);
    } else
        angle = 0;

    // Adjust angle based on quadrant
    if (y1 < y2) angle = pi - angle;
    if (x1 < x2) angle = (2 * pi) - angle;

    return angle;

}