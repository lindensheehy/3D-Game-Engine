#include "xml/ParameterInfo.h"

using namespace Xml;


/* ----------------------------------- */
/* ---------- ParameterInfo ---------- */
/* ----------------------------------- */

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

    this->types = new ParameterType[this->length];

    // Index pointer for the next slot in the 'types' array
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

ParameterInfo::~ParameterInfo() {

    delete[] this->names;
    delete[] this->namesIndexes;
    delete[] this->namesLengths;
    delete[] this->types;

    return;

}

ParameterType ParameterInfo::matchParameter(const char* name, int* positionOut) const {

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

ParameterInfoBuilder::ParameterInfoBuilder() {

    this->params = new LinkedList<Parameter*>();

    return;

}

ParameterInfoBuilder::~ParameterInfoBuilder() {

    for (this->params->iterStart(0); this->params->iterHasNext(); this->params->iterNext()) {
        delete this->params->iterGetObj();
    }

    delete this->params;

    return;

}

ParameterInfo* ParameterInfoBuilder::build() {

    ParameterInfo* ret =  new ParameterInfo(this->params);

    this->reset();

    return ret;

}

void ParameterInfoBuilder::reset() {

    for (this->params->iterStart(0); this->params->iterHasNext(); this->params->iterNext()) {
        delete this->params->iterGetObj();
    }

    delete this->params;

    this->params = new LinkedList<Parameter*>();

    return;

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
