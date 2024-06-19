#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdint.h>

#include "log.h"

typedef uint8_t int1byte;
typedef uint16_t int2bytes;
typedef uint32_t int4bytes;
typedef uint64_t int8bytes;

std::ofstream outputFile;

// Init
void logInit(std::string fileName) {
    try {
        outputFile.open(fileName);
    } catch (...) {
        std::cout << "Couldnt open log.txt" << std::endl;
        system("pause");
        return;
    }
}

// Primative Functions
void logClear() {
    if (!outputFile.is_open()) {
        std::cout << "logInit must be called first" << std::endl;
        system("pause");
        return;
    }
    outputFile.clear();
}

void logNewLine() {

    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        std::cout << "logInit must be called first" << std::endl;
        system("pause");
        return;
    }

    outputFile << "\n";
}

// Strings and chars
void logWrite(std::string message, bool newLine /* default value = false */) {

    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        std::cout << "logInit must be called first" << std::endl;
        system("pause");
        return;
    }

    // Write message to file
    outputFile << message;

    // End line
    if (newLine) outputFile << std::endl;

    return;
}

void logWrite(char message, bool newLine /* default value = false */) {
    std::string outputString;
    outputString += message;
    logWrite(outputString, newLine);
}

void logWrite(wchar_t message, bool newLine /* default value = false */) {
    std::string outputString;
    outputString += message;
    logWrite(outputString, newLine);
}

// Decimal Values
void logWrite(int message, bool newLine /* default value = false */) {
    logWrite(std::to_string(message), newLine);
    return;
}

void logWrite(long message, bool newLine /* default value = false */) {
    logWrite(std::to_string(message), newLine);
    return;
}

void logWrite(long long message, bool newLine /* default value = false */) {
    logWrite(std::to_string(message), newLine);
    return;
}

void logWrite(double message, bool newLine /* default value = false */) {
    logWrite(std::to_string(message), newLine);
    return;
}

// Hex values
void logWrite(int8bytes message, bool newLine /* default value = false */) {

    std::stringstream stream;
    stream << "0x" << std::hex << std::uppercase << message;
    std::string hexString = stream.str();

    logWrite(hexString, newLine);
    return;
}

void logWrite(int2bytes message, bool newLine /* default value = false */) {
    logWrite( (int8bytes) message, newLine);
    return;
}

void logWrite(int4bytes message, bool newLine /* default value = false */) {
    logWrite( (int8bytes) message, newLine);
    return;
}

void logWrite(int1byte message, bool newLine /* default value = false */) {
    logWrite( (int8bytes) message, newLine);
    return;
}

// Variable Format
void logVar(std::string message, int variable) {
    logWrite(message, false);
    logWrite(": ", false);
    logWrite(variable, true);
}

void logVar(std::string message, double variable) {
    logWrite(message, false);
    logWrite(": ", false);
    logWrite(variable, true);
}
