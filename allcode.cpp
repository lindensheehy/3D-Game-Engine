/*
    This file serves no functional purpose. Just wanted to have a visual on how much code is in this project
    This doesnt actually compile for some reason, but in theory it should based on how to structured the code
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdint.h>
#include <chrono>

#include "src/lodepng/lodepng.cpp"

#include <SDL2/SDL.h>

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
    logWrite(std::to_string(message), newLine);
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
#define inf 1e12
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
double sqrt(double x, double tolerance = 0.001);


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

// Returns a value 0-1 for how far between 'from' and 'to' the value is. Returns -1 if its outside the range.
double range(double num, double from, double to);

// Same as above, but allows values outside the range, in which case it would return values outside 0-1
double inRange(double num, double from, double to);

// Swaps the values in two memory locations.
void swap(int* var1, int* var2);

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

// Returns the lesser value (int)
inline int min(int var1, int var2) {
    return (var1 < var2) ? var1 : var2;
}

// Returns the lesser value (double)
inline double min(double var1, double var2) {
    return (var1 < var2) ? var1 : var2;
}

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

    // Avoid returning small negative value in place of 0
    if (abs_(returnValue) < 1e-6) return 0;

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
        bool magnitudeUpdated;
        
};

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
        this->magnitudeValue = sqrt( (this->x * this->x) + (this->y * this->y) );
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

    double dx = this->x - other->x;
    double dy = this->y - other->y;
    return sqrt( (dx * dx) + (dy * dy) );
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

    double sinValue = sin(toRadians(degrees));
    double cosValue = cos(toRadians(degrees));

    this->x = (cosValue * relativeX) - (sinValue * relativeY) + aroundX;
    this->y = (cosValue * relativeY) + (sinValue * relativeX) + aroundY;

    return;
}

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

        // Sets the components of the Vec3 to specific values
        Vec3* set(double x, double y, double z);

        // Acts similar to '=='. Returns true if all components are equal to each other
        bool is(Vec3* other);


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

        // Find the angle between this and other. This angle will always be between 0-180.
        double getAngle(Vec3* other);

        // Rotates the vector around a certain point (by default (0, 0, 0)) by a given angle on each direction.
        // Each rotation occurs COUNTER CLOCKWISE assuming you are looking down upon the rotation.
        void rotate(double yaw, double pitch, double roll, Vec3* around = nullptr);

    private:

        /*   Instance variables   */

        // This is the length of the vector in 3d space.
        // This value is private because it is not always accurate, and is only update when requested.
        // Doing this means there wont be unnesecary updates to the magnitude when it wont even be read.
        double magnitudeValue;

        // Flag showing if the above value is accurate. This allows the function call which returns the magnitude to only do the math when nessecary.
        bool magnitudeUpdated;

};

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
        this->magnitudeValue = sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
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

    double dx = this->x - other->x;
    double dy = this->y - other->y;
    double dz = this->z - other->z;
    return sqrt( (dx * dx) + (dy * dy) + (dz * dz));
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
    if (ratio < -1) return pi;
    if (ratio > 1)  return 0;

    return arccos(ratio);
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

    if (yaw != 0) {
        double sinValue = sin(toRadians(yaw));
        double cosValue = cos(toRadians(yaw));

        this->x = (cosValue * relativeX) - (sinValue * relativeZ) + aroundX;
        this->z = (cosValue * relativeZ) + (sinValue * relativeX) + aroundZ;
    }

    if (pitch != 0) {
        double sinValue = sin(toRadians(pitch));
        double cosValue = cos(toRadians(pitch));

        this->y = (cosValue * relativeY) - (sinValue * relativeZ) + aroundY;
        this->z = (cosValue * relativeZ) + (sinValue * relativeY) + aroundZ;
    }

    if (roll != 0) {
        double sinValue = sin(toRadians(roll));
        double cosValue = cos(toRadians(roll));

        this->y = (cosValue * relativeY) - (sinValue * relativeX) + aroundY;
        this->x = (cosValue * relativeX) + (sinValue * relativeY) + aroundX;
    }

    return;
}

class Tri2 {

    /*
        Represents a triangle in 2d space.
        Simply holds 3 Vec2 objects, and has setters.
        Theres really not all that much to do in 2d.
    */

    public:

        // Instance variables
        Vec2* v1;
        Vec2* v2;
        Vec2* v3;


        /*   Constructor   */

        // nullPointers determines if the instance variables should be initialized or not.
        // When this is false, all v1, v2, and v3 are set to individual copies of (0, 0)
        Tri2(bool nullPointers = false);


        // Destructor
        ~Tri2();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Tri2* copy();

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

// Constructor
Tri2::Tri2(bool nullPointers /* default value = false */) {
    /*
        Stores a set of 3 vectors
        nullPointers flag allows the pointers to be manually set instead of autocreating objects
    */

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

class Tri3 {

    /*
        Similar to Tri2, but for 3d. This also contains a normal vector.
        There are several other functions here becuase these are the objects used for all program physics items items.
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

        // Returns a Vec3 object defining the center of the triangle. takes the average of each component.
        Vec3* getCenter();
        
};

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

    Vec3* vec1to2 = new Vec3(
        this->v1->x - this->v2->x,
        this->v1->y - this->v2->y,
        this->v1->z - this->v2->z 
    );
    Vec3* vec1to3 = new Vec3(
        this->v1->x - this->v3->x,
        this->v1->y - this->v3->y,
        this->v1->z - this->v3->z 
    );

    Vec3* newNormal = vec1to2->crossProduct(vec1to3);
    newNormal->normalise();
    
    delete this->normal;
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

    return vec->getAngle(this->normal) >= (pi / 2); // 90 degrees
}

Vec3* Tri3::getCenter() {

    // Average all 3 components
    double x = this->v1->x + this->v2->x + this->v3->x;
    double y = this->v1->y + this->v2->y + this->v3->y;
    double z = this->v1->z + this->v2->z + this->v3->z;
    x /= 3; y /= 3; z /= 3;

    return new Vec3(x, y, z);
    
}

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


class Color {

    public:

        // Constant color codes
        // Bytes are [opacity][red][green][blue]
        static const uint32 RED    = 0xFFFF0000;
        static const uint32 GREEN  = 0xFF00FF00;
        static const uint32 BLUE   = 0xFF0000FF;
        static const uint32 BLACK  = 0xFF000000;
        static const uint32 WHITE  = 0xFFFFFFFF;
        static const uint32 GREY   = 0xFF888888;


        /*   Instance variables   */

        // Raw value which was given
        uint32 rawValue;

        // Individual color channels
        uint8 redValue, greenValue, blueValue, opacityValue;


        // Contructors
        Color(uint32 color);
        Color(uint8 o, uint8 r, uint8 g, uint8 b);


        /*   Class functions   */

        // Sets the brightness of a given color (uint32) to a double between 0-1.
        // Values higher than 1 CAN be used, but could cause overflow issues.
        static uint32 setBrightness(uint32 color, double newBrightness);

};

// Contructors
Color::Color(uint32 color) {

    this->rawValue = color;

    // This gets the sub values at each 8 bit interval of the 32 bit input
    this->opacityValue = (uint8) (color >> 24);
    this->redValue = (uint8) (color >> 16);
    this->greenValue = (uint8) (color >> 8);
    this->blueValue = (uint8) (color);
}

Color::Color(uint8 o, uint8 r, uint8 g, uint8 b) {

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
uint32 Color::setBrightness(uint32 color, double newBrightness) {

    // Unpack color code
    uint8 opacityValue = (uint8) (color >> 24);
    uint8 redValue = (uint8) (color >> 16);
    uint8 greenValue = (uint8) (color >> 8);
    uint8 blueValue = (uint8) (color);

    // Update values
    redValue *= newBrightness;
    greenValue *= newBrightness;
    blueValue *= newBrightness;

    // Repack color code
    uint32 newColor = 0x00000000;
    newColor |= opacityValue;
    newColor <<= 8;
    newColor |= redValue;
    newColor <<= 8;
    newColor |= greenValue;
    newColor <<= 8;
    newColor |= blueValue;

    return newColor;

}

class FrameState {

    /*
        This class serves to handle events from frame to frame.
        It keeps track of the events currently happening on this frame, and which events happened last frame.
        Subclasses MouseState and KeyboardState keep track of their respective events.
    */

    public:

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
                void keyDown(int keyCode);
                void keyUp(int keyCode);

                // Getter for keys
                bool keyIsDown(int keyCode);

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
        
        // Value which increments every frame
        int frameCount;

        // Subclasses
        MouseState* mouse;
        KeyboardState* keys;

        // This is another FrameState object which hold the state of the previous frame.
        // Used to let some events happen once when an event happens, rather than repeating while its held.
        FrameState* lastFrame;


        /*   Constructor   */

        // hasChild determines if the lastFrame instance variable should be created.
        // This is set to true for the version created in the program, then false for the actual lastFrame instance.
        // The option therefore exists to create FrameState with no child, but there is no reason to do this.
        FrameState(bool hasChild = true);


        // Destructor
        ~FrameState();


        /*   Instance functions   */

        // Takes an event object from SDL2 and changes the respective value appropriately.
        void addEvent(SDL_Event* event);

        // Increments frameCount + updates lastFrame to match current frame
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
        
    private:

        // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
        void setState(FrameState* state);

};

/*  ------------------------------------  */
/*  ----------   MouseState   ----------  */
/*  ------------------------------------  */

// Contructor
FrameState::MouseState::MouseState() {
    this->leftButtonIsDown = false;
    this->rightButtonIsDown = false;
    this->posX = 0;
    this->posY = 0;
}

// Instance functions
void FrameState::MouseState::setState(MouseState* state) {
    this->leftButtonIsDown = state->leftButtonIsDown;
    this->rightButtonIsDown = state->rightButtonIsDown;
    this->middleButtonIsDown = state->middleButtonIsDown;
    this->posX = state->posX;
    this->posY = state->posY;
}

void FrameState::MouseState::leftButtonDown() {
    this->leftButtonIsDown = true;
}

void FrameState::MouseState::leftButtonUp() {
    this->leftButtonIsDown = false;
}

void FrameState::MouseState::middleButtonDown() {
    this->middleButtonIsDown = true;
}

void FrameState::MouseState::middleButtonUp() {
    this->middleButtonIsDown = false;
}

void FrameState::MouseState::rightButtonDown() {
    this->rightButtonIsDown = true;
}

void FrameState::MouseState::rightButtonUp() {
    this->rightButtonIsDown = false;
}

void FrameState::MouseState::setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
}



/*  -------------------------------------  */
/*  ---------   KeyboardState   ---------  */
/*  -------------------------------------  */

// Constructor
FrameState::KeyboardState::KeyboardState() {

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
FrameState::KeyboardState::~KeyboardState() {
    delete[] this->letterKeys;
    delete[] this->numKeys;
    delete[] this->miscKeys;
}

// Instance variables
void FrameState::KeyboardState::setState(KeyboardState* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called FrameState::KeyboardState->setState(KeyboardState*) on a null pointer!", true);
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

bool* FrameState::KeyboardState::getKeyRef(int keyCode) {

    /*
        Returns a pointer to the key boolean value within the instance variables
        This is reused in other instance functions
    */
    
    switch (keyCode) {

        // Letter keys
        case SDLK_a:
            return &( this->letterKeys[letterKeyIndex::a] );
            break;
        case SDLK_b:
            return &( this->letterKeys[letterKeyIndex::b] );
            break;
        case SDLK_c:
            return &( this->letterKeys[letterKeyIndex::c] );
            break;
        case SDLK_d:
            return &( this->letterKeys[letterKeyIndex::d] );
            break;
        case SDLK_e:
            return &( this->letterKeys[letterKeyIndex::e] );
            break;
        case SDLK_f:
            return &( this->letterKeys[letterKeyIndex::f] );
            break;
        case SDLK_g:
            return &( this->letterKeys[letterKeyIndex::g] );
            break;
        case SDLK_h:
            return &( this->letterKeys[letterKeyIndex::h] );
            break;
        case SDLK_i:
            return &( this->letterKeys[letterKeyIndex::i] );
            break;
        case SDLK_j:
            return &( this->letterKeys[letterKeyIndex::j] );
            break;
        case SDLK_k:
            return &( this->letterKeys[letterKeyIndex::k] );
            break;
        case SDLK_l:
            return &( this->letterKeys[letterKeyIndex::l] );
            break;
        case SDLK_m:
            return &( this->letterKeys[letterKeyIndex::m] );
            break;
        case SDLK_n:
            return &( this->letterKeys[letterKeyIndex::n] );
            break;
        case SDLK_o:
            return &( this->letterKeys[letterKeyIndex::o] );
            break;
        case SDLK_p:
            return &( this->letterKeys[letterKeyIndex::p] );
            break;
        case SDLK_q:
            return &( this->letterKeys[letterKeyIndex::q] );
            break;
        case SDLK_r:
            return &( this->letterKeys[letterKeyIndex::r] );
            break;
        case SDLK_s:
            return &( this->letterKeys[letterKeyIndex::s] );
            break;
        case SDLK_t:
            return &( this->letterKeys[letterKeyIndex::t] );
            break;
        case SDLK_u:
            return &( this->letterKeys[letterKeyIndex::u] );
            break;
        case SDLK_v:
            return &( this->letterKeys[letterKeyIndex::v] );
            break;
        case SDLK_w:
            return &( this->letterKeys[letterKeyIndex::w] );
            break;
        case SDLK_x:
            return &( this->letterKeys[letterKeyIndex::x] );
            break;
        case SDLK_y:
            return &( this->letterKeys[letterKeyIndex::y] );
            break;
        case SDLK_z:
            return &( this->letterKeys[letterKeyIndex::z] );
            break;

        // Number keys
        case SDLK_0:
            return &( this->numKeys[numKeyIndex::zero] );
            break;
        case SDLK_1:
            return &( this->numKeys[numKeyIndex::one] );
            break;
        case SDLK_2:
            return &( this->numKeys[numKeyIndex::two] );
            break;
        case SDLK_3:
            return &( this->numKeys[numKeyIndex::three] );
            break;
        case SDLK_4:
            return &( this->numKeys[numKeyIndex::four] );
            break;
        case SDLK_5:
            return &( this->numKeys[numKeyIndex::five] );
            break;
        case SDLK_6:
            return &( this->numKeys[numKeyIndex::six] );
            break;
        case SDLK_7:
            return &( this->numKeys[numKeyIndex::seven] );
            break;
        case SDLK_8:
            return &( this->numKeys[numKeyIndex::eight] );
            break;
        case SDLK_9:
            return &( this->numKeys[numKeyIndex::nine] );
            break;

        // Misc keys
        case SDLK_BACKSPACE:
            return &( this->miscKeys[miscKeyIndex::backspace] );
            break;
        case SDLK_TAB:
            return &( this->miscKeys[miscKeyIndex::tab] );
            break;
        case SDLK_RETURN:
            return &( this->miscKeys[miscKeyIndex::enter] );
            break;
        case SDLK_ESCAPE:
            return &( this->miscKeys[miscKeyIndex::escape] );
            break;
        case SDLK_SPACE:
            return &( this->miscKeys[miscKeyIndex::space] );
            break;
        case SDLK_CAPSLOCK:
            return &( this->miscKeys[miscKeyIndex::capslock] );
            break;
        case SDLK_LCTRL:
            return &( this->miscKeys[miscKeyIndex::control] );
            break;
        case SDLK_LSHIFT:
            return &( this->miscKeys[miscKeyIndex::shift] );
            break;
        case SDLK_LALT:
            return &( this->miscKeys[miscKeyIndex::alt] );
            break;

    }

    return nullptr;
}

void FrameState::KeyboardState::keyDown(int keyCode) {

    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = true;

    return;

}

void FrameState::KeyboardState::keyUp(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = false;

    return;

}

bool FrameState::KeyboardState::keyIsDown(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) return (*key) == true;
    else return false;

}



/*  ------------------------------------  */
/*  ----------   FrameState   ----------  */
/*  ------------------------------------  */

FrameState::// Contructor
FrameState(bool hasChild /* default value = true */) {

    this->frameCount = 0;
    this->mouse = new MouseState();
    this->keys = new KeyboardState();

    if (hasChild) this->lastFrame = new FrameState(false);
    else this->lastFrame = nullptr;

}

// Destructor
FrameState::~FrameState() {
    if (this->mouse != nullptr) delete this->mouse;
    if (this->keys != nullptr) delete this->keys;
    if (this->lastFrame != nullptr) delete this->lastFrame;
}

// Instance functions
void FrameState::addEvent(SDL_Event* event) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (event == nullptr) {
        logWrite("Called FrameState->addEvent(SDL_Event*) on a null pointer!", true);
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
        this->keys->keyDown((*event).key.keysym.sym);
    }

    // Keyboard buttons up
    if ((*event).type == SDL_KEYUP) {
        this->keys->keyUp((*event).key.keysym.sym);
    }

    return;
}

void FrameState::nextFrame() {

    if (this->lastFrame == nullptr) return;

    this->lastFrame->setState(this);
    this->frameCount++;

    return;

}

bool FrameState::wasLeftJustPressed() {
    return (this->mouse->leftButtonIsDown && !this->lastFrame->mouse->leftButtonIsDown);
}

bool FrameState::wasRightJustPressed() {
    return (this->mouse->rightButtonIsDown && !this->lastFrame->mouse->rightButtonIsDown);
}

bool FrameState::wasLeftJustReleased() {
    return (!this->mouse->leftButtonIsDown && this->lastFrame->mouse->leftButtonIsDown);
}

bool FrameState::wasRightJustReleased() {
    return (!this->mouse->rightButtonIsDown && this->lastFrame->mouse->rightButtonIsDown);
}

int FrameState::deltaMousePosX() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posX) - (this->lastFrame->mouse->posX);
}

int FrameState::deltaMousePosY() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posY) - (this->lastFrame->mouse->posY);
}

bool FrameState::keyIsDown(int keyCode) {
    return this->keys->keyIsDown(keyCode);
}

void FrameState::setState(FrameState* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called FrameState->setState(FrameState*) on a null pointer!", true);
        return;
    }

    this->frameCount = state->frameCount;
    this->mouse->setState(state->mouse);
    this->keys->setState(state->keys);
}

class Mesh {

    /*
        This is the class used to define and transform meshes, some default meshes are populted after a call to initMeshes()
        Contains transformation functions
        The reason there is a verticies list and a tri list is to simplify transformations and to use less memory
        The verticies list stores the actual points, and the tris list only point to values in the verticies list
        Same goes for the normals
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
        static Mesh* tetrahedronMesh;

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
        uint32 color;

        // Maps vecs from verticies and normals to tris
        IndexMap* indexMap;

        // Contains the position on the window which thier respective points from the Vec3 list should appear
        Vec2** projectedVerticies;

        // Same as 'tris' list. all the vecs witihin these triangles are the same ones from 'projectedVerticies' list.
        Tri2** projectedTris;


        // Constructor
        Mesh();

        // Destructor
        ~Mesh();


        /*   Instance Funtions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Mesh* copy();

        // Moves all the Vec3 objects within 'verticies' by the specified distance.
        Mesh* move(double dx, double dy, double dz);

        // Scales the mesh by a given factor on each axis. Simply applies these factors to each component of every Vec3 object.
        Mesh* scale(double fx, double fy, double fz);

        // Rotates all the Vec3 objects by the specified angles. just calls Vec3->rotate() for each Vec3.
        Mesh* rotate(double yaw, double pitch, double roll, Vec3* around = nullptr);

        // Sets the color of the mesh
        Mesh* setColor(uint32 color);

        // This uses the IndexMap to map the Tri3 vectors so that they point to Vec3 objects from the verticies and normals lists.
        // Also does the same thing for the projected versions of both.
        // Should be called when creating a custom mesh. This is done by default for the standard meshes.
        void mapTris();


        /*   Class functions   */

        // Initializes all the standard meshes. Such as cubeMesh for example.
        static void initMeshes();

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
    this->map[index].vertex1 = v1;
    this->map[index].vertex2 = v2;
    this->map[index].vertex3 = v3;
    this->map[index].normal = normal;
}

void Mesh::IndexMap::getGroup(int index, int* v1, int* v2, int* v3, int* normal) {
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
Mesh* Mesh::tetrahedronMesh = nullptr;

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
    newCopy->projectedVerticies = new Vec2*[this->vertexCount];
    newCopy->projectedTris = new Tri2*[this->triCount];

    // Fill lists
    for (int i = 0; i < this->vertexCount; i++)
        newCopy->verticies[i] = this->verticies[i]->copy();

    for (int i = 0; i < this->normalCount; i++)
        newCopy->normals[i] = this->normals[i]->copy();

    for (int i = 0; i < this->triCount; i++) {
        newCopy->tris[i] = new Tri3(true);
        newCopy->projectedTris[i] = new Tri2(true);
    }

    for (int i = 0; i < this->vertexCount; i++) 
        newCopy->projectedVerticies[i] = new Vec2();

    // Copy index map
    newCopy->indexMap = this->indexMap->copy();

    newCopy->mapTris();

    return newCopy;
}

Mesh* Mesh::move(double dx, double dy, double dz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->add(dx, dy, dz);
    }

    return this;

}

Mesh* Mesh::scale(double fx, double fy, double fz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->scale(fx, fy, fz);
    }

    return this;

}

Mesh* Mesh::rotate(double yaw, double pitch, double roll, Vec3* around /* default value = nullptr */) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (around == nullptr) {
        logWrite("Called Mesh->rotate(double, double, double, Vec3*) on a null pointer!", true);
        return nullptr;
    }

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->rotate(yaw, pitch, roll, around);
    }

    return this;

}

Mesh* Mesh::setColor(uint32 color) {
    this->color = color;
    return this;
}

void Mesh::mapTris() {

    int vertex1Index, vertex2Index, vertex3Index, normalIndex;

    for (int i = 0; i < this->indexMap->size; i++) {

        // Get values from map
        this->indexMap->getGroup(i, &vertex1Index, &vertex2Index, &vertex3Index, &normalIndex);

        // Set pointers for 3d tris
        this->tris[i]->v1 = this->verticies[vertex1Index];
        this->tris[i]->v2 = this->verticies[vertex2Index];
        this->tris[i]->v3 = this->verticies[vertex3Index];
        this->tris[i]->normal = this->verticies[normalIndex];

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
    Vec2** projectedVertexList;
    Tri2** projectedTriList;
    IndexMap* indexMap;

    /* ---  Cube Mesh  --- */

    // Create lists
    vertexList = new Vec3*[8];
    normalList = new Vec3*[6];
    triList = new Tri3*[12];
    projectedVertexList = new Vec2*[8];
    projectedTriList = new Tri2*[12];
    
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
    indexMap = new IndexMap(12);
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
    for (int i = 0; i < 12; i++)
        triList[i] = new Tri3(true);

    // allocate space for projection values
    for (int i = 0; i < 8; i++) 
        projectedVertexList[i] = new Vec2();
    for (int i = 0; i < 12; i++)
        projectedTriList[i] = new Tri2(true);

    // Store the created mesh in the class variable
    Mesh::cubeMesh = new Mesh();

    Mesh::cubeMesh->indexMap = indexMap;
    Mesh::cubeMesh->verticies = vertexList;
    Mesh::cubeMesh->normals = normalList;

    Mesh::cubeMesh->vertexCount = 8;
    Mesh::cubeMesh->normalCount = 6;
    Mesh::cubeMesh->triCount = 12;

    Mesh::cubeMesh->tris = triList;
    Mesh::cubeMesh->projectedVerticies = projectedVertexList;
    Mesh::cubeMesh->projectedTris = projectedTriList;

    // Populate tri lists with pointers
    Mesh::cubeMesh->mapTris();

}

class PNG {

    /*
        This class holds data to describe a PNG file.
        This class makes use of the library 'lodepng', which was NOT written by me.
    */

    public:

        // Indexes for color channels of each pixel in the buffer array returned by lodepng
        // I just used char becuase they dont need to be big, values are 0-3
        static const char RED, GREEN, BLUE, OPACITY;


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

// Color indexes. Used to parse the return data from lodepng
const char PNG::RED = 0;
const char PNG::GREEN = 1;
const char PNG::BLUE = 2;
const char PNG::OPACITY = 3;

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

        // Does the above step for each vertex in a mesh
        void toDisplayPos(Mesh* mesh);

};

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


        // This rotates the camera based on the input angles in DEGREES
        // Also updates the facing direction vector
        void rotate(double yaw, double pitch, double roll);

        // Takes a Vec3 object, and projects it into a Vec2 object.
        // The Vec2 components will be overwritten with the output of this function.
        // The values will be given in terms of fov (0 -> 1 is one fov length) so they dont mean anything for drawing until converted using a Display object
        void project(Vec3* vec, Vec2* displayPos);

        // Runs the function above for all the verticies in a mesh
        void project(Mesh* mesh);

    private:

        // Just used to ensure angles between 0-360
        void rolloverAngles();
        
};

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

void Camera::rotate(double yaw, double pitch, double roll) {

    // Update angles
    this->yaw += yaw;
    this->pitch += pitch;
    this->roll += roll;
    this->rolloverAngles();

    // Find new facing direction vector
    this->facingDirection->set(0, 0, 1);
    this->facingDirection->rotate(-this->yaw, -this->pitch, this->roll);
}

void Camera::project(Vec3* vec, Vec2* displayPos) {
    /*
        This returns a value between 0 and 1 which determines how far along each axis the given point should be drawn
        Can return values outside the 0-1 range, in this case the point lies off screen, but the location might still be needed
        These values are returned through the displayPos argument
    */

    // Address error cases, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec2*) with 'vec' being a null pointer!", true);
        return;
    }

    if (displayPos == nullptr) {
        logWrite("Called Camera->setAcceleration(Vec3*) with 'displayPos' being a null pointer!", true);
        return;
    }
    
    // Get points location relative to the cameras position and rotation
    Vec3* relative = vec->copy();
    relative->sub(this->pos);
    relative->rotate(this->yaw, 0, 0);
    relative->rotate(0, this->pitch, 0);

    // If the point is behind the camera
    if (relative->z < 0) {
        delete relative;
        displayPos->x = -1;
        displayPos->y = -1;
        return;
    }

    // Find the distance along the x,z axis, and the dy from the camera to the vec, this is used to find pitch
    Vec2* tempVar = new Vec2(relative->x, relative->z);
    double dist = tempVar->magnitude();
    double dy = relative->y - this->pos->y;
    delete tempVar;

    // Get the angle the point makes from the camera position on
    double angleYaw = getAngle(relative->x, relative->z);       // Angle from the +z axis
    double anglePitch = (double) 90 - getAngle(dist, dy);       // Angle from the +y axis, 90 - becuase its not against the axis used for getAngle

    // Gets the screen position given the angles found and the camera rotation angles
    /* ---  YAW  --- */

    double camYawFrom = -((double) this->fov->x / 2);
    double camYawTo = ((double) this->fov->x / 2);
    if (angleYaw > 180) {
        angleYaw -= 360;
    }

    double locationX = inRange(angleYaw, (double) -180, (double) 180);

    /* ---  PITCH  --- */
    double camPitchFrom = -(this->fov->y / 2);
    double camPitchTo = (this->fov->y / 2);
    if (anglePitch > 180) {
        anglePitch -= 360;
    }

    double locationY = inRange(anglePitch, (double) -180, (double) 180);

    // Value adjusting

    /*
        This code converts the range value between -180 and 180 into a value within the fov where values outside of 0-1 mean its outside the fov
        This is an extremely simplified version of the formula so it looks like nonsense but this is the math:
        First find the decimal value between -180 and 180 which represents the start of the fov
        value = (360 - k) / (2 * 360)
        Then use this value so find the new decimal for the posision
        pos = (360 * (oldpos - value)) / fov
        so this all simplifies to the math below, with a lot of type casting because I dont trust cpp auto typing
    */

    locationX = (((double) 180 * ((double) 2 * locationX - (double) 1)) / this->fov->x) + ((double) 0.5);
    locationY = (((double) 180 * ((double) 2 * locationY - (double) 1)) / this->fov->y) + ((double) 0.5);

    displayPos->x = locationX;
    displayPos->y = locationY;

    delete relative;

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

class Drawer {

    /*
        This class acts as a function set to draw to a gui window.
        A pixel buffer is the only SDL2 functionality I allowed myself to do, so this class implements all the drawing functions I need.
        The pixel buffer is simply a single dimension array, and the buffer width represents the length of each 'set' within the array.
        Treating the pixel buffer as a 2d array acts as follows:
        buffer[2][3] = buffer[(2 * bufferHeight) + 3], where 2,3 is x,y
    */

    public:
        
        // Instance variables
        Uint32* buffer;
        unsigned int bufferHeight, bufferWidth;
        unsigned int bufferSize;


        // Constructor
        Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput);


        /*   Instance functions   */

        // Writes a color to a coordinate within the buffer. Foundation for all further drawing functions.
        void writePixel(Uint32 pixel, int x, int y);

        // Draws a straight line from (x1, y1) to (x2, y2) in the given color
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2);

        // Same as above, but uses Vec2 objects. These objects are NOT deleted by this function call and must be handled properly
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to);

        // Draws a straight line along a given axis. Similar to drawLine, but less complex.
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y);

        // Draws a FILLED rectangle from (x1, y1) to (x2, y2)
        void drawRect(Uint32 pixel, int x1, int y1, int x2, int y2);

        // Fills whole buffer with a given color
        void fillScreen(Uint32 pixel);

        // Draws an elipse at a given location, with a given radius along each axis.
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy);

        // Same as above, but only one radius allowed.
        void drawCircle(Uint32 pixel, int locationx, int locationy, int radius);

        // Draws a FILLED triangle which uses (x1, y1), (x2, y2), and (x3, y3) as vertices
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3);

        // Same as above but uses a Tri2 object. This object is NOT deleted by this function call and must be handled properly
        void drawTriangle(Uint32 pixel, Tri2* tri);

        // Draws a PNG file using a PNG object. the top left corner of the PNG will lie at (x, y)
        void drawpng(PNG* file, int x, int y);

};

// Constructor
Drawer::Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput) {
    this->buffer = buffer;
    this->bufferWidth = bufferWidthInput;
    this->bufferHeight = bufferHeightInput;
    this->bufferSize = bufferHeightInput * bufferWidthInput;
}

// Instance functions
void Drawer::writePixel(Uint32 pixel, int x, int y) {

    if (this->buffer == nullptr) {
        return;
    }

    // Dont draw if it outside the buffer
    if (x >= this->bufferWidth || x < 0) return;
    if (y >= this->bufferHeight || y < 0) return;

    int index = (y * this->bufferWidth) + x;
    if (index > this->bufferSize) return;

    buffer[index] = pixel;

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

void Drawer::drawVerticalLine(Uint32 pixel, int startY, int endY, int x) {
    for (int i = startY; i <= endY; i++) {
        this->writePixel(pixel, x, i);
    }
}

void Drawer::drawHorizontalLine(Uint32 pixel, int startX, int endX, int y) {
    for (int i = startX; i <= endX; i++) {
        this->writePixel(pixel, i, y);
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

    // Sort the coordinates by thier x values from least to greatest (left to right)
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
    else slopeLeftMid = 1e250; // just a big number representing infinity

    // Slope between middle point and the right-most point
    if (x2 != x3) slopeMidRight = ((double) (y3 - y2)) / (double) (x3 - x2);
    else slopeMidRight = 1e250; // just a big number representing infinity

    // Slope between the left-most point and the right-most point
    if (x1 != x3) slopeLeftRight = ((double) (y3 - y1)) / (double) (x3 - x1);
    else slopeLeftRight = 1e250; // just a big number representing infinity

    // this checks if all the points have the same x coordinate and draws a single line accordingly
    // Since the points are sorted, if the lowest (left) and highest (right) have the same x, so does the middle
    if (slopeLeftRight == 1e250) {
        startY = min(min(y1, y2), y3);
        endY = max(max(y1, y2), y3);
        this->drawVerticalLine(pixel, startY, endY, x1);
        return;
    }

    // From left to right until the mid vertex is hit
    if (slopeLeftMid != 1e250) {
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
    if (slopeMidRight != 1e250) {
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

void Drawer::drawTriangle(Uint32 pixel, Tri2* tri) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (tri == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) on a null pointer!", true);
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
    int windowWidthTemp = this->windowWidth;
    SDL_LockTexture(this->texture, nullptr, (void**) &(this->buffer), &windowWidthTemp);
}

void Gui::flip() {
    int windowWidthTemp = this->windowWidth;
    SDL_UnlockTexture(this->texture);
    SDL_UpdateTexture(this->texture, nullptr, this->buffer, windowWidthTemp * sizeof(Uint32));
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, nullptr, nullptr);
    SDL_RenderPresent(this->renderer);
}

void drawMesh(Mesh* mesh, Drawer* drawer, Camera* camera, Display* display) {

    // Because of how this function is called from drawGraphics, none of these should ever be null but it doesnt really hurt to check

    // Address error cases, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'frameState' as a null pointer!", true);
        return;
    }

    if (drawer == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Draw Tris
    for (int i = 0; i < mesh->triCount; i++) {
        if (!mesh->tris[i]->isFacing(camera->facingDirection)) continue;
        drawer->drawTriangle(Color::WHITE, mesh->projectedTris[i]);
    }

    Vec2* vecStart = new Vec2(); 
    Vec2* vecEnd = new Vec2();

    // Draw Normals
    for (int i = 0; i < mesh->triCount; i++) {

        // Pass if tri isnt facing cam
        if (!mesh->tris[i]->isFacing(camera->facingDirection)) continue;

        // Get projected coords for normal start and end
        Vec3* triCenter = mesh->tris[i]->getCenter();
        Vec3* normalOffset = mesh->tris[i]->normal->copy()->normalise();
        Vec3* triNormal = triCenter->add(normalOffset);

        logWrite("here", true);

        camera->project(triCenter, vecStart);
        camera->project(triNormal, vecEnd);
        display->toDisplayPos(vecStart);
        display->toDisplayPos(vecEnd);

        logWrite(vecStart->x);
        logWrite(", ");
        logWrite(vecStart->y, true);
        logWrite(vecEnd->x);
        logWrite(", ");
        logWrite(vecEnd->y, true);
        logNewLine();

        drawer->drawLine(Color::RED, vecStart, vecEnd);

        delete triCenter; delete normalOffset; delete triNormal;

    }

    delete vecStart; delete vecEnd;

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
    if (height < 0) return;

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

    return;

}

// Static variables for objects to draw, reimplement later
Vec3* points[8];
Mesh* cube1;
Mesh* cube2;

void initGraphics() {

    // Init points to draw
    for (int i = 0; i < 8; i++) {

        // These values will count in binary
        int x = i % 2;
        int y = (int) (i % 4) >= 2;
        int z = (int) i >= 4;

        points[i] = new Vec3(5 * x, 5 * y, 5 * z);

    }

    // Init cube mesh then move it away and make it bigger
    cube1 = Mesh::cubeMesh->copy()->scale(15, 15, 15)->move(0, 0, 10);
    //cube2 = Mesh::cubeMesh->copy()->scale(5, 5, 5)->move(0, 10, 0)->rotate(0, 10, 0);

}

void drawGraphics(Drawer* drawer, FrameState* frameState, Camera* camera, Display* display) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (drawer == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (frameState == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'frameState' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    drawSky(drawer, camera, display);

    camera->project(cube1);
    // camera->project(cube2);
    display->toDisplayPos(cube1);
    // display->toDisplayPos(cube2);

    drawMesh(cube1, drawer, camera, display);
    // drawMesh(cube2, drawer, camera, display);

    // Vec3* camFacingVec = camera->facingDirection->copy()->scale(50);
    // Vec3* camFacingVecStart = new Vec3(0, 0, 0);
    // Vec2* projectedCamFacingVec = new Vec2();
    // Vec2* projectedCamFacingVecStart = new Vec2();
    // camera->project(camFacingVec, projectedCamFacingVec);
    // camera->project(camFacingVecStart, projectedCamFacingVecStart);
    // display->toDisplayPos(projectedCamFacingVec);
    // display->toDisplayPos(projectedCamFacingVecStart);

    // drawer->drawLine(Color::RED, projectedCamFacingVecStart, projectedCamFacingVec);

    // delete camFacingVec, camFacingVecStart;
    // delete projectedCamFacingVec, projectedCamFacingVecStart;

    return;

}

Gui* gui = nullptr;

void handleInput(FrameState* frameState, Camera* camera, double dt) {

    /*
        ---  Directional Movement  ---

        The camera movement depends on facing direction for x,z movement (using WASD), while the up and down movement do not change based on facing direction
        First a value 'dist' is found which determines how far the camera should move based on the dt (delta time)
        Then the up and down movement are simple because the camera y position is just added or subtracted by the dist amount
        The x,z movement is a bit more complicated because it uses a 2d vector to hold the actual movement where the x and y components hold the left-right and front-back
        then rotates it based on the camera yaw and adds that to position.
    */

    // Distance to move
    if (frameState->keyIsDown(SDLK_LSHIFT)) camera->movementSpeed = 10;
    else camera->movementSpeed = 3;
    double dist = ((double) camera->movementSpeed) * (dt / 1000);

    if (frameState->keyIsDown(SDLK_SPACE)) camera->pos->y += dist; // Up
    if (frameState->keyIsDown(SDLK_LCTRL)) camera->pos->y -= dist; // Down
    
    Vec2* cameraMovVec = new Vec2();
    if (frameState->keyIsDown(SDLK_w)) cameraMovVec->y += dist; // Forward
    if (frameState->keyIsDown(SDLK_s)) cameraMovVec->y -= dist; // Backward
    if (frameState->keyIsDown(SDLK_a)) cameraMovVec->x -= dist; // Left
    if (frameState->keyIsDown(SDLK_d)) cameraMovVec->x += dist; // Right

    // Move camera based on its rotation
    cameraMovVec->rotate(-camera->yaw);
    camera->pos->x += cameraMovVec->x;
    camera->pos->z += cameraMovVec->y;
    delete cameraMovVec;

    /*  ---  Camera Rotation  ---  */
    if (frameState->mouse->leftButtonIsDown) {

        // 0.2 is just a random number I chose becuase it felt good in the app
        double mouseSensitivity = 0.2;
        double camDeltaYaw = (double) frameState->deltaMousePosX();
        double camDeltaPitch = (double) frameState->deltaMousePosY();
        camera->rotate( camDeltaYaw * mouseSensitivity, -camDeltaPitch * mouseSensitivity, 0 );

    }

}

int main(int argc, char* argv[]) {

    // Start the gui window
    gui = new Gui(1000, 600);
    gui->init();

    // Log stuff
    logInit("log.txt");
    logClear();
    logWrite("Starting...", true);

    // Sets up the objects to be drawn and the camera
    Mesh::initMeshes();
    initGraphics();

    FrameState* frameState = new FrameState();
    Drawer* drawer;
    SDL_Event event;
    int mouseX, mouseY;

    // Init main camera and the associated display
    Display* display1 = new Display(gui->windowWidth, gui->windowHeight);
    Camera* camera1 = new Camera();
    camera1->setPos(0, 0, -10);
    camera1->setFov(90, 54);
    camera1->setLightingVec(1, -5, 2); // downfacing off axis lighting

    // Time stuff
    auto timeVar = std::chrono::high_resolution_clock::now();
    double appStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
    double lastFrameTime = appStartTime;
    double thisFrameTime = appStartTime;
    double dt;

    std::cout << "display size: " << "(" << display1->width << ", " << display1->height << ")" << std::endl;



    // return 0;

    // Main event loop
    bool leave = false;
    while (!leave) {

        // Logging
        logWrite("Frame ", false);
        logWrite(frameState->frameCount, true);

        // Delta time
        timeVar = std::chrono::high_resolution_clock::now();
        lastFrameTime = thisFrameTime;
        thisFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
        dt = thisFrameTime - lastFrameTime;

        // Mouse position
        SDL_GetMouseState(&mouseX, &mouseY);
        frameState->mouse->setPos(mouseX, mouseY);
        // std::cout << "(" << frameState->mouse->posX << ", " << frameState->mouse->posY << ")" << std::endl;
        
        // Handle SDL events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) { leave = true; std::cout<<"closed"; }
            else frameState->addEvent(&event);
        }

        // Does all the user input handling
        handleInput(frameState, camera1, dt);
        gui->getBuffer();

        drawer = new Drawer(gui->buffer, gui->windowWidth, gui->windowHeight);
        drawer->fillScreen(Color::BLACK);
        drawGraphics(drawer, frameState, camera1, display1); // from graphics.cpp
        gui->flip();
        delete drawer;

        std::cout << "(" << camera1->yaw << ", " << camera1->pitch << ")";
        //std::cout << " - (" << camera1->pos->x << ", " << camera1->pos->y << ", " << camera1->pos->z << ")" << std::endl;
        std::cout << " - (" << camera1->facingDirection->x << ", " << camera1->facingDirection->y << ", " << camera1->facingDirection->z << ")" << std::endl;

        // Make current frameState become last frame
        frameState->nextFrame();
    }

    delete frameState;
    delete camera1;
    delete display1;

    // Destroy the window and quit SDL
    gui->exit();

    return 0;

}