#include "xml/ParameterInfo.h"

/* ----------------------------------- */
/* ---------- ParameterInfo ---------- */
/* ----------------------------------- */

// Constructor
ParameterInfo::ParameterInfo(LinkedList<Parameter*>* params) {

    this->length = params->length;


    /*   Find Buffer Length   */

    int bufferLength = 0;

    Parameter* current;

    for (params->iterStart(0); params->iterHasNext(); params->iterNext()) {

        current = params->iterGetObj();

        for (int i = 0; current->name[i] != '\0'; i++)
            bufferLength++;

    }

    
    /*   Allocate And Populate Arrays   */

    // This will be passed to the ParameterInfo constructor
    this->names = new char[bufferLength];

    // Allocate for names info arrays
    this->namesIndexes = new int[this->length];
    this->namesLengths = new int[this->length];

    // Index pointer for the next free char in the buffer
    int bufferIndex = 0;

    // Stores the length of the current sub string
    int length;


    // This will be passed to the ParameterInfo constructor
    this->types = new ParameterType[this->length];

    // Index pointer for the next slot in the array
    int typesArrayIndex = 0;
    

    for (int i = 0;; i++) {

        current = params->getById(i);

        // Break if the id (position) does not exist
        if (current == nullptr) break;

        // Store starting index of the name
        this->namesIndexes[i] = bufferIndex;

        // Copy characters over while tracking length
        for (length = 0; current->name[length] != '\0'; length++) {
            this->names[bufferIndex] = current->name[length];
            bufferIndex++;
        }

        // Store the length of the name
        this->namesLengths[i] = length;

        this->types[i] = current->type;

    }

    return;

}

// Destructor
ParameterInfo::~ParameterInfo() {

    if (this->names != nullptr) delete[] this->names;

    if (this->namesIndexes != nullptr) delete[] this->namesIndexes;
    if (this->namesLengths != nullptr) delete[] this->namesLengths;

    if (this->types != nullptr) delete[] this->types;

}

// Instance Functions
ParameterType ParameterInfo::matchParameter(const char* name, int* positionOut) {

    if (name == nullptr) return TYPE_NONE;
    if (positionOut == nullptr) return TYPE_NONE;

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
            
            *positionOut = -1;
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
            *positionOut = i;
            return this->types[i];
        }

    }

    // If no match found, return TYPE_NONE
    *positionOut = -1;
    return TYPE_NONE;

}



/* ------------------------------------------ */
/* ---------- ParameterInfoBuilder ---------- */
/* ------------------------------------------ */

// Constructor
ParameterInfoBuilder::ParameterInfoBuilder() {

    this->params = new LinkedList<Parameter*>();

    return;

}

// Destructor
ParameterInfoBuilder::~ParameterInfoBuilder() {

    for (this->params->iterStart(0); this->params->iterHasNext(); this->params->iterNext())
        delete this->params->iterGetObj();

    delete this->params;

    return;

}

// Instance Functions
ParameterInfo* ParameterInfoBuilder::build() {

    ParameterInfo* ret =  new ParameterInfo(this->params);

    this->reset();

    return ret;

}

void ParameterInfoBuilder::reset() {

    for (this->params->iterStart(0); this->params->iterHasNext(); this->params->iterNext())
        delete this->params->iterGetObj();

    delete this->params;

    this->params = new LinkedList<Parameter*>();

}

void ParameterInfoBuilder::addParameter(const char* name, ParameterType type, int position) {

    if (name == nullptr) {
        logWrite("Tried to call ParameterInfoBuilder::addParameter(const char*, int) on a nullptr!", true);
        return;
    }

    Parameter* param = new Parameter();
    param->name = name;
    param->type = type;

    this->params->pushBack(param, position);

    return;

}

void ParameterInfoBuilder::addParameter(char* name, ParameterType type, int position) {
    this->addParameter( (const char*) name, type, position );
}
