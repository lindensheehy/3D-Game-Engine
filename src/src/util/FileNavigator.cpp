#include "util/FileNavigator.h"


FileNavigator::FileNavigator(const char* workingPath) {

    int pathLength = 0;
    while (true) {
        if (workingPath[pathLength] == '\0') break;
        pathLength++;
    }

    this->workingPathEndIndex = pathLength;

    // Add one to include the null terminator
    pathLength++;

    // Make sure its not too big
    if (pathLength > MAX_PATH) {
        logWrite("FileNavigator constructor was called with too long of a path!", true);
        logWrite(" -> path \"");
        logWrite(workingPath);
        logWrite("\" has length ");
        logWrite(pathLength);
        logWrite(" but max allowed is ");
        logWrite(MAX_PATH);
        return;
    }

    this->workingPath = new char[MAX_PATH];
    memcpy(this->workingPath, workingPath, pathLength);

    return;

}

FileNavigator::~FileNavigator() {
    
    delete[] this->workingPath;

}

void FileNavigator::setWorkingPath(const char* newPath) {

    int pathLength = 0;
    while (true) {
        if (newPath[pathLength] == '\0') break;
        pathLength++;
    }

    this->workingPathEndIndex = pathLength;

    // Add one to include the null terminator
    pathLength++;

    // Make sure its not too big
    if (pathLength > MAX_PATH) {
        logWrite("FileNavigator::setWorkingPath() was called with too long of a path!", true);
        logWrite(" -> path \"");
        logWrite(newPath);
        logWrite("\" has length ");
        logWrite(pathLength);
        logWrite(" but max allowed is ");
        logWrite(MAX_PATH);
        return;
    }

    this->workingPath = new char[MAX_PATH];
    memcpy(this->workingPath, newPath, pathLength);

    return;

}

void FileNavigator::iterStart(const char* searchPath) {

    if (this->hCurrentFile != INVALID_HANDLE_VALUE) {
        FindClose(this->hCurrentFile);
        hCurrentFile = INVALID_HANDLE_VALUE;
    }

    // Find searchPaths length
    int pathLength = 0;
    while (true) {
        if (searchPath[pathLength] == '\0') break;
        pathLength++;
    }

    // Add one for null terminator
    pathLength++;

    // Make sure it wont overflow this->workingPath
    int fullSearchPathLength = pathLength + this->workingPathEndIndex;
    if (fullSearchPathLength >= MAX_PATH) {
        logWrite("FileNavigator::iterStart() called with too long of a path!", true);
        logWrite(" -> path \"");
        logWrite(this->workingPath);
        logWrite(searchPath);
        logWrite("\" has length ");
        logWrite(pathLength);
        logWrite(" but max allowed is ");
        logWrite(MAX_PATH);
        return;
    }

    memcpy(this->workingPath + this->workingPathEndIndex, searchPath, pathLength);

    this->hCurrentFile = FindFirstFileA(this->workingPath, &(this->fileData));
    if (this->hCurrentFile == INVALID_HANDLE_VALUE) {
        logWrite("FileNavigator::iterStart() found no files with search path \"");
        logWrite(this->workingPath);
        logWrite("\"!", true);
        return;
    }

    // Set the null terminator byte back into this->workingPath
    // This effectively cuts off the search path which was just added
    this->workingPath[this->workingPathEndIndex] = '\0';

    return;

}

void FileNavigator::iterNext() {

    if (this->hCurrentFile == INVALID_HANDLE_VALUE) return;

    if (this->doRecursion) {
        this->iterNextRecursive(); 
        return; 
    }

    bool foundValidFile = FindNextFileA(this->hCurrentFile, &fileData);

    if (!foundValidFile) {
        FindClose(this->hCurrentFile);
        this->hCurrentFile = INVALID_HANDLE_VALUE;
    }

    return;

}

void FileNavigator::iterNextRecursive() {
    
}

bool FileNavigator::iterIsValid() {

    return this->hCurrentFile != INVALID_HANDLE_VALUE;

}

char* FileNavigator::readCurrentFile() {

    if (!this->iterIsValid()) {
        logWrite("FileNavigator::readCurrentFile() called while the iterator is not valid!", true);
        return nullptr;
    }

    return readFile(this->hCurrentFile);

}
