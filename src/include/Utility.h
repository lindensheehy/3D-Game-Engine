#pragma once

/*
    This just contains code that should be accessible and included across all other files
*/

#include <windows.h>

#include "Math.h"


typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;



// Swaps the values in two memory locations.
void swap(int* var1, int* var2);
void swap(double* var1, double* var2);
void swap(unsigned int* var1, unsigned int* var2);



/*   Casting functions for char* types   */

// Writes the given double value to the char* given. Will not write past MAXLENGTH
bool doubleToString(double value, char* string, int MAXLENGTH, int MAXDECIMALDIGITS = 2);

// Returns a double value representing the contents of the string. Will read until '\0' or MAXLENGTH. invalid strings will return 0
double stringToDouble(char* string, int MAXLENGTH);

// Writes the given int value to the char* given. Will not write past MAXLENGTH. Returns true if the whole int was parsed
bool intToString(int value, char* string, int MAXLENGTH);

// Returns a int value representing the contents of the string. Will read until '\0' or MAXLENGTH. invalid strings will return 0
int stringToInt(char* string, int MAXLENGTH);



// Returns the greater value
inline int max(int var1, int var2) {
    return (var1 > var2) ? var1 : var2;
}

inline double max(double var1, double var2) {
    return (var1 > var2) ? var1 : var2;
}

inline unsigned int max(unsigned int var1, unsigned int var2) {
    return (var1 > var2) ? var1 : var2;
}



// Returns the lesser value
inline int min(int var1, int var2) {
    return (var1 < var2) ? var1 : var2;
}

inline double min(double var1, double var2) {
    return (var1 < var2) ? var1 : var2;
}

inline unsigned int min(unsigned int var1, unsigned int var2) {
    return (var1 < var2) ? var1 : var2;
}
