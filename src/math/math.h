#pragma once

#ifndef pi
#define pi 3.14159265358979323846
#endif

// For degree conversion
const double degToRadFactor = pi / 180;


// Returns a value 0-1 for how far between 'from' and 'to' the value is. Returns -1 if its outside the range.
double inRange(double num, double from, double to);

// Same as above, but allows values outside the range, in which case it would return values outside 0-1
double outRange(double num, double from, double to);

// Swaps the values in two memory locations.
void swap(int* var1, int* var2);

// Arctan. this is an approximation, but its generally close enough.
double quickArctan(double x);

// Returns the angle between two points in DEGREES.
// This angle is from a vertical line on (x1, y1) to (x2, y2)
// For example if (x2, y2) is directly right of (x1, y1) this returns 90. 
// The second position is set to (0, 0) by default.
double getAngle(double x1, double y1, double x2 = 0, double y2 = 0);


/*   Inline Functions   */

// Absolute value (int)
inline int abs(int num) {
    return ( num < 0 ? -num : num);
}

// Absolute value (double)
inline double abs(double num) {
    return ( num < 0 ? -num : num);
}

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
