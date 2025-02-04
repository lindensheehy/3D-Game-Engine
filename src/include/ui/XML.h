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
                Its worth noting that some of these do not need to be here, as they are implicitly done by another tag
                I chose to put them anyway to make the parsing a little easier
            */
            
            // Full tags
            TAG_START = 0x01,
            TAG_END = 0x02,

            // Tag Traits (This counts any extra information given within a tag)
            TRAITS_START = 0x03,
            TRAITS_END = 0x04,

            // Children section (This counts anything between an open and close tag)
            CHILDREN_START = 0x05,
            CHILDREN_END = 0x06

        };

        const int MAX_TAG_LENGTH = 32;

        /*   Instance Variables   */

        const char* fileName;

        // Raw file data
        char* file;

        // Holds a modified version of the file contents
        // Its pre-processed so its esaier to work with
        char* tagSequence;
        int tagSequenceLength;

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

        // Helper functions for contruction

        // Finds and stores the index of all reserved tags start and end locations (eg. <main>)
        void locateReservedTags();

        // Returns the size needed to fit the tag sequence
        int getSequenceLength(char* file);

        // Populates the tag sequence
        void populateTagSequence(char* file);

        // Just returns true if the character should be considered.
        // This helps to filter out any chars that do not contribute to the data
        bool validChar(char c);

        // Indexes of all the reserved tag locations
        int tagParametersStart;
        int tagParametersEnd;
        
        int tagLabelsStart;
        int tagLabelsEnd;

        int tagMainStart;
        int tagMainEnd;

};
