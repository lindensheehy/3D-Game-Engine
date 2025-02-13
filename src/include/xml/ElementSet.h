#pragma once

#include "util/Utility.h"
#include "util/LinkedList.h"

#include "xml/Core.h"
#include "xml/ParameterInfo.h"


class ElementSet {

    /*  
        This class holds information about the currently recognized xml element names
        This includes the name and the parameter names and types
        This is indended to act like a wrapper for the underlying data
        Intended to simplify the process of matching XML elements to actual UI elements
    */

    public:

        // Helper struct
        struct Element {

            const char* name;
            int nameLength;
        
            ParameterInfo* params;
        
        };

        // Constructor
        ElementSet();

        // Destructor
        ~ElementSet();


        /*   Instance Functions   */

        // Returns the ParameterInfo object for the given element
        ParameterInfo* matchElement(const char* elementName);

        // Adds a new element to the set
        // This will copy elementName into a new allocation. The argument must be handled externally
        // This will not make a copy for parameterInfo, so it should not be used after passing
        void addElement(const char* elementName, ParameterInfo* parameterInfo);
        void addElement(char* elementName, ParameterInfo* parameterInfo);

    private:

        /*   Instance Variables   */

        // Holds the name of each element
        LinkedList<Element*>* set;


};
