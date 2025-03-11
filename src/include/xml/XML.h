#pragma once

#include "util/Utility.h"

#include "xml/XMLFile.h"
#include "xml/ElementSet.h"

#include "ui/Window.h"
#include "ui/WindowElement.h"


class XML {

    /*
        This is the top level class in this xml module
        This serves as a way for XMLFile objects to interact with eachother
        Also provides an easier way to this module to interact with the UI
    */

    public:

        // Constructor
        XML();

        // Destructor
        ~XML();

        
        /*   Instance Functions   */

        // Populates the element set with all the default elements signatures
        void initDefaultElements();

        // Loads all the elements defined in "src/assets/ui/elements/"
        void initCustomElements();

        // Builds an element from an XMLFile object
        // Takes a predefined XMLFile object
        Ui::WindowElement* buildElement(XMLFile* xmlFile);

        // Builds a window from a file name
        Ui::Window* buildWindow(const char* fileName);
        

    private:

        /*   Instance Variables   */

        // These are the currently recognized elements
        ElementSet* elementSet;

        // This is the length that will be used for the parameter buffers when calling buildElement()
        static constexpr int PARAMS_BUFFER_SIZE = 5;

        // This is used to limit the recursive calls
        // If there were to be two xml files that both referenced each other, the function would recursively call endlessly
        static constexpr int CALL_LIMIT = 32;
        int callCount;

};
