#include "util/Utility.h"


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

float stringToFloat(char* string, int MAXLENGTH) {
    return (float) stringToDouble(string, MAXLENGTH);
}

bool doubleToString(double value, char* string, int MAXLENGTH, int MAXDECIMALDIGITS) {

    // Not enough space in the string for a number and '\0'
    if (MAXLENGTH < 2) return false;
    
    // Use intToString to handle the integer portion of the double
    int intPart = (int) value;
    bool intPartComplete = intToString(intPart, string, MAXLENGTH);
    if (!intPartComplete) return false;
    
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

double stringToDouble(char* string, int MAXLENGTH) {

    if (string == nullptr) return 0;

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
        if (c < '0' || c > '9') return 0;

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
        if (c < '0' || c > '9') return 0;

        holder = c - '0';
        returnValue += decimalPlace * holder;

        decimalPlace /= 10;
        i++;

    }

    end:
        return (negative) ? -returnValue : returnValue;

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

int stringToInt(char* string, int MAXLENGTH) {

    if (string == nullptr) return 0;

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
        if (c == '\0') goto end;

        // Invalid char
        if (c < '0' || c > '9') return 0;

        holder = c - '0';
        returnValue = (returnValue * 10) + holder;

        i++;

    }

    end:
        return (negative) ? -returnValue : returnValue;

}
