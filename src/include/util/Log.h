#pragma once

#include <windows.h>

#include "util/Utility.h"


// Control functions
void logInit(const char* fileName);
void logInit(char* fileName);
void logClose();

// Clears all characters from the output file
void logClear();

// Strings and chars
void logWrite(const char* message, bool newLine = false);
void logWrite(char* message, bool newLine = false);

void logWrite(char message, bool newLine = false);
void logWrite(wchar_t message, bool newLine = false);

// Decimal Values`
void logWrite(int message, bool newLine = false);
void logWrite(long message, bool newLine = false);
void logWrite(long long message, bool newLine = false);
void logWrite(float message, bool newLine = false);
void logWrite(double message, bool newLine = false);

// Hex values
void logWriteHex(char message, bool newLine = false);
void logWriteHex(short message, bool newLine = false);
void logWriteHex(int message, bool newLine = false);
void logWriteHex(long long message, bool newLine = false);

// New line
void logNewLine();

// Variable Format (prints "message: variable value")
void logVar(const char* message, int variable);
void logVar(const char* message, double variable);
