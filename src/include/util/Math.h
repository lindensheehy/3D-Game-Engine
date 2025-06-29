#pragma once

#include "util/Utility.h"
#include "util/Log.h"


const float pi = 3.14159265358979323846;
const float inf = 1e34;
const float degToRadFactor = pi / 180;



// Returns a value within the given tolerance from the actual square root of x
float sqrt(float x, float tolerance = 0.00001);
double sqrt(double x, double tolerance = 0.00001);



/*   --------------------------   */
/*   ---   Trig Functions   ---   */
/*   --------------------------   */

// Sine function. Uses radians
float sin(float x);
double sin(double x);

// Cosine function. Uses radians
float cos(float x);
double cos(double x);

// Tangent function. Uses radians
float tan(float x);
double tan(double x);

// Reverse sine function. Uses radians
float arcsin(float x);
double arcsin(double x);

// Reverse cosine function. Uses radians
float arccos(float x);
double arccos(double x);

// Reverse tangent function. Uses radians
float arctan(float x);
double arctan(double x);



/*   ---------------------------   */
/*   ---   Other Functions   ---   */
/*   ---------------------------   */

// Returns the distance between 2 sets of 2 dimensional coordinates
float distance2(float x1, float y1, float x2 = 0, float y2 = 0);

// Returns the distance between 2 sets of 3 dimensional coordinates
float distance3(float x1, float y1, float z1, float x2 = 0, float y2 = 0, float z2 = 0);

// Returns a value 0-1 for how far between 'from' and 'to' the value is. Returns -1 if its outside the range.
float normalize(float num, float from, float to);

// Same as above, but allows values outside the range, in which case it will return values outside 0-1
float inRange(float num, float from, float to);

// Returns the angle between two points in DEGREES.
// This angle is from a vertical line on (x1, y1) to (x2, y2)
// For example if (x2, y2) is directly right of (x1, y1) this returns 90. 
// The second position is set to (0, 0) by default.
float getAngle(float x1, float y1, float x2 = 0, float y2 = 0);

// Normalizes the angle to a 0-360 range. Adds and subtracts by 360 to achieve this
// Angle is an out parameter, this function works directly on the given value
void rolloverAngle(float* angle);



/*   ----------------------------   */
/*   ---   Inline Functions   ---   */
/*   ----------------------------   */

// Angle conversion. Degrees -> Radians
inline float toRadians(float degrees) { return degrees * degToRadFactor; }

// Angle conversion. Radians -> Degrees
inline float toDegrees(float radians) { return radians / degToRadFactor; }
