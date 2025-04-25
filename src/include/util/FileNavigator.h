#pragma once

#include "util/Utility.h"
#include "util/Log.h"
#include "util/FileReader.h"
#include "util/LinkedList.h"

class FileNavigator {

    /*
        This class serves to iterator over files in a directory
        To use it:
        - construct with the full path to the directory (relative path from the exe also works)
        - call iterStart with a pattern you want to match. For example, "*" is all files or "*.txt" is all text files
        - call iterNext to go to the next file
        - when iterIsValid returns false, the iterator is done

        There is also the 'iterUseSubDirs' flag that can be set to allow recursive iteration
        This keeps the pattern given in iterStart, but also iterates over all files in subdirectories
    */

    public:

        /*   Instance Variables   */

        // For interacting with Windows
        HANDLE hCurrentFile = INVALID_HANDLE_VALUE;
        WIN32_FIND_DATAA fileData;

        // Heap allocated path buffers. Owned by this class
        char* workingPath;
        char* currentPattern;

        // When true, this will make the iterator also include files in subdirectories
        bool iterUseSubDirs = true;


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

        // Pointer to the shared buffer for workingPath and currentPattern
        char* mem;

        // Index in 'workingPath' where the null terminator lies
        // This is used to make string concats easier
        int workingPathEndIndex;
        
        int currentPatternLength;

        // Jumps past the directories "." and ".."
        // These are Windows generated, and they dont hold any value here
        void skipNavDirs();

        // If the current file is a directory, this function will either skip or enter it depending on the state of iterUseSubDirs
        void handleCurrentDir();


        /*
            The following code is for subdirectory handling
            This uses a LinkedList as a stack. Entering a subdirectory pushes to the stack, leaving pops
            This means several file handles can be held at once, but this->hCurrentFile will be set to the handle at the top of the stack
            This effectively performs a depth first traversal
        */

        struct File {

            /*
                Small helper struct to hold per-directory search nodes
            */

            HANDLE handle;

            // Holds the relative path from workingPath to this search node
            char* relativePath;
            int relativePathLength;

            File(
                HANDLE handle, char* relativePath, int relativePathLength
            ) : handle(handle), relativePath(relativePath), relativePathLength(relativePathLength) {}
        
        };

        LinkedList<File*>* dirStack;

        // Tells the iterator to enter the dir that hCurrentFile lies on
        // Also ensures the iterator will point to an actual file, entering sub directories if iterUseSubDirs is set
        void enterDir();

        // Tells the iterator to pop the last dir on the stack, and close the cooresponding handle
        // Also updates hCurrentFile to the new top node, or INVALID_HANDLE_VALUE if the stack is empty
        void exitDir();

};
