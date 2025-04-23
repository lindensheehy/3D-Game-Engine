#pragma once

#include "util/Utility.h"
#include "util/Log.h"
#include "util/FileReader.h"
#include "util/LinkedList.h"

class FileNavigator {

    public:

        /*   Instance Variables   */

        // For interacting with Windows
        HANDLE hCurrentFile;
        WIN32_FIND_DATAA fileData;

        // Heap allocated buffer for the current root file path being used
        char* workingPath;

        // When true, this will make the iterator also include files in subdirectories
        bool iterUseSubDirs = false;


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

        // Intended to be used in loops as the condition. Returns false once there are no more valid files for the iterator to use
        bool iterIsValid();

        // Kills the iterator early. This closes all file handles if any are open
        void iterEnd();

        // Returns a heap allocated buffer containing the current files contents
        char* readCurrentFile();

    private:

        // Index in 'workingPath' where the null terminator lies
        // This is used to make string concats easier
        int workingPathEndIndex;

        // Jumps the iterator pointer forward to the first non directory file
        // This updates the file pointer whenever this->iterUseSubDirs is false
        void skipDirs();


        /*
            The following code is for subdirectory handling
            This uses a LinkedList as a stack. Entering a subdirectory pushes to the stack, leaving pops
            This means several file handles can be held at once, but this->hCurrentFile will be set to the handle at the top of the stack
            This effectively performs a depth first traversal
        */

        struct File {
            HANDLE handle;
            WIN32_FIND_DATAA data;
            File(HANDLE handle, WIN32_FIND_DATAA data) : handle(handle), data(data) {}
        };

        LinkedList<File*>* dirStack;

        // Tells the iterator to
        void enterDir();

};
