#include "log.h"

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

    // Get a string without trailing zeros after the decimal
    std::string output = std::to_string(message);

    int decimalPos = output.find('.');

    if (decimalPos != std::string::npos) {

        // Find the position of the last non-zero digit after the decimal point
        int endPos = output.find_last_not_of('0');
        
        // If the last non-zero digit is after the decimal point, remove trailing zeros
        if (endPos != std::string::npos && endPos > decimalPos)
            output = output.substr(0, endPos + 1);

        // If there are no non-zero digits after the decimal point, return the integer part
        else
            output = output.substr(0, decimalPos);
            
    }

    // Log it
    logWrite(output, newLine);
    return;
}

// Hex values
// void logWrite(int8bytes message, bool newLine /* default value = false */) {

//     std::stringstream stream;
//     stream << "0x" << std::hex << std::uppercase << message;
//     std::string hexString = stream.str();

//     logWrite(hexString, newLine);
//     return;
// }

// void logWrite(int2bytes message, bool newLine /* default value = false */) {
//     logWrite( (int8bytes) message, newLine);
//     return;
// }

// void logWrite(int4bytes message, bool newLine /* default value = false */) {
//     logWrite( (int8bytes) message, newLine);
//     return;
// }

// void logWrite(int1byte message, bool newLine /* default value = false */) {
//     logWrite( (int8bytes) message, newLine);
//     return;
// }

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
