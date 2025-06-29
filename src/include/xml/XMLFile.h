#pragma once

#include "util/Utility.h"
#include "util/FileReader.h"

#include "xml/Core.h"
#include "xml/TagSequence.h"


namespace Xml {

class XMLFile {

    /*
        This class is responsible for parsing XML files that define UI elements
        This translates the raw text data from the file into a more usable format (TagSequence objects)
        This class should be treated like a black box
        Just pass a file name, let it do what it does, and use the resulting data
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
        XMLFile* copy() const;

        // Logs the contents of this object
        void log() const;

        // Sets any instance of the string tag to the designated value (in string form)
        void setParameter(const char* tag, int value);
        void setParameter(const char* tag, float value);
        void setParameter(const char* tag, const char* value);

        // Similar to setParameter, but it doesnt use the underscore prefix
        void setLabel(const char* tag, const char* value);


    private:

        /*   Instance Variables   */

        // Raw file data
        char* file;
        int fileLength;

        // Indexes of the start and end of each reserved section
        // These include only whats in between the reserved tags, not the tags themselves
        int parametersStart;
        int parametersEnd;
        
        int labelsStart;
        int labelsEnd;

        int mainStart;
        int mainEnd;


        // Empty constructor for easier deep copies
        XMLFile() {}


        /*   Helper functions for construction   */

        // Removes all unnessecary characters from the file. For example, whitespace (in most contexts)
        // Also removes comments like "<!-- comment -->"
        void formatFile(); 

        // Populates the reserved section indexes ('parametersStart', etc.)
        void locateSections();

        // Applies all the labels defined in the XML file
        // This just swaps any occurrence of the label string with the value given in the <labels> section
        void applyLabels();

};

}
