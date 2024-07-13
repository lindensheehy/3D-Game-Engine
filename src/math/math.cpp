/*
    Note: Im very aware that there are several libraries which have most of, if not all, of these functions, but I wanted to write it myself
          There are more function definitions in the header file (math.h), becuase they are inline functions
*/

#include "math.h"


/*   -----   Basic Functions   -----   */
double abs_(double x) {
    return (x > 0) ? x : -x;
}

int floor(double x) {
    /*
        Type casting is used to truncate the fractional part of the value

        For negative number this returns floor(x) + 1
        So those cases are handled
    */

    int returnValue = (int) x;

    if (x < 0 && x != returnValue) returnValue--;   
    
    return returnValue;

}

int round(double x) {
    /*
        This just calls floor(x + 0.5)
        This does the same thing as rounding to 0 decimal points
        Rounding to more decimal points is not supported
    */

    double y = x + 0.5;
    return floor(y);

}

/*   -----   sqrt   -----   */
double sqrt(double x, double tolerance) {
    /*
        This function makes use of the Newton Raphson method to find the sqrt of x as follows:

        let     x = the input value
                y_n = the nth approximation of sqrt(x)
                f(y) = y^2 + x
                f'(y) = 2y

                        f(y_n)
        y_n+1 = y_n - -----------
                        f'(y_n)

          f(y_n)       1    (         x    )
        ----------- = --- * ( y_n + -----  )
          f'(y_n)      2    (        y_n   )

        Therefore y_n+1 = y_n - 0.5*(y_n + x/y_n)

        This solves for sqrt(x) as the root of f(y).

        The Newton Raphson method repeats over several iterations to approximate the value of sqrt(x)
        When the value is only changed by the designated tolerance (0.001 by default) on a given iteration, the function ends and the value is returned.
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (x < 0) {
        logWrite("Called sqrt(double) on a negative value!", true);
        return -1;
    }

    // Zero input
    if (x == 0) return 0;

    // This will break the loop after a set number of iterations
    int maxIterations = 4;

    // Newton Raphson method
    double y = x;
    double yNext = 0;

    while (true) {

        if (maxIterations == 0) return y;
        else maxIterations--;

        yNext = y - (0.5 * (y + (x / y)));

        // Break case
        if (abs(y - yNext) < tolerance) return yNext;

        y = yNext;

    }

}


/*   --------------------------   */
/*   ---   Trig Functions   ---   */
/*   --------------------------   */

double sin(double x) {
    /*
        Uses radians
        This function uses the power series defined for sin(x) as

              x^3     x^5
        x -  ----- + ----- - ...
               3!      5!

        This function uses the first 5 terms. as this gives at most an error of 0.007 ( making 0.35% on a range of (-1, 1) ) for values inside (-pi, pi)
        In interest of performance, I will not add more terms as this should be accurate enough for what I need.

        For values outside (-pi, pi), x is simply adjusted by amounts of 2pi until it lies in that range.
    */

    // Find valid x
    double value = x;

    while (value > pi) value -= (2 * pi);
    while (value < -pi) value += (2 * pi);

    // Exponents
    double exp3 = value * value * value;
    double exp5 = exp3 * value * value;
    double exp7 = exp5 * value * value;
    double exp9 = exp7 * value * value;

    // Factorials
    double fac3 = 2 * 3;
    double fac5 = fac3 * 4 * 5;
    double fac7 = fac5 * 6 * 7;
    double fac9 = fac7 * 8 * 9;

    // Put it all together
    double returnValue = value;

    returnValue -= (exp3) / fac3;
    returnValue += (exp5) / fac5;
    returnValue -= (exp7) / fac7;
    returnValue += (exp9) / fac9;

    return returnValue;
}

double cos(double x) {
    /*
        Uses radians
        This function uses the power series defined for sin(x) as

              x^2     x^4
        1 -  ----- + ----- - ...
               2!      4!

        This function uses the first 6 terms. as this gives at most an error of 0.002 ( making 0.1% on a range of (-1, 1) ) for values inside (-pi, pi)
        In interest of performance, I will not add more terms as this should be accurate enough for what I need.

        For values outside (-pi, pi), x is simply adjusted by amounts of 2pi until it lies in that range.
    */

    // Find valid x
    double value = x;

    while (value > pi) value -= (2 * pi);
    while (value < -pi) value += (2 * pi);

    // Exponents
    double exp2 = value * value;
    double exp4 = exp2 * value * value;
    double exp6 = exp4 * value * value;
    double exp8 = exp6 * value * value;
    double exp10 = exp8 * value * value;

    // Factorials
    double fac2 = 2;
    double fac4 = fac2 * 3 * 4;
    double fac6 = fac4 * 5 * 6;
    double fac8 = fac6 * 7 * 8;
    double fac10 = fac8 * 9 * 10;

    // Put it all together
    double returnValue = 1;

    returnValue -= exp2 / fac2;
    returnValue += exp4 / fac4;
    returnValue -= exp6 / fac6;
    returnValue += exp8 / fac8;
    returnValue -= exp10 /fac10;

    return returnValue;
}

double tan(double x) {
    /*
        Uses radians
        The tan power series is quite complicated and is not very accurate with only a few terms, so it is not used
        Since tan is defined as sin/cos, this function simply calls sin() and cos() from above
        The value adjusting is done here to avoid doing it twice
    */

    // Find valid x
    double value = x;

    while (value > pi) value -= (2 * pi);
    while (value < -pi) value += (2 * pi);

    // Find sin and cos, then get tan
    double sinValue = sin(value);
    double cosValue = cos(value);

    return sinValue / cosValue;
}

// Arctan defined first because it is used for the other two
double arctan(double x) {
    /*
        Returns radians
        This function is sort of complicated so heres the breakdown:

        1.  This way of calculating only works if the value of x is in (-1, 1)
            If the value is outside that range, 1/x is used instead and the angle is given as (pi/2 - found angle)

        2.  Im using power series to calculate the angle, but for performance im only using the first 5 terms.
            This series is accurate until around |x| > 0.76

            That being:

                 x^3     x^5
            x - ----- + ----- - ...
                  3       5

        3.  When the value is outside that range, I am using linear functions which closely fit the graph of arctan
            I used desmos to find these functions and fine tuned the values, so they may seem arbitrary

            Those being:

                For x < -0.76:
                    f(x) = 0.55x - 0.235

                For x > 0.76:
                    f(x) = 0.55x + 0.235


        This method gives at most a 0.5% error, with the majority of inputs giving less than 0.05% error
        This function does not need to be perfectly accurate, so I am choosing to optimize performance over accuracy
    */

    double value = x;
    bool inverseFlag = false;
    double returnValue;

    // Fix value if its outside (-1, 1)
    if (abs(x) > 1) {
        value = 1 / value;
        inverseFlag = true;
    }

    // Linear Functions for values outside (-0.76, 0.76)
    if (value < -0.76) {
        returnValue = (0.55 * x) - 0.235;
    }

    else if (value > 0.76) {
        returnValue = (0.55 * x) + 0.235;
    }

    else {

        // Power series for values inside (-0.76, 0.76)

        // Just defining these here for readability
        double exp3 = value * value * value;
        double exp5 = exp3 * value * value;
        double exp7 = exp5 * value * value;
        double exp9 = exp7 * value * value;

        // Put it all together
        returnValue = value;

        returnValue -= (exp3) / 3;
        returnValue += (exp5) / 5;
        returnValue -= (exp7) / 7;
        returnValue += (exp9) / 9;

    }

    // Return the angle found, or pi/2 - angle found depending on the flag
    return (inverseFlag) ? returnValue : (pi / 2) - returnValue;

}

double arcsin(double x) {
    /*
        This function makes use of the arctan function defined above, along side the following identity:

                          (         x         )
        arcsin(x) = arctan( ----------------- )
                          (   sqrt(1 - x^2)   )

        The power series defined for arcsin are very inaccurate at values close to |1|, even with many terms
        However my arctan function has a very low error margin so I have no problem relying on it for this

        This function also uses my sqrt function as defined above, which has a very small error margin
        So the total error on this would be very slightly higher than the error on arctan

        Arcsin is undefined outside (-1, 1)
        So when given a value outside that range, I log an error and simply return 0.
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (abs(x) > 1) {
        logWrite("Called arcsin(double) on a value outside (-1, 1)", true);
        return 0;
    }

    double y;

    y = 1 - (x * x);
    y = sqrt(y);
    y = x / y;

    return arctan(y);

}

double arccos(double x) {
    /*
        This function makes use of the arctan function defined above, along side the following identity:

                          (   sqrt(1 - x^2)   )
        arccos(x) = arctan( ----------------- )
                          (         x         )

        The power series defined for arccos are very inaccurate at values close to |1|, even with many terms
        However my arctan function has a very low error margin so I have no problem relying on it for this

        This function also uses my sqrt function as defined above, which has a very small error margin
        So the total error on this would be very slightly higher than the error on arctan

        Arccos is undefined outside (-1, 1)
        So when given a value outside that range, I log an error and simply return 0.

        This identity is also wierd becuase it gives values of x < 0, a return value pi lower than it should be
        So theres simply a check at the end of fix that.
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (abs(x) > 1) {
        logWrite("Called arccos(double) on a value outside (-1, 1)", true);
        return 0;
    }

    double y;

    y = 1 - (x * x);
    y = sqrt(y);
    y = y / x;

    double returnValue = arctan(y);
    
    // Check both the result of arctan and the value of x due to overlaps in the graphs
    return (returnValue < 0 || x < 0) ? returnValue + pi : returnValue;

}


/*   ---------------------------   */
/*   ---   Other Functions   ---   */
/*   ---------------------------   */

double range(double num, double from, double to) {
    /*
        This function basically normalizes a value with respect to some given range
        Returns a value between 0-1 if the num is in the range, and can be bigger or smaller depending how far outside the range is lies
    */

    return ( (num - from) / (to - from) );

}

double inRange(double num, double from, double to) {
    /*
        Function is similar to range, but returns -1 for values outside the range
    */

    if ( (num >= from) && (num <= to) )
        return ( (num - from) / (to - from) );
    return -1;
}

void swap(int* var1, int* var2) {
    /*
        Just swaps the values in var1 and var2 using pointers to those values
    */

    int temp = *var1;
    *var1 = *var2;
    *var2 = temp;
    return;

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
