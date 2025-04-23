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
    memset(this->workingPath, 0x00, MAX_PATH);
    memcpy(this->workingPath, workingPath, pathLength);

    this->dirStack = new LinkedList<File*>();

    return;

}

FileNavigator::~FileNavigator() {

    if (this->dirStack->length > 0) {
        logWrite("FileNavigator destructor called while the iterator is active!", true);
        logWrite(" -> the directory stack has ");
        logWrite(this->dirStack->length);
        logWrite(" elements. (it should be empty)", true);
    }

    delete this->dirStack;

    if (this->hCurrentFile != INVALID_HANDLE_VALUE) {
        CloseHandle(this->hCurrentFile);
    }
    
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

    this->iterEnd();

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

    logWrite("iterStart:", true);
    logWrite(" -> workingPath = ");
    logWrite(this->workingPath, true);
    logWrite(" -> searchPath = ");
    logWrite(searchPath, true);

    memcpy( &(this->workingPath[this->workingPathEndIndex]), searchPath, pathLength );

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

    // Update the directory stack with this first found file
    File* newFile = new File(this->hCurrentFile, this->fileData);
    this->dirStack->pushFront(newFile);

    return;

}

void FileNavigator::iterNext() {

    if (this->hCurrentFile == INVALID_HANDLE_VALUE) return;

    bool foundValidFile = FindNextFileA(this->hCurrentFile, &fileData);

    if (!foundValidFile) {
        FindClose(this->hCurrentFile);
        this->hCurrentFile = INVALID_HANDLE_VALUE;
    }

    return;

}

bool FileNavigator::iterIsValid() {

    return this->hCurrentFile != INVALID_HANDLE_VALUE;

}

char* FileNavigator::readCurrentFile() {

    if (!this->iterIsValid()) {
        logWrite("FileNavigator::readCurrentFile() called while the iterator is not valid!", true);
        return nullptr;
    }

    if (this->fileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
        logWrite("Dir!\n\n");
        return nullptr;
    }

    return readFile(this->hCurrentFile);

}
