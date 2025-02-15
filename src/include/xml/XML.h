#pragma once

#include "util/Utility.h"

#include "xml/XMLFile.h"
#include "xml/ElementSet.h"

#include "ui/UI.h"


class XML {

    /*
        This is the top level class in this xml module
        This serves as a way for XMLFile objects to interact with eachother
        Also provides an easier way to this module to interact with the UI
    */

    public:

        // Constructor
        XML(UI* ui);

        // Destructor
        ~XML();

        
        /*   Instance Functions   */

        // Populates the element set with all the default elements signatures
        void initDefaultElements();

        // Loads all the elements defined in "src/assets/ui/elements/"
        void initCustomElements();

        // Loads the file, creates the window object, and passes it to UI
        int loadWindow(const char* fileName);
        

    private:

        /*   Instance Variables   */

        UI* ui;

        // These are the currently recognized elements
        ElementSet* elementSet;

};
