#pragma once

/*
    This just contains code that should be accessible and included across all other files
*/

#include <windows.h>

#include "util/Math.h"


typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;


// This is the default size of any pixel mapped buffer
// This is intended to be big enough that resizing will never require reallocations
static constexpr int PIXEL_BUFFER_WIDTH = 1920;
static constexpr int PIXEL_BUFFER_HEIGHT = 1080;



// Swaps the values in two memory locations.
void swap(int* var1, int* var2);
void swap(unsigned int* var1, unsigned int* var2);
void swap(float* var1, float* var2);
void swap(double* var1, double* var2);



/*   Casting functions for char* types   */

// Writes the given float value to the char* given. Will not write past MAXLENGTH. Returns true if the whole int was parsed
bool floatToString(float value, char* string, int MAXLENGTH, int MAXDECIMALDIGITS = 2);

// Returns a float value representing the contents of the string. Will read until '\0' or MAXLENGTH. invalid strings will return 0
bool stringToFloat(char* string, float* result, int MAXLENGTH);

// Writes the given double value to the char* given. Will not write past MAXLENGTH. Returns true if the whole int was parsed
bool doubleToString(double value, char* string, int MAXLENGTH, int MAXDECIMALDIGITS = 2);

// Returns a double value representing the contents of the string. Will read until '\0' or MAXLENGTH. invalid strings will return 0
bool stringToDouble(char* string, double* result, int MAXLENGTH);

// Writes the given int value to the char* given. Will not write past MAXLENGTH. Returns true if the whole int was parsed
bool intToString(int value, char* string, int MAXLENGTH);

// Returns the int interpretation of the string into result. Will read until '\0' or MAXLENGTH. Invalid strings will return false
bool stringToInt(char* string, int* result, int MAXLENGTH);

// Returns the int interpretation of the string (treated as hex) into result. Will read until '\0' or MAXLENGTH. Invalid strings will return false
// Both strings starting with "0x" and with no prefix are valid
bool stringHexToInt(char* string, int* result, int MAXLENGTH);



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
