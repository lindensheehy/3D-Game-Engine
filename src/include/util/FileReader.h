#pragma once

#include "util/Utility.h"

/*
    This file is responsible for reading data from files.
    This can read any file format, but may require further handling depending on file.
    Returns the data in one long, null-terminated, string

    These functions will work on one file at a time.
    If you try to open another file, while one is already open, it will close the current one.
*/

// Returns -1 if the file failed to open, 0 otherwise
int openFile(const char* fileName);

// Closes the file handle if one is open
void closeFile();

// Returns the size of the open file in bytes when interpreted as raw binary data
int getFileSizeBytes();

// Returns a heap allocated char array holding the raw binary contents of the file
// This array should be handled properly externally
char* readFile();

// Does all the work for you, just give a filepath and get the contents
// NOTE: If you had another file open, this will close it
char* readFile(const char* fileName);
