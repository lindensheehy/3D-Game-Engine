#include "xml/ElementSet.h"

// Constructor
ElementSet::ElementSet() {

    this->set = new LinkedList<Element*>();

    return;

}

// Destructor
ElementSet::~ElementSet() {

    // Delete strings and ParameterInfo objects from the set
    Element* current;
    for (this->set->iterStart(0); this->set->iterHasNext(); this->set->iterNext()) {

        current = this->set->iterGetObj();

        if (current == nullptr) continue;
        
        if (current->name != nullptr) delete[] current->name;
        if (current->params != nullptr) delete current->params;

    }

    delete this->set;

    return;

}

// Instance Functions
ParameterInfo* ElementSet::matchElement(const char* elementName) {

    // Start by finding the length of the requested string
    int nameLength = 0;
    while (elementName[nameLength] != '\0') {

        // Break after too many chars
        if (nameLength >= MAX_TAG_LENGTH) {

            logWrite("Tried to call ElementSet::matchElement() on too long of a string!", true);
            
            logWrite(" -> Tried string \"");
            logWrite(elementName);
            logWrite("\" while max length is ");
            logWrite(MAX_TAG_LENGTH, true);
            
            return nullptr;

        }

        nameLength++;

    }


    // Iterate through all stored elements
    Element* current;
    for (this->set->iterStart(0); this->set->iterHasNext(); this->set->iterNext()) {

        current = this->set->iterGetObj();

        // Skip if length differs from requested
        if (current->nameLength != nameLength) continue;

        // Compare character by character
        bool matches = true;
        for (int j = 0; j < current->nameLength; j++) {

            if (current->name[j] != elementName[j]) {
                matches = false;
                break;
            }

        }

        // If all characters match, return the cooresponding ParameterInfo object
        if (matches) {
            return current->params;
        }

    }

    // If no match found, return nullptr
    return nullptr;

}

void ElementSet::addElement(const char* elementName, ParameterInfo* parameterInfo) {

    if (elementName == nullptr) {
        logWrite("Called ElementSet::addElement(const char*, ParameterInfo*) with arg1 as nullptr!", true);
        return;
    }

    if (parameterInfo == nullptr) {
        logWrite("Called ElementSet::addElement(const char*, ParameterInfo*) with arg2 as nullptr!", true);
        return;
    }

    /*   Make a copy of the string   */

    // Find length of elementName
    int length = 0;
    while (elementName[length] != '\0') {

        // Break after too many chars
        if (length >= MAX_TAG_LENGTH) {

            logWrite("Tried to call ElementSet::addElement() on too long of a string!", true);
            
            logWrite(" -> Tried string \"");
            logWrite(elementName);
            logWrite("\" while max length is ");
            logWrite(MAX_TAG_LENGTH, true);
            
            return;

        }

        length++;

    }

    char* copy = new char[length];

    memcpy(copy, elementName, length);

    
    // Create and push the new element

    Element* newElement = new Element();
    newElement->name = copy;
    newElement->nameLength = length;
    newElement->params = parameterInfo;

    this->set->pushBack(newElement);

    return;

}

void ElementSet::addElement(const char* elementName, ParameterInfo* parameterInfo) {

    this->addElement( (const char*) elementName, parameterInfo );

    return;

}
