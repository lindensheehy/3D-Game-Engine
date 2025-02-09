#pragma once

#include "util/Utility.h"

#include "ui/UIEnums.h"
#include "ui/Action.h"
#include "ui/WindowElement.h"
#include "ui/Window.h"
#include "ui/UI.h"

#include "util/FileReader.h"


// The namespace here keeps these names local to this file only, NOT across includes
// This is an effort to abstract as far away from the low level logic as possible
// Also just keeps the global namespace clean
namespace {

    constexpr int MAX_TAG_LENGTH = 32;
    constexpr int PRIM_TAG_LENGTH = 3;

    enum PrimitiveTag : char {

        // These replace the other tags when they are assigned
        ELEMENT_NONE = 0x01,
        PARAMS_NONE = 0x02,
        CHILDREN_NONE = 0x03,

        // Says where elements open and close. This is roughly on each < and / respectively
        ELEMENT_OPEN = 0x04,
        ELEMENT_CLOSE = 0x05,

        // Marks the parameter section of an element
        PARAMS_START = 0x06,
        PARAMS_END = 0x07,

        // Marks the children section of an element
        CHILDREN_START = 0x08,
        CHILDREN_END = 0x09

    };

    /*   Some general helper functions   */

    // Returns true if the char should be considered valid in the XML file
    static bool isValidChar(char c);

    // Returns true if the char is reserved. ie. disallowed in tag names
    // This counts: '<' '>' '/' '=' ' '
    static bool isReservedChar(char c);

}

class TagSequence {

    public:

        /*   Instance Variables   */

        // Constructor
        TagSequence(int length);

        // Destructor
        ~TagSequence();

        /*   Instance Functions   */

        // Gets the string tag at the given index. lengthOut will be filled with the length of the tag
        char* getTag(int index, int* lengthOut);

        // Will set the tag at the given index to the string. Will only write to length, or XML::MAX_TAG_LENGTH (whatever is smaller)
        void setTag(int index, char* tag, int length);
        
        // Sets all the primitive tags at that index to NONE states
        void resetPrimitiveTags(int index);

        // Puts a primitive tag at a location. The actual position is right before the cooresponding string tag index
        // More than one can be set at once. This is capped at XML::PRIM_TAG_LENGTH, which is the amount of types of prim tags
        // This is just to abstract away from the byte level operations involved
        void setPrimitiveTag(int index, PrimitiveTag tag);

};



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

        /*   Instance Variables   */

        const char* fileName;

        // Raw file data
        char* file;

        // The tag sequence. This is the preprocessed version of the file contents
        TagSequence tagSequence;

        /*   Helper functions for construction   */

        // Removes all unnessecary characters from the file. For example, whitespace (in most contexts)
        void formatFile(); 

        // Populates the reserved section indexes
        void locateSections();

        // Returns the size needed to fit the tag sequence
        int getSequenceLength();

        // Populates the tag sequence
        void populateTagSequence();


        // Indexes of the start and end of each reserved section
        // These count only whats in between the reserved tags, not the tags themselves
        int parametersStart;
        int parametersEnd;
        
        int labelsStart;
        int labelsEnd;

        int mainStart;
        int mainEnd;

};
