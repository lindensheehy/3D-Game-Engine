#include "util/Utility.h"


/*   -----   Color Functions   -----   */
uint32 Color::setBrightness(uint32 color, float newBrightness) {

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

uint32 Color::merge(uint32 color1, float opacity1, uint32 color2, float opacity2) {

    // Unpack color codes
    uint8 redValue1 = (uint8) (color1 >> 16);
    uint8 greenValue1 = (uint8) (color1 >> 8);
    uint8 blueValue1 = (uint8) (color1);

    uint8 redValue2 = (uint8) (color2 >> 16);
    uint8 greenValue2 = (uint8) (color2 >> 8);
    uint8 blueValue2 = (uint8) (color2);

    // Downscale values accordingly, ignoring opacityValue
    redValue1 *= opacity1;
    greenValue1 *= opacity1;
    blueValue1 *= opacity1;

    redValue2 *= opacity2;
    greenValue2 *= opacity2;
    blueValue2 *= opacity2;

    // Get resulting color codes, using the first set to store this to avoid unnecessary variables
    redValue1 += redValue2;
    greenValue1 += greenValue2;
    blueValue1 += blueValue2;

    // Pack resulting color code
    uint32 newColor = 0x0000FF00; // This FF will become the opacity value after the bit shifts
    newColor |= redValue1;
    newColor <<= 8;
    newColor |= greenValue1;
    newColor <<= 8;
    newColor |= blueValue1;

    return newColor;

}


/*   -----   Swap Variants   -----   */
void swap(int* var1, int* var2) {
    /*
        Just swaps the values in var1 and var2 using pointers to those values
    */

    int temp = *var1;
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

void swap(float* var1, float* var2) {
    /*
        Just swaps the values in var1 and var2 using pointers to those values
    */

    float temp = *var1;
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


/*   -----   Casting With char*   -----   */
bool floatToString(float value, char* string, int MAXLENGTH, int MAXDECIMALDIGITS) {
    return doubleToString((double) value, string, MAXLENGTH, MAXDECIMALDIGITS);
}

bool stringToFloat(char* string, float* result, int MAXLENGTH) {

    if (result == nullptr) return false;

    double doubleResult;

    bool passed = stringToDouble(string, &doubleResult, MAXLENGTH);

    *result = (float) doubleResult;

    return passed; 

}

bool doubleToString(double value, char* string, int MAXLENGTH, int MAXDECIMALDIGITS) {

    if (string == nullptr) return false;

    // Not enough space in the string for a number and '\0'
    if (MAXLENGTH < 2) return false;

    // Using intToString to handle the integer portion of the double
    int intPart = (int) abs(value);
    bool intPartSucceded;

    // Add a negative sign if needed
    if (value < 0) {
        string[0] = '-';
        intPartSucceded = intToString(intPart, &(string[1]), MAXLENGTH - 1);
    }

    else {
        intPartSucceded = intToString(intPart, string, MAXLENGTH);
    }

    if (!intPartSucceded) return false;
    
    // Find index where intToString left off
    int index = 0;
    while (string[index] != '\0') index++;

    // Handle decimal part if necessary
    if (MAXDECIMALDIGITS > 0) {

        //
        if (index >= MAXLENGTH - 1) return false;
        string[index] = '.';
        index++;

        double absValue = (value < 0) ? -value : value;
        double absIntPart = (intPart < 0) ? -intPart : intPart;
        
        double decimalPart = absValue - absIntPart;
        int decimalDigit;

        // Add all the requested decimal digits
        for (int i = 0; i < MAXDECIMALDIGITS; ++i) {

            decimalPart *= 10;
            decimalDigit = (int) decimalPart;
            decimalPart -= decimalDigit;

            if (index >= MAXLENGTH - 1) return false;

            string[index++] = '0' + decimalDigit;

        }

    }

    // Null-terminate the string
    if (index >= MAXLENGTH) return false;
    string[index] = '\0';

    return true;

}

bool stringToDouble(char* string, double* result, int MAXLENGTH) {

    if (string == nullptr) return false;
    if (result == nullptr) return false;

    double returnValue = 0.0;
    int i = 0;
    char c;
    int holder; // Holds the int equivalent of the current char being parsed. ex. '1' -> 1
    bool negative = false;
    double decimalPlace = 0.1;

    // Check for negative
    if (string[i] == '-') {
        negative = true;
        i++;
    }

    while (i < MAXLENGTH) {

        c = string[i];

        // Break cases

        // Done
        if (c == '\0') goto end;

        // Leave this loop to do the loop for the decimal part
        if (c == '.') break;

        // Invalid char
        if (c < '0' || c > '9') return false;

        holder = c - '0';
        returnValue = (returnValue * 10) + holder;

        i++;

    }

    i++; // Skip the decimal where the index currently is

    while (i < MAXLENGTH) {

        c = string[i];

        // Break Cases

        // Done
        if (c == '\0') goto end;

        // Invalid char
        if (c < '0' || c > '9') return false;

        holder = c - '0';
        returnValue += decimalPlace * holder;

        decimalPlace /= 10;
        i++;

    }

    end:
        *result = (negative) ? -returnValue : returnValue;

        return true;

}

bool intToString(int value, char* string, int MAXLENGTH) {

    // Not enough space in the string
    if (MAXLENGTH < 2) return false;

    if (value == 0) {
        string[0] = '0';
        string[1] = '\0';
        return true;
    }

    // Determine the sign and get the absolute value
    bool isNegative = value < 0;
    int absValue = isNegative ? -value : value;

    // Calculate the number of digits
    int numDigits = 0;
    int tempValue = absValue;
    while (tempValue > 0) {
        tempValue /= 10;
        numDigits++;
    }

    // If the number is negative, we need one extra space for the '-' sign
    int strLength = numDigits + (isNegative ? 1 : 0);
    
    // Return false if theres not enough room in the string for the value (+1 for '\0')
    if (strLength + 1 > MAXLENGTH) return false;

    // Fill the string with characters

    string[strLength] = '\0'; // Null-terminate the string

    for (int i = strLength - 1; i >= 0; i--) {
        string[i] = (absValue % 10) + '0'; // Convert digit to character
        absValue /= 10;
    }

    // If the number is negative, add the '-' sign
    if (isNegative) {
        string[0] = '-';
    }

    return true;

}

bool stringToInt(char* string, int* result, int MAXLENGTH) {

    if (string == nullptr) return false;
    if (result == nullptr) return false;

    int returnValue = 0;
    int i = 0;
    char c;
    int holder; // Holds the int equivalent of the current char being parsed. ex. '1' -> 1
    bool negative = false;

    // Check for negative
    if (string[i] == '-') {
        negative = true;
        i++;
    }

    while (i < MAXLENGTH) {

        c = string[i];

        // Break cases

        // Done
        if (c == '\0') break;

        // Invalid char
        if (c < '0' || c > '9') return false;

        holder = c - '0';
        returnValue = (returnValue * 10) + holder;

        i++;

    }

    *result = (negative) ? -returnValue : returnValue;
        
    return true;

}

bool stringHexToInt(char* string, int* result, int MAXLENGTH) {

    if (string == nullptr) return false;
    if (result == nullptr) return false;

    int returnValue = 0;
    int i = 0;
    char c;
    int holder;

    // Check for optional "0x" or "0X" prefix
    if (string[i] == '0' && (string[i + 1] == 'x' || string[i + 1] == 'X')) {
        i += 2;
    }

    while (i < MAXLENGTH) {

        c = string[i];

        // Done
        if (c == '\0') break;

        // Convert hex character to integer
        if (c >= '0' && c <= '9') {
            holder = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            holder = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            holder = c - 'a' + 10;
        } else {
            return false; // Invalid character for hex
        }

        returnValue = (returnValue * 16) + holder;
        i++;

    }

    *result = returnValue;

    return true;
    
}
