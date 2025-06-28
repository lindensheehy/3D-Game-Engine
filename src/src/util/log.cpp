#include "util/Log.h"


HANDLE hOutputFile = nullptr;

// Exists primarily for casting (like 'intToString' for example)
char* stringBuffer = nullptr;

// Control functions
void logInit(const char* fileName) {

    if (hOutputFile != nullptr) logClose();
    
    if (fileName == nullptr) return;
    
    // Get handle to file
    hOutputFile = CreateFile(
        fileName,                 // File name
        GENERIC_WRITE,            // Desired access: write
        FILE_SHARE_READ,          // Share mode: allow other processes to read
        NULL,                     // Security attributes
        CREATE_ALWAYS,            // Creation disposition: Create new file if none exists, otherwise overwrite existing file with empty file
        FILE_ATTRIBUTE_NORMAL,    // Flags and attributes
        NULL                      // Template file handle
    );

    // Allocate a string buffer, and delete old one if needed
    if (stringBuffer != nullptr) delete[] stringBuffer;
    stringBuffer = new char[64];

    return;

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

    // Truncates anything past the file pointer, so everything
    SetEndOfFile(hOutputFile);

    return;

}

// Strings and chars
void logWrite(const char* message, bool newLine) {

    if (hOutputFile == nullptr) return;

    if (message == nullptr) return;

    DWORD bytesWritten;
    WriteFile(hOutputFile, message, strlen(message), &bytesWritten, NULL);
    
    if (newLine) {
        WriteFile(hOutputFile, "\r\n", 2, &bytesWritten, NULL);
    }

    return;

}

void logWrite(char* message, bool newLine) {
    logWrite((const char*) message, newLine);
}

void logWrite(char message, bool newLine) {

    const char messageString[] = {message, '\0'};
    logWrite(messageString, newLine);

    return;

}

void logWrite(wchar_t message, bool newLine) {}

// Decimal Values
void logWrite(int message, bool newLine) {

    intToString(message, stringBuffer, 64);
    logWrite(stringBuffer, newLine);

    return;

}

void logWrite(long message, bool newLine) {
    logWrite((int) message, newLine);
}

void logWrite(long long message, bool newLine) {
    logWrite((int) message, newLine);
}

void logWrite(float message, bool newLine) {

    floatToString(message, stringBuffer, 64, 4);
    logWrite(stringBuffer, newLine);

    return;

}

void logWrite(double message, bool newLine) {

    doubleToString(message, stringBuffer, 64, 4);
    logWrite(stringBuffer, newLine);

    return;

}

// Hex values
void logWriteHex(char message, bool newLine) {}

void logWriteHex(short message, bool newLine) {}

void logWriteHex(int message, bool newLine) {}

void logWriteHex(long long message, bool newLine) {}

// New line
void logNewLine() {
    logWrite("\n");
}

// Variable Format
void logVar(const char* message, int variable) {

    logWrite(message, false);
    logWrite(": ", false);
    logWrite(variable, true);

    return;

}

void logVar(const char* message, double variable) {

    logWrite(message, false);
    logWrite(": ", false);
    logWrite(variable, true);

    return;

}
