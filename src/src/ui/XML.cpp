#include "ui/XML.h"

// Constructor
XML::XML(const char* fileName) {

    char* fileContents = readFile(fileName);

    // Loop through the data to count tags

    // Primitive tags like '<' will get a single, translated, byte stored in TagType
    // Other tags will be stored as their string

    // Allocate a new string that has enough space for all tags of dynamic lengths
    // count primitive tags as +1, other tags as maybe +32

    // Then loop through the data again to populate this new string with values

    // This leaves a pre-processed string that will have quicker parsing due to the primitive tags
    // And this will also let you swap tags to anything that would fit in a 32 byte string

    delete fileContents;

    return;

}

// Destructor
XML::~XML() {

    if (this->file != nullptr) delete this->file;

    return;

}

// Instance Functions
void XML::setParameter(const char* tag, int value) {
    
    char* valueString = new char[32];
    intToString(value, valueString, 32);

    this->setParameter(tag, (const char*) valueString);

    delete[] valueString;

}

void XML::setParameter(const char* tag, float value) {

    char* valueString = new char[32];
    floatToString(value, valueString, 32, 4);

    this->setParameter(tag, (const char*) valueString);

    delete[] valueString;
    
}

void XML::setParameter(const char* tag, const char* value) {

    // Traverse the XML file, this can be sped up by:
    //      - Using the fact that every custom tag is 32 bytes, and every primitive tag is 1 byte
    //      - This lets you check each custom char until it mismatches, then jump almost directly to the start of the next

    // find any tags that match the requested one
    // Anything that matches will be swapped with value
    
}