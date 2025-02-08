#pragma once

#include "util/Utility.h"

#include "ui/UIEnums.h"
#include "ui/Action.h"
#include "ui/WindowElement.h"
#include "ui/Window.h"
#include "ui/UI.h"

#include "util/FileReader.h"



class XML {

    /*
        This class is responsible for parsing XML files that define UI elements
        This turns the text from the file into a more usable format that can be used elsewhere
        Most of the content of this class is private, as its intended to be treated like a black box
        Steps to use are:
        - Construct with a file name
        - Set parameter values if needed
        - Build your element or window
    */

    public:

        /*   Instance Variables   */

        // Constructor
        XML(const char* fileName);

        // Destructor
        ~XML();

        /*   Instance Functions   */

        // Sets any instance of the string "tag" to the designated value (in string form)
        void setParameter(const char* tag, int value);
        void setParameter(const char* tag, float value);
        void setParameter(const char* tag, const char* value);

        // Builds the current XML file to a WindowElement instance
        // Will fail and return null if an unrecognized token exists, like a unset parameter
        WindowElement* buildElement();

        // Same thing as buildElement, but returns a Window instead
        Window* buildWindow();

    private:

        /*   Instance Variables   */

        const int MAX_TAG_LENGTH = 32;

        const char* fileName;

        // Raw file data
        char* file;

        // Holds a modified version of the file contents
        // Its pre-processed so its esaier to work with
        char* tagSequence;
        int tagSequenceLength;

        /*   Helper functions for contruction   */

        // Removes all unnessecary characters from the file. For example, whitespace (in most contexts)
        void formatFile(); 

        // Populates the reserved section indexes
        void locateSections();

        // Returns the size needed to fit the tag sequence
        int getSequenceLength();

        // Populates the tag sequence
        void populateTagSequence();

        /*   Static helper functions   */

        // Returns true if the char should be considered valid in the XML file
        static bool isValidChar(char c);

        // Returns true if the char is reserved. ie. disallowed in tag names
        // This counts: '<' '>' '/' '=' ' '
        static bool isReservedChar(char c);


        // Indexes of the start and end of each reserved section
        // These count only whats in between the reserved tags, not the tags themselves
        int parametersStart;
        int parametersEnd;
        
        int labelsStart;
        int labelsEnd;

        int mainStart;
        int mainEnd;

};
