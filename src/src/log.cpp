#include "../include/Log.h"

HANDLE hOutputFile = nullptr;

char* stringBuffer = nullptr;

// Init and Close
void logInit(const char* fileName) {

    if (hOutputFile != nullptr) return;
    
    // Get handle to file
    hOutputFile = CreateFile(
        fileName,                 // File name
        GENERIC_WRITE,            // Desired access: write
        0,                        // Share mode: no sharing
        NULL,                     // Security attributes
        CREATE_ALWAYS,            // Creation disposition: Create new file if none exists, otherwise overwrite existing file with empty file
        FILE_ATTRIBUTE_NORMAL,    // Flags and attributes
        NULL                      // Template file handle
    );

    // Allocate a string buffer, and delete old one if needed
    if (stringBuffer != nullptr) delete[] stringBuffer;
    stringBuffer = new char[64];

}

void logInit(char* fileName) {
    logInit((const char*) fileName);
}

void logClose() {

    if (hOutputFile == nullptr) return;

    CloseHandle(hOutputFile);
    hOutputFile = nullptr;

    return;

}

// Clears all characters from the output file
void logClear() {

    if (hOutputFile == nullptr) return;

    // Move the file pointer to the start of the file
    SetFilePointer(hOutputFile, 0, NULL, FILE_BEGIN);

    // Truncates everything past the file pointer, that being everyhting
    SetEndOfFile(hOutputFile);

}

// Strings and chars
void logWrite(const char* message, bool newLine /* default value = false */) {

    if (hOutputFile == nullptr) return;

    DWORD bytesWritten;
    WriteFile(hOutputFile, message, strlen(message), &bytesWritten, NULL);
    
    if (newLine) 
        WriteFile(hOutputFile, "\r\n", 2, &bytesWritten, NULL);

}

void logWrite(char* message, bool newLine /* default value = false */) {
    logWrite((const char*) message, newLine);
}

void logWrite(char message, bool newLine /* default value = false */) {
    char messageString[] = {message, '\n'};
    logWrite((const char*) messageString, newLine);
}

void logWrite(wchar_t message, bool newLine /* default value = false */) {
    
    return;

}

// Decimal Values
void logWrite(int message, bool newLine /* default value = false */) {

    intToString(message, stringBuffer, 64);
    logWrite(stringBuffer, newLine);

    return;
}

void logWrite(long message, bool newLine /* default value = false */) {
    logWrite((int) message, newLine);
}

void logWrite(long long message, bool newLine /* default value = false */) {
    logWrite((int) message, newLine);
}

void logWrite(double message, bool newLine /* default value = false */) {

    doubleToString(message, stringBuffer, 64);
    logWrite(stringBuffer, newLine);

    return;

}

// Hex values
void logWriteHex(char message, bool newLine /* default value = false */) {

    return;

}

void logWriteHex(short message, bool newLine /* default value = false */) {
    
    return;

}

void logWriteHex(int message, bool newLine /* default value = false */) {
    
    return;

}

void logWriteHex(long long message, bool newLine /* default value = false */) {

    return;

}

// New line
void logNewLine() {
    logWrite("\n");
}

// Variable Format
void logVar(const char* message, int variable) {
    logWrite(message, false);
    logWrite(": ", false);
    logWrite(variable, true);
}

void logVar(const char* message, double variable) {
    logWrite(message, false);
    logWrite(": ", false);
    logWrite(variable, true);
}
