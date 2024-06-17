#pragma once

#ifndef pi
#define pi 3.14159265358979323846
#endif

#include <cmath>

// Absolute value
inline int myabs(int num);
inline double myabs(double num);

// Returns a value 0-1 for how far between 'from' and 'to' the value is. Returns -1 if its outside the range.
double inRange(double num, double from, double to);

// Same as above, but allows values outside the range, in which case it would return values outside 0-1
double outRange(double num, double from, double to);

// Convert degrees and radians
inline double toRadians(double degrees);
inline double toDegrees(double radians);

// Returns the higher value
inline int max(int var1, int var2);
inline double max(double var1, double var2);

// Returns the lower value
inline int min(int var1, int var2);
inline double min(double var1, double var2);

// Swaps the values in two memory locations.
void swap(int* var1, int* var2);

// Arctan. this is an approximation, but its generally close enough.
double quickArctan(double x);

// Returns the angle between two points in DEGREES.
// This angle is from a vertical line on (x1, y1) to (x2, y2)
// For example if (x2, y2) is directly right of (x1, y1) this returns 90. 
double getAngle(double x1, double y1, double x2, double y2);
