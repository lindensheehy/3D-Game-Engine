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

        // Enum for primitive tags. These are individual bytes that will be placed into tagSequence
        enum PrimitiveTag : char {

            // Says where elements open and close. This is roughly on each < and / respectively
            ELEMENT_OPEN = 0x01,
            ELEMENT_CLOSE = 0x02,

            // Marks the parameter section of an element
            PARAMS_START = 0x03,
            PARAMS_END = 0x04,

            // Marks the children section of an element
            CHILDREN_START = 0x05,
            CHILDREN_END = 0x06

        };

        /*   Instance Variables   */

        static const int MAX_TAG_LENGTH = 32;
        static const int PRIM_TAG_LENGTH = 3;

        const char* fileName;

        // Raw file data
        char* file;

        // Holds a modified version of the file contents
        // Its pre-processed so its easier to work with
        char* tagSequence;
        int tagSequenceLength;
        
        // Higher level equivalent of tagSequenceLength
        // This stores the count of string tags. Helpful when indexing with getTag and setTag
        int tagCount;

        /*   Helper functions for construction   */

        // Removes all unnessecary characters from the file. For example, whitespace (in most contexts)
        void formatFile(); 

        // Populates the reserved section indexes
        void locateSections();

        // Returns the size needed to fit the tag sequence
        int getSequenceLength();

        // Populates the tag sequence
        void populateTagSequence();


        /*   Helper functions for reading and writing tags in tagSequence   */

        // Gets the string tag at the given index. lengthOut will be filled with the length of the tag
        char* getTag(int index, int* lengthOut);

        // Will set the tag at the given index to the string. Will only write to length, or XML::MAX_TAG_LENGTH (whatever is smaller)
        void setTag(int index, char* tag, int length);

        // Puts a primitive tag at a location. The actual position is right before the cooresponding string tag index
        // More than one can be set at once. This is capped at XML::PRIM_TAG_LENGTH, which is the amount of types of prim tags
        // This is just to abstract away from the byte level operations involved
        void setPrimitiveTag(int index, XML::PrimitiveTag tag);


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
