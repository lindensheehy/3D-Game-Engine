#pragma once

#include "util/Utility.h"
#include "util/LinkedList.h"

#include "xml/Core.h"
#include "xml/XMLFile.h"
#include "xml/ParameterInfo.h"


namespace Xml {

class ElementSet {

    /*  
        This class holds information about the currently recognized xml element names
        This includes the name and the parameter names and types
        This is indended to act like a wrapper for the underlying data
        Intended to simplify the process of matching XML elements to actual UI elements
    */

    public:

        // This defines what type the element is
        enum ElementType {

            // Default types that have constructors in the code
            DIV,
            LINE,
            FILLED_RECT,
            OUTLINED_RECT,
            CIRCLE,
            TEXT_STATIC,
            TEXT_INPUT,
            TEXTURE,
            BUTTON,
            DRAGABLE,

            // This will be used for any element defined in an xml file
            // Theres different handling for these
            CUSTOM
            
        };

        // Helper struct
        struct Element {

            const char* name;
            int nameLength;
        
            ParameterInfo* params;

            ElementType type;

            // Will contain nullptr unless type == CUSTOM
            XMLFile* xmlFile = nullptr;
        
        };

        // Constructor
        ElementSet();

        // Destructor
        ~ElementSet();


        /*   Instance Functions   */

        // Returns the ParameterInfo object for the given element
        Element* matchElement(const char* elementName);

        // Adds a new element to the set. This assumes the element exists in the code
        // This will copy elementName into a new allocation. The argument must be handled externally
        // This will not make a copy for parameterInfo, so it should not be used after passing
        void addDefaultElement(const char* elementName, ParameterInfo* parameterInfo, ElementType type);
        void addDefaultElement(char* elementName, ParameterInfo* parameterInfo, ElementType type);

        // Adds a new element to the set. This assumes the element exists in XML
        // This will copy elementName into a new allocation. The argument must be handled externally
        // This will not make a copy for parameterInfo, so it should not be used after passing
        void addCustomElement(const char* elementName, ParameterInfo* parameterInfo, XMLFile* elementXml);
        void addCustomElement(char* elementName, ParameterInfo* parameterInfo, XMLFile* elementXml);

    private:

        /*   Instance Variables   */

        // Holds the name of each element
        LinkedList<Element*>* set;


};

}
