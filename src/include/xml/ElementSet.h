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

        // Constructor
        ElementSet();

        // Destructor
        ~ElementSet();


        /*   Instance Functions   */

        // Returns the ParameterInfo object for the given element
        ParameterInfo* matchElement(const char* elementName);

        // Adds a new element to the set
        void addElement(const char* elementName, ParameterInfo* parameterInfo);

    private:

        /*   Instance Variables   */

        // Holds the name of each element
        LinkedList<const char*>* elementNames;

        // Holds the parameter information for each element
        LinkedList<ParameterInfo*>* elementParams;


};
