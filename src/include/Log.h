#pragma once

// Basic Includes
#include <iostream>
#include <fstream>

// Pretty much a std::cout function
void consoleOut(std::string message) {
    
}

// Init
void logInit(std::string fileName);

// Primative Functions
void logClear();
void logNewLine();

// Strings and chars
void logWrite(std::string message, bool newLine = false);
void logWrite(char message, bool newLine = false);
void logWrite(wchar_t message, bool newLine = false);

// Decimal Values
void logWrite(int message, bool newLine = false);
void logWrite(long message, bool newLine = false);
void logWrite(long long message, bool newLine = false);
void logWrite(double message, bool newLine = false);

// Hex values
// void logWriteHex(int8bytes message, bool newLine = false);
// void logWriteHex(int2bytes message, bool newLine = false);
// void logWriteHex(int4bytes message, bool newLine = false);
// void logWriteHex(int1byte message, bool newLine = false);

// Variable Format
void logVar(std::string message, int variable);
void logVar(std::string message, double variable);
