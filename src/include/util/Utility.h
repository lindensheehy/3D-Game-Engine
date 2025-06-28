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


// Returns the length of the string INCLUDING the null terminator byte (0x00)
int stringLength(const char* str);


// A small Color namespace for general use
namespace Color {

    // Constant color codes
    // Bytes are [opacity][red][green][blue]
    constexpr uint32 RED         = 0xFFFF0000;
    constexpr uint32 GREEN       = 0xFF00FF00;
    constexpr uint32 BLUE        = 0xFF0000FF;
    constexpr uint32 BLACK       = 0xFF000000;
    constexpr uint32 WHITE       = 0xFFFFFFFF;
    constexpr uint32 GREY        = 0xFF888888;
    constexpr uint32 DARKGREY    = 0xFF333333;

    // For UI drawing
    constexpr uint32 BACKGROUND  = 0xFF303030;
    constexpr uint32 LIGHTER     = 0xFF505050;
    constexpr uint32 DARKER      = 0xFF181818;
    constexpr uint32 ACCENT      = 0xFFA78BFA;


    // Sets the brightness of a given color (uint32) to a float between 0-1.
    // Values higher than 1 CAN be used, but could cause overflow issues.
    uint32 setBrightness(uint32 color, float newBrightness);

    // Merges the rgb values of two colors based on opacity values. The sum of opacity1 and opacity2 should be 1
    uint32 merge(uint32 color1, float opacity1, uint32 color2, float opacity2);

}



// Swaps the values in two memory locations.
void swap(int* var1, int* var2);
void swap(unsigned int* var1, unsigned int* var2);
void swap(float* var1, float* var2);
void swap(double* var1, double* var2);



/*   Casting functions for char* types   */

// Writes the given float value to the char* given. Will not write past MAXLENGTH. Returns true if the whole int was parsed
bool floatToString(float value, char* string, int MAXLENGTH, int MAXDECIMALDIGITS = 2);

// Returns a float value representing the contents of the string. Will read until '\0' or MAXLENGTH. invalid strings will return 0
bool stringToFloat(const char* string, float* result, int MAXLENGTH);

// Writes the given double value to the char* given. Will not write past MAXLENGTH. Returns true if the whole int was parsed
bool doubleToString(double value, char* string, int MAXLENGTH, int MAXDECIMALDIGITS = 2);

// Returns a double value representing the contents of the string. Will read until '\0' or MAXLENGTH. invalid strings will return 0
bool stringToDouble(const char* string, double* result, int MAXLENGTH);

// Writes the given int value to the char* given. Will not write past MAXLENGTH. Returns true if the whole int was parsed
bool intToString(int value, char* string, int MAXLENGTH);

// Returns the int interpretation of the string into result. Will read until '\0' or MAXLENGTH. Invalid strings will return false
bool stringToInt(const char* string, int* result, int MAXLENGTH);

// Returns the int interpretation of the string (treated as hex) into result. Will read until '\0' or MAXLENGTH. Invalid strings will return false
// Both strings starting with "0x" and with no prefix are valid
bool stringHexToInt(const char* string, int* result, int MAXLENGTH);



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
