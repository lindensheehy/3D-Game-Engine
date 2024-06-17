#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdint.h>

typedef uint8_t int1byte;
typedef uint16_t int2bytes;
typedef uint32_t int4bytes;
typedef uint64_t int8bytes;

// Init
void logInit(std::string fileName);

// Primative Functions
void logClear();
void logNewLine();

// Strings and chars
void logWrite(std::string message, bool newLine);
void logWrite(char message, bool newLine);
void logWrite(wchar_t message, bool newLine);

// Decimal Values
void logWrite(int message, bool newLine);
void logWrite(long message, bool newLine);
void logWrite(long long message, bool newLine);
void logWrite(double message, bool newLine);

// Hex values
void logWrite(int8bytes message, bool newLine);
void logWrite(int2bytes message, bool newLine);
void logWrite(int4bytes message, bool newLine);
void logWrite(int1byte message, bool newLine);

// Variable Format
void logVar(std::string message, int variable);
void logVar(std::string message, double variable);
