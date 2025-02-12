#pragma once

#include "util/Utility.h"
#include "util/FileReader.h"

#include "ui/UI.h"

#include "xml/Core.h"
#include "xml/TagSequence.h"


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
        TagSequence* parameters;
        TagSequence* labels;
        TagSequence* main;

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
