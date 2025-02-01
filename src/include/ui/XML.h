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
    */

    public:

        // These are the bytes in the string that represent tags
        // Used to shorten the string, and make parsing easier
        // These are not nessecarily 1-to-1 with actual characters, but are rather logical tags
        enum TagType : uint8 {

            /*
                Its worth noting that some of these do not need to be here, as they are implcitly done by another tag
                I chose to put them anyway to make the parsing a little easier
            */

            // Parameters section
            PARAMETERS_START = 0x01,
            PARAMETERS_END = 0x02,

            // Labels section
            LABELS_START = 0x03,
            LABELS_END = 0x04,
            
            // Full tags
            TAG_START = 0x05,
            TAG_END = 0x06,

            // Children section
            CHILDREN_START = 0x07,
            CHILDREN_END = 0x08,

            // Tag Traits
            TRAIT_START = 0x09,
            TRAIT_END = 0x0A

        };

        /*   Instance Variables   */

        const char* fileName;

        // Holds a modified version of the file contents
        // Its pre-processed so its esaier to work with
        char* file;

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

};
