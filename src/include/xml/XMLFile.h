#pragma once

#include "util/Utility.h"
#include "util/FileReader.h"

#include "xml/Core.h"
#include "xml/TagSequence.h"
#include "xml/ParameterInfo.h"


namespace Xml {

class XMLFile {

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

        const char* fileName;

        // The tag sequences. These are the preprocessed versions of the file contents
        TagSequence* parameters;
        TagSequence* labels;
        TagSequence* main;


        // Constructor
        XMLFile(const char* fileName);

        // Destructor
        ~XMLFile();

        /*   Instance Functions   */

        // Performs a deep copy
        XMLFile* copy();

        // Logs the contents of the object
        void log();

        // Sets any instance of the string tag to the designated value (in string form)
        void setParameter(const char* tag, int value);
        void setParameter(const char* tag, float value);
        void setParameter(const char* tag, const char* value);

        // Similar to setParameter, but it doesnt add the underscore prefix
        void setLabel(const char* tag, const char* value);


    private:

        /*   Instance Variables   */

        // Raw file data
        char* file;
        int fileLength;


        // Empty constructor to make deep copy easier
        XMLFile() {}


        /*   Helper functions for construction   */

        // Removes all unnessecary characters from the file. For example, whitespace (in most contexts)
        // Also removes comments like "<!-- comment -->"
        void formatFile(); 

        // Populates the reserved section indexes
        void locateSections();

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

}
