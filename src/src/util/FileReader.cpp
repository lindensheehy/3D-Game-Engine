#include "util/FileReader.h"


HANDLE hFileGlobal = nullptr;

int openFile(const char* fileName) {

    if (hFileGlobal != nullptr) {
        closeFile();
    }
    
    // Get handle to file
    hFileGlobal = CreateFileA(
        fileName,                 // File name
        GENERIC_READ,             // Desired access: read
        FILE_SHARE_READ,          // Share mode: allow other processes to read
        NULL,                     // Security attributes
        OPEN_EXISTING,            // Creation disposition: Open the existing file, or fail if none exists
        FILE_ATTRIBUTE_NORMAL,    // Flags and attributes
        NULL                      // Template file handle
    );

    if (hFileGlobal == INVALID_HANDLE_VALUE) {
        hFileGlobal = nullptr;
        return -1;
    }

    return 0;

}

void closeFile() {

    if (hFileGlobal == nullptr) return;

    CloseHandle(hFileGlobal);
    hFileGlobal = nullptr;

    return;

}

int getFileSizeBytes() {

    // No file open
    if (hFileGlobal == nullptr) return -1;

    LARGE_INTEGER fileSize;
    const bool status = GetFileSizeEx(hFileGlobal, &fileSize);

    // Failed to get size
    if (!status) return -1;
            
    return static_cast<int>(fileSize.QuadPart);

}

int getFileSizeBytes(HANDLE hFile) {

    // No file open
    if (hFile == INVALID_HANDLE_VALUE) return -1;

    LARGE_INTEGER fileSize;
    const bool status = GetFileSizeEx(hFile, &fileSize);

    // Failed to get size
    if (!status) return -1;
            
    return static_cast<int>(fileSize.QuadPart);

}

char* readFile() {

    // No file open
    if (hFileGlobal == nullptr) return nullptr;

    // Get file size, return nullptr if failed
    const int fileSize = getFileSizeBytes();
    if (fileSize <= 0) return nullptr;

    char* buffer = new char[fileSize + 1];  // +1 for null terminator
    DWORD bytesRead;

    const bool status = ReadFile(hFileGlobal, buffer, fileSize, &bytesRead, nullptr);

    // Failed to read all bytes
    if ( !status || (bytesRead != fileSize) ) {
        delete[] buffer;
        return nullptr;
    }

    buffer[fileSize] = '\0';
    return buffer;

}

char* readFile(const char* fileName) {

    // Close the open file if there is one
    if (hFileGlobal != nullptr) closeFile();

    const int status = openFile(fileName);

    // Failed to open file
    if (status == -1) {
        logWrite("Failed to open file: ");
        logWrite(fileName, true);
        return nullptr;
    }

    char* buffer = readFile();

    // Failed to read file
    if (buffer == nullptr) {
        logWrite("Failed to read file: ");
        logWrite(fileName, true);
        closeFile();
        return nullptr;
    }

    // Clean up
    closeFile();

    return buffer;

}

char* readFile(HANDLE hFile) {

    // Get file size, return nullptr if failed
    const int fileSize = getFileSizeBytes(hFile);
    if (fileSize <= 0) return nullptr;

    char* buffer = new char[fileSize + 1];  // +1 for null terminator
    DWORD bytesRead;

    const bool status = ReadFile(hFile, buffer, fileSize, &bytesRead, nullptr);

    // Failed to read all bytes
    if ( !status || (bytesRead != fileSize) ) {
        delete[] buffer;
        return nullptr;
    }

    buffer[fileSize] = '\0';

    return buffer;

}
