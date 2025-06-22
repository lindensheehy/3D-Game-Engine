#pragma once

#include "util/Utility.h"

/*
    This file is responsible for reading data from files.
    This can read any file format, but may require further handling depending on file.
    Returns the data in one long, null-terminated char array

     --- IMPORTANT NOTE ---
    Only one file can be open at a time, and is therefore NOT thread safe
    This is not an issue from a safety perspective, the functions will handle unsafe behaviour properly
    This just means if you try to open another file while one is already open, it will close the current one

    The exception to the above statement is 'readFile(const char*)'
    That function is the intended use case for this module, as its the most 'hands off'
    The other functions just exist in case finer control is needed
*/

// Returns -1 if the file failed to open, 0 otherwise
int openFile(const char* fileName);

// Closes the file handle if one is open
void closeFile();

// Returns the size of the open file in bytes when interpreted as raw binary data
int getFileSizeBytes();

// Same as above, but uses the given handle instead of the local one
int getFileSizeBytes(HANDLE hFile);

// Returns a heap allocated char array holding the raw binary contents of the file
// This array should be handled properly externally
char* readFile();

// Does all the work for you, just give a filepath and get the contents
// NOTE: If you had another file open, this will close it
char* readFile(const char* fileName);

// Same as above, but for Windows HANDLE types
// This function is the one exception to the "one file at a time" limitation
// It does not require the local handle, and is therefore thread safe
char* readFile(HANDLE hFile);
