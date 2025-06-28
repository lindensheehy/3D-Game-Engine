#pragma once

#include "util/Utility.h"

#include "xml/XMLFile.h"
#include "xml/ElementSet.h"

#include "ui/Window.h"
#include "ui/WindowElement.h"


namespace Xml {

class XML {

    /*
        This is the indended entry point in this xml module
        
        Two primary responsibilities are handled here:
        - building UI structures: This is the main use case for this class. 
          By passing an XMLFile instance or a file name, this class will create a UI Window or WindowElement
        - element initialization: This object needs to know what elements are valid
          To make it aware of these, call 'initDefaultElements' and/or 'initCustomElements'
    */

    public:

        // Constructor
        XML();

        // Destructor
        ~XML();

        
        /*   Instance Functions   */

        // Populates the element set with all the default elements signatures (see ui/WindowElement)
        void initDefaultElements();

        // Loads all the elements defined in "src/assets/ui/elements/"
        void initCustomElements();

        // Builds a window from a file name
        // This is the primary entry point for this module
        Ui::Window* buildWindow(const char* fileName);

        // Builds an WindowElement object from an XMLFile object
        // The main use case is nested file elements (like if file X uses an element defined in file Y)
        Ui::WindowElement* buildElement(XMLFile* xmlFile);
        

    private:

        /*   Instance Variables   */

        // These are the currently recognized elements (populated by the 'init___Elements' functions)
        ElementSet* elementSet;

        // This is the length that will be used for the parameter buffers when calling buildElement()
        // Its 5 right now because thats the highest amount of params used by any existing element
        static constexpr int PARAMS_BUFFER_SIZE = 5;

        // This is used to limit the recursive calls
        // This defends against circular references by avoiding infinite recursion
        static constexpr int CALL_LIMIT = 32;
        int callCount = 0;

};

}
