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

        // Builds an element from an XMLFile object
        // Takes a predefined XMLFile object
        WindowElement* buildElement(XMLFile* xmlFile);

        // Builds a window from a file name
        Window* buildWindow(const char* fileName);
        

    private:

        /*   Instance Variables   */

        UI* ui;

        // These are the currently recognized elements
        ElementSet* elementSet;

        // These buffers are used for creating UI elements
        // They are containers for the arguments that get passed to the in-code constructors
        static constexpr int PARAMS_BUFFER_SIZE = 5;
        int* intBuffer;
        float* floatBuffer;
        char** stringBuffer;    // Each string is MAX_TAG_LENGTH long

        // This is used to limit the recursive calls
        // If there were to be two xml files that both referenced each other, the function would recursively call endlessly
        static constexpr int CALL_LIMIT = 32;
        int callCount;

};
