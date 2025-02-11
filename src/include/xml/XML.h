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

    constexpr int MAX_TAG_LENGTH = 64;

    // These help to group the Primitive tags. The values are the relative indexes
    constexpr int PRIM_TAG_LENGTH = 3;
    enum PrimitiveTagType : int {

        ELEMENT = 0,
        PARAMS = 1,
        CHILDREN = 2

    };

    // These are the actual bytes that are stored in the buffer
    enum PrimitiveTagState : char {

        // These are the possible states for each PrimitiveTagType
        NONE = 0x00,
        OPEN = 0x02,
        CLOSE = 0x03,

        /*   These ones should be unique to the ELEMENT type   */

        // This is used when two elements lie directly next to each other
        // Indicated by substring "/><"
        CLOSE_OPEN = 0x04,

        // This is used when there is a self closing tag right before a closing tag
        // Indicated by substring "/></"
        DOUBLE_CLOSE = 0x05

    };

    /*   Some general helper functions   */

    // Returns true if the char should be considered valid in the XML file
    static bool isValidChar(char c);

    // Returns true if the char is reserved. ie. disallowed in tag names
    // This counts: '<' '>' '/' '=' ' '
    static bool isReservedChar(char c);

    // Returns the length of the tag. 
    // Very similar to strlen, but this early returns after a certain length
    int getTagLength(const char* tag);

}



class XML {

    /*
        This class is responsible for parsing XML files that define UI elements
        This turns the text from the file into a more usable format to generate WindowElement or Window objects
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
        TagSequence* tagSequence;

        /*   Helper functions for construction   */

        // Removes all unnessecary characters from the file. For example, whitespace (in most contexts)
        // Also removes comments like "<!-- comment -->"
        void formatFile(); 

        // Populates the reserved section indexes
        void locateSections();

        // Populates the tag sequence
        void populateTagSequence();

        // Applys all the labels defined in the XML file
        // This effectively treats them as parameters with default values
        void applyLabels();


        // Indexes of the start and end of each reserved section
        // These count only whats in between the reserved tags, not the tags themselves
        int parametersStart;
        int parametersEnd;
        
        int labelsStart;
        int labelsEnd;

        int mainStart;
        int mainEnd;

};
