/*

    This file doesnt do anything, and its very outdated.

    At one point i wanted to see all my code in one single file, just to put it into scale.
    This file is the result of that. 

    Im just leaving it because I think its somewhat valuable to me personally,
    But as far as the project goes, its worthless.

*/


// Basic Includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <SDL2/SDL.h>
#include <chrono>
#include "src/lodepng/lodepng.h"

// Init
void logInit(std::string fileName);

// Primative Functions
void logClear();
void logNewLine();

// Strings and chars
void logWrite(std::string message, bool newLine = false);
void logWrite(char message, bool newLine = false);
void logWrite(wchar_t message, bool newLine = false);

// Decimal Values
void logWrite(int message, bool newLine = false);
void logWrite(long message, bool newLine = false);
void logWrite(long long message, bool newLine = false);
void logWrite(double message, bool newLine = false);

// Hex values
// void logWrite(int8bytes message, bool newLine = false);
// void logWrite(int2bytes message, bool newLine = false);
// void logWrite(int4bytes message, bool newLine = false);
// void logWrite(int1byte message, bool newLine = false);

// Variable Format
void logVar(std::string message, int variable);
void logVar(std::string message, double variable);

//#include "../include/Log.h"

std::ofstream outputFile;

// Init
void logInit(std::string fileName) {
    try {
        outputFile.open(fileName);
    } catch (...) {
        std::cout << "Couldnt open log.txt" << std::endl;
        system("pause");
        return;
    }
}

// Primative Functions
void logClear() {
    if (!outputFile.is_open()) {
        std::cout << "logInit must be called first" << std::endl;
        system("pause");
        return;
    }
    outputFile.clear();
}

void logNewLine() {

    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        std::cout << "logInit must be called first" << std::endl;
        system("pause");
        return;
    }

    outputFile << "\n";
}

// Strings and chars
void logWrite(std::string message, bool newLine /* default value = false */) {

    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        std::cout << "logInit must be called first" << std::endl;
        system("pause");
        return;
    }

    // Write message to file
    outputFile << message;

    // End line
    if (newLine) outputFile << std::endl;

    return;
}

void logWrite(char message, bool newLine /* default value = false */) {
    std::string outputString;
    outputString += message;
    logWrite(outputString, newLine);
}

void logWrite(wchar_t message, bool newLine /* default value = false */) {
    std::string outputString;
    outputString += message;
    logWrite(outputString, newLine);
}

// Decimal Values
void logWrite(int message, bool newLine /* default value = false */) {
    logWrite(std::to_string(message), newLine);
    return;
}

void logWrite(long message, bool newLine /* default value = false */) {
    logWrite(std::to_string(message), newLine);
    return;
}

void logWrite(long long message, bool newLine /* default value = false */) {
    logWrite(std::to_string(message), newLine);
    return;
}

void logWrite(double message, bool newLine /* default value = false */) {

    // Get a string without trailing zeros after the decimal
    std::string output = std::to_string(message);

    int decimalPos = output.find('.');

    if (decimalPos != std::string::npos) {

        // Find the position of the last non-zero digit after the decimal point
        int endPos = output.find_last_not_of('0');
        
        // If the last non-zero digit is after the decimal point, remove trailing zeros
        if (endPos != std::string::npos && endPos > decimalPos)
            output = output.substr(0, endPos + 1);

        // If there are no non-zero digits after the decimal point, return the integer part
        else
            output = output.substr(0, decimalPos);
            
    }

    // Log it
    logWrite(output, newLine);
    return;
}

// Hex values
// void logWrite(int8bytes message, bool newLine /* default value = false */) {

//     std::stringstream stream;
//     stream << "0x" << std::hex << std::uppercase << message;
//     std::string hexString = stream.str();

//     logWrite(hexString, newLine);
//     return;
// }

// void logWrite(int2bytes message, bool newLine /* default value = false */) {
//     logWrite( (int8bytes) message, newLine);
//     return;
// }

// void logWrite(int4bytes message, bool newLine /* default value = false */) {
//     logWrite( (int8bytes) message, newLine);
//     return;
// }

// void logWrite(int1byte message, bool newLine /* default value = false */) {
//     logWrite( (int8bytes) message, newLine);
//     return;
// }

// Variable Format
void logVar(std::string message, int variable) {
    logWrite(message, false);
    logWrite(": ", false);
    logWrite(variable, true);
}

void logVar(std::string message, double variable) {
    logWrite(message, false);
    logWrite(": ", false);
    logWrite(variable, true);
}

#ifndef pi
#define pi 3.14159265358979323846
#endif

// This doesnt need to be extremely high becuase its just for trig functions and such
#ifndef inf
#define inf 1e100
#endif

// For degree conversion
const double degToRadFactor = pi / 180;


/*   -----   Basic Functions   -----   */

// Returns the floor value of x as an int
int floor(double x);

// Returns the rounded value of x as an integer. That means this rounds to ZERO decimal points
int round(double x);


/*   -----   sqrt   -----   */

// Returns a value within the given tolerance from the actual square root of x
double sqrt(double x, double tolerance = 0.000001);


/*   --------------------------   */
/*   ---   Trig Functions   ---   */
/*   --------------------------   */

// Sine function. Uses radians
double sin(double x);

// Cosine function. Uses radians
double cos(double x);

// Tangent function. Uses radians
double tan(double x);

// Reverse sine function. Uses radians
double arcsin(double x);

// Reverse cosine function. Uses radians
double arccos(double x);

// Reverse tangent function. Uses radians
double arctan(double x);


/*   ---------------------------   */
/*   ---   Other Functions   ---   */
/*   ---------------------------   */

// Returns the distance between 2 sets of 2 dimensional coordinates
double distance2(double x1, double y1, double x2 = 0, double y2 = 0);

// Returns the distance between 2 sets of 3 dimensional coordinates
double distance3(double x1, double y1, double z1, double x2 = 0, double y2 = 0, double z2 = 0);

// Returns a value 0-1 for how far between 'from' and 'to' the value is. Returns -1 if its outside the range.
double range(double num, double from, double to);

// Same as above, but allows values outside the range, in which case it would return values outside 0-1
double inRange(double num, double from, double to);

// Swaps the values in two memory locations.
void swap(int* var1, int* var2);
void swap(double* var1, double* var2);
void swap(unsigned int* var1, unsigned int* var2);

// Returns the angle between two points in DEGREES.
// This angle is from a vertical line on (x1, y1) to (x2, y2)
// For example if (x2, y2) is directly right of (x1, y1) this returns 90. 
// The second position is set to (0, 0) by default.
double getAngle(double x1, double y1, double x2 = 0, double y2 = 0);


/*   ----------------------------   */
/*   ---   Inline Functions   ---   */
/*   ----------------------------   */

// Angle conversion. Degrees -> Radians
inline double toRadians(double degrees) {
    return degrees * degToRadFactor;
}

// Angle conversion. Radians -> Degrees
inline double toDegrees(double radians) {
    return radians / degToRadFactor;
}

// Returns the greater value (int)
inline int max(int var1, int var2) {
    return (var1 > var2) ? var1 : var2;
}

// Returns the greater value (double)
inline double max(double var1, double var2) {
    return (var1 > var2) ? var1 : var2;
}

// Returns the greater value (unsigned int)
inline unsigned int max(unsigned int var1, unsigned int var2) {
    return (var1 > var2) ? var1 : var2;
}

// Returns the lesser value (int)
inline int min(int var1, int var2) {
    return (var1 < var2) ? var1 : var2;
}

// Returns the lesser value (double)
inline double min(double var1, double var2) {
    return (var1 < var2) ? var1 : var2;
}

// Returns the lesser value (unsigned int)
inline unsigned int min(unsigned int var1, unsigned int var2) {
    return (var1 < var2) ? var1 : var2;
}

/*   -----   Basic Functions   -----   */
double abs(double x) {
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

double sqrt(double x, double tolerance) {
    /*
        This function makes use of the Newton Raphson method to find the sqrt of x as follows:

        let     x = the input value
                y_n = the nth approximation of sqrt(x)
                f(y) = y^2 - x
                f'(y) = 2y

        Newton Raphson Formula:

                        f(y_n)
        y_n+1 = y_n - -----------
                        f'(y_n)
                        
        Second term:

          f(y_n)        (   y_n^2 - x   )     (  y_n        x    )  
        -----------  =  ( ------------- )  =  ( -----  -  ------ )
          f'(y_n)       (      2y_n     )     (   2        2y_n  )

        Therefore

                         (  y_n        x    )     (  y_n         x     )
        y_n+1  =  y_n -  ( -----  -  ------ )  =  ( -----  +  -------- )
                         (   2        2y_n  )     (   2         2y_n   )

        Which is  ->  y_n+1  =  0.5 * ( -y_n + (x / y_n) )

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
    int maxIterations = 25;

    // Newton Raphson method
    double y = x;
    double yNext = 0;

    while (true) {

        if (maxIterations == 0) return y;
        else maxIterations--;

        yNext = 0.5 * ( y + (x / y) );

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

    // Avoid returning small negative value in place of 0
    if (abs(returnValue) < 1e-6) return 0;

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

    // Dont divide by zero
    if (cosValue == 0)
        return (sinValue > 0) ? inf : -inf;
        
    return sinValue / cosValue;

}

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

    // Value close to 0
    if (abs(value) < 0.05) {
        returnValue = value;
    }

    // Linear Functions for values outside (-0.76, 0.76)
    else if (value < -0.76) {
        returnValue = (0.55 * value) - 0.235;
    }

    else if (value > 0.76) {
        returnValue = (0.55 * value) + 0.235;
    }

    // Power series for values inside (-0.76, 0.76)
    else {

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

    // Handle inverse return values
    if (inverseFlag) {

        // offset = pi/2 or -pi/2 depending of sign of returnvalue
        double offset = (returnValue > 0) ? (pi / 2) : -(pi / 2);

        return offset - returnValue;

    }

    return returnValue;

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

    // Check for value of 0, as this could give a divide by 0 error
    if (y == 0) {
        return ( (x > 0) ? (pi/2) : (-pi/2) );
    }

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

        This identity is also weird becuase it gives values of x < 0, a return value pi lower than it should be
        So theres simply a check at the end of fix that.
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (abs(x) > 1) {
        logWrite("Called arccos(double) on a value outside (-1, 1)", true);
        return 0;
    }

    // When x = 0, there will be a divide by 0 error. So return manually
    if (x == 0) {
        return pi/2;
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

double distance2(double x1, double y1, double x2 /* default value = 0 */, double y2 /* default value = 0 */) {

    double dx = x1 - x2;
    double dy = y1 - y2;

    return sqrt((dx * dx) + (dy * dy));

}

double distance3(double x1, double y1, double z1, double x2 /* default value = 0 */, double y2 /* default value = 0 */, double z2 /* default value = 0 */) {

    double dx = x1 - x2;
    double dy = y1 - y2;
    double dz = z1 - z2;

    return sqrt((dx * dx) + (dy * dy) + (dz * dz));

}

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

void swap(double* var1, double* var2) {
    /*
        Just swaps the values in var1 and var2 using pointers to those values
    */

    double temp = *var1;
    *var1 = *var2;
    *var2 = temp;
    return;

}

void swap(unsigned int* var1, unsigned int* var2) {
    /*
        Just swaps the values in var1 and var2 using pointers to those values
    */

    unsigned int temp = *var1;
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
        return 180;
    }

    if (y1 == y2) {
        if (x1 >= x2) return 90;
        return 270;
    }

    double radians;

    if (x1 != x2) {

        double m = abs( (x1 - x2) / (y1 - y2) );
        radians = arctan(m);

    } 
    
    else
        radians = 0;

    // Adjust angle based on quadrant
    if (y1 < y2) radians = pi - radians;
    if (x1 < x2) radians = (2 * pi) - radians;

    return toDegrees(radians);

}

class Vec2 {

    /*
        Class encapsulating 2 double values so that they are treated as a vector.
        Wide array of functions to act upon these vector.
        These are the base for everything 2d in this program.
    */

    public:

        // Instance variables
        double x, y;


        /*   Constructors   */

        // Specified values
        Vec2(double inputX, double inputY);

        // Defaults to (0, 0)
        Vec2(); 


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Vec2* copy();

        // Logs the vector in the format "Vec2( x, y )"
        void log();

        // Sets the values of the components
        Vec2* set(Vec2* other);
        Vec2* set(double x, double y);

        // Acts similar to '=='. Returns true if all components are equal to each other
        bool is(double x, double y);
        bool is(Vec2* other);

        // The following are self transformation functions. they all return 'this' so they can be chained ( ex. this->add(vec)->sub(vec2) )

        // Adds the components of other to those of this.
        Vec2* add(double x, double y);
        Vec2* add(Vec2* other);

        // Subtracts the components of other from those of this.
        Vec2* sub(double x, double y);
        Vec2* sub(Vec2* other);

        // Scalar multiplication by a given factor
        Vec2* scale(double factor);

        // Same as above, but uses 1/factor
        Vec2* inverseScale(double factor);

        // Sets the magnitude of the vector to a given value, while keeping the ratios between components the same.
        Vec2* normalise(double toMagnitude = 1.0);


        // Allows these objects to be indexed like an array.
        double get(int index);

        // Converts the Vec2 to an array. [Vec2->x, Vec2->y]
        double* toArray();

        // Returns the magnitude of the vector
        double magnitude();

        // Returns the distance between this vector and other
        double distanceTo(Vec2* other);

        // Returns the midpoint between this and other as a new Vec2 object.
        Vec2* midpoint(Vec2* other);

        // Returns the dot product of this and other.
        double dotProduct(Vec2* other);

        // Rotates the vector around a given point (by default (0, 0)) by a given angle.
        // Vector will be rotated COUNTER CLOCKWISE
        void rotate(double degrees, Vec2* around = nullptr);

    private:
    
        /*   Instance variables   */

        // This is the length of the vector in 2d space.
        // This value is private because it is not always accurate, and is only update when requested.
        // Doing this means there wont be unnesecary updates to the magnitude when it wont even be read.
        double magnitudeValue;

        // Flag showing if the above value is accurate. This allows the function call which returns the magnitude to only do the math when nessecary.
        // Any instance function which can change the magnitude, will set this to false.
        bool magnitudeUpdated;
        
};



class Vec3 {

    /*
        Class encapsulating 3 double values so that they are treated as a vector.
        Wide array of functions to act upon these vector.
        These are the base for everything 3d in this program.
    */

    public:

        // Instance variables
        double x, y, z;


        /*   Constructors   */

        // Specified values
        Vec3(double inputX, double inputY, double inputZ);

        // Defaults to (0, 0, 0)
        Vec3();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Vec3* copy();

        // Logs the vector in the format "Vec3( x, y, z )"
        void log();

        // Sets the values of the components
        Vec3* set(Vec3* other);
        Vec3* set(double x, double y, double z);

        // Acts similar to '=='. Returns true if all components are equal to each other
        bool is(Vec3* other);
        bool is(double x, double y, double z);

        // The following are self transformation functions. they all return 'this' so they can be chained ( ex. this->add(vec)->sub(vec2) )

        // Adds the components of other to those of this.
        Vec3* add(Vec3* other);
        Vec3* add(double dx, double dy, double dz);

        // Subtracts the components of other from those of this.
        Vec3* sub(Vec3* other);
        Vec3* sub(double dx, double dy, double dz);

        // Scalar multiplication by a given factor
        Vec3* scale(double factor);
        Vec3* scale(double fx, double fy, double fz);

        // Same as above, but uses 1/factor
        Vec3* inverseScale(double factor);

        // Sets the magnitude of the vector to a given value, while keeping the ratios between components the same.
        Vec3* normalise(double toMagnitude = 1.0);


        // Allows these objects to be indexed like an array.
        double get(int index);

        // Converts the Vec3 to an array. [Vec3->x, Vec3->y, Vec3->z]
        double* toArray();

        // Returns the magnitude of the vector
        double magnitude();

        // Returns the distance between this vector and other
        double distanceTo(Vec3* other);

        // Returns the midpoint between this and other as a new Vec3 object.
        Vec3* midpoint(Vec3* other);

        // Returns the dot product of this and other.
        double dotProduct(Vec3* other);

        // Returns the cross product of this and other as a new Vec3 object. This vector is perpendicular to both other and this.
        Vec3* crossProduct(Vec3* other);

        // Find the angle in degrees between this and other. This angle will always be between 0-180.
        double getAngle(Vec3* other);

        // Rotates the vector around a certain point (by default (0, 0, 0)) by a given angle on each direction.
        // Each rotation occurs COUNTER CLOCKWISE assuming you are looking down upon the rotation.
        void rotate(double yaw, double pitch, double roll, Vec3* around = nullptr);

        // Projects the point to 2d space. The z value becomes the depth. The values of the components are changed
        void project();

    private:

        /*   Instance variables   */

        // This is the length of the vector in 3d space.
        // This value is private because it is not always accurate, and is only update when requested.
        // Doing this means there wont be unnesecary updates to the magnitude when it wont even be read.
        double magnitudeValue;

        // Flag showing if the above value is accurate. This allows the function call which returns the magnitude to only do the math when nessecary.
        bool magnitudeUpdated;

};

/* ------------ */
/* --- Vec2 --- */
/* ------------ */

// Constructor
Vec2::Vec2(double inputX, double inputY) {
    this->x = inputX;
    this->y = inputY;
    this->magnitudeValue = 0;
    this->magnitudeUpdated = false;
}

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
    this->magnitudeValue = 0;
    this->magnitudeUpdated = false;
}

// Instance functions
Vec2* Vec2::copy() {
    return new Vec2(this->x, this->y);
}

void Vec2::log() {

    logWrite("Vec2( ");
    logWrite(this->x);
    logWrite(", ");
    logWrite(this->y);
    logWrite(" )", true);

    return;
    
}

Vec2* Vec2::set(Vec2* other) {

    if (other == nullptr) {
        logWrite("Called Vec2->set(Vec2*) on a null pointer!", true);
        return this;
    }

    this->x = other->x;
    this->y = other->y;
    return this;

}

Vec2* Vec2::set(double x, double y) {

    this->x = x;
    this->y = y;
    return this;

}

bool Vec2::is(double x, double y) {

    return (
        this->x == x &&
        this->y == y
    );
}

bool Vec2::is(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->is(Vec2*) on a null pointer!", true);
        return false;
    }

    return (
        this->x == other->x &&
        this->y == other->y
    );
}

Vec2* Vec2::add(double x, double y) {
    this->x += x;
    this->y += y;
    this->magnitudeUpdated = false;
    return this;
}

Vec2* Vec2::add(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->add(Vec2*) on a null pointer!", true);
        return nullptr;
    }

    this->x += other->x;
    this->y += other->y;
    this->magnitudeUpdated = false;
    return this;
}

Vec2* Vec2::sub(double x, double y) {
    this->x -= x;
    this->y -= y;
    this->magnitudeUpdated = false;
    return this;
}

Vec2* Vec2::sub(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->sub(Vec2*) on a null pointer!", true);
        return nullptr;
    }

    this->x -= other->x;
    this->y -= other->y;
    this->magnitudeUpdated = false;
    return this;
}

Vec2* Vec2::scale(double factor) {
    this->x *= factor;
    this->y *= factor;
    if (this->magnitudeUpdated) this->magnitudeValue *= factor;
    return this;
}

Vec2* Vec2::inverseScale(double factor) {
    return this->scale(1 / factor);
}

Vec2* Vec2::normalise(double toMagnitude /* default value = 1.0 */) {
    double factor = toMagnitude / this->magnitude();
    return this->scale(factor);
}

double Vec2::get(int index) {
    switch (index) {
        case 0:
            return this->x;
        case 1:
            return this->y;
        default:
            return 0;
    }
}

double* Vec2::toArray() {
    double* array = new double[2];
    array[0] = this->x;
    array[1] = this->y;
    return array;
}

double Vec2::magnitude() {
    if (!this->magnitudeUpdated) {
        this->magnitudeValue = distance2(this->x, this->y);
        this->magnitudeUpdated = true;
    }
    return this->magnitudeValue;
}

double Vec2::distanceTo(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->distanceTo(Vec2*) on a null pointer!", true);
        return 0;
    }

    return distance2(this->x, this->y, other->x, other->y);

}

Vec2* Vec2::midpoint(Vec2* other) {
    
    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->midpoint(Vec2*) on a null pointer!", true);
        return nullptr;
    }

    return new Vec2(
        (this->x + other->x) / 2,
        (this->y + other->y) / 2
    );

}

double Vec2::dotProduct(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->dotProduct(Vec2*) on a null pointer!", true);
        return 0;
    }

    return (this->x * other->x) + (this->y * other->y);

}

void Vec2::rotate(double degrees, Vec2* around /* default value = nullptr */) {
    
    // around = nullptr already addressed here, no need for error case

    if (degrees == 0) return;

    double aroundX = 0;
    double aroundY = 0;
    double relativeX = this->x;
    double relativeY = this->y;

    if (around != nullptr) {
        aroundX = around->x;
        aroundY = around->y;
        relativeX -= aroundX;
        relativeY -= aroundY;
    }

    double radians = toRadians(degrees);

    double sinValue = sin(radians);
    double cosValue = cos(radians);

    this->x = (cosValue * relativeX) - (sinValue * relativeY) + aroundX;
    this->y = (cosValue * relativeY) + (sinValue * relativeX) + aroundY;

    return;
    
}



/* ------------ */
/* --- Vec3 --- */
/* ------------ */

// Constructors
Vec3::Vec3(double inputX, double inputY, double inputZ) {
    this->x = inputX;
    this->y = inputY;
    this->z = inputZ;
    this->magnitudeValue = 0;
    this->magnitudeUpdated = false;
}

Vec3::Vec3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->magnitudeValue = 0;
    this->magnitudeUpdated = false;
}

// Instance functions
Vec3* Vec3::copy() {
    return new Vec3(this->x, this->y, this->z);
}

void Vec3::log() {

    logWrite("Vec3( ");
    logWrite(this->x);
    logWrite(", ");
    logWrite(this->y);
    logWrite(", ");
    logWrite(this->z);
    logWrite(" )", true);

    return;
    
}

Vec3* Vec3::set(Vec3* other) {

    if (other == nullptr) {
        logWrite("Called Vec3->set(Vec3*) on a null pointer!", true);
        return this;
    }

    this->x = other->x;
    this->y = other->y;
    this->z = other->z;
    return this;

}

Vec3* Vec3::set(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    return this;
}

bool Vec3::is(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->is(Vec3*) on a null pointer!", true);
        return false;
    }

    return (
        this->x == other->x &&
        this->y == other->y &&
        this->z == other->z
    );
}

bool Vec3::is(double x, double y, double z) {

    return (
        this->x == x &&
        this->y == y &&
        this->z == z
    );

}

Vec3* Vec3::add(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->add(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    this->x += other->x;
    this->y += other->y;
    this->z += other->z;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::add(double dx, double dy, double dz) {
    this->x += dx;
    this->y += dy;
    this->z += dz;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::sub(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->sub(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    this->x -= other->x;
    this->y -= other->y;
    this->z -= other->z;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::sub(double dx, double dy, double dz) {
    this->x -= dx;
    this->y -= dy;
    this->z -= dz;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::scale(double factor) {
    this->x *= factor;
    this->y *= factor;
    this->z *= factor;
    if (this->magnitudeUpdated) this->magnitudeValue *= factor;
    return this;
}

Vec3* Vec3::scale(double fx, double fy, double fz) {
    this->x *= fx;
    this->y *= fy;
    this->z *= fz;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::inverseScale(double factor) {
    return this->scale(1 / factor);
}

Vec3* Vec3::normalise(double toMagnitude /* default value = 1.0 */) {
    double factor = toMagnitude / this->magnitude();
    return this->scale(factor);
}

double Vec3::get(int index) {
    switch (index) {
        case 0:
            return this->x;
        case 1:
            return this->y;
        case 2:
            return this->z;
        default:
            return 0;
    }
}

double* Vec3::toArray() {
    double* array = new double[3];
    array[0] = this->x;
    array[1] = this->y;
    array[2] = this->z;
    return array;
}

double Vec3::magnitude() {

    if (!this->magnitudeUpdated) {
        this->magnitudeValue = distance3(this->x, this->y, this->z);
        this->magnitudeUpdated = true;
    }
    
    return this->magnitudeValue;

}

double Vec3::distanceTo(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->distanceTo(Vec3*) on a null pointer!", true);
        return 0;
    }

    return distance3(this->x, this->y, this->z, other->x, other->y, other->z);

}

Vec3* Vec3::midpoint(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->midpoint(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    return new Vec3(
        (this->x + other->x) / 2,
        (this->y + other->y) / 2,
        (this->z + other->z) / 2
    );
}

double Vec3::dotProduct(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->dotProduct(Vec3*) on a null pointer!", true);
        return 0;
    }

    return (this->x * other->x) + (this->y * other->y) + (this->z * other->z);
}

Vec3* Vec3::crossProduct(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->crossProduct(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    double x = (this->y * other->z) - (this->z * other->y);
    double y = (this->z * other->x) - (this->x * other->z);
    double z = (this->x * other->y) - (this->y * other->x);
    return new Vec3(x, y, z);
}

double Vec3::getAngle(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->getAngle(Vec3*) on a null pointer!", true);
        return 0;
    }

    double dotProduct = this->dotProduct(other);
    double magnitudeFactor = this->magnitude() * other->magnitude();
    double ratio = dotProduct / magnitudeFactor;

    // These cases shouldnt happen but floating point errors can cause them
    if (ratio < -1) return 180;
    if (ratio > 1)  return 0;

    double radians = arccos(ratio);
    
    return toDegrees(radians);
}

void Vec3::rotate(double yaw, double pitch, double roll, Vec3* around /* default value = nullptr */) {

    // around = nullptr already addressed here, no need for error case

    if (yaw == 0 && pitch == 0 && roll == 0) return;

    double aroundX = 0;
    double aroundY = 0;
    double aroundZ = 0;
    double relativeX = this->x;
    double relativeY = this->y;
    double relativeZ = this->z;

    if (around != nullptr) {
        aroundX = around->x;
        aroundY = around->y;
        aroundZ = around->z;
        relativeX -= aroundX;
        relativeY -= aroundY;
        relativeZ -= aroundZ;
    }

    double radians;

    if (yaw != 0) {
        
        radians = toRadians(yaw);

        double sinValue = sin(radians);
        double cosValue = cos(radians);

        this->x = (cosValue * relativeX) - (sinValue * relativeZ) + aroundX;
        this->z = (cosValue * relativeZ) + (sinValue * relativeX) + aroundZ;

    }

    // Reset relative values
    relativeX = this->x - aroundX;
    relativeZ = this->z - aroundZ;

    if (pitch != 0) {

        radians = toRadians(pitch);

        double sinValue = sin(radians);
        double cosValue = cos(radians);

        this->y = (cosValue * relativeY) - (sinValue * relativeZ) + aroundY;
        this->z = (cosValue * relativeZ) + (sinValue * relativeY) + aroundZ;

    }

    // Reset relative values
    relativeY = this->y - aroundY;
    relativeZ = this->z - aroundZ;

    if (roll != 0) {

        radians = toRadians(roll);

        double sinValue = sin(radians);
        double cosValue = cos(radians);

        this->y = (cosValue * relativeY) - (sinValue * relativeX) + aroundY;
        this->x = (cosValue * relativeX) + (sinValue * relativeY) + aroundX;

    }

    return;
}

void Vec3::project() {

    /*
        Find a 2d coordinate coorsponding to a 3d point.
        depth (distance from camera) goes in the z component
    */

    // Constant. Can be changed
    double focalLengthX = 0.6;
    double focalLengthY = 1;

    // If the point is behind the camera
    if (this->z < 0) {
        this->x = -1;
        this->y = -1;
        this->z = inf;
        return;
    }

    double depth = this->magnitude();

    this->x = (this->x * focalLengthX) / this->z;
    this->y = (this->y * focalLengthY) / this->z;

    // adjust so its relative to the top left rather than middle
    this->x += 0.5;
    this->y += 0.5;

    this->z = depth;

    return;

}

class Tri2 {

    /*
        Represents a triangle in 2d space.
        Holds 3 Vec2 objects, and has setters.
        This also includes a depth value for each vertex which is optional. 
        Depth is used to hold distance between the 3d vertex and the camera from projection.
    */

    public:

        // Instance variables
        Vec2* v1;
        Vec2* v2;
        Vec2* v3;

        double depth1;
        double depth2;
        double depth3;


        /*   Constructor   */

        // nullPointers determines if the instance variables should be initialized or not.
        // When this is false, all v1, v2, and v3 are set to individual copies of (0, 0)
        Tri2(bool nullPointers = false);


        // Destructor
        ~Tri2();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Tri2* copy();

        void log();

        // Setters for each vertex. Allowing double or Vec2 inputs
        // The ones which take a Vec2 object will delete the current instance variable, then point to the one given.
        // That means the Vec2 given, should NOT be changed after running this, unless changing the triangle is intended.
        void setv1(double x, double y, double z);
        void setv1(Vec2* vec);

        void setv2(double x, double y, double z);
        void setv2(Vec2* vec);

        void setv3(double x, double y, double z);
        void setv3(Vec2* vec);

};



class Tri3 {

    /*
        Similar to Tri2, but for 3d. This also contains a normal vector.
        There are several other functions here becuase these are the objects used for all the Mesh objects.
    */

    public:

        // Instance variables
        Vec3* v1;
        Vec3* v2;
        Vec3* v3;
        Vec3* normal;


        /*   Constructor   */

        // nullPointers determines if the instance variables should be initialized or not.
        // When this is false, all v1, v2, v3, and normal are set to individual copies of (0, 0, 0)
        Tri3(bool nullPointers = false);


        // Destructor
        ~Tri3();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Tri3* copy();

        void log();

        // Setters for each vertex, and the normal. Allowing double or Vec3 inputs
        // The ones which take a Vec3 object will delete the current instance variable, then point to the one given.
        // That means the Vec3 given, should NOT be changed after running this, unless also changing the triangle is intended.
        void setv1(double x, double y, double z);
        void setv1(Vec3* vec);

        void setv2(double x, double y, double z);
        void setv2(Vec3* vec);

        void setv3(double x, double y, double z);
        void setv3(Vec3* vec);

        void setNormal(double x, double y, double z);
        void setNormal(Vec3* normal);

        // Uses cross product to find a normal vector for the existing verticies in the triangle.
        // New normal may be facing either direction from the triangle.
        void updateNormal();

        // Returns true if the triangle should be visible assuming its only opaque on the side the normal sticks out from.
        // This just returns true when the angle between the Vec3 and the normal is >= 90
        bool isFacing(Vec3* vec);

        // Returns a Vec3 object defining the center of the triangle. takes the average of each component. This returns a NEW object
        Vec3* getCenter();
        
};

/* ------------ */
/* --- Tri2 --- */
/* ------------ */

// Constructor
Tri2::Tri2(bool nullPointers /* default value = false */) {
    /*
        Stores a set of 3 vectors
        nullPointers flag allows the pointers to be manually set instead of autocreating objects
    */

    this->depth1 = 0;
    this->depth2 = 0;
    this->depth3 = 0;

    if (nullPointers) {
        this->v1 = nullptr;
        this->v2 = nullptr;
        this->v3 = nullptr;
    }

    else {
        this->v1 = new Vec2(0, 0);
        this->v2 = new Vec2(0, 0);
        this->v3 = new Vec2(0, 0);
    }
}

Tri2::~Tri2() {
    delete this->v1;
    delete this->v2;
    delete this->v3;
}

// Instance functions
Tri2* Tri2::copy() {

    Tri2* ret = new Tri2(true);

    Vec2* v1 = this->v1->copy();
    Vec2* v2 = this->v2->copy();
    Vec2* v3 = this->v3->copy();

    ret->setv1(v1);
    ret->setv2(v2);
    ret->setv3(v3);

    return ret;
    
}

void Tri2::log() {

    logWrite("Tri2(", true);
    logWrite("  ");

    if (this->v1 == nullptr)
        logWrite("null", true);
    else
        this->v1->log();

    logWrite("  ");

    if (this->v2 == nullptr)
        logWrite("null", true);
    else
        this->v2->log();

    logWrite("  ");

    if (this->v3 == nullptr)
        logWrite("null", true);
    else
        this->v3->log();

    logWrite(")", true);

    return;

}

void Tri2::setv1(double x, double y, double z) {
    this->v1->x = x;
    this->v1->y = y;
}

void Tri2::setv1(Vec2* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri2->setv1(Vec2*) on a null pointer!", true);
        return;
    }

    if (this->v1 != nullptr) delete this->v1;
    this->v1 = vec->copy();
}

void Tri2::setv2(double x, double y, double z) {
    this->v2->x = x;
    this->v2->y = y;
}

void Tri2::setv2(Vec2* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri2->setv2(Vec2*) on a null pointer!", true);
        return;
    }

    if (this->v2 != nullptr) delete this->v2;
    this->v2 = vec->copy();
}

void Tri2::setv3(double x, double y, double z) {
    this->v3->x = x;
    this->v3->y = y;
}

void Tri2::setv3(Vec2* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri2->setv3(Vec2*) on a null pointer!", true);
        return;
    }

    if (this->v3 != nullptr) delete this->v3;
    this->v3 = vec->copy();
}



/* ------------ */
/* --- Tri3 --- */
/* ------------ */

// Constructor
Tri3::Tri3(bool nullPointers /* default value = false */) {
    /*
        Stores a set of 3 vectors as well as their normal, the normal can be updated using the instance function but this may be facing the wrong way
        nullPointers flag allows the pointers to be manually set instead of autocreating objects
    */

    if (nullPointers) {
        this->v1 = nullptr;
        this->v2 = nullptr;
        this->v2 = nullptr;
        this->normal = nullptr;
        return;
    }

    else {
        this->v1 = new Vec3(0, 0, 0);
        this->v2 = new Vec3(0, 0, 0);
        this->v3 = new Vec3(0, 0, 0);
        this->normal = new Vec3(0, 0, 0);
        return;
    }

}

Tri3::~Tri3() {
    delete this->v1;
    delete this->v2;
    delete this->v3;
    delete this->normal;
}

// Instance functions
Tri3* Tri3::copy() {
    Tri3* newCopy = new Tri3(true);
    newCopy->v1 = this->v1->copy();
    newCopy->v2 = this->v2->copy();
    newCopy->v3 = this->v3->copy();
    newCopy->normal = this->normal->copy();
    return newCopy;
}

void Tri3::log() {

    logWrite("Tri3(", true);
    logWrite("  ");

    if (this->v1 == nullptr)
        logWrite("null", true);
    else
        this->v1->log();

    logWrite("  ");

    if (this->v2 == nullptr)
        logWrite("null", true);
    else
        this->v2->log();

    logWrite("  ");

    if (this->v3 == nullptr)
        logWrite("null", true);
    else
        this->v3->log();

    logWrite(")", true);

    return;

}

void Tri3::setv1(double x, double y, double z) {
    this->v1->x = x;
    this->v1->y = y;
    this->v1->z = z;
}

void Tri3::setv1(Vec3* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri3->setv1(Vec3*) on a null pointer!", true);
        return;
    }

    if (this->v1 != nullptr) delete this->v1;
    this->v1 = vec->copy();
}

void Tri3::setv2(double x, double y, double z) {
    this->v2->x = x;
    this->v2->y = y;
    this->v2->z = z;
}

void Tri3::setv2(Vec3* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri3->setv2(Vec3*) on a null pointer!", true);
        return;
    }

    if (this->v2 != nullptr) delete this->v2;
    this->v2 = vec->copy();
}

void Tri3::setv3(double x, double y, double z) {
    this->v3->x = x;
    this->v3->y = y;
    this->v3->z = z;
}

void Tri3::setv3(Vec3* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri3->setv3(Vec3*) on a null pointer!", true);
        return;
    }

    if (this->v3 != nullptr) delete this->v3;
    this->v3 = vec->copy();
}

void Tri3::setNormal(double x, double y, double z) {
    this->normal->x = x;
    this->normal->y = y;
    this->normal->z = z;
}

void Tri3::setNormal(Vec3* normal) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (normal == nullptr) {
        logWrite("Called Tri3->setNormal(Vec3*) on a null pointer!", true);
        return;
    }

    delete this->normal;
    this->normal = normal->copy();
}

void Tri3::updateNormal() {

    Vec3* vec1to2 = this->v1->copy()->sub(this->v2);
    Vec3* vec1to3 = this->v1->copy()->sub(this->v3);

    Vec3* newNormal = vec1to2->crossProduct(vec1to3);
    newNormal->normalise();
    
    if (this->normal != nullptr) delete this->normal;
    delete vec1to2, vec1to3;

    this->normal = newNormal;

    return;

}

bool Tri3::isFacing(Vec3* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri3->isFacing(Vec3*) on a null pointer!", true);
        return false;
    }

    return vec->getAngle(this->normal) >= 90;
}

Vec3* Tri3::getCenter() {

    // Average all 3 components
    double x = this->v1->x + this->v2->x + this->v3->x;
    double y = this->v1->y + this->v2->y + this->v3->y;
    double z = this->v1->z + this->v2->z + this->v3->z;
    x /= 3; y /= 3; z /= 3;

    return new Vec3(x, y, z);
    
}

class State {

    /*
        This class serves to handle events from frame to frame.
        It keeps track of the events currently happening on this frame, and which events happened last frame.
        Subclasses MouseState and KeyboardState keep track of their respective events.
    */

    public:

        class TimeState {

            /*
                Stores everything time related needed for the code.
                This holds current time, delta time since last frame, and fps variables.
                This also holds anything which counts frames.
            */

            public:

                /*   Instance Variables   */

                // Value which increments every frame
                int totalFrameCount;

                // Time stamps
                double frameTime;
                double lastFrameTime;

                // Delta time since last frame. requires updateDt() to be called
                double dt;

                // Counts the frames since the last full second
                double framesSinceLastSecond;

                // Saves the last full second (multiple of 1000) as a tell for when to update dt
                double nextSecond;

                // Frames per second
                int fps;
                
                
                // Constructor
                TimeState();

                /*   Instance Functions   */

                // Updates the dt and frameTime variables
                void updateDt();

                // Updates the fps counter, or adds to framesSinceLastSecond
                void updateFps();

                // Does everything for the next frame. Including calling the above functions
                void update();

                // Returns the current time in milliseconds
                double getTimeMillis();


        };

        class MouseState {

            /*
                Keeps track of mouse events.
                position (x, y) in pixels, and buttons down.
                Instance functions are for writing, instance variables are for reading.
            */
            
            public:

                // Instance variables
                bool leftButtonIsDown, rightButtonIsDown, middleButtonIsDown;
                int posX, posY;


                // Contructor
                MouseState();
                

                /*   Instance functions   */

                // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
                void setState(MouseState* state);

                // These are SETTERS for all the mouse buttons
                // To GET the value, simply use the variable since its public
                void leftButtonDown();
                void leftButtonUp();

                void middleButtonDown();
                void middleButtonUp();

                void rightButtonDown();
                void rightButtonUp();

                // Set the (x, y) position of the mouse
                void setPos(int x, int y);

        };

        class KeyboardState {

            /*
                Keeps track of keyboard events.
                Not every key is tracked, but all the common ones are. The list of keys is under private in the enums
                each 'type' of key has its own array, and these arrays are indexed via instance functions which take inputs from the SDL2 keycode system.
            */

            public:

                // Instance variables
                bool* letterKeys;
                bool* numKeys;
                bool* miscKeys;

                // Constructor
                KeyboardState();

                // Destructor
                ~KeyboardState();

                /*   Instance variables   */

                // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
                void setState(KeyboardState* state);

                // Returns a pointer to a keystate within one of the instance arrays, based on a given keycode from SDL2
                bool* getKeyRef(int keyCode);

                // Setters for keys
                void setKeyDown(int keyCode);
                void setKeyUp(int keyCode);

                // Getter for keys
                bool keyDown(int keyCode);

            private:

                // Indexes for each key
                enum letterKeyIndex : int {
                    a = 0,
                    b = 1,
                    c = 2,
                    d = 3,
                    e = 4,
                    f = 5,
                    g = 6,
                    h = 7,
                    i = 8,
                    j = 9,
                    k = 10,
                    l = 11,
                    m = 12,
                    n = 13,
                    o = 14,
                    p = 15,
                    q = 16,
                    r = 17,
                    s = 18,
                    t = 19,
                    u = 20,
                    v = 21,
                    w = 22,
                    x = 23,
                    y = 24,
                    z = 25
                };

                enum numKeyIndex : int {
                    zero = 0,
                    one = 1,
                    two = 2,
                    three = 3,
                    four = 4,
                    five = 5,
                    six = 6,
                    seven = 7,
                    eight = 8,
                    nine = 9
                };

                enum miscKeyIndex : int {
                    space = 0,
                    control = 1,
                    shift = 2,
                    alt = 3,
                    capslock = 4,
                    tab = 5,
                    enter = 6,
                    escape = 7,
                    backspace = 8
                };

        };

        /*   Instance variables   */

        // Subclasses
        TimeState* time;
        MouseState* mouse;
        KeyboardState* keys;

        // This is another State object which hold the state of the previous frame.
        // Used to let some events happen once when an event happens, rather than repeating while its held.
        State* lastFrame;


        /*   Constructor   */

        // hasChild determines if the lastFrame instance variable should be created.
        // This is set to true for the version created in the program, then false for the actual lastFrame instance.
        // The option therefore exists to create State with no child, but there is no reason to do this.
        State(bool hasChild = true);


        // Destructor
        ~State();


        /*   Instance functions   */

        // Takes an event object from SDL2 and changes the respective value appropriately.
        void addEvent(SDL_Event* event);

        // Updates everything to be ready for the next frame. Makes this become this->lastFrame
        void nextFrame();


        // Checks for single mouse click events. checks if it is pressed on this frame, but wasnt pressed last frame.
        // Or the other way around for releases

        // Pressed
        bool wasLeftJustPressed();
        bool wasRightJustPressed();

        // Released
        bool wasLeftJustReleased();
        bool wasRightJustReleased();

        // Returns the distance in pixels that the mouse has moved since last frame in the respective direction
        int deltaMousePosX();
        int deltaMousePosY();

        // Simply returns the bool for the key state. Does not cross check with lastFrame.
        bool keyIsDown(int keyCode);

        // Returns true only if the key was pressed this frame, but not last frame
        bool keyJustDown(int keyCode);
        
    private:

        // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
        void setState(State* state);

};

/*  -----------------------------------  */
/*  ----------   TimeState   ----------  */
/*  -----------------------------------  */

// Constructor
State::TimeState::TimeState() {

    // Variable initialization
    this->totalFrameCount = 0;
    this->framesSinceLastSecond = 0;
    this->fps = 0;
    this->nextSecond = 0;
    this->dt = 0;


    // Get time
    auto timeVar = std::chrono::high_resolution_clock::now();
    this->frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
    this->lastFrameTime = frameTime;

    this->updateFps();

}

// Instance functions
void State::TimeState::updateDt() {

    auto timeVar = std::chrono::high_resolution_clock::now();
    this->lastFrameTime = this->frameTime;
    this->frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
    this->dt = this->frameTime - this->lastFrameTime;

}

void State::TimeState::updateFps() {

    if (this->frameTime > this->nextSecond) {

        // Reset next second
        long long temp = (long long) ((frameTime + 1000) / 1000);
        this->nextSecond = (double) temp * 1000;

        // Store fps
        this->fps = this->framesSinceLastSecond;

        // Reset counter
        this->framesSinceLastSecond = 0;

    }

}

void State::TimeState::update() {

    this->totalFrameCount++;
    this->framesSinceLastSecond++;

    this->updateDt();
    this->updateFps();

}

double State::TimeState::getTimeMillis() {

    auto timeVar = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();

}



/*  ------------------------------------  */
/*  ----------   MouseState   ----------  */
/*  ------------------------------------  */

// Contructor
State::MouseState::MouseState() {
    this->leftButtonIsDown = false;
    this->rightButtonIsDown = false;
    this->posX = 0;
    this->posY = 0;
}

// Instance functions
void State::MouseState::setState(MouseState* state) {
    this->leftButtonIsDown = state->leftButtonIsDown;
    this->rightButtonIsDown = state->rightButtonIsDown;
    this->middleButtonIsDown = state->middleButtonIsDown;
    this->posX = state->posX;
    this->posY = state->posY;
}

void State::MouseState::leftButtonDown() {
    this->leftButtonIsDown = true;
}

void State::MouseState::leftButtonUp() {
    this->leftButtonIsDown = false;
}

void State::MouseState::middleButtonDown() {
    this->middleButtonIsDown = true;
}

void State::MouseState::middleButtonUp() {
    this->middleButtonIsDown = false;
}

void State::MouseState::rightButtonDown() {
    this->rightButtonIsDown = true;
}

void State::MouseState::rightButtonUp() {
    this->rightButtonIsDown = false;
}

void State::MouseState::setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
}



/*  -------------------------------------  */
/*  ---------   KeyboardState   ---------  */
/*  -------------------------------------  */

// Constructor
State::KeyboardState::KeyboardState() {

    this->letterKeys = new bool[26];
    this->numKeys = new bool[10];
    this->miscKeys = new bool[9];

    for (int i = 0; i < 26; i++) {

        this->letterKeys[i] = false;

        if (i < 10) 
            this->numKeys[i] = false;

        if (i < 9) 
            this->miscKeys[i] = false;
            
    }

    return;
}

// Destructor
State::KeyboardState::~KeyboardState() {
    delete[] this->letterKeys;
    delete[] this->numKeys;
    delete[] this->miscKeys;
}

// Instance functions
void State::KeyboardState::setState(KeyboardState* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called State::KeyboardState->setState(KeyboardState*) on a null pointer!", true);
        return;
    }

    for (int i = 0; i < 26; i++) {

        this->letterKeys[i] = state->letterKeys[i];

        if (i < 10)
            this->numKeys[i] = state->numKeys[i];

        if (i < 9)
            this->miscKeys[i] = state->miscKeys[i];

    }
}

bool* State::KeyboardState::getKeyRef(int keyCode) {

    /*
        Returns a pointer to the key boolean value within the instance variables
        This is reused in other instance functions
    */
    
    switch (keyCode) {

        // Letter keys
        case SDLK_a:
            return &( this->letterKeys[letterKeyIndex::a] );

        case SDLK_b:
            return &( this->letterKeys[letterKeyIndex::b] );

        case SDLK_c:
            return &( this->letterKeys[letterKeyIndex::c] );

        case SDLK_d:
            return &( this->letterKeys[letterKeyIndex::d] );

        case SDLK_e:
            return &( this->letterKeys[letterKeyIndex::e] );

        case SDLK_f:
            return &( this->letterKeys[letterKeyIndex::f] );

        case SDLK_g:
            return &( this->letterKeys[letterKeyIndex::g] );

        case SDLK_h:
            return &( this->letterKeys[letterKeyIndex::h] );

        case SDLK_i:
            return &( this->letterKeys[letterKeyIndex::i] );

        case SDLK_j:
            return &( this->letterKeys[letterKeyIndex::j] );

        case SDLK_k:
            return &( this->letterKeys[letterKeyIndex::k] );

        case SDLK_l:
            return &( this->letterKeys[letterKeyIndex::l] );

        case SDLK_m:
            return &( this->letterKeys[letterKeyIndex::m] );

        case SDLK_n:
            return &( this->letterKeys[letterKeyIndex::n] );

        case SDLK_o:
            return &( this->letterKeys[letterKeyIndex::o] );

        case SDLK_p:
            return &( this->letterKeys[letterKeyIndex::p] );

        case SDLK_q:
            return &( this->letterKeys[letterKeyIndex::q] );

        case SDLK_r:
            return &( this->letterKeys[letterKeyIndex::r] );

        case SDLK_s:
            return &( this->letterKeys[letterKeyIndex::s] );

        case SDLK_t:
            return &( this->letterKeys[letterKeyIndex::t] );

        case SDLK_u:
            return &( this->letterKeys[letterKeyIndex::u] );

        case SDLK_v:
            return &( this->letterKeys[letterKeyIndex::v] );

        case SDLK_w:
            return &( this->letterKeys[letterKeyIndex::w] );

        case SDLK_x:
            return &( this->letterKeys[letterKeyIndex::x] );

        case SDLK_y:
            return &( this->letterKeys[letterKeyIndex::y] );

        case SDLK_z:
            return &( this->letterKeys[letterKeyIndex::z] );


        // Number keys
        case SDLK_0:
            return &( this->numKeys[numKeyIndex::zero] );

        case SDLK_1:
            return &( this->numKeys[numKeyIndex::one] );

        case SDLK_2:
            return &( this->numKeys[numKeyIndex::two] );

        case SDLK_3:
            return &( this->numKeys[numKeyIndex::three] );

        case SDLK_4:
            return &( this->numKeys[numKeyIndex::four] );

        case SDLK_5:
            return &( this->numKeys[numKeyIndex::five] );

        case SDLK_6:
            return &( this->numKeys[numKeyIndex::six] );

        case SDLK_7:
            return &( this->numKeys[numKeyIndex::seven] );

        case SDLK_8:
            return &( this->numKeys[numKeyIndex::eight] );

        case SDLK_9:
            return &( this->numKeys[numKeyIndex::nine] );


        // Misc keys
        case SDLK_BACKSPACE:
            return &( this->miscKeys[miscKeyIndex::backspace] );

        case SDLK_TAB:
            return &( this->miscKeys[miscKeyIndex::tab] );

        case SDLK_RETURN:
            return &( this->miscKeys[miscKeyIndex::enter] );

        case SDLK_ESCAPE:
            return &( this->miscKeys[miscKeyIndex::escape] );

        case SDLK_SPACE:
            return &( this->miscKeys[miscKeyIndex::space] );

        case SDLK_CAPSLOCK:
            return &( this->miscKeys[miscKeyIndex::capslock] );

        case SDLK_LCTRL:
            return &( this->miscKeys[miscKeyIndex::control] );

        case SDLK_LSHIFT:
            return &( this->miscKeys[miscKeyIndex::shift] );

        case SDLK_LALT:
            return &( this->miscKeys[miscKeyIndex::alt] );


    }

    return nullptr;
}

void State::KeyboardState::setKeyDown(int keyCode) {

    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = true;

    return;

}

void State::KeyboardState::setKeyUp(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = false;

    return;

}

bool State::KeyboardState::keyDown(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) return (*key) == true;
    else return false;

}



/*  ------------------------------------  */
/*  ----------   State   ----------  */
/*  ------------------------------------  */

// Contructor
State::State(bool hasChild /* default value = true */) {

    this->time = new TimeState();
    this->mouse = new MouseState();
    this->keys = new KeyboardState();

    if (hasChild) this->lastFrame = new State(false);
    else this->lastFrame = nullptr;

}

// Destructor
State::~State() {
    if (this->time != nullptr) delete this->time;
    if (this->mouse != nullptr) delete this->mouse;
    if (this->keys != nullptr) delete this->keys;
    if (this->lastFrame != nullptr) delete this->lastFrame;
}

// Instance functions
void State::addEvent(SDL_Event* event) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (event == nullptr) {
        logWrite("Called State->addEvent(SDL_Event*) on a null pointer!", true);
        return;
    }

    // Mouse buttons down
    if ((*event).type == SDL_MOUSEBUTTONDOWN) {

        if ((*event).button.button == SDL_BUTTON_LEFT) {
            this->mouse->leftButtonDown();
        }

        if ((*event).button.button == SDL_BUTTON_RIGHT) {
            this->mouse->rightButtonDown();
        }

        if ((*event).button.button == SDL_BUTTON_MIDDLE) {
            this->mouse->middleButtonDown();
        }

        return;

    }

    // Mouse buttons up
    if ((*event).type == SDL_MOUSEBUTTONUP) {

        if ((*event).button.button == SDL_BUTTON_LEFT) {
            this->mouse->leftButtonUp();
        }

        if ((*event).button.button == SDL_BUTTON_RIGHT) {
            this->mouse->rightButtonUp();
        }

        if ((*event).button.button == SDL_BUTTON_MIDDLE) {
            this->mouse->middleButtonUp();
        }

        return;

    }

    // Keyboard buttons down
    if ((*event).type == SDL_KEYDOWN) {
        this->keys->setKeyDown((*event).key.keysym.sym);
    }

    // Keyboard buttons up
    if ((*event).type == SDL_KEYUP) {
        this->keys->setKeyUp((*event).key.keysym.sym);
    }

    return;
}

void State::nextFrame() {

    if (this->lastFrame == nullptr) return;

    this->lastFrame->setState(this);

    this->time->update();

    return;

}

bool State::wasLeftJustPressed() {
    return (this->mouse->leftButtonIsDown && !this->lastFrame->mouse->leftButtonIsDown);
}

bool State::wasRightJustPressed() {
    return (this->mouse->rightButtonIsDown && !this->lastFrame->mouse->rightButtonIsDown);
}

bool State::wasLeftJustReleased() {
    return (!this->mouse->leftButtonIsDown && this->lastFrame->mouse->leftButtonIsDown);
}

bool State::wasRightJustReleased() {
    return (!this->mouse->rightButtonIsDown && this->lastFrame->mouse->rightButtonIsDown);
}

int State::deltaMousePosX() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posX) - (this->lastFrame->mouse->posX);
}

int State::deltaMousePosY() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posY) - (this->lastFrame->mouse->posY);
}

bool State::keyIsDown(int keyCode) {
    return this->keys->keyDown(keyCode);
}

bool State::keyJustDown(int keyCode) {

    bool isDown = this->keys->keyDown(keyCode);
    bool wasDown = this->lastFrame->keys->keyDown(keyCode);

    return (isDown && !wasDown);

}

void State::setState(State* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called State->setState(State*) on a null pointer!", true);
        return;
    }

    this->mouse->setState(state->mouse);
    this->keys->setState(state->keys);
}

template<typename type>
class LinkedList {

    /*
        Doubly linked list implementation.
        Any type is allowed, and nodes also store an integer id alongside their item
        There is an included iterator, to avoid using ids to iterate
    */

    public:

        class Node {

            /*
                Item for the doubly linked list
                Includes an item, and a int tag
            */

            public:

                /*   Instance Variables   */

                Node* next;
                Node* last;

                type item;
                int id;


                /*   Constructors   */
                Node() {
                    this->next = nullptr;
                    this->last = nullptr;
                    this->item = nullptr;
                    this->id = 0;
                }

                Node(type item) {
                    this->next = nullptr;
                    this->last = nullptr;
                    this->item = item;
                    this->id = 0;
                }

                Node(int id) {
                    this->next = nullptr;
                    this->last = nullptr;
                    this->item = nullptr;
                    this->id = id;
                }

                Node(type item, int id) {
                    this->next = nullptr;
                    this->last = nullptr;
                    this->item = item;
                    this->id = id;
                }


                /*   Instance Functions   */

                // Returns true if this node is the first node in the list.
                bool isFirst() {
                    return (this->last == nullptr);
                }

                // Returns true if this node is the last node in the list.
                bool isLast() {
                    return (this->next == nullptr);
                }
                
                // Logs the node in the format:  last id <- this id -> next id
                void log() {

                    if (this->last == nullptr)
                        logWrite("null");
                    else
                        logWrite(this->last->id);

                    logWrite(" <- ");
                    logWrite(this->id);
                    logWrite(" -> ");

                    if (this->next == nullptr)
                        logWrite("null", true);
                    else
                        logWrite(this->next->id, true);

                    return;

                }

        };

        /*   Instance Variables   */

        int length;


        // Constructor
        LinkedList() {
            this->first = nullptr;
            this->last = nullptr;

            this->length = 0;
            this->nextFreeId = 0;
        }

        // Destructor
        ~LinkedList() {

            Node* currentRef = this->first;
            Node* nextRef = this->first->next;

            while (true) {

                delete currentRef;
                
                // Break case
                if (nextRef == nullptr) break;

                currentRef = nextRef;
                nextRef = currentRef->next;

            }

        }


        /*   Instance Functions   */
        
        void pushBack(type item) {

            this->pushBack(item, this->nextFreeId);
            this->nextFreeId++;
            return;

        }

        void pushBack(type item, int id) {

            Node* newNode = new Node(item, id);

            this->length++;

            // Empty list
            if (this->first == nullptr && this->last == nullptr) {
                this->first = newNode;
                this->last = newNode;
                return;
            }

            // Length 1 list
            if (this->first == this->last) {
                this->last = newNode;
                this->first->next = newNode;
                newNode->last = this->first;
                return;
            }

            // Length >2 list
            this->last->next = newNode;
            newNode->last = this->last;
            this->last = newNode;

            return;

        }

        void pushFront(type item) {

            this->pushFront(item, this->nextFreeId);
            this->nextFreeId++;
            return;

        }

        void pushFront(type item, int id) {

            Node* newNode = new Node(item, id);

            this->length++;

            // Empty list
            if (this->first == nullptr && this->last == nullptr) {
                this->first = newNode;
                this->last = newNode;
                return;
            }

            // Length 1 list
            if (this->first == this->last) {
                this->first = newNode;
                this->last->last = newNode;
                newNode->next = this->last;
                return;
            }

            // Length >2 list
            this->first->last = newNode;
            newNode->next = this->first;
            this->first = newNode;

            return;

        }

        type popBack() {

            Node* ret;
            type item;

            // Empty list
            if (this->first == nullptr && this->last == nullptr) {
                return nullptr;
            }

            this->length--;

            // Length 1 list
            if (this->first == this->last) {

                ret = this->last;
                this->last = nullptr;
                this->first = nullptr;

                item = ret->item;
                delete ret;

                return item;

            }

            // Length >2 list
            ret = this->last;
            this->last = ret->last;
            this->last->next = nullptr;

            item = ret->item;
            delete ret;

            return item;

        }

        type popFront() {

            Node* ret;
            type item;

            // Empty list
            if (this->first == nullptr && this->last == nullptr) {
                return nullptr;
            }

            this->length--;

            // Length 1 list
            if (this->first == this->last) {

                ret = this->first;
                this->last = nullptr;
                this->first = nullptr;

                item = ret->item;
                delete ret;

                return item;

            }

            // Length >2 list
            ret = this->first;
            this->first = ret->next;
            this->first->last = nullptr;

            item = ret->item;
            delete ret;

            return item;

        }

        // Pops the node with this id. If the id doesnt exist in the list, this returns nullptr
        type popById(int id) {

            Node* current = this->first;

            while (true) {

                if (current == nullptr) return nullptr;

                if (current->id == id) {

                    current->last->next = current->next;
                    current->next->last = current->last;

                    type ret = current->item;

                    delete current;
                    this->length--;

                    return ret;

                }

                current = current->next;

            }

        }

        // Returns a reference to the object with a given id. DOES NOT change the internal list.
        type getById(int id) {

            Node* current = this->first;

            while (true) {

                if (current == nullptr) return nullptr;

                if (current->id == id)
                    return current->item;

                current = current->next;

            }

        }

        // Sets the instance variable iterCurrent to an index, from where the other iterator functions can be called
        void iterStart(int index) {

            this->iterCurrent = this->first;

            for (int i = 0; i < index; i++) {

                if (iterCurrent == nullptr) {
                    logWrite("Tried to start at iter at too high of an index! (LinkedList->iterStart(int))");
                    return;
                }

                this->iterCurrent = this->iterCurrent->next;

            }

        }

        // Returns the object of iterCurrent. Returns nullptr if the iterator is at null
        type iterGetObj() {

            if (this->iterCurrent == nullptr) return nullptr;

            return this->iterCurrent->item;

        }

        // Returns the id of iterCurrent. Returns -1 if the iterator is at null
        int iterGetId() {

            if (this->iterCurrent == nullptr) return -1;

            return this->iterCurrent->id;

        }

        // Moves the iterator forward 1
        void iterNext() {

            if (this->iterCurrent == nullptr) return;

            this->iterCurrent = this->iterCurrent->next;
            return;

        }

        // Moves the iterator back 1
        void iterLast() {

            if (this->iterCurrent == nullptr) return;

            this->iterCurrent = this->iterCurrent->last;
            return;

        }

        // Returns true if iterCurrent equals nullptr
        bool iterIsDone() {

            return (this->iterCurrent == nullptr);

        }

        // Logs all of the nodes in the order they stand in the list
        void log() {

            logWrite("LinkedList( length = ");
            logWrite(this->length, true);

            Node* current = this->first;

            while (true) {

                if (current == nullptr) break;

                logWrite("  ");
                current->log();

                current = current->next;

            }

            logWrite(")", true);

            return;

        }

    private:
        
        /*   Instance Variables   */

        // Node objects shouldnt be used outside of the class
        Node* first;
        Node* last;
        Node* iterCurrent;

        // No reason to make this public
        int nextFreeId;


        /*   Instance Functions   */

        // Swaps the two nodes in the list. This changes the affected nodes, as well as those around them.
        void swap(Node* node1, Node* node2) {

            // Different handling for when the two nodes are adjacent
            if (node1->next == node2) {
                
                // Update adjacent node pointers
                if (node1->last != nullptr) node1->last->next = node2;
                else this->first = node2;
                if (node2->next != nullptr) node2->next->last = node1;
                else this->last = node1;

                // Update affected node pointers
                node1->next = node2->next;
                node2->next = node1;

                node2->last = node1->last;
                node1->last = node2;

                return;

            }

            if (node2->next == node2) {
                
                // Update adjacent node pointers
                if (node2->last != nullptr) node2->last->next = node1;
                else this->first = node1;
                if (node1->next != nullptr) node1->next->last = node2;
                else this->last = node2;

                // Update affected node pointers
                node2->next = node1->next;
                node1->next = node2;

                node1->last = node2->last;
                node2->last = node1;

                return;

            }

            // Get adjacent nodes
            Node* node1Last = node1->last;
            Node* node1Next = node1->next;

            Node* node2Last = node2->last;
            Node* node2Next = node2->next;

            // Update adjacent node pointers
            if (node1Last != nullptr) node1Last->next = node2;
            if (node1Next != nullptr) node1Next->last = node2;

            if (node2Last != nullptr) node2Last->next = node1;
            if (node2Next != nullptr) node2Next->last = node1;

            // Update affected node pointers
            node1->next = node2Next;
            node1->last = node2Last;

            node2->last = node1Last;
            node2->next = node1Next;

            return;

        }

};

class Color {

    public:

        // Constant color codes
        // Bytes are [opacity][red][green][blue]
        static const Uint32 RED    = 0xFFFF0000;
        static const Uint32 GREEN  = 0xFF00FF00;
        static const Uint32 BLUE   = 0xFF0000FF;
        static const Uint32 BLACK  = 0xFF000000;
        static const Uint32 WHITE  = 0xFFFFFFFF;
        static const Uint32 GREY   = 0xFF888888;


        /*   Instance variables   */

        // Raw value which was given
        Uint32 rawValue;

        // Individual color channels
        Uint8 redValue, greenValue, blueValue, opacityValue;


        // Contructors
        Color(Uint32 color);
        Color(Uint8 o, Uint8 r, Uint8 g, Uint8 b);


        /*   Class functions   */

        // Sets the brightness of a given color (Uint32) to a double between 0-1.
        // Values higher than 1 CAN be used, but could cause overflow issues.
        static Uint32 setBrightness(Uint32 color, double newBrightness);

};



class PNG {

    /*
        This class holds data to describe a PNG file.
        This class makes use of the library 'lodepng', which was NOT written by me.
    */

    public:

        // Indexes for color channels of each pixel in the buffer array returned by lodepng
        // I just used char becuase they dont need to be big
        static const char RED = 0;
        static const char GREEN = 1;
        static const char BLUE = 2;
        static const char OPACITY = 3;


        /*   Instance variables   */

        // This is the filename of the PNG file which was loaded for this instance.
        const char* fileName;

        // Size of the PNG
        unsigned int width, height;

        // Raw data returned from lodepng. This is an array of length (width * height * 4 color channels)
        Uint8* rawData;

        // This holds the same data as rawData, but parsed by my constructor to be more usable.
        Color** pixels;


        /*   Contructors   */

        // Takes a filename/filepath and uses a function from lodepng to get its pixel data.
        PNG(const char* filename);

        // Allows taking an existing PNG object, and pulling a subset of pixels from it.
        PNG(PNG* input, int startx, int starty, int endx, int endy);

        // Destructor
        ~PNG();


        /*   Instance Functions   */

        // Returns a Color object represeting the pixel data at (x, y) in the PNG
        Color* getPixel(int x, int y);

        // Sets the pixel value at (x, y)
        bool setPixel(int x, int y, Color* pixel);

        // Same as above, but for single color channels
        Uint8 getChannel(int x, int y, char channel);
        bool setChannel(int x, int y, char channel, Uint8 value);

};



class Drawer {

    /*
        This class acts as a function set to draw to a gui window.
        A pixel buffer is the only SDL2 functionality I allowed myself to do, so this class implements all the drawing functions I need.
        The pixel buffer is simply a single dimension array, and the buffer width represents the length of each 'set' within the array.
        Treating the pixel buffer as a 2d array acts as follows:
        buffer[2][3] = buffer[(2 * bufferHeight) + 3], where 2,3 is x,y
        This class supports the use of depth. When including depth values into function calls, the depthBuffer will be checked before writing pixels
        Depth is optional, and any call where depth is not included will be drawn at depth 0, while NOT updating the depthBuffer values
    */

    public:
        
        /*   Instance variables   */
        
        Uint32* buffer;
        unsigned int bufferHeight, bufferWidth;
        unsigned int bufferSize;

        // The depth buffer stores the distance between each pixel and the camera. this allows meshes to be drawn in any order while appearing accurately.
        double* depthBuffer;


        // Constructors
        Drawer(unsigned int bufferWidthInput, unsigned int bufferHeightInput);
        Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput);

        // Destructor
        ~Drawer();


        /*   Instance functions   */

        // Sets all the values in the depth buffer to infinity
        void resetDepthBuffer();

        // Returns the 1d index cooresponding to a 2d set of indices
        int bufferIndex(int x, int y);

        // Returns true if the coordinate exists in the buffer
        bool inBufferRange(int x, int y);

        // Writes a color to a coordinate within the buffer. Foundation for all further drawing functions.
        void writePixel(Uint32 pixel, int x, int y);
        void writePixel(Uint32 pixel, int x, int y, double depth);

        // Draws a straight line from (x1, y1) to (x2, y2) in the given color
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2);
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2, double depth1, double depth2);

        // Same as above, but uses Vec2 objects. These objects are NOT deleted by this function call and must be handled properly
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to);
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to, double depth1, double depth2);

        // Draws a straight line along a given axis. Similar to drawLine, but less complex.
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x);
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x, double depth1, double depth2);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y, double depth1, double depth2);

        // Draws a FILLED rectangle from (x1, y1) to (x2, y2)
        void drawRect(Uint32 pixel, int x1, int y1, int x2, int y2);

        // Fills whole buffer with a given color
        void fillScreen(Uint32 pixel);

        // Draws an elipse at a given location, with a given radius along each axis.
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy);
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy, double depth);

        // Same as above, but only one radius allowed.
        void drawCircle(Uint32 pixel, int locationx, int locationy, int radius);
        void drawCircle(Uint32 pixel, int locationx, int locationy, int radius, double depth);

        // Draws a FILLED triangle which uses (x1, y1), (x2, y2), and (x3, y3) as vertices
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3);
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, double depth1, double depth2, double depth3);

        // Same as above but uses a Tri object. This object is NOT deleted by this function call and must be handled properly. The Tri3 call includes depth.
        void drawTriangle(Uint32 pixel, Tri2* tri);
        void drawTriangle(Uint32 pixel, Tri3* tri);

        // Draws a PNG file using a PNG object. the top left corner of the PNG will lie at (x, y)
        void drawpng(PNG* file, int x, int y);
        void drawpng(PNG* file, int x, int y, double depth);

        // Adds a point to the depth buffer range. This updates the range if the point lies outside the current range
        void addPoint(int x, int y);

};



class Font {

    /*
        This class holds data to print text characters to the screen
        Before using, an instance must be made by referencing a drawer instance so that this class can actually draw
        The contructor here loads all the pixel arts for each text character
    */

    public:

        // Instance Variables
        Drawer* drawer;

        // Constructors
        Font();
        Font(Drawer* drawer);

        /*   Instance Functions   */

        // Loads the character pixel arts into memory
        void init();

        // Returns a pointer to the pixels for a character
        bool* getCharRef(char ch);
        bool* getCharRef(int num);

        // Draws a set of pixels to the screen. the other draw functions rely on this
        void drawPixels(bool* pixels, int x, int y, Uint32 color);

        // Draws a character to the screen, the upper left will be at (x, y)
        void drawChar(char ch, int x, int y, Uint32 color);

        // Draws a string to the screen, the top left will be at (x, y)
        void drawString(const char* string, int x, int y, Uint32 color);

        // Draws an integer value to the screen, the top left will be at (x, y)
        void drawInt(int num, int x, int y, Uint32 color);
    
    private:

        /*
            Character Pixel Arts
            This bool** type is a list of lists of bools.
            The primary list is length 38 for the amount of chars which can be drawn
            Each of the sub lists is length 49, which gives a 7x7 grid of pixels per char
            This list is filled by running init
        */

        bool** chars;

        // Here you can see the data which is used to create the bool lists
        // underscore is 0 (false) and 0 is 1 (true), the bool values coorespond to if they are shown or not when drawing
        // All the seperate strings here get put together by the compiler into one big string, so the /n chars are the seperators
        // | acts as a line end char
        // String length is: char size + 1 * char count + 1 = length 2110 
        const char* rawChars = {

            // A
            "_______|"
            "__000__|"
            "_0___0_|"
            "_00000_|"
            "_0___0_|"
            "_0___0_|"
            "_______|"
            "\n"

            // B
            "_______|"
            "_0000__|"
            "_0___0_|"
            "_0000__|"
            "_0___0_|"
            "_0000__|"
            "_______|"
            "\n"

            // C
            "_______|"
            "__0000_|"
            "_0_____|"
            "_0_____|"
            "_0_____|"
            "__0000_|"
            "_______|"
            "\n"

            // D
            "_______|"
            "_0000__|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "_0000__|"
            "_______|"
            "\n"

            // E
            "_______|"
            "_00000_|"
            "_0_____|"
            "_0000__|"
            "_0_____|"
            "_00000_|"
            "_______|"
            "\n"

            // F
            "_______|"
            "_00000_|"
            "_0_____|"
            "_0000__|"
            "_0_____|"
            "_0_____|"
            "_______|"
            "\n"

            // G
            "_______|"
            "_00000_|"
            "_0_____|"
            "_0__00_|"
            "_0___0_|"
            "_00000_|"
            "_______|"
            "\n"

            // H
            "_______|"
            "_0___0_|"
            "_0___0_|"
            "_00000_|"
            "_0___0_|"
            "_0___0_|"
            "_______|"
            "\n"

            // I
            "_______|"
            "_00000_|"
            "___0___|"
            "___0___|"
            "___0___|"
            "_00000_|"
            "_______|"
            "\n"

            // J
            "_______|"
            "_00000_|"
            "___0___|"
            "___0___|"
            "___0___|"
            "_00____|"
            "_______|"
            "\n"

            // K
            "_______|"
            "_0___0_|"
            "_0__0__|"
            "_000___|"
            "_0__0__|"
            "_0___0_|"
            "_______|"
            "\n"

            // L
            "_______|"
            "_0_____|"
            "_0_____|"
            "_0_____|"
            "_0_____|"
            "_00000_|"
            "_______|"
            "\n"

            // M
            "_______|"
            "_0___0_|"
            "_00000_|"
            "_0_0_0_|"
            "_0___0_|"
            "_0___0_|"
            "_______|"
            "\n"

            // N
            "_______|"
            "_0___0_|"
            "_00__0_|"
            "_0_0_0_|"
            "_0__00_|"
            "_0___0_|"
            "_______|"
            "\n"

            // O
            "_______|"
            "__000__|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "__000__|"
            "_______|"
            "\n"

            // P
            "_______|"
            "_0000__|"
            "_0___0_|"
            "_0000__|"
            "_0_____|"
            "_0_____|"
            "_______|"
            "\n"

            // Q
            "_______|"
            "__000__|"
            "_0___0_|"
            "_0___0_|"
            "__000__|"
            "____00_|"
            "_______|"
            "\n"

            // R
            "_______|"
            "_0000__|"
            "_0___0_|"
            "_0000__|"
            "_0__0__|"
            "_0___0_|"
            "_______|"
            "\n"

            // S
            "_______|"
            "__0000_|"
            "_0_____|"
            "__000__|"
            "_____0_|"
            "_0000__|"
            "_______|"
            "\n"

            // T
            "_______|"
            "_00000_|"
            "___0___|"
            "___0___|"
            "___0___|"
            "___0___|"
            "_______|"
            "\n"

            // U
            "_______|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "__000__|"
            "_______|"
            "\n"

            // V
            "_______|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "__0_0__|"
            "___0___|"
            "_______|"
            "\n"

            // W
            "_______|"
            "_0___0_|"
            "_0___0_|"
            "_0_0_0_|"
            "_00_00_|"
            "_0___0_|"
            "_______|"
            "\n"

            // X
            "_______|"
            "_0___0_|"
            "__0_0__|"
            "___0___|"
            "__0_0__|"
            "_0___0_|"
            "_______|"
            "\n"

            // Y
            "_______|"
            "_0___0_|"
            "__0_0__|"
            "___0___|"
            "___0___|"
            "___0___|"
            "_______|"
            "\n"

            // Z
            "_______|"
            "_00000_|"
            "____0__|"
            "___0___|"
            "__0____|"
            "_00000_|"
            "_______|"
            "\n"

            // 0
            "_______|"
            "__000__|"
            "_0__00_|"
            "_0_0_0_|"
            "_00__0_|"
            "__000__|"
            "_______|"
            "\n"

            // 1
            "_______|"
            "__00___|"
            "_0_0___|"
            "___0___|"
            "___0___|"
            "_00000_|"
            "_______|"
            "\n"

            // 2
            "_______|"
            "__000__|"
            "_0___0_|"
            "___00__|"
            "__0____|"
            "_00000_|"
            "_______|"
            "\n"

            // 3
            "_______|"
            "__000__|"
            "_____0_|"
            "___00__|"
            "_____0_|"
            "__000__|"
            "_______|"
            "\n"

            // 4
            "_______|"
            "___0___|"
            "__00___|"
            "_0_0___|"
            "_00000_|"
            "___0___|"
            "_______|"
            "\n"

            // 5
            "_______|"
            "_00000_|"
            "_0_____|"
            "_0000__|"
            "_____0_|"
            "_0000__|"
            "_______|"
            "\n"

            // 6
            "_______|"
            "__000__|"
            "_0_____|"
            "_0000__|"
            "_0___0_|"
            "__000__|"
            "_______|"
            "\n"

            // 7
            "_______|"
            "_00000_|"
            "____0__|"
            "___0___|"
            "__0____|"
            "_0_____|"
            "_______|"
            "\n"
            
            // 8
            "_______|"
            "__000__|"
            "_0___0_|"
            "__000__|"
            "_0___0_|"
            "__000__|"
            "_______|"
            "\n"

            // 9
            "_______|"
            "__000__|"
            "_0___0_|"
            "__0000_|"
            "_____0_|"
            "__000__|"
            "_______|"
            "\n"

            // Space
            "_______|"
            "_______|"
            "_______|"
            "_______|"
            "_______|"
            "_______|"
            "_______|"
            "\n"

            // Disallowed char
            "_______|"
            "_00000_|"
            "_00_00_|"
            "_0_0_0_|"
            "_00_00_|"
            "_00000_|"
            "_______|"
            "\n"

        };

};

/* --------------------------- */
/* ---------- Color ---------- */
/* --------------------------- */

// Contructors
Color::Color(Uint32 color) {

    this->rawValue = color;

    // This gets the sub values at each 8 bit interval of the 32 bit input
    this->opacityValue = (Uint8) (color >> 24);
    this->redValue = (Uint8) (color >> 16);
    this->greenValue = (Uint8) (color >> 8);
    this->blueValue = (Uint8) (color);
}

Color::Color(Uint8 o, Uint8 r, Uint8 g, Uint8 b) {

    this->redValue = r;
    this->greenValue = g;
    this->blueValue = b;
    this->opacityValue = o;
    
    // Load each 8 sub bits into a bigger variable
    this->rawValue = 0x00000000;
    this->rawValue |= o;
    this->rawValue <<= 8;
    this->rawValue |= r;
    this->rawValue <<= 8;
    this->rawValue |= g;
    this->rawValue <<= 8;
    this->rawValue |= b;
}

// Class functions
Uint32 Color::setBrightness(Uint32 color, double newBrightness) {

    // Unpack color code
    Uint8 opacityValue = (Uint8) (color >> 24);
    Uint8 redValue = (Uint8) (color >> 16);
    Uint8 greenValue = (Uint8) (color >> 8);
    Uint8 blueValue = (Uint8) (color);

    // Update values
    redValue *= newBrightness;
    greenValue *= newBrightness;
    blueValue *= newBrightness;

    // Repack color code
    Uint32 newColor = 0x00000000;
    newColor |= opacityValue;
    newColor <<= 8;
    newColor |= redValue;
    newColor <<= 8;
    newColor |= greenValue;
    newColor <<= 8;
    newColor |= blueValue;

    return newColor;

}



/* ------------------------- */
/* ---------- PNG ---------- */
/* ------------------------- */

// Constructor from filename
PNG::PNG(const char* filename) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (fileName == nullptr) {
        logWrite("Called PNG->PNG(const char*) on a null pointer!", true);
        return;
    }

    std::vector<unsigned char> returnData;
    unsigned int failed = lodepng::decode(returnData, this->width, this->height, filename);

    if (failed) {
        std::cerr << "Error loading PNG file: " << lodepng_error_text(failed) << std::endl;
        return;
    }

    this->fileName = filename;
    int size = this->width * this->height;
    this->rawData = new Uint8[size * 4];
    this->pixels = new Color*[size];

    for (int i = 0; i < size * 4; i += 4) {

        Uint8 r = (Uint8) returnData[i];
        Uint8 g = (Uint8) returnData[i + 1];
        Uint8 b = (Uint8) returnData[i + 2];
        Uint8 o = (Uint8) returnData[i + 3];

        this->rawData[i] = r;
        this->rawData[i + 1] = g;
        this->rawData[i + 2] = b;
        this->rawData[i + 3] = o;

        this->pixels[i / 4] = new Color(o, r, g, b);

    }
    
    return;

}

// Constructor from other PNG object
PNG::PNG(PNG* input, int startx, int starty, int endx, int endy) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (input == nullptr) {
        logWrite("Called PNG->PNG(PNG*, int, int, int, int) on a null pointer!", true);
        return;
    }

    this->width = (endx - startx);
    this->height = (endy - starty);

    this->fileName = nullptr;
    int size = this->width * this->height;
    this->rawData = new Uint8[size * 4];
    this->pixels = new Color*[size];

    for (int i = 0; i < size; i += 1) {

        int x = ((i % this->width) + startx);
        int y = (int) (i / this->width) + (starty);

        Uint8 r = input->getChannel( x, y, RED);
        Uint8 g = input->getChannel( x, y, GREEN);
        Uint8 b = input->getChannel( x, y, BLUE);
        Uint8 o = input->getChannel( x, y, OPACITY);

        if (r == -1 || g == -1 || b == -1 || o == -1) {
            std::cout << "color channel failed to get" << std::endl;
            system("pause");
            return;
        }

        this->rawData[i * 4] = r;
        this->rawData[(i * 4) + 1] = g;
        this->rawData[(i * 4) + 2] = b;
        this->rawData[(i * 4) + 3] = o;

        this->pixels[i] = new Color(o, r, g, b);

    }
    
    return;

}

// Destructor
PNG::~PNG() {

    for (int i = 0; i < this->width * this-> height; i++) {
        delete this->pixels[i];
    }

    delete[] this->rawData;
    delete[] this->pixels;

    return;

}

// Instance Functions
Color* PNG::getPixel(int x, int y) {

    if (x >= this->width || y >= this->height) return nullptr;

    return this->pixels[ (this->width * y) + x ];

}

bool PNG::setPixel(int x, int y, Color* pixel) {

    if (x >= this->width || y >= this->height) return false;

    if (pixel == nullptr) return false;

    this->pixels[ (this->width * y) + x ] = pixel;

    return true;

}

Uint8 PNG::getChannel(int x, int y, char channel) {

    if (x >= this->width || y >= this->height) return -1;

    if (channel > 3 || channel < 0) return -1;

    return this->rawData[ (((this->width * y) + x) * 4) + channel];

}

bool PNG::setChannel(int x, int y, char channel, Uint8 value) {
    
    if (x >= this->width || y >= this->height) return false;

    if (channel > 3 || channel < 0) return false;

    this->rawData[ (((this->width * y) + x) * 4) + channel] = value;

    return true;

}



/* ---------------------------- */
/* ---------- Drawer ---------- */
/* ---------------------------- */

// Constructors
Drawer::Drawer(unsigned int bufferWidthInput, unsigned int bufferHeightInput) {

    this->buffer = nullptr;
    this->bufferWidth = bufferWidthInput;
    this->bufferHeight = bufferHeightInput;
    this->bufferSize = bufferHeightInput * bufferWidthInput;

    // Depth buffer
    this->depthBuffer = new double[this->bufferSize];
    for (int i = 0; i < this->bufferSize; i++)
        this->depthBuffer[i] = inf;

}

Drawer::Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput) {

    this->buffer = buffer;
    this->bufferWidth = bufferWidthInput;
    this->bufferHeight = bufferHeightInput;
    this->bufferSize = bufferHeightInput * bufferWidthInput;

    // Depth buffer
    this->depthBuffer = new double[this->bufferSize];
    for (int i = 0; i < this->bufferSize; i++)
        this->depthBuffer[i] = inf;

}

// Destructor
Drawer::~Drawer() {
    delete[] this->depthBuffer;
}

// Instance functions
void Drawer::resetDepthBuffer() {

    for (int i = 0; i < this->bufferSize; i++)
        this->depthBuffer[i] = inf;

}

int Drawer::bufferIndex(int x, int y) {

    if (!this->inBufferRange(x, y)) return -1;

    return (y * this->bufferWidth) + x;

}

bool Drawer::inBufferRange(int x, int y) {

    return (
        x >= 0 &&
        x < this->bufferWidth &&
        y >= 0 &&
        y < this->bufferHeight
    );

}

void Drawer::writePixel(Uint32 pixel, int x, int y) {

    if (this->buffer == nullptr) {
        return;
    }

    // Get index, and skip if its outside the buffer size
    int index = this->bufferIndex(x, y);
    if (index == -1) return;

    buffer[index] = pixel;

    return;
    
}

void Drawer::writePixel(Uint32 pixel, int x, int y, double depth) {

    if (this->buffer == nullptr) {
        return;
    }

    int index = this->bufferIndex(x, y);
    if (index == -1) return;

    if (depth > this->depthBuffer[index]) return;

    buffer[index] = pixel;
    depthBuffer[index] = depth;

    return;
}

void Drawer::drawLine(Uint32 pixel, int x1, int y1, int x2, int y2) {

    if (this->buffer == nullptr) {
        return;
    }
    
    int distx = x2 - x1;
    int disty = y2 - y1;

    int totalDist = max(abs(distx), abs(disty));

    for (int i = 0; i < totalDist; i++) {
        int x = floor( (x1) + (distx * ( (double) i / totalDist)) );
        int y = floor( (y1) + (disty * ( (double) i / totalDist)) );
        this->writePixel(pixel, x, y);
    }

    return;

}

void Drawer::drawLine(Uint32 pixel, int x1, int y1, int x2, int y2, double depth1, double depth2) {

    if (this->buffer == nullptr) {
        return;
    }
    
    int distx = x2 - x1;
    int disty = y2 - y1;
    double distDepth = depth2 - depth1;

    int totalDist = max(abs(distx), abs(disty));

    for (int i = 0; i < totalDist; i++) {
        int x = floor( (x1) + (distx * ( (double) i / totalDist)) );
        int y = floor( (y1) + (disty * ( (double) i / totalDist)) );
        double d = (depth1) + (distDepth * ( (double) i / totalDist ));
        this->writePixel(pixel, x, y, d);
    }

    return;

}

void Drawer::drawLine(Uint32 pixel, Vec2* from, Vec2* to) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (from == nullptr) {
        logWrite("Called Drawer->drawLine(Uint32, Vec2*, Vec2*) with 'from' as a null pointer!", true);
        return;
    }

    if (to == nullptr) {
        logWrite("Called Drawer->drawLine(Uint32, Vec2*, Vec2*) with 'to' as a null pointer!", true);
        return;
    }

    this->drawLine(pixel, from->x, from->y, to->x, to->y);
    return;

}

void Drawer::drawLine(Uint32 pixel, Vec2* from, Vec2* to, double depth1, double depth2) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (from == nullptr) {
        logWrite("Called Drawer->drawLine(Uint32, Vec2*, Vec2*) with 'from' as a null pointer!", true);
        return;
    }

    if (to == nullptr) {
        logWrite("Called Drawer->drawLine(Uint32, Vec2*, Vec2*) with 'to' as a null pointer!", true);
        return;
    }

    this->drawLine(pixel, from->x, from->y, to->x, to->y, depth1, depth2);
    return;

}

void Drawer::drawVerticalLine(Uint32 pixel, int y1, int y2, int x) {

    if (y1 > y2) {
        swap(&y1, &y2);
    }

    for (int i = y1; i <= y2; i++) {
        this->writePixel(pixel, x, i);
    }

}

void Drawer::drawVerticalLine(Uint32 pixel, int y1, int y2, int x, double depth1, double depth2) {

    // Skip if coordinates are out of range
    if (!this->inBufferRange(x, y1) && !this->inBufferRange(x, y2)) return;

    if (y1 == y2) {
        double d = min(depth1, depth2);
        this->writePixel(pixel, x, y1, d);
        return;
    }

    double depthSlope;
    double d;

    if (y1 < y2) {

        depthSlope = (depth2 - depth1) / (y2 - y1);
        d = depth1;

        for (int i = y1; i <= y2; i++) {
            this->writePixel(pixel, x, i, d);
            d += depthSlope;
        }


    }

    else {

        depthSlope = (depth1 - depth2) / (y1 - y2);
        d = depth2;

        for (int i = y2; i <= y1; i++) {
            this->writePixel(pixel, x, i, d);
            d += depthSlope;
        }


    }

}

void Drawer::drawHorizontalLine(Uint32 pixel, int startX, int endX, int y) {
    for (int i = startX; i <= endX; i++) {
        this->writePixel(pixel, i, y);
    }
}

void Drawer::drawHorizontalLine(Uint32 pixel, int startX, int endX, int y, double depth1, double depth2) {

    double distDepth = depth2 - depth1;

    for (int i = startX; i <= endX; i++) {
        double d = depth1 + (distDepth * ( (i - startX) / (endX - startX) ));
        this->writePixel(pixel, i, y, d);
    }
}

void Drawer::drawRect(Uint32 pixel, int startx, int starty, int endx, int endy) {

    if (this->buffer == nullptr) {
        return;
    }

    int incerementI = 1;
    int incerementJ = 1;

    if ( startx > endx ) incerementI = -1;
    if ( starty > endy ) incerementJ = -1;

    for (int i = startx; i != endx; i += incerementI) {
        for (int j = starty; j != endy; j += incerementJ) {
            this->writePixel(pixel, i, j);
        }
    }

    return;
}

void Drawer::fillScreen(Uint32 pixel) {
    this->drawRect(pixel, 0, 0, this->bufferWidth, this->bufferHeight);
}

void Drawer::drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy) {

    int limit = radiusx * radiusy;
    double factorx = sqrt( radiusy / radiusx );
    double factory = 1 / factorx;

    for (int i = -radiusx; i < radiusx; i++) {
        for (int j = -radiusy; j < radiusy; j++) {

            if ( ((factorx * i) * (factorx * i)) + ((factory * j) * (factory * j)) < limit ) {
                this->writePixel(pixel, locationx + i, locationy + j);
            }
            
        }
    }
}

void Drawer::drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy, double depth) {

    int limit = radiusx * radiusy;
    double factorx = sqrt( radiusy / radiusx );
    double factory = 1 / factorx;

    for (int i = -radiusx; i < radiusx; i++) {
        for (int j = -radiusy; j < radiusy; j++) {

            if ( ((factorx * i) * (factorx * i)) + ((factory * j) * (factory * j)) < limit ) {
                this->writePixel(pixel, locationx + i, locationy + j, depth);
            }
            
        }
    }
}

void Drawer::drawCircle(Uint32 pixel, int locationx, int locationy, int radius) {

    int limit = radius * radius;

    for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {

            if ( (i * i) + (j * j) < limit ) {
                this->writePixel(pixel, locationx + i, locationy + j);
            }
            
        }
    }
}

void Drawer::drawCircle(Uint32 pixel, int locationx, int locationy, int radius, double depth) {

    int limit = radius * radius;

    for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {

            if ( (i * i) + (j * j) < limit ) {
                this->writePixel(pixel, locationx + i, locationy + j, depth);
            }
            
        }
    }
}

void Drawer::drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle
        First find where each point stands in relation to eachother, then from the lowest x go to the highest x
    */

    // When all 3 points have the same coordinates we just return and draw nothing
    if ( x1 == x2 && x2 == x3 && y1 == y2 && y2 == y3 ) return;

    // Cases where the 'triangle' should just be drawn as a line, meaning two verticies share the same coordinates
    if ( x1 == x2 && y1 == y2 ) {
        this->drawLine(pixel, x1, y1, x3, y3);
        return;
    }

    if ( x1 == x3 && y1 == y3 ) {
        this->drawLine(pixel, x1, y1, x2, y2);
        return;
    }

    if ( x2 == x3 && y2 == y3 ) {
        this->drawLine(pixel, x2, y2, x1, y1);
        return;
    }

    // Sort the coordinates by their x values from least to greatest (left to right)
    if (x2 < x1) {
        swap(&x1, &x2);
        swap(&y1, &y2);
    }

    if (x3 < x1) {
        swap(&x1, &x3);
        swap(&y1, &y3);
    }

    if (x3 < x2) {
        swap(&x2, &x3);
        swap(&y2, &y3);
    }

    // These are the y values the line will go to/from for each x
    // The doubles store the actual value, and the ints are rounded
    // The actual values may not actually be start and end as they say and might be backwards, thats why the min and max functions are used later
    int startY, endY;
    double actualStartY = y1;
    double actualEndY = y1;

    // Find slopes, 1e250 slope means that they have the same x value
    double slopeLeftMid;
    double slopeMidRight;
    double slopeLeftRight;

    // Slope between left-most point and the middle point
    if (x1 != x2) slopeLeftMid = ((double) (y2 - y1)) / (double) (x2 - x1);
    else slopeLeftMid = inf; // just a big number representing infinity

    // Slope between middle point and the right-most point
    if (x2 != x3) slopeMidRight = ((double) (y3 - y2)) / (double) (x3 - x2);
    else slopeMidRight = inf; // just a big number representing infinity

    // Slope between the left-most point and the right-most point
    if (x1 != x3) slopeLeftRight = ((double) (y3 - y1)) / (double) (x3 - x1);
    else slopeLeftRight = inf; // just a big number representing infinity

    // this checks if all the points have the same x coordinate and draws a single line accordingly
    // Since the points are sorted, if the lowest (left) and highest (right) have the same x, so does the middle
    if (slopeLeftRight == inf) {
        startY = min(min(y1, y2), y3);
        endY = max(max(y1, y2), y3);
        this->drawVerticalLine(pixel, startY, endY, x1);
        return;
    }

    // From left to right until the mid vertex is hit
    if (slopeLeftMid != inf) {
        for (int i = x1; i < x2; i++) {

            actualStartY += slopeLeftMid;
            actualEndY += slopeLeftRight;

            startY = min(actualStartY, actualEndY);
            endY = max(actualStartY, actualEndY);

            this->drawVerticalLine(pixel, startY, endY, i);

        }
    
    // When the two left points have the same x, the startY and endY need to be adjusted becuase the first loop was skipped
    } else {
        actualStartY = y2;
        actualEndY = y1;
    }
    
    // Carry on from the last loop
    if (slopeMidRight != inf) {
        for (int i = x2; i < x3; i++) {

            actualStartY += slopeMidRight;
            actualEndY += slopeLeftRight;

            startY = min(actualStartY, actualEndY);
            endY = max(actualStartY, actualEndY);

            this->drawVerticalLine(pixel, startY, endY, i);

        }
    }

    return;

}

void Drawer::drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, double depth1, double depth2, double depth3) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle
        First find where each point stands in relation to eachother, then from the lowest x go to the highest x
    */
  

    bool oneIsTwo = (x1 == x2) && (y1 == y2);
    bool twoIsThree = (x2 == x3) && (y2 == y3);
    bool oneIsThree = (x1 == x3) && (y1 == y3);

    // Cases where the 'triangle' has more than one point with the same coordinates, so these are checked here for quick handling
    if ( oneIsTwo ) {

        // If two also equals three, all three coordinates are the same, so just return.
        // I should draw a single pixel in this case, but its not really worth it as it will barely be noticable
        if (twoIsThree) return;

        this->drawLine(pixel, x1, y1, x3, y3, depth1, depth3);
        return;

    }

    // Either of these cases draw the same line
    if ( oneIsThree || twoIsThree) {
        this->drawLine(pixel, x1, y1, x2, y2, depth1, depth2);
        return;
    }


    // Sort the coordinates by their x values from least to greatest (left to right)
    if (x2 < x1) {
        swap(&x1, &x2);
        swap(&y1, &y2);
        swap(&depth1, &depth2);
    }

    if (x3 < x1) {
        swap(&x1, &x3);
        swap(&y1, &y3);
        swap(&depth1, &depth3);
    }

    if (x3 < x2) {
        swap(&x2, &x3);
        swap(&y2, &y3);
        swap(&depth2, &depth3);
    }

    // These are the y values the line will go to/from for each x
    // The doubles store the actual value, and the ints are rounded
    // The actual values may not actually be start and end as they say and might be backwards
    double startY = (double) y1;
    double endY = (double) y1;
    int startYInt, endYInt;

    double slope12;
    double slope23;
    double slope13;

    double startDepth = depth1;
    double endDepth = depth1;

    double slopeDepth12;
    double slopeDepth23;
    double slopeDepth13;

    bool invalidSlope12 = false;
    bool invalidSlope23 = false;
    bool invalidSlope13 = false;


    // Slope between left-most point and the middle point
    if (x1 != x2) {
        slope12 = (double) (y2 - y1) / (x2 - x1);
        slopeDepth12 = (depth2 - depth1) / (x2 - x1);
    }

    else invalidSlope12 = true;

    // Slope between middle point and the right-most point
    if (x2 != x3) {
        slope23 = (double) (y3 - y2) / (x3 - x2);
        slopeDepth23 = (depth3 - depth2) / (x3 - x2);
    }

    else invalidSlope23 = true;

    // Slope between the left-most point and the right-most point
    if (x1 != x3) {
        slope13 = (double) (y3 - y1) / (x3 - x1);
        slopeDepth13 = (depth3 - depth1) / (x3 - x1);
    }

    else invalidSlope13 = true;


    // this checks if all the points have the same x coordinate and draws a single line accordingly (in two parts)
    // If the slope between 1 and 2, and the slope between 2 and 3 are both inf, theres no need to check the slope between 1 and 3.
    if (invalidSlope13) {

        if (y1 < y2)
            this->drawVerticalLine(pixel, y1, y2, x1, depth1, depth2);
        else
            this->drawVerticalLine(pixel, y2, y1, x1, depth2, depth1);

        if (y2 < y3)
            this->drawVerticalLine(pixel, y2, y3, x1, depth2, depth3);
        else
            this->drawVerticalLine(pixel, y3, y2, x1, depth3, depth2);

        return;

    }

    // From left to right until the mid vertex is hit
    if (!invalidSlope12) {

        for (int i = x1; i < x2; i++) {

            startY += slope12;
            endY += slope13;

            startYInt = (int) startY;
            endYInt = (int) endY;

            startDepth += slopeDepth12;
            endDepth += slopeDepth13;

            this->drawVerticalLine(pixel, startYInt, endYInt, i, startDepth, endDepth);

        }

    }
    
    // When the two left points have the same x, the startY and endY need to be adjusted becuase the first loop was skipped
    else {

        startY = (double) y2;
        endY = (double) y1;

        startDepth = depth2;
        endDepth = depth1;

    }
    
    // Carry on from the last loop
    if (!invalidSlope23) {

        for (int i = x2; i < x3; i++) {

            startY += slope23;
            endY += slope13;

            startYInt = (int) startY;
            endYInt = (int) endY;

            startDepth += slopeDepth23;
            endDepth += slopeDepth13;

            this->drawVerticalLine(pixel, startYInt, endYInt, i, startDepth, endDepth);

        }

    }

    return;

}

void Drawer::drawTriangle(Uint32 pixel, Tri2* tri) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (tri == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) on a null pointer!", true);
        return;
    }

    if (tri->v1 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v1 as a null pointer", true);
        return;
    }

    if (tri->v2 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v2 as a null pointer", true);
        return;
    }

    if (tri->v3 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v3 as a null pointer", true);
        return;
    }
    
    int x1 = (int) round(tri->v1->x);
    int y1 = (int) round(tri->v1->y);
    int x2 = (int) round(tri->v2->x);
    int y2 = (int) round(tri->v2->y);
    int x3 = (int) round(tri->v3->x);
    int y3 = (int) round(tri->v3->y);

    this->drawTriangle(pixel, x1, y1, x2, y2, x3, y3);

    return;

}

void Drawer::drawTriangle(Uint32 pixel, Tri3* tri) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (tri == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) on a null pointer!", true);
        return;
    }

    if (tri->v1 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v1 as a null pointer", true);
        return;
    }

    if (tri->v2 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v2 as a null pointer", true);
        return;
    }

    if (tri->v3 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v3 as a null pointer", true);
        return;
    }
    
    int x1 = (int) round(tri->v1->x);
    int y1 = (int) round(tri->v1->y);
    int x2 = (int) round(tri->v2->x);
    int y2 = (int) round(tri->v2->y);
    int x3 = (int) round(tri->v3->x);
    int y3 = (int) round(tri->v3->y);

    double d1 = tri->v1->z;
    double d2 = tri->v2->z;
    double d3 = tri->v3->z;

    this->drawTriangle(pixel, x1, y1, x2, y2, x3, y3, d1, d2, d3);

    return;

}

void Drawer::drawpng(PNG* file, int x, int y) {

    if (x + file->width > bufferWidth) return;
    if (y + file->height > bufferHeight) return;
    
    if (this->buffer == nullptr) {
        return;
    }

    for (int i = x; i < (x + file->width); i++) {
        for (int j = y; j < (y + file->height); j++) {

            Color* pixel = file->getPixel(i - x, j - y);

            if (pixel->opacityValue != 0x00) {
                this->writePixel(pixel->rawValue, i, j);
            }

        }
    }
    
    return;
}

void Drawer::drawpng(PNG* file, int x, int y, double depth) {

    if (x + file->width > bufferWidth) return;
    if (y + file->height > bufferHeight) return;
    
    if (this->buffer == nullptr) {
        return;
    }

    for (int i = x; i < (x + file->width); i++) {
        for (int j = y; j < (y + file->height); j++) {

            Color* pixel = file->getPixel(i - x, j - y);

            if (pixel->opacityValue != 0x00) {
                this->writePixel(pixel->rawValue, i, j, depth);
            }

        }
    }
    
    return;
}



/* -------------------------- */
/* ---------- Font ---------- */
/* -------------------------- */

// Constructors
Font::Font() {
    this->drawer = nullptr;
}

Font::Font(Drawer* drawer) {
    this->drawer = drawer;
}

// Instance Functions
void Font::init() {

    this->chars = new bool*[38];

    for (int i = 0; i < 38; i++) {
        this->chars[i] = new bool[49];
    }

    int index1 = 0;
    int index2 = 0;

    for (int i = 0; i < 2167; i++) {

        switch (this->rawChars[i]) {
            
            // false pixel
            case '_':
                this->chars[index1][index2] = false;
                index2++;
                break;

            // true pixel
            case '0':
                this->chars[index1][index2] = true;
                index2++;
                break;

            // End of the horizontal line of pixels
            case '|':
                // Just realised theres no reason for these
                break;

            // End of the char
            case '\n':
                index2 = 0;
                index1++;
                break;

            // This is the string end char
            case '\0':
                return;

        }

    }

    return;

}

bool* Font::getCharRef(char ch) {

    switch (ch) {

        case 'a':
        case 'A':
            return this->chars[0];

        case 'b':
        case 'B':
            return this->chars[1];

        case 'c':
        case 'C':
            return this->chars[2];

        case 'd':
        case 'D':
            return this->chars[3];

        case 'e':
        case 'E':
            return this->chars[4];

        case 'f':
        case 'F':
            return this->chars[5];

        case 'g':
        case 'G':
            return this->chars[6];

        case 'h':
        case 'H':
            return this->chars[7];

        case 'i':
        case 'I':
            return this->chars[8];

        case 'j':
        case 'J':
            return this->chars[9];

        case 'k':
        case 'K':
            return this->chars[10];

        case 'l':
        case 'L':
            return this->chars[11];

        case 'm':
        case 'M':
            return this->chars[12];

        case 'n':
        case 'N':
            return this->chars[13];

        case 'o':
        case 'O':
            return this->chars[14];

        case 'p':
        case 'P':
            return this->chars[15];

        case 'q':
        case 'Q':
            return this->chars[16];

        case 'r':
        case 'R':
            return this->chars[17];

        case 's':
        case 'S':
            return this->chars[18];

        case 't':
        case 'T':
            return this->chars[19];

        case 'u':
        case 'U':
            return this->chars[20];

        case 'v':
        case 'V':
            return this->chars[21];

        case 'w':
        case 'W':
            return this->chars[22];

        case 'x':
        case 'X':
            return this->chars[23];

        case 'y':
        case 'Y':
            return this->chars[24];

        case 'z':
        case 'Z':
            return this->chars[25];

        case '0':
            return this->chars[26];

        case '1':
            return this->chars[27];

        case '2':
            return this->chars[28];

        case '3':
            return this->chars[29];

        case '4':
            return this->chars[30];

        case '5':
            return this->chars[31];

        case '6':
            return this->chars[32];

        case '7':
            return this->chars[33];

        case '8':
            return this->chars[34];

        case '9':
            return this->chars[35];      

        case ' ':
            return this->chars[36];

        default:
            return this->chars[37];
        
    }

}

bool* Font::getCharRef(int num) {

    switch (num) {

        case 0:
            return this->chars[26];

        case 1:
            return this->chars[27];

        case 2:
            return this->chars[28];

        case 3:
            return this->chars[29];

        case 4:
            return this->chars[30];

        case 5:
            return this->chars[31];

        case 6:
            return this->chars[32];

        case 7:
            return this->chars[33];

        case 8:
            return this->chars[34];

        case 9:
            return this->chars[35];      

        default:
            return this->chars[37];
        
    }

}

void Font::drawPixels(bool* pixels, int x, int y, Uint32 color) {

    if (pixels == nullptr) return;
    
    int dx = 0;
    int dy = 0;

    for (int i = 0; i < 49; i++) {

        if (pixels[i])
            this->drawer->writePixel(color, x + dx, y + dy);

        dx++;
        if (dx > 6) {
            dx = 0;
            dy++;
        }

    }

}

void Font::drawChar(char ch, int x, int y, Uint32 color) {

    if (this->drawer == nullptr) return;

    bool* pixels = this->getCharRef(ch);

    this->drawPixels(pixels, x, y, color);

}

void Font::drawString(const char* string, int x, int y, Uint32 color) {

    if (this->drawer == nullptr) return;

    int dx = 0;

    for (int i = 0; string[i] != '\0'; i++) {

        this->drawChar(string[i], x + dx, y, color);
        dx += 6;

    }
    
}

void Font::drawInt(int num, int x, int y, Uint32 color) {

    double a = (double) num;
    int b; // for casting 'a' into
    int counter = 0;

    int dx = 0;

    while (a >= 1) {
        a /= 10;
        counter++;
    }

    for (; counter != 0; counter--) {

        // Add the next digit of num
        a *= 10;
        b = (int) a;

        // Get last digit
        b %= 10;

        bool* pixels = this->getCharRef(b);

        this->drawPixels(pixels, x + dx, y, color);
        dx += 6;

    }

}

class Mesh {

    /*
        This is the class used to define and transform meshes, some default meshes are populted after a call to initMeshes()
        Contains transformation functions
        The reason there is a verticies list and a tri list is to simplify transformations and to use less memory
        The verticies list stores the actual points, and the tris list only point to values in the verticies list
        Same goes for the normals
        The projected vertices use Vec3 objects to store depth. the x,y values are the screen coordinates and the z is the depth
    */

    public:

        class IndexMap {

            /*
                This contains an array named 'map' of the input size, where each item contains a Set struct.
                Each Set item contains the index to various vecs for the triangles in a mesh.
                These indexes refer to the position of the vectors in thier respective array.
            */

            public:

                // List items for the map variable
                struct Set {
                    int vertex1;
                    int vertex2;
                    int vertex3;
                    int normal;
                };

                // Instance variables
                Set* map;
                int size;

                // Constructor
                IndexMap(int size);

                // Destructor
                ~IndexMap();

                /*   Instance Functions   */

                // Creates a copy of the instance, and returns a pointer to it.
                IndexMap* copy();

                // Sets the values of the Set item at a given index
                void setGroup(int index, int v1, int v2, int v3, int normal);
                //void setValue(int index, int subIndex, int value);

                // Gets the values of the Set item at a given index. These values will be placed into the pointers given to the function.
                void getGroup(int index, int* v1, int* v2, int* v3, int* normal);
                //int getValue(int index, int subIndex);

        };

        // Meshes, populated from initMeshes()
        static Mesh* cubeMesh;
        static Mesh* sphereMesh;
        static Mesh* tetrahedronMesh;
        static Mesh* capsuleMesh;

        /*   Instance Variables   */

        // List containing pointers to the verticies in the mesh.
        Vec3** verticies;

        // List containing pointers to the normals for the triangles in the mesh
        Vec3** normals;

        // List containing the triangles making up the mesh. All vecs within these triangles are the same ones from 'verticies' list.
        Tri3** tris;

        // Variables which count how many items are in each of the above lists. used for list iteration.
        int vertexCount, normalCount, triCount;

        // The color which the mesh should appear as.
        Uint32 color;

        // Maps vecs from verticies and normals to tris
        IndexMap* indexMap;

        // Contains the position on the window which thier respective points from the Vec3 list should appear. Vec3 to hold depth
        Vec3** projectedVerticies;

        // Same as 'tris' list. all the vecs witihin these triangles are the same ones from 'projectedVerticies' list.
        Tri3** projectedTris;


        // Constructor
        Mesh();

        // Destructor
        ~Mesh();


        /*   Instance Funtions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Mesh* copy();

        // Returns the center of the mesh (average of all verticies). This returns a reference to an instance variable.
        Vec3* getCenter();

        // Moves all the Vec3 objects within 'verticies' by the specified distance.
        Mesh* move(Vec3* dist);
        Mesh* move(double dx, double dy, double dz);

        // Scales the mesh by a given factor on each axis. Simply applies these factors to each component of every Vec3 object.
        Mesh* scale(double factor);
        Mesh* scale(double fx, double fy, double fz);

        // Rotates all the Vec3 objects by the specified angles. just calls Vec3->rotate() for each vertex.
        Mesh* rotate(Vec3* angle, Vec3* around);
        Mesh* rotate(double yaw, double pitch, double roll, Vec3* around = nullptr);

        // Rotates the mesh around its center
        Mesh* rotateSelf(Vec3* angle);
        Mesh* rotateSelf(double yaw, double pitch, double roll);

        // Sets the color of the mesh
        Mesh* setColor(Uint32 color);

        void updateNormals();

        // This uses the IndexMap to map the Tri3 vectors so that they point to Vec3 objects from the verticies and normals lists.
        // Also does the same thing for the projected versions of both.
        // Should be called when creating a custom mesh. This is done by default for the standard meshes.
        void mapTris();


        /*   Class functions   */

        // Initializes all the standard meshes. Such as cubeMesh for example.
        static void initMeshes();

    private:

        // The center of the mesh. Will be updated when the flag is false.
        Vec3* center;
        bool centerValid;

};

/*  ------------------------------------  */
/*  -----------   IndexMap   -----------  */
/*  ------------------------------------  */

// Constructor
Mesh::IndexMap::IndexMap(int size) {
    this->map = new Set[size];
    this->size = size;
}

// Destructor
Mesh::IndexMap::~IndexMap() {
    delete this->map;
}

// Instance variables
Mesh::IndexMap* Mesh::IndexMap::copy() {

    IndexMap* newCopy = new IndexMap(this->size);

    for (int i = 0; i < (this->size); i++) {
        newCopy->map[i].vertex1 = this->map[i].vertex1;
        newCopy->map[i].vertex2 = this->map[i].vertex2;
        newCopy->map[i].vertex3 = this->map[i].vertex3;
        newCopy->map[i].normal = this->map[i].normal;
    }

    return newCopy;

}

void Mesh::IndexMap::setGroup(int index, int v1, int v2, int v3, int normal) {

    if (index >= this->size) {
        logWrite("Called Mesh::IndexMap->setGroup() for index ");
        logWrite(index);
        logWrite(" of size ");
        logWrite(this->size, true);
        return;
    }

    this->map[index].vertex1 = v1;
    this->map[index].vertex2 = v2;
    this->map[index].vertex3 = v3;
    this->map[index].normal = normal;
}

void Mesh::IndexMap::getGroup(int index, int* v1, int* v2, int* v3, int* normal) {

    if (index >= this->size) {
        logWrite("Called Mesh::IndexMap->getGroup() for index ");
        logWrite(index);
        logWrite(" of size ");
        logWrite(this->size, true);
        return;
    }

    (*v1) = this->map[index].vertex1;
    (*v2) = this->map[index].vertex2;
    (*v3) = this->map[index].vertex3;
    (*normal) = this->map[index].normal;
}

/*  ------------------------------------  */
/*  -------------   Mesh   -------------  */
/*  ------------------------------------  */

// Static variables for simple meshes
Mesh* Mesh::cubeMesh = nullptr;
Mesh* Mesh::sphereMesh = nullptr;
Mesh* Mesh::tetrahedronMesh = nullptr;
Mesh* Mesh::capsuleMesh = nullptr;

// Constructor
Mesh::Mesh() {

    this->verticies = nullptr;
    this->normals = nullptr;
    this->tris = nullptr;
    this->vertexCount = 0;
    this->normalCount = 0;
    this->triCount = 0;
    this->color = Color::WHITE;

    this->indexMap = nullptr;

    this->projectedVerticies = nullptr;
    this->projectedTris = nullptr;

    this->center = new Vec3();
    this->centerValid = false;
    
}

// Destructor
Mesh::~Mesh() {

    if (this->indexMap != nullptr) delete this->indexMap;

    // Delete all objects in the lists
    for (int i = 0; i < this->vertexCount; i++) { 
        if (this->verticies[i] != nullptr) delete this->verticies[i]; 
        if (this->projectedVerticies[i] != nullptr) delete this->projectedVerticies[i]; 
    }
    for (int i = 0; i < this->triCount; i++) {
        if (this->tris[i] != nullptr) delete this->tris[i];
        if (this->projectedTris[i] != nullptr) delete this->projectedTris[i];
    }
    for (int i = 0; i < this->normalCount; i++) {
        if (this->normals[i] != nullptr) delete this->normals[i];
    }

    // Delete lists
    if (this->verticies != nullptr) delete[] this->verticies;
    if (this->normals != nullptr) delete[] this->normals;
    if (this->tris != nullptr) delete[] this->tris;
    if (this->projectedVerticies != nullptr) delete[] this->projectedVerticies;
    if (this->projectedTris != nullptr) delete[] this->projectedTris;

    return;

}

// Instance Funtions
Mesh* Mesh::copy() {
    /*
        Makes a copy of a mesh where all the values are at new locations
        DOES NOT copy over projection data, must project again after copy
    */

    Mesh* newCopy = new Mesh();
    newCopy->vertexCount = this->vertexCount;
    newCopy->normalCount = this->normalCount;
    newCopy->triCount = this->triCount;

    // allocate space for lists
    newCopy->verticies = new Vec3*[this->vertexCount];
    newCopy->normals = new Vec3*[this->normalCount];
    newCopy->tris = new Tri3*[this->triCount];
    newCopy->projectedVerticies = new Vec3*[this->vertexCount];
    newCopy->projectedTris = new Tri3*[this->triCount];

    // Fill lists
    for (int i = 0; i < this->vertexCount; i++)
        if (this->verticies[i] == nullptr) newCopy->verticies[i] = nullptr;
        else newCopy->verticies[i] = this->verticies[i]->copy();

    for (int i = 0; i < this->normalCount; i++)
        if (this->normals[i] == nullptr) newCopy->normals[i] = nullptr;
        else newCopy->normals[i] = this->normals[i]->copy();

    for (int i = 0; i < this->triCount; i++) {
        newCopy->tris[i] = new Tri3(true);
        newCopy->projectedTris[i] = new Tri3(true);
    }

    for (int i = 0; i < this->vertexCount; i++) 
        newCopy->projectedVerticies[i] = new Vec3();

    // Copy index map
    newCopy->indexMap = this->indexMap->copy();

    newCopy->mapTris();

    return newCopy;
}

Vec3* Mesh::getCenter() {

    if (this->centerValid) return this->center;

    double x = 0;
    double y = 0;
    double z = 0;

    for (int i = 0; i < this->vertexCount; i++) {
        x += this->verticies[i]->x;
        y += this->verticies[i]->y;
        z += this->verticies[i]->z;
    }

    x /= this->vertexCount;
    y /= this->vertexCount;
    z /= this->vertexCount;

    this->center->set(x, y, z);
    this->centerValid = true;

    return this->center;

}

Mesh* Mesh::move(Vec3* dist) {

    // Log the error case
    if (dist == nullptr) {
        logWrite("Called Mesh->move(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    return this->move(dist->x, dist->y, dist->z);

}

Mesh* Mesh::move(double dx, double dy, double dz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->add(dx, dy, dz);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::scale(double factor) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->scale(factor, factor, factor);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::scale(double fx, double fy, double fz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->scale(fx, fy, fz);
    }

    this->updateNormals();

    this->centerValid = false;

    return this;

}

Mesh* Mesh::rotate(Vec3* angle, Vec3* around /* default value = nullptr */) {

    // Log the error case
    if (angle == nullptr) {
        logWrite("Called Mesh->rotate(Vec3*, Vec3*) with 'angle' being a null pointer!", true);
        return nullptr;
    }

    this->rotate(angle->x, angle->y, angle->z, around);

    return this;

}

Mesh* Mesh::rotate(double yaw, double pitch, double roll, Vec3* around /* default value = nullptr */) {

    // around = nullptr is allowed, no need to error check

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->rotate(yaw, pitch, roll, around);
    }

    // Normals are not relative to anything, and as such should not be rotated around anything but (0, 0, 0)
    for (int i = 0; i < this->normalCount; i++) {
        this->normals[i]->rotate(yaw, pitch, roll);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::rotateSelf(Vec3* angle) {
    
    // Log the error case
    if (angle == nullptr) {
        logWrite("Called Mesh->rotateSelf(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    this->rotateSelf(angle->x, angle->y, angle->z);

    return this;

}

Mesh* Mesh::rotateSelf(double yaw, double pitch, double roll) {

    // This doesnt create any new object
    Vec3* center = this->getCenter();

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->rotate(yaw, pitch, roll, center);
    }

    // Normals are not relative to anything, and as such should not be rotated around anything but (0, 0, 0)
    for (int i = 0; i < this->normalCount; i++) {
        this->normals[i]->rotate(yaw, pitch, roll);
    }

    return this;

}

Mesh* Mesh::setColor(Uint32 color) {
    this->color = color;
    return this;
}

void Mesh::updateNormals() {

    for (int i = 0; i < this->triCount; i++) {

        Vec3* newNormal;
        Tri3* tri = this->tris[i];

        // Get one of the two possible normals
        Vec3* vec1to2 = tri->v1->copy()->sub(tri->v2);
        Vec3* vec1to3 = tri->v1->copy()->sub(tri->v3);

        newNormal = vec1to2->crossProduct(vec1to3);
        newNormal->normalise();

        delete vec1to2, vec1to3;

        // Check if the found normal faces outwards
        Vec3* meshCenter = this->getCenter();                   // Not a new object
        Vec3* triCenter = tri->getCenter();                     // New object
        Vec3* normalOffset = newNormal->copy()->scale(0.05);    // New object

        triCenter->add(normalOffset);
        double dist1 = triCenter->distanceTo(meshCenter);
        triCenter->sub(normalOffset)->sub(normalOffset);
        double dist2 = triCenter->distanceTo(meshCenter);

        delete triCenter, normalOffset;

        // Flip if its facing towards the center
        if (dist1 < dist2) newNormal->scale(-1);

        // Place the found normal into its place in the list
        int _, index; // The underscore represents a value which isnt wanted/needed

        this->indexMap->getGroup(i, &_, &_, &_, &index);

        if (this->normals[index] == nullptr) {
            this->normals[index] = newNormal;
            continue;
        };

        this->normals[index]->set(newNormal);
        delete newNormal;

    }

}

void Mesh::mapTris() {

    if (this->triCount != this->indexMap->size) {
        logWrite("Called Mesh->mapTris() with ");
        logWrite(this->triCount);
        logWrite(" tris, but ");
        logWrite(this->indexMap->size);
        logWrite(" entries in the index map", true);
        return;
    }

    int vertex1Index, vertex2Index, vertex3Index, normalIndex;

    for (int i = 0; i < this->indexMap->size; i++) {

        // Get values from map
        this->indexMap->getGroup(i, &vertex1Index, &vertex2Index, &vertex3Index, &normalIndex);

        // Set pointers for 3d tris
        this->tris[i]->v1 = this->verticies[vertex1Index];
        this->tris[i]->v2 = this->verticies[vertex2Index];
        this->tris[i]->v3 = this->verticies[vertex3Index];
        this->tris[i]->normal = this->normals[normalIndex];

        // Set pointers for 2d tris
        this->projectedTris[i]->v1 = this->projectedVerticies[vertex1Index];
        this->projectedTris[i]->v2 = this->projectedVerticies[vertex2Index];
        this->projectedTris[i]->v3 = this->projectedVerticies[vertex3Index];

    }

}

// Class function
void Mesh::initMeshes() {

    Vec3** vertexList;
    Vec3** normalList;
    Tri3** triList;
    Vec3** projectedVertexList;
    Tri3** projectedTriList;
    IndexMap* indexMap;

    int vertexCount;
    int triCount;
    int normalCount;

    /* ------------------- */
    /* ---  Cube Mesh  --- */
    /* ------------------- */

    vertexCount = 8;
    triCount = 12;
    normalCount = 6;


    // Create lists
    vertexList = new Vec3*[vertexCount];
    normalList = new Vec3*[normalCount];
    triList = new Tri3*[triCount];
    projectedVertexList = new Vec3*[vertexCount];
    projectedTriList = new Tri3*[triCount];
    
    // Load verticies
    vertexList[0] = new Vec3(-0.5, -0.5, -0.5);
    vertexList[1] = new Vec3(-0.5, -0.5, 0.5);
    vertexList[2] = new Vec3(0.5, -0.5, -0.5);
    vertexList[3] = new Vec3(0.5, -0.5, 0.5);
    vertexList[4] = new Vec3(-0.5, 0.5, -0.5);
    vertexList[5] = new Vec3(-0.5, 0.5, 0.5);
    vertexList[6] = new Vec3(0.5, 0.5, -0.5);
    vertexList[7] = new Vec3(0.5, 0.5, 0.5);

    // Load Normals
    normalList[0] = new Vec3(0, -1, 0);
    normalList[1] = new Vec3(0, 1, 0);
    normalList[2] = new Vec3(-1, 0, 0);
    normalList[3] = new Vec3(1, 0, 0);
    normalList[4] = new Vec3(0, 0, -1);
    normalList[5] = new Vec3(0, 0, 1);

    // Load index map
    indexMap = new IndexMap(triCount);
    //              triangle     v2      normal
    //                 ||   v1   ||   v3   ||
    //                 \/   \/   \/   \/   \/
    indexMap->setGroup(0,   0,   3,   1,   0); // facing -y
    indexMap->setGroup(1,   0,   3,   2,   0); // facing -y
    indexMap->setGroup(2,   4,   7,   5,   1); // facing +y
    indexMap->setGroup(3,   4,   7,   6,   1); // facing +y
    indexMap->setGroup(4,   0,   5,   4,   2); // facing -x
    indexMap->setGroup(5,   0,   5,   1,   2); // facing -x
    indexMap->setGroup(6,   2,   7,   3,   3); // facing +x
    indexMap->setGroup(7,   2,   7,   6,   3); // facing +x
    indexMap->setGroup(8,   0,   6,   2,   4); // facing -z
    indexMap->setGroup(9,   0,   6,   4,   4); // facing -z
    indexMap->setGroup(10,  1,   7,   3,   5); // facing +z
    indexMap->setGroup(11,  1,   7,   5,   5); // facing +z

    // Space for triangle objects (which point to the verticies vectors)
    for (int i = 0; i < triCount; i++)
        triList[i] = new Tri3(true);

    // allocate space for projection values
    for (int i = 0; i < vertexCount; i++) 
        projectedVertexList[i] = new Vec3();
    for (int i = 0; i < triCount; i++)
        projectedTriList[i] = new Tri3(true);

    // Store the created mesh in the class variable
    Mesh::cubeMesh = new Mesh();

    Mesh::cubeMesh->indexMap = indexMap;
    Mesh::cubeMesh->verticies = vertexList;
    Mesh::cubeMesh->normals = normalList;

    Mesh::cubeMesh->vertexCount = vertexCount;
    Mesh::cubeMesh->triCount = triCount;
    Mesh::cubeMesh->normalCount = normalCount;

    Mesh::cubeMesh->tris = triList;
    Mesh::cubeMesh->projectedVerticies = projectedVertexList;
    Mesh::cubeMesh->projectedTris = projectedTriList;

    // Populate tri lists with pointers
    Mesh::cubeMesh->mapTris();

    /* --------------------- */
    /* ---  Sphere Mesh  --- */
    /* --------------------- */

    vertexCount = 102;
    triCount = 200;
    normalCount = 200;

    // Create lists
    vertexList = new Vec3*[vertexCount];
    normalList = new Vec3*[normalCount];
    triList = new Tri3*[triCount];
    projectedVertexList = new Vec3*[vertexCount];
    projectedTriList = new Tri3*[triCount];
    
    // Load verticies

    // Bottom and top
    vertexList[100] = new Vec3(0, -0.5, 0);
    vertexList[101] = new Vec3(0, 0.5, 0);

    // Rotate a vector around at a certain length to make new vertices
    double theta = 360 / 20;
    Vec3* newVec = new Vec3();

    // Along the circumference (index 0-19 inclusive)
    newVec->set(0, 0, 0.5);

    for (int i = 0; i < 20; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }

    // 30 degrees below the circumference (index 20-39 inclusive)
    newVec->set(0, 0, 0.5);
    newVec->rotate(0, 30, 0);
    newVec->rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 20; i < 40; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }

    // 30 degrees above the circumference (index 40-59 inclusive)
    newVec->set(0, 0, 0.5);
    newVec->rotate(0, -30, 0);
    newVec->rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 40; i < 60; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }

    // 60 degrees below the circumference (index 60-79 inclusive)
    newVec->set(0, 0, 0.5);
    newVec->rotate(0, 60, 0);

    for (int i = 60; i < 80; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }

    // 60 degrees above the circumference (index 80-99 inclusive)
    newVec->set(0, 0, 0.5);
    newVec->rotate(0, -60, 0);

    for (int i = 80; i < 100; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }



    // Clear space for normal vectors
    for (int i = 0; i < triCount; i++) {
        normalList[i] = nullptr;
    }

    // Load index map
    indexMap = new IndexMap(triCount);
    //                triangle          v2          normal
    //                   ||      v1     ||     v3     ||
    //                   \/      \/     \/     \/     \/
    indexMap->setGroup(  0,     101,    80,    81,    0    );     // -------------
    indexMap->setGroup(  1,     101,    81,    82,    1    );     //
    indexMap->setGroup(  2,     101,    82,    83,    2    );     //
    indexMap->setGroup(  3,     101,    83,    84,    3    );     //
    indexMap->setGroup(  4,     101,    84,    85,    4    );     //
    indexMap->setGroup(  5,     101,    85,    86,    5    );     //     here
    indexMap->setGroup(  6,     101,    86,    87,    6    );     //     ----     
    indexMap->setGroup(  7,     101,    87,    88,    7    );     //     ----     
    indexMap->setGroup(  8,     101,    88,    89,    8    );     //     ----    
    indexMap->setGroup(  9,     101,    89,    90,    9    );     //     ----     
    indexMap->setGroup(  10,    101,    90,    91,    10   );     //     ----     
    indexMap->setGroup(  11,    101,    91,    92,    11   );     //     ----    
    indexMap->setGroup(  12,    101,    92,    93,    12   );     //     ----     
    indexMap->setGroup(  13,    101,    93,    94,    13   );     //     ----     
    indexMap->setGroup(  14,    101,    94,    95,    14   );     //     ----     
    indexMap->setGroup(  15,    101,    95,    96,    15   );     //
    indexMap->setGroup(  16,    101,    96,    97,    16   );     //
    indexMap->setGroup(  17,    101,    97,    98,    17   );     //
    indexMap->setGroup(  18,    101,    98,    99,    18   );     //
    indexMap->setGroup(  19,    101,    99,    80,    19   );     // -------------

    indexMap->setGroup(  20,     81,    40,    41,    20   );     // -------------
    indexMap->setGroup(  21,     82,    41,    42,    21   );     //
    indexMap->setGroup(  22,     83,    42,    43,    22   );     //
    indexMap->setGroup(  23,     84,    43,    44,    23   );     //
    indexMap->setGroup(  24,     85,    44,    45,    24   );     //
    indexMap->setGroup(  25,     86,    45,    46,    25   );     //     ----
    indexMap->setGroup(  26,     87,    46,    47,    26   );     //     here     
    indexMap->setGroup(  27,     88,    47,    48,    27   );     //     ----     
    indexMap->setGroup(  28,     89,    48,    49,    28   );     //     ----    
    indexMap->setGroup(  29,     90,    49,    50,    29   );     //     ----     
    indexMap->setGroup(  30,     91,    50,    51,    30   );     //     ----     
    indexMap->setGroup(  31,     92,    51,    52,    31   );     //     ----    
    indexMap->setGroup(  32,     93,    52,    53,    32   );     //     ----     
    indexMap->setGroup(  33,     94,    53,    54,    33   );     //     ----     
    indexMap->setGroup(  34,     95,    54,    55,    34   );     //     ----     
    indexMap->setGroup(  35,     96,    55,    56,    35   );     //
    indexMap->setGroup(  36,     97,    56,    57,    36   );     //
    indexMap->setGroup(  37,     98,    57,    58,    37   );     //
    indexMap->setGroup(  38,     99,    58,    59,    38   );     //
    indexMap->setGroup(  39,     80,    59,    40,    39   );     // -------------

    indexMap->setGroup(  40,     40,    80,    81,    40   );     // -------------
    indexMap->setGroup(  41,     41,    81,    82,    41   );     //
    indexMap->setGroup(  42,     42,    82,    83,    42   );     //
    indexMap->setGroup(  43,     43,    83,    84,    43   );     //
    indexMap->setGroup(  44,     44,    84,    85,    44   );     //
    indexMap->setGroup(  45,     45,    85,    86,    45   );     //     ----
    indexMap->setGroup(  46,     46,    86,    87,    46   );     //     ----     
    indexMap->setGroup(  47,     47,    87,    88,    47   );     //     here     
    indexMap->setGroup(  48,     48,    88,    89,    48   );     //     ----    
    indexMap->setGroup(  49,     49,    89,    90,    49   );     //     ----     
    indexMap->setGroup(  50,     50,    90,    91,    50   );     //     ----     
    indexMap->setGroup(  51,     51,    91,    92,    51   );     //     ----    
    indexMap->setGroup(  52,     52,    92,    93,    52   );     //     ----     
    indexMap->setGroup(  53,     53,    93,    94,    53   );     //     ----     
    indexMap->setGroup(  54,     54,    94,    95,    54   );     //     ----     
    indexMap->setGroup(  55,     55,    95,    96,    55   );     //
    indexMap->setGroup(  56,     56,    96,    97,    56   );     //
    indexMap->setGroup(  57,     57,    97,    98,    57   );     //
    indexMap->setGroup(  58,     58,    98,    99,    58   );     //
    indexMap->setGroup(  59,     59,    99,    80,    59   );     // -------------

    indexMap->setGroup(  60,      1,    40,    41,    60   );     // -------------
    indexMap->setGroup(  61,      2,    41,    42,    61   );     //
    indexMap->setGroup(  62,      3,    42,    43,    62   );     //
    indexMap->setGroup(  63,      4,    43,    44,    63   );     //
    indexMap->setGroup(  64,      5,    44,    45,    64   );     //
    indexMap->setGroup(  65,      6,    45,    46,    65   );     //     ----
    indexMap->setGroup(  66,      7,    46,    47,    66   );     //     ----     
    indexMap->setGroup(  67,      8,    47,    48,    67   );     //     ----     
    indexMap->setGroup(  68,      9,    48,    49,    68   );     //     here    
    indexMap->setGroup(  69,     10,    49,    50,    69   );     //     ----     
    indexMap->setGroup(  70,     11,    50,    51,    70   );     //     ----     
    indexMap->setGroup(  71,     12,    51,    52,    71   );     //     ----    
    indexMap->setGroup(  72,     13,    52,    53,    72   );     //     ----     
    indexMap->setGroup(  73,     14,    53,    54,    73   );     //     ----     
    indexMap->setGroup(  74,     15,    54,    55,    74   );     //     ----     
    indexMap->setGroup(  75,     16,    55,    56,    75   );     //
    indexMap->setGroup(  76,     17,    56,    57,    76   );     //
    indexMap->setGroup(  77,     18,    57,    58,    77   );     //
    indexMap->setGroup(  78,     19,    58,    59,    78   );     //
    indexMap->setGroup(  79,      0,    59,    40,    79   );     // -------------

    indexMap->setGroup(  80,     40,     0,     1,    80   );     // -------------
    indexMap->setGroup(  81,     41,     1,     2,    81   );     //
    indexMap->setGroup(  82,     42,     2,     3,    82   );     //
    indexMap->setGroup(  83,     43,     3,     4,    83   );     //
    indexMap->setGroup(  84,     44,     4,     5,    84   );     //
    indexMap->setGroup(  85,     45,     5,     6,    85   );     //     ----
    indexMap->setGroup(  86,     46,     6,     7,    86   );     //     ----     
    indexMap->setGroup(  87,     47,     7,     8,    87   );     //     ----     
    indexMap->setGroup(  88,     48,     8,     9,    88   );     //     ----    
    indexMap->setGroup(  89,     49,     9,    10,    89   );     //     here     
    indexMap->setGroup(  90,     50,    10,    11,    90   );     //     ----     
    indexMap->setGroup(  91,     51,    11,    12,    91   );     //     ----    
    indexMap->setGroup(  92,     52,    12,    13,    92   );     //     ----     
    indexMap->setGroup(  93,     53,    13,    14,    93   );     //     ----     
    indexMap->setGroup(  94,     54,    14,    15,    94   );     //     ----     
    indexMap->setGroup(  95,     55,    15,    16,    95   );     //
    indexMap->setGroup(  96,     56,    16,    17,    96   );     //
    indexMap->setGroup(  97,     57,    17,    18,    97   );     //
    indexMap->setGroup(  98,     58,    18,    19,    98   );     //
    indexMap->setGroup(  99,     59,    19,     0,    99   );     // -------------

    indexMap->setGroup(  100,    20,     0,     1,    100  );     // -------------
    indexMap->setGroup(  101,    21,     1,     2,    101  );     //
    indexMap->setGroup(  102,    22,     2,     3,    102  );     //
    indexMap->setGroup(  103,    23,     3,     4,    103  );     //
    indexMap->setGroup(  104,    24,     4,     5,    104  );     //
    indexMap->setGroup(  105,    25,     5,     6,    105  );     //     ----
    indexMap->setGroup(  106,    26,     6,     7,    106  );     //     ----     
    indexMap->setGroup(  107,    27,     7,     8,    107  );     //     ----     
    indexMap->setGroup(  108,    28,     8,     9,    108  );     //     ----    
    indexMap->setGroup(  109,    29,     9,    10,    109  );     //     ----     
    indexMap->setGroup(  110,    30,    10,    11,    110  );     //     here     
    indexMap->setGroup(  111,    31,    11,    12,    111  );     //     ----    
    indexMap->setGroup(  112,    32,    12,    13,    112  );     //     ----     
    indexMap->setGroup(  113,    33,    13,    14,    113  );     //     ----     
    indexMap->setGroup(  114,    34,    14,    15,    114  );     //     ----     
    indexMap->setGroup(  115,    35,    15,    16,    115  );     //
    indexMap->setGroup(  116,    36,    16,    17,    116  );     //
    indexMap->setGroup(  117,    37,    17,    18,    117  );     //
    indexMap->setGroup(  118,    38,    18,    19,    118  );     //
    indexMap->setGroup(  119,    39,    19,     0,    119  );     // -------------

    indexMap->setGroup(  120,     1,    20,    21,    120  );     // -------------
    indexMap->setGroup(  121,     2,    21,    22,    121  );     //
    indexMap->setGroup(  122,     3,    22,    23,    122  );     //
    indexMap->setGroup(  123,     4,    23,    24,    123  );     //
    indexMap->setGroup(  124,     5,    24,    25,    124  );     //
    indexMap->setGroup(  125,     6,    25,    26,    125  );     //     ----
    indexMap->setGroup(  126,     7,    26,    27,    126  );     //     ----     
    indexMap->setGroup(  127,     8,    27,    28,    127  );     //     ----     
    indexMap->setGroup(  128,     9,    28,    29,    128  );     //     ----    
    indexMap->setGroup(  129,    10,    29,    30,    129  );     //     ----     
    indexMap->setGroup(  130,    11,    30,    31,    130  );     //     ----     
    indexMap->setGroup(  131,    12,    31,    32,    131  );     //     here    
    indexMap->setGroup(  132,    13,    32,    33,    132  );     //     ----     
    indexMap->setGroup(  133,    14,    33,    34,    133  );     //     ----     
    indexMap->setGroup(  134,    15,    34,    35,    134  );     //     ----     
    indexMap->setGroup(  135,    16,    35,    36,    135  );     //
    indexMap->setGroup(  136,    17,    36,    37,    136  );     //
    indexMap->setGroup(  137,    18,    37,    38,    137  );     //
    indexMap->setGroup(  138,    19,    38,    39,    138  );     //
    indexMap->setGroup(  139,     0,    39,    20,    139  );     // -------------

    indexMap->setGroup(  140,    61,    20,    21,    140  );     // -------------
    indexMap->setGroup(  141,    62,    21,    22,    141  );     //
    indexMap->setGroup(  142,    63,    22,    23,    142  );     //
    indexMap->setGroup(  143,    64,    23,    24,    143  );     //
    indexMap->setGroup(  144,    65,    24,    25,    144  );     //
    indexMap->setGroup(  145,    66,    25,    26,    145  );     //     ----
    indexMap->setGroup(  146,    67,    26,    27,    146  );     //     ----     
    indexMap->setGroup(  147,    68,    27,    28,    147  );     //     ----     
    indexMap->setGroup(  148,    69,    28,    29,    148  );     //     ----    
    indexMap->setGroup(  149,    70,    29,    30,    149  );     //     ----     
    indexMap->setGroup(  150,    71,    30,    31,    150  );     //     ----     
    indexMap->setGroup(  151,    72,    31,    32,    151  );     //     ----    
    indexMap->setGroup(  152,    73,    32,    33,    152  );     //     here     
    indexMap->setGroup(  153,    74,    33,    34,    153  );     //     ----     
    indexMap->setGroup(  154,    75,    34,    35,    154  );     //     ----     
    indexMap->setGroup(  155,    76,    35,    36,    155  );     //
    indexMap->setGroup(  156,    77,    36,    37,    156  );     //
    indexMap->setGroup(  157,    78,    37,    38,    157  );     //
    indexMap->setGroup(  158,    79,    38,    39,    158  );     //
    indexMap->setGroup(  159,    60,    39,    20,    159  );     // -------------

    indexMap->setGroup(  160,    20,    60,    61,    160  );     // -------------
    indexMap->setGroup(  161,    21,    61,    62,    161  );     //
    indexMap->setGroup(  162,    22,    62,    63,    162  );     //
    indexMap->setGroup(  163,    23,    63,    64,    163  );     //
    indexMap->setGroup(  164,    24,    64,    65,    164  );     //
    indexMap->setGroup(  165,    25,    65,    66,    165  );     //     ----
    indexMap->setGroup(  166,    26,    66,    67,    166  );     //     ----     
    indexMap->setGroup(  167,    27,    67,    68,    167  );     //     ----     
    indexMap->setGroup(  168,    28,    68,    69,    168  );     //     ----    
    indexMap->setGroup(  169,    29,    69,    70,    169  );     //     ----     
    indexMap->setGroup(  170,    30,    70,    71,    170  );     //     ----     
    indexMap->setGroup(  171,    31,    71,    72,    171  );     //     ----    
    indexMap->setGroup(  172,    32,    72,    73,    172  );     //     ----     
    indexMap->setGroup(  173,    33,    73,    74,    173  );     //     here     
    indexMap->setGroup(  174,    34,    74,    75,    174  );     //     ----     
    indexMap->setGroup(  175,    35,    75,    76,    175  );     //
    indexMap->setGroup(  176,    36,    76,    77,    176  );     //
    indexMap->setGroup(  177,    37,    77,    78,    177  );     //
    indexMap->setGroup(  178,    38,    78,    79,    178  );     //
    indexMap->setGroup(  179,    39,    79,    60,    179  );     // -------------

    indexMap->setGroup(  180,   100,    60,    61,    180  );     // -------------
    indexMap->setGroup(  181,   100,    61,    62,    181  );     //
    indexMap->setGroup(  182,   100,    62,    63,    182  );     //
    indexMap->setGroup(  183,   100,    63,    64,    183  );     //
    indexMap->setGroup(  184,   100,    64,    65,    184  );     //
    indexMap->setGroup(  185,   100,    65,    66,    185  );     //     ----
    indexMap->setGroup(  186,   100,    66,    67,    186  );     //     ----     
    indexMap->setGroup(  187,   100,    67,    68,    187  );     //     ----     
    indexMap->setGroup(  188,   100,    68,    69,    188  );     //     ----    
    indexMap->setGroup(  189,   100,    69,    70,    189  );     //     ----     
    indexMap->setGroup(  190,   100,    70,    71,    190  );     //     ----     
    indexMap->setGroup(  191,   100,    71,    72,    191  );     //     ----    
    indexMap->setGroup(  192,   100,    72,    73,    192  );     //     ----     
    indexMap->setGroup(  193,   100,    73,    74,    193  );     //     ----     
    indexMap->setGroup(  194,   100,    74,    75,    194  );     //     here     
    indexMap->setGroup(  195,   100,    75,    76,    195  );     //
    indexMap->setGroup(  196,   100,    76,    77,    196  );     //
    indexMap->setGroup(  197,   100,    77,    78,    197  );     //
    indexMap->setGroup(  198,   100,    78,    79,    198  );     //
    indexMap->setGroup(  199,   100,    79,    60,    199  );     // -------------


    // Space for triangle objects (which point to the verticies vectors)
    for (int i = 0; i < triCount; i++)
        triList[i] = new Tri3(true);

    // allocate space for projection values
    for (int i = 0; i < vertexCount; i++)
        projectedVertexList[i] = new Vec3();
    for (int i = 0; i < triCount; i++)
        projectedTriList[i] = new Tri3(true);

    // Store the created mesh in the class variable
    Mesh::sphereMesh = new Mesh();

    Mesh::sphereMesh->indexMap = indexMap;
    Mesh::sphereMesh->verticies = vertexList;
    Mesh::sphereMesh->normals = normalList;

    Mesh::sphereMesh->vertexCount = vertexCount;
    Mesh::sphereMesh->triCount = triCount;
    Mesh::sphereMesh->normalCount = normalCount;

    Mesh::sphereMesh->tris = triList;
    Mesh::sphereMesh->projectedVerticies = projectedVertexList;
    Mesh::sphereMesh->projectedTris = projectedTriList;

    // Populate tri lists with pointers
    Mesh::sphereMesh->mapTris();

    // Load normals
    Mesh::sphereMesh->updateNormals();



    /* ---------------------- */
    /* ---  Capsule Mesh  --- */
    /* ---------------------- */

    vertexCount = 122;
    triCount = 240;
    normalCount = 240;

    // Create lists
    vertexList = new Vec3*[vertexCount];
    normalList = new Vec3*[normalCount];
    triList = new Tri3*[triCount];
    projectedVertexList = new Vec3*[vertexCount];
    projectedTriList = new Tri3*[triCount];
    
    // Load verticies

    // Bottom and top
    vertexList[120] = new Vec3(0, -0.5, 0);
    vertexList[121] = new Vec3(0, 0.5, 0);

    // Rotate a vector around at a certain length to make new vertices
    theta = 360 / 20;
    newVec = new Vec3();

    // Along the circumference (index 0-19 inclusive for the top, index 100-119 inclusive for the bottom)
    newVec->set(0, 0, 0.25);

    for (int i = 0; i < 20; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->add(0, 0.25, 0);
        vertexList[i + 100] = newVec->copy()->sub(0, 0.25, 0);

    }

    // 30 degrees below the circumference (index 20-39 inclusive)
    newVec->set(0, 0, 0.25);
    newVec->rotate(0, 30, 0);
    newVec->rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 20; i < 40; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->sub(0, 0.25, 0);

    }

    // 30 degrees above the circumference (index 40-59 inclusive)
    newVec->set(0, 0, 0.25);
    newVec->rotate(0, -30, 0);
    newVec->rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 40; i < 60; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->add(0, 0.25, 0);

    }

    // 60 degrees below the circumference (index 60-79 inclusive)
    newVec->set(0, 0, 0.25);
    newVec->rotate(0, 60, 0);

    for (int i = 60; i < 80; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->sub(0, 0.25, 0);

    }

    // 60 degrees above the circumference (index 80-99 inclusive)
    newVec->set(0, 0, 0.25);
    newVec->rotate(0, -60, 0);

    for (int i = 80; i < 100; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->add(0, 0.25, 0);

    }

    // Clear space for normal vectors
    for (int i = 0; i < triCount; i++) {
        normalList[i] = nullptr;
    }

    // Load index map
    indexMap = new IndexMap(triCount);
    //                triangle          v2          normal
    //                   ||      v1     ||     v3     ||
    //                   \/      \/     \/     \/     \/
    indexMap->setGroup(  0,     121,    80,    81,    0    );     // -------------
    indexMap->setGroup(  1,     121,    81,    82,    1    );     //
    indexMap->setGroup(  2,     121,    82,    83,    2    );     //
    indexMap->setGroup(  3,     121,    83,    84,    3    );     //
    indexMap->setGroup(  4,     121,    84,    85,    4    );     //     here
    indexMap->setGroup(  5,     121,    85,    86,    5    );     //     ----
    indexMap->setGroup(  6,     121,    86,    87,    6    );     //     ----     
    indexMap->setGroup(  7,     121,    87,    88,    7    );     //     ----     
    indexMap->setGroup(  8,     121,    88,    89,    8    );     //     ----    
    indexMap->setGroup(  9,     121,    89,    90,    9    );     //     ----     
    indexMap->setGroup(  10,    121,    90,    91,    10   );     //     ----     
    indexMap->setGroup(  11,    121,    91,    92,    11   );     //     ----    
    indexMap->setGroup(  12,    121,    92,    93,    12   );     //     ----     
    indexMap->setGroup(  13,    121,    93,    94,    13   );     //     ----     
    indexMap->setGroup(  14,    121,    94,    95,    14   );     //     ----     
    indexMap->setGroup(  15,    121,    95,    96,    15   );     //     ----
    indexMap->setGroup(  16,    121,    96,    97,    16   );     //
    indexMap->setGroup(  17,    121,    97,    98,    17   );     //
    indexMap->setGroup(  18,    121,    98,    99,    18   );     //
    indexMap->setGroup(  19,    121,    99,    80,    19   );     // -------------

    indexMap->setGroup(  20,     81,    40,    41,    20   );     // -------------
    indexMap->setGroup(  21,     82,    41,    42,    21   );     //
    indexMap->setGroup(  22,     83,    42,    43,    22   );     //
    indexMap->setGroup(  23,     84,    43,    44,    23   );     //
    indexMap->setGroup(  24,     85,    44,    45,    24   );     //     ----
    indexMap->setGroup(  25,     86,    45,    46,    25   );     //     here
    indexMap->setGroup(  26,     87,    46,    47,    26   );     //     ----     
    indexMap->setGroup(  27,     88,    47,    48,    27   );     //     ----     
    indexMap->setGroup(  28,     89,    48,    49,    28   );     //     ----    
    indexMap->setGroup(  29,     90,    49,    50,    29   );     //     ----     
    indexMap->setGroup(  30,     91,    50,    51,    30   );     //     ----     
    indexMap->setGroup(  31,     92,    51,    52,    31   );     //     ----    
    indexMap->setGroup(  32,     93,    52,    53,    32   );     //     ----     
    indexMap->setGroup(  33,     94,    53,    54,    33   );     //     ----     
    indexMap->setGroup(  34,     95,    54,    55,    34   );     //     ----     
    indexMap->setGroup(  35,     96,    55,    56,    35   );     //     ----
    indexMap->setGroup(  36,     97,    56,    57,    36   );     //
    indexMap->setGroup(  37,     98,    57,    58,    37   );     //
    indexMap->setGroup(  38,     99,    58,    59,    38   );     //
    indexMap->setGroup(  39,     80,    59,    40,    39   );     // -------------

    indexMap->setGroup(  40,     40,    80,    81,    40   );     // -------------
    indexMap->setGroup(  41,     41,    81,    82,    41   );     //
    indexMap->setGroup(  42,     42,    82,    83,    42   );     //
    indexMap->setGroup(  43,     43,    83,    84,    43   );     //
    indexMap->setGroup(  44,     44,    84,    85,    44   );     //     ----
    indexMap->setGroup(  45,     45,    85,    86,    45   );     //     ----
    indexMap->setGroup(  46,     46,    86,    87,    46   );     //     here     
    indexMap->setGroup(  47,     47,    87,    88,    47   );     //     ----     
    indexMap->setGroup(  48,     48,    88,    89,    48   );     //     ----    
    indexMap->setGroup(  49,     49,    89,    90,    49   );     //     ----     
    indexMap->setGroup(  50,     50,    90,    91,    50   );     //     ----     
    indexMap->setGroup(  51,     51,    91,    92,    51   );     //     ----    
    indexMap->setGroup(  52,     52,    92,    93,    52   );     //     ----     
    indexMap->setGroup(  53,     53,    93,    94,    53   );     //     ----     
    indexMap->setGroup(  54,     54,    94,    95,    54   );     //     ----     
    indexMap->setGroup(  55,     55,    95,    96,    55   );     //     ----
    indexMap->setGroup(  56,     56,    96,    97,    56   );     //
    indexMap->setGroup(  57,     57,    97,    98,    57   );     //
    indexMap->setGroup(  58,     58,    98,    99,    58   );     //
    indexMap->setGroup(  59,     59,    99,    80,    59   );     // -------------

    indexMap->setGroup(  60,      1,    40,    41,    60   );     // -------------
    indexMap->setGroup(  61,      2,    41,    42,    61   );     //
    indexMap->setGroup(  62,      3,    42,    43,    62   );     //
    indexMap->setGroup(  63,      4,    43,    44,    63   );     //
    indexMap->setGroup(  64,      5,    44,    45,    64   );     //     ----
    indexMap->setGroup(  65,      6,    45,    46,    65   );     //     ----
    indexMap->setGroup(  66,      7,    46,    47,    66   );     //     ----     
    indexMap->setGroup(  67,      8,    47,    48,    67   );     //     here     
    indexMap->setGroup(  68,      9,    48,    49,    68   );     //     ----    
    indexMap->setGroup(  69,     10,    49,    50,    69   );     //     ----     
    indexMap->setGroup(  70,     11,    50,    51,    70   );     //     ----     
    indexMap->setGroup(  71,     12,    51,    52,    71   );     //     ----    
    indexMap->setGroup(  72,     13,    52,    53,    72   );     //     ----     
    indexMap->setGroup(  73,     14,    53,    54,    73   );     //     ----     
    indexMap->setGroup(  74,     15,    54,    55,    74   );     //     ----     
    indexMap->setGroup(  75,     16,    55,    56,    75   );     //     ----
    indexMap->setGroup(  76,     17,    56,    57,    76   );     //
    indexMap->setGroup(  77,     18,    57,    58,    77   );     //
    indexMap->setGroup(  78,     19,    58,    59,    78   );     //
    indexMap->setGroup(  79,      0,    59,    40,    79   );     // -------------

    indexMap->setGroup(  80,     40,     0,     1,    80   );     // -------------
    indexMap->setGroup(  81,     41,     1,     2,    81   );     //
    indexMap->setGroup(  82,     42,     2,     3,    82   );     //
    indexMap->setGroup(  83,     43,     3,     4,    83   );     //
    indexMap->setGroup(  84,     44,     4,     5,    84   );     //     ----
    indexMap->setGroup(  85,     45,     5,     6,    85   );     //     ----
    indexMap->setGroup(  86,     46,     6,     7,    86   );     //     ----     
    indexMap->setGroup(  87,     47,     7,     8,    87   );     //     ----     
    indexMap->setGroup(  88,     48,     8,     9,    88   );     //     here    
    indexMap->setGroup(  89,     49,     9,    10,    89   );     //     ----     
    indexMap->setGroup(  90,     50,    10,    11,    90   );     //     ----     
    indexMap->setGroup(  91,     51,    11,    12,    91   );     //     ----    
    indexMap->setGroup(  92,     52,    12,    13,    92   );     //     ----     
    indexMap->setGroup(  93,     53,    13,    14,    93   );     //     ----     
    indexMap->setGroup(  94,     54,    14,    15,    94   );     //     ----     
    indexMap->setGroup(  95,     55,    15,    16,    95   );     //     ----
    indexMap->setGroup(  96,     56,    16,    17,    96   );     //
    indexMap->setGroup(  97,     57,    17,    18,    97   );     //
    indexMap->setGroup(  98,     58,    18,    19,    98   );     //
    indexMap->setGroup(  99,     59,    19,     0,    99   );     // -------------

    indexMap->setGroup(  100,    101,    0,     1,    100  );     // -------------
    indexMap->setGroup(  101,    102,    1,     2,    101  );     //
    indexMap->setGroup(  102,    103,    2,     3,    102  );     //
    indexMap->setGroup(  103,    104,    3,     4,    103  );     //
    indexMap->setGroup(  104,    105,    4,     5,    104  );     //     ----
    indexMap->setGroup(  105,    106,    5,     6,    105  );     //     ----
    indexMap->setGroup(  106,    107,    6,     7,    106  );     //     ----     
    indexMap->setGroup(  107,    108,    7,     8,    107  );     //     ----     
    indexMap->setGroup(  108,    109,    8,     9,    108  );     //     ----    
    indexMap->setGroup(  109,    110,    9,    10,    109  );     //     here     
    indexMap->setGroup(  110,    111,   10,    11,    110  );     //     ----     
    indexMap->setGroup(  111,    112,   11,    12,    111  );     //     ----    
    indexMap->setGroup(  112,    113,   12,    13,    112  );     //     ----     
    indexMap->setGroup(  113,    114,   13,    14,    113  );     //     ----     
    indexMap->setGroup(  114,    115,   14,    15,    114  );     //     ----     
    indexMap->setGroup(  115,    116,   15,    16,    115  );     //     ----
    indexMap->setGroup(  116,    117,   16,    17,    116  );     //
    indexMap->setGroup(  117,    118,   17,    18,    117  );     //
    indexMap->setGroup(  118,    119,   18,    19,    118  );     //
    indexMap->setGroup(  119,    100,   19,     0,    119  );     // -------------

    indexMap->setGroup(  120,    0,    100,   101,    120  );     // -------------
    indexMap->setGroup(  121,    1,    101,   102,    121  );     //
    indexMap->setGroup(  122,    2,    102,   103,    122  );     //
    indexMap->setGroup(  123,    3,    103,   104,    123  );     //
    indexMap->setGroup(  124,    4,    104,   105,    124  );     //     ----
    indexMap->setGroup(  125,    5,    105,   106,    125  );     //     ----
    indexMap->setGroup(  126,    6,    106,   107,    126  );     //     ----     
    indexMap->setGroup(  127,    7,    107,   108,    127  );     //     ----     
    indexMap->setGroup(  128,    8,    108,   109,    128  );     //     ----    
    indexMap->setGroup(  129,    9,    109,   110,    129  );     //     ----     
    indexMap->setGroup(  130,    10,   110,   111,    130  );     //     here     
    indexMap->setGroup(  131,    11,   111,   112,    131  );     //     ----    
    indexMap->setGroup(  132,    12,   112,   113,    132  );     //     ----     
    indexMap->setGroup(  133,    13,   113,   114,    133  );     //     ----     
    indexMap->setGroup(  134,    14,   114,   115,    134  );     //     ----     
    indexMap->setGroup(  135,    15,   115,   116,    135  );     //     ----
    indexMap->setGroup(  136,    16,   116,   117,    136  );     //
    indexMap->setGroup(  137,    17,   117,   118,    137  );     //
    indexMap->setGroup(  138,    18,   118,   119,    138  );     //
    indexMap->setGroup(  139,    19,   119,   100,    139  );     // -------------

    indexMap->setGroup(  140,    20,   100,   101,    140  );     // -------------
    indexMap->setGroup(  141,    21,   101,   102,    141  );     //
    indexMap->setGroup(  142,    22,   102,   103,    142  );     //
    indexMap->setGroup(  143,    23,   103,   104,    143  );     //
    indexMap->setGroup(  144,    24,   104,   105,    144  );     //     ----
    indexMap->setGroup(  145,    25,   105,   106,    145  );     //     ----
    indexMap->setGroup(  146,    26,   106,   107,    146  );     //     ----     
    indexMap->setGroup(  147,    27,   107,   108,    147  );     //     ----     
    indexMap->setGroup(  148,    28,   108,   109,    148  );     //     ----    
    indexMap->setGroup(  149,    29,   109,   110,    149  );     //     ----     
    indexMap->setGroup(  150,    30,   110,   111,    150  );     //     ----     
    indexMap->setGroup(  151,    31,   111,   112,    151  );     //     here    
    indexMap->setGroup(  152,    32,   112,   113,    152  );     //     ----     
    indexMap->setGroup(  153,    33,   113,   114,    153  );     //     ----     
    indexMap->setGroup(  154,    34,   114,   115,    154  );     //     ----     
    indexMap->setGroup(  155,    35,   115,   116,    155  );     //     ----
    indexMap->setGroup(  156,    36,   116,   117,    156  );     //
    indexMap->setGroup(  157,    37,   117,   118,    157  );     //
    indexMap->setGroup(  158,    38,   118,   119,    158  );     //
    indexMap->setGroup(  159,    39,   119,   100,    159  );     // -------------

    indexMap->setGroup(  160,   101,    20,    21,    160  );     // -------------
    indexMap->setGroup(  161,   102,    21,    22,    161  );     //
    indexMap->setGroup(  162,   103,    22,    23,    162  );     //
    indexMap->setGroup(  163,   104,    23,    24,    163  );     //
    indexMap->setGroup(  164,   105,    24,    25,    164  );     //     ----
    indexMap->setGroup(  165,   106,    25,    26,    165  );     //     ----
    indexMap->setGroup(  166,   107,    26,    27,    166  );     //     ----     
    indexMap->setGroup(  167,   108,    27,    28,    167  );     //     ----     
    indexMap->setGroup(  168,   109,    28,    29,    168  );     //     ----    
    indexMap->setGroup(  169,   110,    29,    30,    169  );     //     ----     
    indexMap->setGroup(  170,   111,    30,    31,    170  );     //     ----     
    indexMap->setGroup(  171,   112,    31,    32,    171  );     //     ----    
    indexMap->setGroup(  172,   113,    32,    33,    172  );     //     here     
    indexMap->setGroup(  173,   114,    33,    34,    173  );     //     ----     
    indexMap->setGroup(  174,   115,    34,    35,    174  );     //     ----     
    indexMap->setGroup(  175,   116,    35,    36,    175  );     //     ----
    indexMap->setGroup(  176,   117,    36,    37,    176  );     //
    indexMap->setGroup(  177,   118,    37,    38,    177  );     //
    indexMap->setGroup(  178,   119,    38,    39,    178  );     //
    indexMap->setGroup(  179,   100,    39,    20,    179  );     // -------------

    indexMap->setGroup(  180,    61,    20,    21,    180  );     // -------------
    indexMap->setGroup(  181,    62,    21,    22,    181  );     //
    indexMap->setGroup(  182,    63,    22,    23,    182  );     //
    indexMap->setGroup(  183,    64,    23,    24,    183  );     //
    indexMap->setGroup(  184,    65,    24,    25,    184  );     //     ----
    indexMap->setGroup(  185,    66,    25,    26,    185  );     //     ----
    indexMap->setGroup(  186,    67,    26,    27,    186  );     //     ----     
    indexMap->setGroup(  187,    68,    27,    28,    187  );     //     ----     
    indexMap->setGroup(  188,    69,    28,    29,    188  );     //     ----    
    indexMap->setGroup(  189,    70,    29,    30,    189  );     //     ----     
    indexMap->setGroup(  190,    71,    30,    31,    190  );     //     ----     
    indexMap->setGroup(  191,    72,    31,    32,    191  );     //     ----    
    indexMap->setGroup(  192,    73,    32,    33,    192  );     //     ----     
    indexMap->setGroup(  193,    74,    33,    34,    193  );     //     here     
    indexMap->setGroup(  194,    75,    34,    35,    194  );     //     ----     
    indexMap->setGroup(  195,    76,    35,    36,    195  );     //     ----
    indexMap->setGroup(  196,    77,    36,    37,    196  );     //
    indexMap->setGroup(  197,    78,    37,    38,    197  );     //
    indexMap->setGroup(  198,    79,    38,    39,    198  );     //
    indexMap->setGroup(  199,    60,    39,    20,    199  );     // -------------

    indexMap->setGroup(  200,    20,    60,    61,    200  );     // -------------
    indexMap->setGroup(  201,    21,    61,    62,    201  );     //
    indexMap->setGroup(  202,    22,    62,    63,    202  );     //
    indexMap->setGroup(  203,    23,    63,    64,    203  );     //
    indexMap->setGroup(  204,    24,    64,    65,    204  );     //     ----
    indexMap->setGroup(  205,    25,    65,    66,    205  );     //     ----
    indexMap->setGroup(  206,    26,    66,    67,    206  );     //     ----     
    indexMap->setGroup(  207,    27,    67,    68,    207  );     //     ----     
    indexMap->setGroup(  208,    28,    68,    69,    208  );     //     ----    
    indexMap->setGroup(  209,    29,    69,    70,    209  );     //     ----     
    indexMap->setGroup(  210,    30,    70,    71,    210  );     //     ----     
    indexMap->setGroup(  211,    31,    71,    72,    211  );     //     ----    
    indexMap->setGroup(  212,    32,    72,    73,    212  );     //     ----     
    indexMap->setGroup(  213,    33,    73,    74,    213  );     //     ----     
    indexMap->setGroup(  214,    34,    74,    75,    214  );     //     here     
    indexMap->setGroup(  215,    35,    75,    76,    215  );     //     ----
    indexMap->setGroup(  216,    36,    76,    77,    216  );     //
    indexMap->setGroup(  217,    37,    77,    78,    217  );     //
    indexMap->setGroup(  218,    38,    78,    79,    218  );     //
    indexMap->setGroup(  219,    39,    79,    60,    219  );     // -------------

    indexMap->setGroup(  220,   120,    60,    61,    220  );     // -------------
    indexMap->setGroup(  221,   120,    61,    62,    221  );     //
    indexMap->setGroup(  222,   120,    62,    63,    222  );     //
    indexMap->setGroup(  223,   120,    63,    64,    223  );     //
    indexMap->setGroup(  224,   120,    64,    65,    224  );     //     ----
    indexMap->setGroup(  225,   120,    65,    66,    225  );     //     ----
    indexMap->setGroup(  226,   120,    66,    67,    226  );     //     ----     
    indexMap->setGroup(  227,   120,    67,    68,    227  );     //     ----     
    indexMap->setGroup(  228,   120,    68,    69,    228  );     //     ----    
    indexMap->setGroup(  229,   120,    69,    70,    229  );     //     ----     
    indexMap->setGroup(  230,   120,    70,    71,    230  );     //     ----     
    indexMap->setGroup(  231,   120,    71,    72,    231  );     //     ----    
    indexMap->setGroup(  232,   120,    72,    73,    232  );     //     ----     
    indexMap->setGroup(  233,   120,    73,    74,    233  );     //     ----     
    indexMap->setGroup(  234,   120,    74,    75,    234  );     //     ----     
    indexMap->setGroup(  235,   120,    75,    76,    235  );     //     here
    indexMap->setGroup(  236,   120,    76,    77,    236  );     //
    indexMap->setGroup(  237,   120,    77,    78,    237  );     //
    indexMap->setGroup(  238,   120,    78,    79,    238  );     //
    indexMap->setGroup(  239,   120,    79,    60,    239  );     // -------------


    // Space for triangle objects (which point to the verticies vectors)
    for (int i = 0; i < triCount; i++)
        triList[i] = new Tri3(true);

    // allocate space for projection values
    for (int i = 0; i < vertexCount; i++)
        projectedVertexList[i] = new Vec3();
    for (int i = 0; i < triCount; i++)
        projectedTriList[i] = new Tri3(true);

    // Store the created mesh in the class variable
    Mesh::capsuleMesh = new Mesh();

    Mesh::capsuleMesh->indexMap = indexMap;
    Mesh::capsuleMesh->verticies = vertexList;
    Mesh::capsuleMesh->normals = normalList;

    Mesh::capsuleMesh->vertexCount = vertexCount;
    Mesh::capsuleMesh->normalCount = normalCount;
    Mesh::capsuleMesh->triCount = triCount;

    Mesh::capsuleMesh->tris = triList;
    Mesh::capsuleMesh->projectedVerticies = projectedVertexList;
    Mesh::capsuleMesh->projectedTris = projectedTriList;

    // Populate tri lists with pointers
    Mesh::capsuleMesh->mapTris();

    // Load normals
    Mesh::capsuleMesh->updateNormals();

}

class Camera {
    public:
        
        /*   Instance variables   */

        // Physics vectors
        Vec3* pos;
        Vec3* velocity;
        Vec3* acceleration;

        // Facing vectors. yaw -> about Y-axis, pitch -> about X-axis, roll -> about Z-axis
        double yaw, pitch, roll;

        // Vector which points in the same direction the camera is facing
        Vec3* facingDirection;

        // degrees of fov on the x and y axis
        Vec2* fov;

        // Movement speed in units per second
        double movementSpeed;
        double sprintFactor;

        // This is the vector representing the direction of the global light source for this camera
        Vec3* lightingVec;


        // Constructor
        Camera();

        // Destructor
        ~Camera();


        /*   Instance functions   */

        // Setters for all the instance variable vector objects.
        // The functions which take a Vec object as input DO NOT delete the object, it must be done manually.

        // Position 
        void setPos(double x, double y, double z);
        void setPos(Vec3* position);

        // Velocity
        void setVelocity(double x, double y, double z);
        void setVelocity(Vec3* velocity);

        // Acceleration
        void setAcceleration(double x, double y, double z);
        void setAcceleration(Vec3* acceleration);

        // Facing direction
        void setFacingDirection(double x, double y, double z);
        void setFacingDirection(Vec3* facingDirection);

        // Fov
        void setFov(double x, double y);
        void setFov(Vec2* fov);

        // Lighting Vector
        void setLightingVec(double x, double y, double z);
        void setLightingVec(Vec3* lightingVec);

        // Sets all the instance variables to one of the presets
        void setPreset(int preset);


        // This rotates the camera based on the input angles in DEGREES
        // Also updates the facing direction vector
        void rotate(double yaw, double pitch, double roll);

        // Takes a Vec3 object, and projects it into a Vec2 object.
        // The Vec2 components will be overwritten with the output of this function.
        // The values will be given in terms of fov (0 -> 1 is one fov length) so they dont mean anything for drawing until converted using a Display object
        void project(Vec3* vec, Vec2* displayPos);

        // here the places distance between point and camera position into the z coordinate of displayPos
        void project(Vec3* vec, Vec3* displayPos);
        void project(Vec3* vec, Vec3* displayPos, Vec3* offset);

        // Runs the functions above for all the verticies in a mesh
        void project(Mesh* mesh);
        void project(Mesh* mesh, Vec3* offset);

        // Returns true if the camera can see the triangle, based on the location of the tri relative to the cam, and the normal vector of the tri
        bool canSee(Tri3* tri);
        bool canSee(Tri3* tri, Vec3* offset);

    private:

        // Just used to ensure angles between 0-360
        void rolloverAngles();
        
};



class Display {

    /*
        This class IS NOT the same as GuiClass.
        The gui class is used for making an actual window and drawing to it.
        This class simply defines an area within an existing window where things should be drawn.
        Think of it like a way to do split screen. you can define areas of any size and position which can act as the whole window.

        width and height are straightforward. the offsets are the distance from the top left for each.
        every length is in pixels.
    */

    public:

        // Instance variables
        int width, height;
        int widthOffset, heightOffset;


        /*   Constructors   */

        // No offset values. Sets both to 0.
        Display(int width, int height);

        // Given offset values
        Display(int width, int height, int widthOffset, int heightOffset);


        /*   Instance functions   */

        // Returns the center of the display area on the given axis relative to the whole gui window
        int middleX();
        int middleY();

        // The second step of projection. 
        // This takes the fov factor from the output of a projection call, and turns it into a pixel position on the gui window.
        // The return values of this are placed into the components of the input vector. meaning the old values are overwritten
        void toDisplayPos(Vec2* vec);

        // Same as above but supports depth in the z value. the z value is upscaled by 2^8 times in this
        void toDisplayPos(Vec3* vec);

        // Does the above step for each vertex in a mesh
        void toDisplayPos(Mesh* mesh);

};

/* -------------- */
/* --- Camera --- */
/* -------------- */

// Constructors
Camera::Camera() {

    this->pos = new Vec3();
    this->velocity = new Vec3();
    this->acceleration = new Vec3();

    this->facingDirection = new Vec3(0, 0, 1);
    this->fov = new Vec2();
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->movementSpeed = 3;
    this->sprintFactor = 2;

    this->lightingVec = new Vec3();

}

// Destructor
Camera::~Camera() {
    delete this->pos;
    delete this->velocity;
    delete this->acceleration;
    delete this->facingDirection;
    delete this->fov;
}

// Instance functions
void Camera::setPos(double x, double y, double z) {
    this->pos->x = x;
    this->pos->y = y;
    this->pos->z = z;
    return;
}

void Camera::setPos(Vec3* position) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (position == nullptr) {
        logWrite("Called Camera->setPos(Vec3*) on a null pointer!\n");
        return;
    }

    delete this->pos;
    this->pos = position->copy();
}

void Camera::setVelocity(double x, double y, double z) {
    this->velocity->x = x;
    this->velocity->y = y;
    this->velocity->z = z;
    return;
}

void Camera::setVelocity(Vec3* velocity) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (velocity == nullptr) {
        logWrite("Called Camera->setVelocity(Vec3*) on a null pointer!");
        return;
    }

    delete this->velocity;
    this->velocity = velocity->copy();
}

void Camera::setAcceleration(double x, double y, double z) {
    this->acceleration->x = x;
    this->acceleration->y = y;
    this->acceleration->z = z;
    return;
}

void Camera::setAcceleration(Vec3* acceleration) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (acceleration == nullptr) {
        logWrite("Called Camera->setAcceleration(Vec3*) on a null pointer!");
        return;
    }

    delete this->acceleration;
    this->acceleration = acceleration->copy();
}

void Camera::setFacingDirection(double x, double y, double z) {
    this->facingDirection->x = x;
    this->facingDirection->y = y;
    this->facingDirection->z = z;
    return;
}

void Camera::setFacingDirection(Vec3* facingDirection) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (facingDirection == nullptr) {
        logWrite("Called Camera->setFacingDirection(Vec3*) on a null pointer!");
        return;
    }

    delete this->facingDirection;
    this->facingDirection = facingDirection->copy();
    return;
}

void Camera::setFov(double x, double y) {
    this->fov->x = x;
    this->fov->y = y;
    return;
}

void Camera::setFov(Vec2* fov) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (fov == nullptr) {
        logWrite("Called Camera->setFov(Vec2*) on a null pointer!", true);
        return;
    }

    delete this->fov;
    this->fov = fov->copy();
    return;
}

void Camera::setLightingVec(double x, double y, double z) {
    this->lightingVec->x = x;
    this->lightingVec->y = y;
    this->lightingVec->z = z;
    return;
}

void Camera::setLightingVec(Vec3* lightingVec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (lightingVec == nullptr) {
        logWrite("Called Camera->setLightingVec(Vec3*) on a null pointer!", true);
        return;
    }

    delete this->lightingVec;
    this->lightingVec = lightingVec->copy();
    return;
}

void Camera::setPreset(int preset) {

    switch (preset) {

        case 0:
            this->setPos(0, 0, -10);
            this->setFov(90, 54);
            this->setLightingVec(1, -5, 2); // downfacing off axis lighting
            this->movementSpeed = 50;
            break;

    }

}

void Camera::rotate(double yaw, double pitch, double roll) {

    // Update angles
    this->yaw += yaw;
    this->pitch += pitch;
    this->roll += roll;
    this->rolloverAngles();

    // Find new facing direction vector
    this->facingDirection->set(0, 0, 1);
    this->facingDirection->rotate(-this->yaw, -this->pitch, this->roll);

    return;

}

void Camera::project(Vec3* vec, Vec3* displayPos) {

    /*
        Same as above, but this one places the distance between the point and the camera pos into the z component of displayPos
    */

    // Address error cases, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*) with 'vec' being a null pointer!", true);
        return;
    }

    if (displayPos == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*) with 'displayPos' being a null pointer!", true);
        return;
    }
    
    // Get points location relative to the cameras position and rotation
    displayPos->set(vec);
    displayPos->sub(this->pos);
    displayPos->rotate(this->yaw, 0, 0);
    displayPos->rotate(0, this->pitch, 0);

    displayPos->project();

    return;
    
}

void Camera::project(Vec3* vec, Vec3* displayPos, Vec3* offset) {

    /*
        Same as above, but this one allows for the point to be treated as though its in a different location.
        'offset' acts as a relative position for the point from (0, 0, 0), so it is simply added to 'relative'
    */

    // Address error cases, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*, Vec3*) with 'vec' being a null pointer!", true);
        return;
    }

    if (displayPos == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*, Vec3*) with 'displayPos' being a null pointer!", true);
        return;
    }

    if (offset == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*, Vec3*) with 'offset' being a null pointer!", true);
        return;
    }
    
    // Get points location relative to the cameras position and rotation
    displayPos->set(vec);
    displayPos->add(offset);
    displayPos->sub(this->pos);
    displayPos->rotate(this->yaw, 0, 0);
    displayPos->rotate(0, this->pitch, 0);

    displayPos->project();

    return;

}

void Camera::project(Mesh* mesh) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called Camera->project(Mesh*) on a null pointer!", true);
        return;
    }
    
    // This uses the other project function to project each of the mesh verticies to the meshes projectedVerticies
    for (int i = 0; i < mesh->vertexCount; i++) {
        this->project(mesh->verticies[i], mesh->projectedVerticies[i]);
    }

}

void Camera::project(Mesh* mesh, Vec3* offset) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called Camera->relativeProject(Mesh*, Vec3*) with 'mesh' being a null pointer!", true);
        return;
    }

    if (offset == nullptr) {
        logWrite("Called Camera->relativeProject(Mesh*, Vec3*) with 'offset' being a null pointer!", true);
        return;
    }
    
    // This uses the other project function to project each of the mesh verticies to the meshes projectedVerticies
    for (int i = 0; i < mesh->vertexCount; i++) {
        this->project(mesh->verticies[i], mesh->projectedVerticies[i], offset);
    }

}

bool Camera::canSee(Tri3* tri) {

    // Find the distance to the triangle, relative to the camera position
    Vec3* distance;
    distance = tri->getCenter();
    distance->sub(this->pos);

    bool returnValue = tri->isFacing(distance);

    delete distance;

    return returnValue;

}

bool Camera::canSee(Tri3* tri, Vec3* offset) {

    // Find the distance to the triangle, relative to the camera position, accounting for offset
    Vec3* distance;
    distance = tri->getCenter();
    distance->add(offset);
    distance->sub(this->pos);

    bool returnValue = tri->isFacing(distance);

    delete distance;

    return returnValue;

}

void Camera::rolloverAngles() {
    while (this->yaw > (double) 360) {
        this->yaw -= 360;
    }
    while (this->yaw < (double) 0) {
        this->yaw += 360;
    }
    while (this->pitch > (double) 360) {
        this->pitch -= 360;
    }
    while (this->pitch < (double) 0) {
        this->pitch += 360;
    }
    while (this->roll > (double) 360) {
        this->roll -= 360;
    }
    while (this->roll < (double) 0) {
        this->roll += 360;
    }
}



/* --------------- */
/* --- Display --- */
/* --------------- */

// Constructors
Display::Display(int width, int height) {    
    this->width = width;
    this->height = height;
    this->widthOffset = 0;
    this->heightOffset = 0;
}

Display::Display(int width, int height, int widthOffset, int heightOffset) {    
    this->width = width;
    this->height = height;
    this->widthOffset = widthOffset;
    this->heightOffset = heightOffset;
}

// Instance functions
int Display::middleX() {
    return ((int) (this->width / 2)) + this->widthOffset;
}

int Display::middleY() {
    return ((int) (this->height / 2)) + this->heightOffset;
}

void Display::toDisplayPos(Vec2* vec) {
    /*
        Converts factors from 0-1 into display cooridnates given a Display object
        CHANGES THE ACTUAL VALUES OF THE ARGUMENT
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Display->toDisplayPos(Vec2*) on a null pointer!", true);
        return;
    }

    int drawPosx = (int) (vec->x * (double) this->width);
    drawPosx += this->widthOffset;

    int drawPosy = this->height - (int) (vec->y * (double) this->height); // minus because y=0 is at the top
    drawPosy += this->heightOffset;

    vec->x = drawPosx;
    vec->y = drawPosy;

    return;

}

void Display::toDisplayPos(Vec3* vec) {
    /*
        Converts factors from 0-1 into display cooridnates given a Display object
        CHANGES THE ACTUAL VALUES OF THE ARGUMENT
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Display->toDisplayPos(Vec2*) on a null pointer!", true);
        return;
    }

    double drawPosx = vec->x * (double) this->width;
    drawPosx += this->widthOffset;

    double drawPosy = this->height - (vec->y * (double) this->height); // minus because y=0 is at the top
    drawPosy += this->heightOffset;

    vec->x = drawPosx;
    vec->y = drawPosy;

    return;

}

void Display::toDisplayPos(Mesh* mesh) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called Display->toDisplayPos(Mesh*) on a null pointer!", true);
        return;
    }

    for (int i = 0; i < mesh->vertexCount; i++) {
        this->toDisplayPos(mesh->projectedVerticies[i]);
    }
}

class Object {
    
    /*
        This class contains a mesh alongside some variables for handling physics interactions
        Most of the instance functions here just directly call the same function from Mesh class
    */

    public:

        /*   Instance Variables   */

        Mesh* mesh;

        Vec3* pos;
        Vec3* velocity;
        Vec3* gravity;

        double mass;
        double gravityFactor;
        double frictionFactor;
        double bounceFactor;


        // Constructor
        Object();
        Object(Mesh* mesh);

        // Destructor
        ~Object();


        /*   Instance Functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Object* copy();

        // Returns the center of the mesh (average of all verticies). This returns a reference to an instance variable.
        Vec3* getCenter();

        // Moves the object in space by the specified distance.
        Object* move(Vec3* dist);
        Object* move(double dx, double dy, double dz);

        // Scales the object by a given factor on each axis
        Object* scale(double factor);
        Object* scale(double fx, double fy, double fz);

        // Rotates the object by the specified angles. rotates around (0, 0, 0) if no around vector is given
        Object* rotate(Vec3* angle, Vec3* around);
        Object* rotate(double yaw, double pitch, double roll, Vec3* around /* default value = nullptr */);

        // Rotates the object around its center
        Object* rotateSelf(Vec3* angle);
        Object* rotateSelf(double yaw, double pitch, double roll);

        // Sets the color of the object
        Object* setColor(Uint32 color);

        // Updates all the physics variables of this object based on a delta time
        void doPhysics(double dt);

        // Simple collision check. the object will act as though there is an infinite mass plane at a y level
        void doFloorCollision(double y);

        bool collides(Object* other);


};



class ObjectSet {

    /*
        Contains a set of Objects in the form of a doubly linked list
        This can be added and removed from, and this way a group of objects can be rendered and drawn together
        This set is used for items unaffected by physics
    */

    public:

        // Constructor
        ObjectSet();

        // Destructor
        ~ObjectSet();


        /*   Instance Functions   */

        // Returns the length of the internal linked list
        int getLength();
        
        void pushBack(Object* obj);
        void pushBack(Object* obj, int id);
        void pushFront(Object* obj);
        void pushFront(Object* obj, int id);

        Object* popBack();
        Object* popFront();

        // Pops the node with this id. If the id doesnt exist in the list, this returns nullptr
        Object* popById(int id);

        // Returns a reference to the object with a given id. DOES NOT change the internal list.
        Object* getById(int id);

        // Sets the instance variable iterCurrent to an index, from where the other iterator functions can be called
        void iterStart(int index);

        // Returns the object of iterCurrent. Returns nullptr if the iterator is at null
        Object* iterGetObj();

        // Returns the id of iterCurrent. Returns -1 if the iterator is at null
        int iterGetId();

        // Moves the iterator forward 1
        void iterNext();

        // Moves the iterator back 1
        void iterLast();

        // Returns true if iterCurrent equals nullptr
        bool iterIsDone();


        /*   Functions to affect all objects in the set   */

        // Changes the position of all the objects
        void moveAll(Vec3* dist);
        void moveAll(double dx, double dy, double dz);

        // Sets the position of all the objects
        void setPosAll(Vec3* pos);
        void setPosAll(double x, double y, double z);

        // Adds velocity to all the objects
        void addVelocityAll(Vec3* v);
        void addVelocityAll(double vx, double vy, double vz);

        // Sets the velocity of all the objects
        void setVelocityAll(Vec3* v);
        void setVelocityAll(double vx, double vy, double vz);

        // Sets the gravitational acceleration for all objects in the set
        void setAllGravity(Vec3* gravity);  // This copies the values from thi Vec3 into instance variables, this one needs to be handled accordingly
        void setAllGravity(double gx, double gy, double gz);  // Sets all the instance variables to these values
        void setAllGravity(double gy);  // Sets the gravity to just down or up

        // Calls Object->doPhysics for all in the set
        void doAllPhysics(double dt);

        // Projects all the objects into window coordinates
        void projectAll(Camera* camera, Display* display);

        // Projects, sorts, and draws all the objects in the set, in order from furthest away to closest
        void drawAll(Drawer* drawer, Camera* camera, Display* display);

        // Does the same as drawAll(), but also draws red normal vectors on all the tris
        void drawAllWithNormals(Drawer* drawer, Camera* camera, Display* display);

        // Logs all of the nodes in the order they stand in the list
        void log();

    private:
        
        /*   Instance Variables   */

        // List shouldnt be directly accessed
        LinkedList<Object*>* list;

};

/* -------------- */
/* --- Object --- */
/* -------------- */

// Constructors
Object::Object() {

    this->mesh = nullptr;
    
    this->pos = new Vec3();
    this->velocity = new Vec3();
    this->gravity = new Vec3();

    this->mass = 100;
    this->gravityFactor = 1;
    this->frictionFactor = 1;
    this->bounceFactor = 1;

    return;

}

Object::Object(Mesh* mesh) {

    this->mesh = mesh;

    this->pos = new Vec3();
    this->velocity = new Vec3();
    this->gravity = new Vec3();

    this->mass = 100;
    this->gravityFactor = 1;
    this->frictionFactor = 1;
    this->bounceFactor = 1;

    return;

}

// Destructor
Object::~Object() {

    if (this->mesh != nullptr) delete this->mesh;

    if (this->pos != nullptr) delete this->pos;
    if (this->velocity != nullptr) delete this->velocity;
    if (this->gravity != nullptr) delete this->gravity;

}

// Instance functions
Object* Object::copy() {

    Object* ret = new Object();

    ret->mesh = this->mesh;

    ret->pos = this->pos;
    ret->velocity = this->velocity;
    ret->gravity = this->gravity;

    ret->mass = this->mass;
    ret->gravityFactor = this->gravityFactor;
    ret->frictionFactor = this->frictionFactor;
    ret->bounceFactor = this->bounceFactor;

    return ret;

}

Vec3* Object::getCenter() {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->getCenter() while Object->mesh was nullptr!", true);
        return nullptr;
    }

    return this->mesh->getCenter();

}

Object* Object::move(Vec3* dist) {

    // Log the error cases
    if (this->mesh == nullptr) {
        logWrite("Called Object->move(Vec3*) while Object->mesh was null pointer!", true);
        return nullptr;
    }

    if (this->mesh == nullptr) {
        logWrite("Called Object->move(Vec3*) with 'dist' being a null pointer!", true);
        return nullptr;
    }

    this->pos->add(dist);
    return this;

}

Object* Object::move(double dx, double dy, double dz) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->move(double, double, double) while Object->mesh was null pointer!", true);
        return nullptr;
    }

    this->pos->add(dx, dy, dz);
    return this;
    
}

Object* Object::scale(double factor) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->scale(double) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->scale(factor);
    return this;

}

Object* Object::scale(double fx, double fy, double fz) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->move(double, double, double) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->scale(fx, fy ,fz);
    return this;

}

Object* Object::rotate(Vec3* angle, Vec3* around) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotate(Vec3*, Vec3*) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->rotate(angle, around);
    return this;

}

Object* Object::rotate(double yaw, double pitch, double roll, Vec3* around = nullptr) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotate(double, double, double, Vec3*) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->rotate(yaw, pitch, roll, around);
    return this;

}

Object* Object::rotateSelf(Vec3* angle) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotateSelf(Vec3*) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->rotateSelf(angle);
    return this;

}

Object* Object::rotateSelf(double yaw, double pitch, double roll) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotateSelf(double, double, double) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->rotateSelf(yaw, pitch, roll);
    return this;

}

Object* Object::setColor(Uint32 color) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->setColor(Uint32) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->setColor(color);
    return this;

}

void Object::doPhysics(double dt) {

    double dtSeconds = dt / 1000;

    Vec3* delta = new Vec3();

    delta->set(this->velocity)->scale(dtSeconds);
    this->pos->add(delta);

    delta->set(this->gravity)->scale(dtSeconds)->scale(this->gravityFactor);
    this->velocity->add(delta);

    delete delta;

}

void Object::doFloorCollision(double y) {

    return;

}

bool Object::collides(Object* other) {

    return false;

}



/* ----------------- */
/* --- ObjectSet --- */
/* ----------------- */

// Constructor
ObjectSet::ObjectSet() {

    this->list = new LinkedList<Object*>();

}

// Destructor
ObjectSet::~ObjectSet() {
    
    delete this->list;

}

// Instance Functions
int ObjectSet::getLength() {

    return this->list->length;

}

void ObjectSet::pushBack(Object* obj) {

    // Log the error case
    if (obj == nullptr) {
        logWrite("Called ObjectSet->pushBack(Object*) on a null pointer!", true);
        return;
    }
    
    this->list->pushBack(obj);
    return;

}

void ObjectSet::pushBack(Object* obj, int id) {

    // Log the error case
    if (obj == nullptr) {
        logWrite("Called ObjectSet->pushBack(Object*, int) on a null pointer!", true);
        return;
    }
    
    this->list->pushBack(obj, id);
    return;

}

void ObjectSet::pushFront(Object* obj) {

    // Log the error case
    if (obj == nullptr) {
        logWrite("Called ObjectSet->pushFront(Object*) on a null pointer!", true);
        return;
    }

    this->list->pushFront(obj);
    return;

}

void ObjectSet::pushFront(Object* obj, int id) {

    // Log the error case
    if (obj == nullptr) {
        logWrite("Called ObjectSet->pushFront(Object*, int) on a null pointer!", true);
        return;
    }

    this->list->pushFront(obj, id);
    return;
    
}

Object* ObjectSet::popBack() {

    return this->list->popBack();

}

Object* ObjectSet::popFront() {

    return this->list->popFront();
    
}

Object* ObjectSet::popById(int id) {

    return this->list->popById(id);

}

Object* ObjectSet::getById(int id) {

    return this->list->getById(id);

}

void ObjectSet::iterStart(int index) {

    this->list->iterStart(index);

}

Object* ObjectSet::iterGetObj() {

    return this->list->iterGetObj();

}

int ObjectSet::iterGetId() {

    return this->list->iterGetId();

}

void ObjectSet::iterNext() {

    this->list->iterNext();

}

void ObjectSet::iterLast() {

    this->list->iterLast();

}

bool ObjectSet::iterIsDone() {

    return this->list->iterIsDone();

}

void ObjectSet::moveAll(Vec3* dist) {

    // Log the error case
    if (dist == nullptr) {
        logWrite("Called ObjectSet->moveAll(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->move(dist);

}

void ObjectSet::moveAll(double dx, double dy, double dz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) 
        this->iterGetObj()->move(dx, dy, dz);

}

void ObjectSet::setPosAll(Vec3* pos) {

    // Log the error case
    if (pos == nullptr) {
        logWrite("Called ObjectSet->setPosAll(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->pos->set(pos);

}

void ObjectSet::setPosAll(double x, double y, double z) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->pos->set(x, y, z); 

}

void ObjectSet::addVelocityAll(Vec3* v) {

    // Log the error case
    if (v == nullptr) {
        logWrite("Called ObjectSet->addVelocityAll(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity->add(v);

}

void ObjectSet::addVelocityAll(double vx, double vy, double vz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity->add(vx, vy, vz); 

}

void ObjectSet::setVelocityAll(Vec3* v) {

    // Log the error case
    if (v == nullptr) {
        logWrite("Called ObjectSet->setVelocityAll(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity->set(v);

}

void ObjectSet::setVelocityAll(double vx, double vy, double vz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity->set(vx, vy, vz);

}

void ObjectSet::setAllGravity(Vec3* gravity) {

    // Log the error case
    if (gravity == nullptr) {
        logWrite("Called ObjectSet->setAllGravity(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())  
        this->iterGetObj()->gravity->set(gravity);

}

void ObjectSet::setAllGravity(double gx, double gy, double gz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->gravity->set(gx, gy, gz);

}

void ObjectSet::setAllGravity(double gy) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->gravity->set(0, gy, 0);

}

void ObjectSet::doAllPhysics(double dt) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->doPhysics(dt);

}

void ObjectSet::projectAll(Camera* camera, Display* display) {

    // Log the error cases
    if (camera == nullptr) {
        logWrite("Called ObjectSet->projectAll(Camera*, Display*) with 'camera' being a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called ObjectSet->projectAll(Camera*, Display*) with 'display' being on a null pointer!", true);
        return;
    }

    Object* currentObj;

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentObj = this->iterGetObj();

        camera->project(currentObj->mesh, currentObj->pos);
        display->toDisplayPos(currentObj->mesh);

    }

}

void ObjectSet::drawAll(Drawer* drawer, Camera* camera, Display* display) {

    // Log the error cases
    if (drawer == nullptr) {
        logWrite("Called ObjectSet->drawAll(Drawer*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet->drawAll(Drawer*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called ObjectSet->drawAll(Drawer*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Set up
    this->projectAll(camera, display);
    Object* currentObj;

    // Main loop
    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentObj = this->iterGetObj();

        for (int i = 0; i < currentObj->mesh->triCount; i++) {

            // Skip if all the vertices are behind the camera. This is flagged by marking the depth as inf
            if (
                currentObj->mesh->projectedTris[i]->v1->z == inf ||
                currentObj->mesh->projectedTris[i]->v2->z == inf ||
                currentObj->mesh->projectedTris[i]->v3->z == inf
            ) continue;
        
            // Skip if tri cant be seen by cam on the outfacing side
            if (!camera->canSee(currentObj->mesh->tris[i], currentObj->pos)) continue;

            // Find a shade based on the lighting vec
            double lightAngle = currentObj->mesh->tris[i]->normal->getAngle(camera->lightingVec);
            double lightFactor = lightAngle / 180;

            Uint32 shade = currentObj->mesh->color;
            shade = Color::setBrightness(shade, lightFactor);

            // Draw the tri    
            drawer->drawTriangle(shade, currentObj->mesh->projectedTris[i]);

        }

    }

}

void ObjectSet::drawAllWithNormals(Drawer* drawer, Camera* camera, Display* display) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (drawer == nullptr) {
        logWrite("Called ObjectSet->drawAllWithNormals(Drawer*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet->drawAllWithNormals(Drawer*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called ObjectSet->drawAllWithNormals(Drawer*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Set up
    this->projectAll(camera, display);
    Mesh* currentMesh;
    Vec3* vecStart = new Vec3(); 
    Vec3* vecEnd = new Vec3();

    // Main loop
    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentMesh = this->iterGetObj()->mesh;

        for (int i = 0; i < currentMesh->triCount; i++) {
        
            // Skip if tri cant be seen by cam on the outfacing side
            if (!camera->canSee(currentMesh->tris[i])) continue;

            // Find a shade based on the lighting vec
            double lightAngle = currentMesh->tris[i]->normal->getAngle(camera->lightingVec);
            double lightFactor = lightAngle / 180;

            Uint32 shade = currentMesh->color;
            shade = Color::setBrightness(shade, lightFactor);

            // Draw the tri    
            drawer->drawTriangle(shade, currentMesh->projectedTris[i]);

        }

        // Draw normals
        for (int i = 0; i < currentMesh->triCount; i++) {

            // Skip if tri cant be seen face on by cam
            if (!camera->canSee(currentMesh->tris[i])) continue;

            Vec3* triCenter;
            Vec3* normalOffset;
            Vec3* triNormal;

            // Get projected coords for normal start and end
            triCenter = currentMesh->tris[i]->getCenter();
            normalOffset = currentMesh->tris[i]->normal->copy()->normalise(1);
            triNormal = triCenter->copy()->add(normalOffset);

            camera->project(triCenter, vecStart);
            camera->project(triNormal, vecEnd);
            display->toDisplayPos(vecStart);
            display->toDisplayPos(vecEnd);

            drawer->drawLine(Color::RED, vecStart->x, vecStart->y, vecEnd->x, vecEnd->y);

            delete triCenter;
            delete normalOffset;
            delete triNormal;

        }

    }

    delete vecStart; delete vecEnd;

}

void ObjectSet::log() {

    this->list->log();
    return;

}

class Gui {

    /*
        This class serves to simplify the process of creating an SDL2 window.
        The whole process of creating many objects and checking if they were initialized properly is now done automatically when init is run.
        All this class requires if a window size (width, height) and it does the rest when instance->init() is called.
        This also serves as a base for the DrawerClass, as it handles pixel buffer interactions with SDL2.
    */

    public:

        /* --- Instance variables --- */

        // Window size
        int windowWidth, windowHeight;
        
        // Used for sdl. stores the amount of bytes per row of pixels
        int pitch;

        // SDL stuff for drawing to the window
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        // Pixel buffer
        Uint32* buffer;


        // Constructor
        Gui(int windowWidth, int windowHeight);

        // Even though this class allocated memory for SDL2 objects. These objects cannot be deleted manually.
        // When running instance->exit(), there is a call made to SDL2 which handles this all.

        /*   Instance functions   */

        // Create all SDL2 objects, and ensure creating went properly.
        int init();

        // Closes the SDL2 window.
        void exit();

        // Gets the pixel buffer, and locks the screen until flip is called.
        void getBuffer();
        
        // Sets the window to the pixel buffer.
        void flip();

};

// Constructor
Gui::Gui(int windowWidth, int windowHeight) {

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    this->window = nullptr;
    this->renderer = nullptr;
    this->texture = nullptr;

    this->buffer = new Uint32[windowWidth * windowHeight];

}

// Instance functions
int Gui::init() {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        logWrite("SDL init failed! from GuiClass.h in init()", true);
        return 1;
    }

    // Create a window
    this->window = SDL_CreateWindow(
        "SDL2 Window", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        this->windowWidth, 
        this->windowHeight, 
        SDL_WINDOW_SHOWN
    );

    if (this->window == nullptr) {
        logWrite("SDL create window failed! from GuiClass.h in init()", true);
        return 1;
    }

    // Create renderer
    this->renderer = SDL_CreateRenderer(
        this->window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );

    if (this->renderer == nullptr) {
        logWrite("SDL create renderer failed! from GuiClass.h in init()", true);
        return 1;
    }
    
    // Create texture
    this->texture = SDL_CreateTexture(
        this->renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        this->windowWidth, 
        this->windowHeight
    );

    if (this->texture == nullptr) {
        logWrite("SDL create texture failed! from GuiClass.h in init()", true);
        return 1;
    }

    return 0;
}

void Gui::exit() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Gui::getBuffer() {
    SDL_LockTexture(this->texture, nullptr, (void**) &(this->buffer), &this->pitch);
}

void Gui::flip() {
    SDL_UnlockTexture(this->texture);
    SDL_UpdateTexture(this->texture, nullptr, this->buffer, this->pitch);
    //SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, nullptr, nullptr);
    SDL_RenderPresent(this->renderer);
}

// Early declarations becuase theres some circular dependancy here
class Window;
class Action;


enum ElementType {
    NONE,
    TEXT,
    VISUAL,
    BUTTON
};


class WindowElement {

    public:

        /*   Pre Defined Variables   */

        Uint32 color;


        /*   Instance Variables   */

        Vec2* pos; // Relative to parent
        Vec2* size;

        Action* action;

        LinkedList<WindowElement*>* children;

        ElementType type = NONE;


        // Constructor
        WindowElement(int posx, int posy, int sizex, int sizey);

        // Destructor
        virtual ~WindowElement();


        /*   Instance Functions   */

        // Offset should be the position of the parent, since all elements are stored in relative positions
        virtual void draw(Drawer* drawer, Vec2* offset);

        // Returns the child element that the click lies on. Returns this if this does but no children do. Returns nullptr if none do
        WindowElement* doClick(int x, int y, Vec2* offset);

        // Runs the action associated with the element. Does nothing if no action has been associated.
        void onClick();

        // Adds a child element to this element
        void addChild(WindowElement* child);


        /*   Class Functions   */
        
        // Returns a NEW WindowElement for the top bar of a window containing the window title, and the buttons
        static WindowElement* createTopBar(Window* window, const char* title);

        static WindowElement* createSlider(int width);

        static WindowElement* createTextBox(int width);

    protected:

        /*   Instance Variables   */
        
        // Used for detecting clicks, and drawing for some subclasses
        Vec2* endPos;


        /*   Instance functions   */

        // This function assumes the given offset already accounts for this->pos
        void drawChildren(Drawer* drawer, Vec2* offset);

};


class WindowLine : public WindowElement {

    public:

        // Constructor
        WindowLine(int x1, int y1, int x2, int y2);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowFilledRect : public WindowElement {

    public:

        // Constructor
        WindowFilledRect(int posx, int posy, int sizex, int sizey);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowOutlinedRect : public WindowElement {

    public:

        // Constructor
        WindowOutlinedRect(int posx, int posy, int sizex, int sizey);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowCircle : public WindowElement {

    public:

        // Constructor
        WindowCircle(int posx, int posy, int size);

        // Destructor
        ~WindowCircle() override;

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        // Used for drawing, stores the center of the circle and the radius
        Vec2* middle;
        int radius;

};


class WindowText : public WindowElement {

    public:

        // Constructor
        WindowText(int posx, int posy, int sizex, int sizey, const char* text);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        const char* text;

};


class WindowTexture : public WindowElement {

    public:

        // Constructor
        WindowTexture(int posx, int posy, int sizex, int sizey, PNG* texture);

        // Destructor
        ~WindowTexture() override;

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        PNG* texture;

};


class WindowButton : public WindowElement {

    /*
        Class for buttons which should have some on click effect
        Note: Any buttons which are children of buttons WILL NOT be found as clicked since the search stops once it finds the first button
        This concept also applies to overlapping buttons, whenever clicking two at the same time, only one will act
    */

    public:

        // Constructor
        WindowButton(int posx, int posy, int sizex, int sizey);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class Window {

    public:

        /*   Pre Defined Variables   */

        Uint32 COLOR_BASE = Color::BACKGROUND;
        Uint32 COLOR_ACCENT = Color::ACCENT;
        Uint32 COLOR_TEXT = Color::BLACK;

        /*   Instance Variables   */

        Vec2* pos;
        Vec2* size;
        int layer; // Front to back - 0 is at the front, 1 behind, and so on

        LinkedList<WindowElement*>* elements;

        // Constructors
        Window(int posx, int posy, int sizex, int sizey, int layer = 0);
        Window(Vec2* pos, Vec2* size, int layer = 0); // References are stored, the Vec2's should not be deleted after calling this

        // Destructor
        ~Window();

        /*   Instance Functions   */

        // Draws the window and all its elements
        void draw(Drawer* drawer);

        // Returns the element that covers the click location. Return nullptr if none do
        WindowElement* doClick(int x, int y);

        // Adds an element to the window
        void addElement(WindowElement* element);

    private:

        Vec2* endPos; // Used for drawing, stores the coordinates of pos + size

};


class Action {

    public:

        /*   Instance Variables   */

        // Constructor
        Action();

        // Destructor
        virtual ~Action();

        /*   Instance Functions   */

        virtual void run() {}

};


class ActionLogWrite : public Action {

    public:

        /*   Instance Variables   */

        const char* message;

        // Constructor
        ActionLogWrite(const char* message);

        // Destructor
        ~ActionLogWrite() override;

        /*   Instance Functions   */

        void run() override;

};


class ActionCloseWindow : public Action {

    public:

        /*   Instance Variables   */

        Window* window;

        // Constructor
        ActionCloseWindow(Window* window);

        // Destructor
        ~ActionCloseWindow() override;

        /*   Instance Functions   */

        void run() override;

};

void doPhysics(ObjectSet* objectSet, State* state) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (objectSet == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'objectSet' as a null pointer!", true);
        return;
    }

    if (state == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'state' as a null pointer!", true);
        return;
    }

    objectSet->doAllPhysics(state->time->dt);

    return;

}

Font* font;
bool drawNormals;

void initGraphics() {

    drawNormals = false;

    font = new Font();
    font->init();

}

void drawSky(Drawer* drawer, Camera* camera, Display* display) {

    // Because of how this function is called from drawGraphics, none of these should ever be null but it doesnt really hurt to check

    // Address error cases, but dont kill the process yet in case its not fatal
    if (drawer == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Find the height on the display to draw the skyline
    Vec2* heightVec = new Vec2(display->height, 0);
    heightVec->rotate(camera->pitch);
    double height = (display->height / 2) + heightVec->y;
    delete heightVec;

    // If the camera is facing down enough that no sky is visible
    if (height < 0) {
        drawer->fillScreen(Color::BLACK);
        return;
    }

    // Draw the rectangles
    uint32_t skyColorLight = 0xFF323296; // o->FF, r->32, g->32, b->96
    uint32_t skyColorDark = 0xFF161648; // o->FF, r->16, g->16, b->48

    drawer->drawRect(
        skyColorLight, 
        display->widthOffset, 
        display->heightOffset, 
        display->widthOffset + display->width, 
        display->heightOffset + (height - (double) 25)
    );
    drawer->drawRect(
        skyColorDark, 
        display->widthOffset, 
        display->heightOffset + (height - (double) 25), 
        display->widthOffset + display->width, 
        display->heightOffset + height
    );
    drawer->drawRect(
        Color::BLACK, 
        display->widthOffset, 
        display->heightOffset + height, 
        display->widthOffset + display->width, 
        display->heightOffset + display->height
    );

    return;

}

void drawGraphics(ObjectSet* objectSet, Drawer* drawer, State* state, Camera* camera, Display* display) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (objectSet == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'objectSet' as a null pointer!", true);
        return;
    }

    if (drawer == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (state == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'state' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Toggle normal vector drawing on key n
    if (state->keyJustDown(SDLK_n))
        drawNormals = !drawNormals;

    drawSky(drawer, camera, display);
    
    // Draw all the objects
    if (drawNormals) 
        objectSet->drawAllWithNormals(drawer, camera, display);
    else 
        objectSet->drawAll(drawer, camera, display);

    // Draw the fps
    drawer->drawRect(Color::BLACK, 0, 0, 30, 13);
    font->drawer = drawer;
    font->drawInt(state->time->fps, 6, 3, Color::WHITE);

    return;

}

// Global declarations
Gui* gui;
State* state;
Drawer* drawer;
Display* display;
Camera* camera;
ObjectSet* objects;

bool gravity;

void handleInput(State* state, Camera* camera) {

    /*
        ---  Directional Movement  ---

        The camera movement depends on facing direction for x,z movement (using WASD), while the up and down movement do not change based on facing direction
        First a value 'dist' is found which determines how far the camera should move based on the dt (delta time)
        Then the up and down movement are simple because the camera y position is just added or subtracted by the dist amount
        The x,z movement is a bit more complicated because it uses a 2d vector to hold the actual movement where the x and y components hold the left-right and front-back
        then rotates it based on the camera yaw and adds that to position.
    */

    // Find distance to move based on the delta time of the frame
    double dist = camera->movementSpeed * (state->time->dt / 1000);

    if (state->keyIsDown(SDLK_LSHIFT))
        dist *= camera->sprintFactor;

    // Vertical Movement
    if (state->keyIsDown(SDLK_SPACE)) camera->pos->y += dist; // Up
    if (state->keyIsDown(SDLK_LCTRL)) camera->pos->y -= dist; // Down

    // Horizontal Movement
    Vec2* cameraMovVec = new Vec2();
    if (state->keyIsDown(SDLK_w)) cameraMovVec->y += dist; // Forward
    if (state->keyIsDown(SDLK_s)) cameraMovVec->y -= dist; // Backward
    if (state->keyIsDown(SDLK_a)) cameraMovVec->x -= dist; // Left
    if (state->keyIsDown(SDLK_d)) cameraMovVec->x += dist; // Right

    // Move camera based on its rotation
    cameraMovVec->rotate(-camera->yaw);
    camera->pos->x += cameraMovVec->x;
    camera->pos->z += cameraMovVec->y;
    delete cameraMovVec;

    /*  ---  Camera Rotation  ---  */
    if (state->mouse->leftButtonIsDown) {

        // 0.2 is just a random number I chose becuase it felt good in the app
        double mouseSensitivity = 0.2;
        double camDeltaYaw = (double) state->deltaMousePosX();
        double camDeltaPitch = (double) state->deltaMousePosY();
        camera->rotate( camDeltaYaw * mouseSensitivity, -camDeltaPitch * mouseSensitivity, 0 );

    }


    /*   Temporary stuff   */

    // This rotates the white sphere on the left when pressing keys j,k,l
    if (state->keyIsDown(SDLK_j))
        objects->getById(6)->mesh->rotateSelf(1, 0, 0);

    if (state->keyIsDown(SDLK_k))
        objects->getById(6)->mesh->rotateSelf(0, 1, 0);

    if (state->keyIsDown(SDLK_l))
        objects->getById(6)->mesh->rotateSelf(0, 0, 1);

    // This moves the blue oval inside the white sphere when pressing keys o,p
    if (state->keyIsDown(SDLK_o))
        objects->getById(5)->mesh->move(0, 0.5, 0);

    if (state->keyIsDown(SDLK_p))
        objects->getById(5)->mesh->move(0, -0.5, 0);

    // Toggles gravity
    if (state->keyJustDown(SDLK_g))
        if (gravity) {
            std::cout << "gravity off" << std::endl;
            objects->setAllGravity(0.0);
            gravity = false;
        }

        else {
            std::cout << "gravity on" << std::endl;
            objects->setAllGravity(-30);
            gravity = true;
        }

    // Gives all the objects some vertical velocity
    if (state->keyJustDown(SDLK_z))
        objects->setVelocityAll(0, 25, 0);

}

void init() {

    // Log stuff
    logInit("log.txt");
    logClear();
    logWrite("Starting...", true);

    // Start the gui window
    gui = new Gui(1000, 600);
    gui->init();

    // Init all the working objects
    state = new State();
    drawer = new Drawer(gui->windowWidth, gui->windowHeight);
    display = new Display(gui->windowWidth, gui->windowHeight);
    camera = new Camera();
    camera->setPreset(0);

    // Sets up the default meshes, and creates the objects to be drawn
    Mesh::initMeshes();
    initGraphics();


    // Create and populate the object set
    objects = new ObjectSet();
    Object* newObject;

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(15)->move(0, 0, 50)->setColor(Color::WHITE);
    objects->pushBack(newObject, 1);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(5)->move(0, 20, 50)->setColor(Color::GREY);
    objects->pushBack(newObject, 2);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(10, 5, 15)->move(30, 10, 40)->rotateSelf(10, 0, 0)->setColor(Color::BLUE);
    objects->pushBack(newObject, 3);

    newObject = new Object();
    newObject->mesh = Mesh::capsuleMesh->copy()->scale(15)->move(0, -20, 50)->setColor(Color::GREEN);
    objects->pushBack(newObject, 4);

    newObject = new Object();
    newObject->mesh = Mesh::sphereMesh->copy()->scale(15, 40, 15)->move(-30, 0, 50)->setColor(Color::BLUE);
    objects->pushBack(newObject, 5);

    newObject = new Object();
    newObject->mesh = Mesh::sphereMesh->copy()->scale(25)->move(-30, 0, 50)->setColor(Color::WHITE);
    objects->pushBack(newObject, 6);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(10)->move(0, 10, 50)->setColor(Color::BLUE);
    objects->pushBack(newObject, 7);

    gravity = false;

}

int main(int argc, char* argv[]) {

    // Starts up everything needed for the main loop
    init();

    // Declarations for the main loop
    SDL_Event event;
    bool leave = false;


    // Main loop
    while (!leave) {

        // Mouse position
        SDL_GetMouseState(   &(state->mouse->posX),   &(state->mouse->posY)   );
        
        // Handle SDL events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) { leave = true; std::cout<<"closed"; }
            else state->addEvent(&event);
        }

        // Does all the user input handling
        handleInput(state, camera);

        // Draw stuff
        gui->getBuffer();
        drawer->buffer = gui->buffer;
        drawer->resetDepthBuffer();

        // Do the main work. functions from other files
        drawGraphics(objects, drawer, state, camera, display); // from graphics.cpp
        doPhysics(objects, state); // from physics.cpp

        gui->flip();

        // Make current state become last frame
        state->nextFrame();

    }

    delete state;
    delete camera;
    delete display;

    // Destroy the window and quit SDL
    gui->exit();

    return 0;

}
