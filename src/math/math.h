#ifndef math
#define math

#ifndef pi
#define pi 3.14159265358979323846
#endif

#include <cmath>

const double degToRadFactor = pi / 180;

inline int myabs(int num);
inline double myabs(double num);
double inRange(double num, double from, double to);
double outRange(double num, double from, double to);
inline double toRadians(double degrees);
inline double toDegrees(double radians);
inline int max(int var1, int var2);
inline double max(double var1, double var2);
inline int min(int var1, int var2);
inline double min(double var1, double var2);
void swap(int* var1, int* var2);
double quickArctan(double x);
double getAngle(double x1, double y1, double x2 = 0, double y2 = 0);

#endif