#include "xml/ParameterInfo.h"

/* ----------------------------------- */
/* ---------- ParameterInfo ---------- */
/* ----------------------------------- */

// Constructor
ParameterInfo::ParameterInfo(LinkedList<const char*>* names, LinkedList<ParameterType>* types) {

    /*   Validate Length   */

    int namesLength = names->length;
    int typesLength = types->length;

    if (namesLength != typesLength) return;

    this->length = namesLength;


    /*   Find Buffer Length   */

    int bufferLength = 0;

    const char* currentName;

    for (names->iterStart(0); names->iterHasNext(); names->iterNext()) {

        currentName = names->iterGetObj();

        for (int i = 0; currentName[i] != '\0'; i++)
            bufferLength++;

    }

    
    /*   Allocate And Populate Arrays For Names   */

    // This will be passed to the ParameterInfo constructor
    char* buffer = new char[bufferLength];

    // Allocate for names info arrays
    this->namesIndexes = new int[this->length];
    this->namesLengths = new int[this->length];

    // Index pointer for the next free char in the buffer
    int bufferIndex = 0;

    // Stores the index of the string being handled. 
    // Note: NOT the index in the string, but rather the index of the string in the list
    int nameIndex = 0;

    // Stores the length of the current sub string
    int length;
    
    for (names->iterStart(0); names->iterHasNext(); names->iterNext()) {

        currentName = names->iterGetObj();

        // Store starting index of the name
        this->namesIndexes[nameIndex] = bufferIndex;

        // Copy characters over while tracking length
        for (length = 0; currentName[length] != '\0'; length++) {
            buffer[bufferIndex] = currentName[length];
            bufferIndex++;
        }

        // Store the length of the name
        this->namesLengths[nameIndex] = length;

        // Move to next index
        nameIndex++;

    }


    /*   Allocate And Populate Array For Types   */

    // This will be passed to the ParameterInfo constructor
    ParameterType* typesArray = new ParameterType[typesLength];

    // Index pointer for the next slot in the array
    int typesArrayIndex = 0;

    for (types->iterStart(0); types->iterHasNext(); types->iterNext()) {

        typesArray[typesArrayIndex] = types->iterGetObj();
        typesArrayIndex++;

    }

}

// Destructor
ParameterInfo::~ParameterInfo() {

    if (this->names != nullptr) delete[] this->names;

    if (this->namesIndexes != nullptr) delete[] this->namesIndexes;
    if (this->namesLengths != nullptr) delete[] this->namesLengths;

    if (this->types != nullptr) delete[] this->types;

}

// Instance Functions
ParameterType ParameterInfo::matchParameter(const char* name) {

    // Start by finding the length of the requested string
    int nameLength = 0;
    while (name[nameLength] != '\0') {

        // Break after too many chars
        if (nameLength >= MAX_TAG_LENGTH) {

            logWrite("Tried to call ParameterInfo::matchParameter() on too long of a string!", true);
            
            logWrite(" -> Tried string \"");
            logWrite(name);
            logWrite("\" while max length is ");
            logWrite(MAX_TAG_LENGTH, true);
            
            return TYPE_NONE;

        }

        nameLength++;

    }


    // Used for the next loop
    int startIndex;
    int length;

    // Iterate through all stored names
    for (int i = 0; i < this->length; i++) {

        startIndex = this->namesIndexes[i];
        length = this->namesLengths[i];

        // Skip if length differs from requested
        if (length != nameLength) continue;

        // Compare character by character
        bool matches = true;
        for (int j = 0; j < length; j++) {

            if (this->names[j + startIndex] != name[j]) {
                matches = false;
                break;
            }

        }

        // If all characters match, return the corresponding type
        if (matches) {
            return this->types[i];
        }

    }

    // If no match found, return TYPE_NONE
    return TYPE_NONE;

}



/* ------------------------------------------ */
/* ---------- ParameterInfoBuilder ---------- */
/* ------------------------------------------ */

// Constructor
ParameterInfoBuilder::ParameterInfoBuilder() {

    this->names = new LinkedList<const char*>();
    this->types = new LinkedList<ParameterType>();

    return;

}

// Destructor
ParameterInfoBuilder::~ParameterInfoBuilder() {

    delete this->names;
    delete this->types;

    return;

}

// Instance Functions
ParameterInfo* ParameterInfoBuilder::build() {

    ParameterInfo* ret =  new ParameterInfo(this->names, this->types);

    this->reset();

    return ret;

}

void ParameterInfoBuilder::reset() {

    delete this->names;
    delete this->types;

    this->names = new LinkedList<const char*>();
    this->types = new LinkedList<ParameterType>();

}

void ParameterInfoBuilder::addParameter(const char* name, ParameterType type) {

    if (name == nullptr) {
        logWrite("Tried to call ParameterInfoBuilder::addParameter(const char*, int) on a nullptr!", true);
        return;
    }

    this->names->pushBack(name);
    this->types->pushBack(type);

}

void ParameterInfoBuilder::addParameter(char* name, ParameterType type) {
    this->addParameter( (const char*) name, type );
}
