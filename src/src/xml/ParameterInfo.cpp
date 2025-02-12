#include "xml/ParameterInfo.h"

/* ----------------------------------- */
/* ---------- ParameterInfo ---------- */
/* ----------------------------------- */

// Constructor
ParameterInfo::ParameterInfo(char* names, ParameterType* types, int length) {

}

// Destructor
ParameterInfo::~ParameterInfo() {

}

// Instance Functions
ParameterType ParameterInfo::matchParameter(const char* name) {

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

    int namesLength = this->names->length;
    int typesLength = this->types->length;

    if (namesLength != typesLength) return nullptr;

    int bufferLength = 0;

    const char* currentName;

    for (this->names->iterStart(0); this->names->iterHasNext(); this->names->iterNext()) {

        currentName = this->names->iterGetObj();

        for (int i = 0; currentName[i] != '\0'; i++)
            bufferLength++;

    }

    // This will be passed to the ParameterInfo constructor
    char* buffer = new char[bufferLength];

    // Index pointer for the next free char in the buffer
    int bufferIndex = 0;
    
    for (this->names->iterStart(0); this->names->iterHasNext(); this->names->iterNext()) {

        currentName = this->names->iterGetObj();

        for (int i = 0; currentName[i] != '\0'; i++) {
            buffer[bufferIndex] = currentName[i];
            bufferIndex++;
        }

    }

    // This will be passed to the ParameterInfo constructor
    ParameterType* typesArray = new ParameterType[typesLength];

    // Index pointer for the next slot in the array
    int typesArrayIndex = 0;

    for (this->types->iterStart(0); this->types->iterHasNext(); this->types->iterNext()) {

        typesArray[typesArrayIndex] = this->types->iterGetObj();
        typesArrayIndex++;

    }

    return new ParameterInfo(buffer, typesArray, namesLength);

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
