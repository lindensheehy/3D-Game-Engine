#include "util/FileNavigator.h"


FileNavigator::FileNavigator(const char* workingPath) {

    int length = stringLength(workingPath);

    // Points to the null byte so it can be set using this index later
    this->workingPathEndIndex = length - 1;

    // Make sure its not too big
    if (length > MAX_PATH) {
        logWrite("FileNavigator constructor was called with too long of a path!", true);
        logWrite(" -> path \"");
        logWrite(workingPath);
        logWrite("\" has length ");
        logWrite(length);
        logWrite(" but max allowed is ");
        logWrite(MAX_PATH);
        return;
    }

    // Allocate and section memory
    this->mem = (char*) operator new(MAX_PATH * 2);
    memset(mem, 0x00, MAX_PATH * 2);
    this->workingPath = mem;
    this->currentPattern = mem + MAX_PATH;

    memcpy(this->workingPath, workingPath, length);

    this->dirStack = new LinkedList<File*>();

    return;

}

FileNavigator::~FileNavigator() {

    if (this->dirStack->length > 0) {
        logWrite("FileNavigator destructor called while the iterator is active!", true);
        logWrite(" -> the directory stack has ");
        logWrite(this->dirStack->length);
        logWrite(" elements. (it should be empty)", true);
        this->iterEnd();
    }

    delete this->dirStack;

    if (this->hCurrentFile != INVALID_HANDLE_VALUE) {
        CloseHandle(this->hCurrentFile);
    }
    
    operator delete(this->mem);

}

void FileNavigator::setWorkingPath(const char* newPath) {

    // Make sure the iter is not active
    this->iterEnd();

    int length = stringLength(workingPath);

    // Points to the null byte so it can be set using this index later
    this->workingPathEndIndex = length - 1;

    // Make sure its not too big
    if (length > MAX_PATH) {
        logWrite("FileNavigator::setWorkingPath() was called with too long of a path!", true);
        logWrite(" -> path \"");
        logWrite(newPath);
        logWrite("\" has length ");
        logWrite(length);
        logWrite(" but max allowed is ");
        logWrite(MAX_PATH);
        return;
    }

    delete this->workingPath;
    this->workingPath = new char[MAX_PATH];
    memcpy(this->workingPath, newPath, length);

    return;

}

void FileNavigator::iterStart(const char* pattern) {

    this->iterEnd();

    int length = stringLength(pattern);

    // Make sure it wont overflow this->workingPath
    int fullLength = this->workingPathEndIndex + length;
    if (fullLength >= MAX_PATH) {
        logWrite("FileNavigator::iterStart() called with too long of a path!", true);
        logWrite(" -> path \"");
        logWrite(this->workingPath);
        logWrite(pattern);
        logWrite("\" has length ");
        logWrite(length);
        logWrite(" but max allowed is ");
        logWrite(MAX_PATH);
        return;
    }

    memcpy(this->currentPattern, pattern, length);
    this->currentPatternLength = length;

    memcpy( &(this->workingPath[this->workingPathEndIndex]), pattern, length );

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
    // nullptr is passed for 'relativePath' because this is the relative root
    File* newFile = new File(this->hCurrentFile, nullptr, 0);
    this->dirStack->pushFront(newFile);

    this->skipNavDirs();

    return;

}

void FileNavigator::iterNext() {

    if (this->hCurrentFile == INVALID_HANDLE_VALUE) return;

    bool foundValidFile = FindNextFileA(this->hCurrentFile, &(this->fileData));

    if (!foundValidFile) this->exitDir();

    return;

}

bool FileNavigator::iterIsValid() {

    return this->hCurrentFile != INVALID_HANDLE_VALUE;

}

void FileNavigator::iterEnd() {

    if (this->dirStack->length == 0) return;

    return;

}

char* FileNavigator::readCurrentFile() {

    if (!this->iterIsValid()) {
        logWrite("FileNavigator::readCurrentFile() called while the iterator is not valid!", true);
        return nullptr;
    }

    // Find the file name length
    int length = 0;
    while (true) {
        if (this->fileData.cFileName[length] == '\0') break;
        length++;
    }

    // Add one for null terminator
    length++;

    // Make sure it wont overflow this->workingPath
    int fullPathLength = length + this->workingPathEndIndex;
    if (fullPathLength >= MAX_PATH) {
        logWrite("FileNavigator::iterStart() called with too long of a path!", true);
        logWrite(" -> path \"");
        logWrite(this->workingPath);
        logWrite(this->fileData.cFileName);
        logWrite("\" has length ");
        logWrite(length);
        logWrite(" but max allowed is ");
        logWrite(MAX_PATH);
        return nullptr;
    }

    memcpy(
        &(this->workingPath[this->workingPathEndIndex]), 
        this->fileData.cFileName, 
        length 
    );

    // Read the file using the whole file path
    char* ret = readFile(this->workingPath);

    // Cut the workingPath back to what it was before
    this->workingPath[this->workingPathEndIndex] = '\0';

    return ret;

}

void FileNavigator::skipNavDirs() {

    while (true) {

        bool dotDir = this->fileData.cFileName[0] == '.';
        bool dotDotDir = dotDir && this->fileData.cFileName[1] == '.';

        // Early break
        if ( (!dotDir) && (!dotDotDir) ) break;
            
        this->iterNext();

        if (this->hCurrentFile == INVALID_HANDLE_VALUE) return;

    }

    // Try entering the dir if the use sub dirs flag is set
    if (this->iterUseSubDirs) {

        // Go until a regular file is found
        if ( (this->fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ) {
            this->enterDir();
        }

    }

    // Otherwise skip all dirs
    else {

        while ( (this->fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ) {
            this->iterNext();
        }

    }

    return;

}

void FileNavigator::enterDir() {

    logWrite("Calling FileNavigator::enterDir()!", true);

    if ( (this->fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ) {
        logWrite("FileNavigator::enterDir() was called while the current file was not a directory!", true);
        return;
    }

    // Append index pointer so each memcpy knows where to start
    int appendIndex = this->workingPathEndIndex;

    // Get relativePath and cFileName
    File* currentFile = this->dirStack->getFirst();
    int fileNameLength = stringLength(this->fileData.cFileName);

    // Defend against buffer overflows
    int fullLength = appendIndex + currentFile->relativePathLength + fileNameLength + this->currentPatternLength;
    if (fullLength >= MAX_PATH) {
        logWrite("FileNavigator::iterStart() called with too long of a path!", true);
        logWrite(" -> path \"");
        logWrite(this->workingPath);
        logWrite(currentFile->relativePath);
        logWrite(this->fileData.cFileName);
        logWrite(this->currentPattern);
        logWrite("\" is too long", true);
        return;
    }

    /*   Construct the full path   */

    // First allocate a buffer for the new relativePath that will be given to the new File at the top of the stack
    char* newRelativePath = new char[currentFile->relativePathLength + fileNameLength];
    int newRelativePathLength = 0;
    {

        if ( (currentFile->relativePath != nullptr) && (currentFile->relativePathLength > 0) ) {

            memcpy(newRelativePath, currentFile->relativePath, currentFile->relativePathLength);
            newRelativePathLength += currentFile->relativePathLength;
            
            // Replace the null terminator with '/'
            newRelativePath[newRelativePathLength - 1] = '/';

        }

        memcpy(newRelativePath + newRelativePathLength, this->fileData.cFileName, fileNameLength);
        newRelativePathLength += fileNameLength;

    }

    memcpy(this->workingPath + appendIndex, newRelativePath, newRelativePathLength);
    appendIndex += newRelativePathLength;

    // Add a slash after the existing path (overwriting the null byte that was there)
    this->workingPath[appendIndex - 1] = '/';

    memcpy(this->workingPath + appendIndex, this->currentPattern, this->currentPatternLength);

    this->hCurrentFile = FindFirstFileA(this->workingPath, &(this->fileData));
    if (this->hCurrentFile == INVALID_HANDLE_VALUE) {
        logWrite("FileNavigator::iterStart() found no files with search path \"");
        logWrite(this->workingPath);
        logWrite("\"!", true);
        logWrite(" -> path \"");
        logWrite(this->workingPath, true);
        logWrite(currentFile->relativePath, true);
        logWrite(this->fileData.cFileName, true);
        logWrite(newRelativePath, true);
        logWrite(this->currentPattern, true);
        logWrite("\" is too long", true);
        return;
    }

    // Set the null terminator byte back into this->workingPath
    // This effectively cuts off the search path which was just added
    this->workingPath[this->workingPathEndIndex] = '\0';

    // Update the directory stack with this first found file
    // nullptr is passed for 'relativePath' because this is the relative root
    File* newFile = new File(this->hCurrentFile, newRelativePath, newRelativePathLength);
    this->dirStack->pushFront(newFile);

    this->skipNavDirs();

    return;

}

void FileNavigator::exitDir() {

    if (this->dirStack->length == 0) {
        logWrite("FileNavigator::exitDir() called with no directories on the stack!", true);
        return;
    }

    File* poppedNode = this->dirStack->popFront();

    FindClose(poppedNode->handle);
    delete[] poppedNode->relativePath;
    delete poppedNode;

    // Update this->hCurrentFile
    if (this->dirStack->length > 0) {

        File* newCurrent = this->dirStack->getFirst();

        this->hCurrentFile = newCurrent->handle;

        // Move past the directory the iterator must now lie on
        this->iterNext();

    }

    else {
        this->hCurrentFile = INVALID_HANDLE_VALUE;
    }

    return;
    
}
