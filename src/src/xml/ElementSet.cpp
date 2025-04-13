#include "xml/ElementSet.h"

using namespace Xml;


ElementSet::ElementSet() {

    this->set = new LinkedList<Element*>();

    return;

}

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

ElementSet::Element* ElementSet::matchElement(const char* elementName) {

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
            return current;
        }

    }

    // If no match found, return nullptr
    return nullptr;

}

void ElementSet::addDefaultElement(const char* elementName, ParameterInfo* parameterInfo, ElementType type) {

    // Error checks
    if (elementName == nullptr) {
        logWrite("Called ElementSet::addDefaultElement(const char*, ParameterInfo*, ElementType) with arg1 as nullptr!", true);
        return;
    }

    if (parameterInfo == nullptr) {
        logWrite("Called ElementSet::addDefaultElement(const char*, ParameterInfo*, ElementType) with arg2 as nullptr!", true);
        return;
    }

    if (type == CUSTOM) {
        logWrite("Cannot call ElementSet::addDefaultElement() with type == CUSTOM!", true);
        logWrite(" -> See ElementSet::ElementType for details", true);
        return;
    }

    // Find length of elementName
    int length = getTagLength(elementName);

    if (length < 0) {

        logWrite("Tried to call ElementSet::addDefaultElement() on too long of a string!", true);
        
        logWrite(" -> Tried string \"");
        logWrite(elementName);
        logWrite("\" while max length is ");
        logWrite(MAX_TAG_LENGTH, true);
        
        return;

    }

    // Create a copy of the string
    char* copy = new char[length];
    memcpy(copy, elementName, length);
    
    // Create and push the new element
    Element* newElement = new Element();
    newElement->name = copy;
    newElement->nameLength = length;
    newElement->params = parameterInfo;
    newElement->type = type;

    this->set->pushBack(newElement);

    return;

}

void ElementSet::addDefaultElement(char* elementName, ParameterInfo* parameterInfo, ElementType type) {

    this->addDefaultElement( (const char*) elementName, parameterInfo, type );

    return;

}

void ElementSet::addCustomElement(const char* elementName, ParameterInfo* parameterInfo, XMLFile* elementXML) {

    // Error checks
    if (elementName == nullptr) {
        logWrite("Called ElementSet::addCustomElement(const char*, ParameterInfo*, XMLFile*) with arg1 as nullptr!", true);
        return;
    }

    if (parameterInfo == nullptr) {
        logWrite("Called ElementSet::addCustomElement(const char*, ParameterInfo*, XMLFile*) with arg2 as nullptr!", true);
        return;
    }

    if (elementXML == nullptr) {
        logWrite("Called ElementSet::addCustomElement(const char*, ParameterInfo*, XMLFile*) with arg3 as nullptr!", true);
        return;
    }

    // Find length of elementName
    int length = getTagLength(elementName);

    if (length < 0) {

        logWrite("Tried to call ElementSet::addCustomElement() on too long of a string!", true);
        
        logWrite(" -> Tried string \"");
        logWrite(elementName);
        logWrite("\" while max length is ");
        logWrite(MAX_TAG_LENGTH, true);
        
        return;

    }

    // Create a copy of the string
    char* copy = new char[length];
    memcpy(copy, elementName, length);
    
    // Create and push the new element
    Element* newElement = new Element();
    newElement->name = copy;
    newElement->nameLength = length;
    newElement->params = parameterInfo;
    newElement->type = CUSTOM;
    newElement->xmlFile = elementXML;

    this->set->pushBack(newElement);

    return;

}

void ElementSet::addCustomElement(char* elementName, ParameterInfo* parameterInfo, XMLFile* elementXML) {

    this->addCustomElement( (const char*) elementName, parameterInfo, elementXML );

    return;

}
