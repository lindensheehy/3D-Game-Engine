#pragma once

#include "util/Utility.h"
#include "util/Log.h"
#include "util/FileReader.h"

class FileNavigator {

    public:

        /*   Instance Variables   */

        // For interacting with Windows
        HANDLE hCurrentFile;
        WIN32_FIND_DATAA fileData;

        // Heap allocated buffer for the current root file path being used
        char* workingPath;

        // Flags for iteration handling
        bool doRecursion = false;
        bool considerDirs = false;


        // Constructor
        FileNavigator(const char* workingPath);

        // Destructor
        ~FileNavigator();


        /*   Instance Functions   */

        // Updates the working path to be the given string. Will also check if the path is valid and log errors if not
        void setWorkingPath(const char* newPath);

        // Starts the iterator at the current working path + the given path. searchPath should be relative to this->workingPath
        // searchPath should also include some form of wildcard. It should be a search that returns all files you want (ex. "dir/*" or "dir/*.txt")
        void iterStart(const char* searchPath);

        // Moves the iterator to the next valid file
        void iterNext();

    private:    

        // Called from iterNext when the doRecursion flag is set
        void iterNextRecursive();

    public:

        // Intended to be used in loops as the condition. Returns false once there are no more valid files for the iterator to use
        bool iterIsValid();

        // Returns a heap allocated buffer containing the current files contents
        char* readCurrentFile();

    private:

        // Index in 'workingPath' where the null terminator lies
        // This is used to make string concats easier
        int workingPathEndIndex;

};
