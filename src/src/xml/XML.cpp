#include "xml/XML.h"

using namespace Xml;


XML::XML() {
    
    this->elementSet = new ElementSet();

    return;

}

XML::~XML() {

    if (this->elementSet != nullptr) delete this->elementSet;

    return;

}

void XML::initDefaultElements() {

    /*   
        This just loads the signature for each element from "ui/WindowElement.h"
        Will need to change this function when adding a new default element
    */

    ParameterInfoBuilder* builder = new ParameterInfoBuilder();
    ParameterInfo* parameterInfo;

    /*   WindowDiv   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("div", parameterInfo, ElementSet::DIV);


    /*   WindowLine   */
    builder->addParameter("x1", TYPE_INT, 0);
    builder->addParameter("y1", TYPE_INT, 1);
    builder->addParameter("x2", TYPE_INT, 2);
    builder->addParameter("y2", TYPE_INT, 3);
    builder->addParameter("color", TYPE_INT, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("line", parameterInfo, ElementSet::LINE);


    /*   WindowFilledRect   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);
    builder->addParameter("color", TYPE_INT, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("filledRect", parameterInfo, ElementSet::FILLED_RECT);


    /*   WindowOutlinedRect   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);
    builder->addParameter("color", TYPE_INT, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("outlinedRect", parameterInfo, ElementSet::OUTLINED_RECT);


    /*   WindowCircle   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("size", TYPE_INT, 2);
    builder->addParameter("color", TYPE_INT, 3);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("circle", parameterInfo, ElementSet::CIRCLE);


    /*   WindowTextStatic   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("text", TYPE_STRING, 2);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("textStatic", parameterInfo, ElementSet::TEXT_STATIC);


    /*   WindowTextInput   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("width", TYPE_INT, 2);
    builder->addParameter("id", TYPE_STRING, 3);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("textInput", parameterInfo, ElementSet::TEXT_INPUT);


    /*   WindowTexture   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);
    builder->addParameter("fileName", TYPE_INT, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("texture", parameterInfo, ElementSet::TEXTURE);


    /*   WindowButton   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);
    builder->addParameter("id", TYPE_STRING, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("button", parameterInfo, ElementSet::BUTTON);


    /*   WindowDragable   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);
    builder->addParameter("id", TYPE_STRING, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("dragable", parameterInfo, ElementSet::DRAGABLE);


    // Clean up
    delete builder;

    return;

}

void XML::initCustomElements() {

    ParameterInfoBuilder* builder = new ParameterInfoBuilder();
    ParameterInfo* parameterInfo;
    XMLFile* xmlFile;
    
    /*                      --- REPLACE THIS LATER ---                          */
    /*   THIS SHOULD DYNAMICALLY USE EVERY XML FILE IN src/assets/ui/elements   */

    // textbox
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("width", TYPE_INT, 2);
    builder->addParameter("id", TYPE_STRING, 3);

    parameterInfo = builder->build();

    xmlFile = new XMLFile("../src/assets/ui/elements/textbox.xml");

    this->elementSet->addCustomElement("textbox", parameterInfo, xmlFile);

    // topbar
    builder->addParameter("width", TYPE_INT, 0);
    builder->addParameter("buttonPos", TYPE_INT, 1);
    builder->addParameter("title", TYPE_STRING, 2);

    parameterInfo = builder->build();

    xmlFile = new XMLFile("../src/assets/ui/elements/topbar.xml");

    this->elementSet->addCustomElement("topbar", parameterInfo, xmlFile);

    // Clean up
    delete builder;

    return;

}

Ui::WindowElement* XML::buildElement(XMLFile* xmlFile) {

    /*
        Yes this function is extremely long
        The main loop here needs to handle A LOT of different things
        This really couldnt be simplified apart from having some single use functions
        Everything is extensively commented, so it should be fairly clear
    */


    // Helper function for error logging
    auto logError = [](const char* message, XMLFile* xmlFile, int index) -> void {

        logWrite("XMLFile::buildElement() ");
        logWrite(message, true);

        logWrite(" -> In file \"");
        logWrite(xmlFile->fileName);
        logWrite("\" at index ");
        logWrite(index, true);

        return;

    };


    // First ill make sure im not over the recursive limit
    if (this->callCount > CALL_LIMIT) {
        logError("hit its recursive call limit!", xmlFile, -1);
        logWrite(" -> This is likely due to circular dependancy. If this is not the case, go update XML::CALL_LIMIT", true);
        return nullptr;
    }

    this->callCount++;


    /*   Set up for the loop   */

    enum ParamState {
        LABEL,
        VALUE
    };

    struct VarContainer {

        // Data for handling the PARAMS section
        ParamState paramState = LABEL;
        ParameterType paramType;
        int paramPosition;

        // Buffers for holding PARAMS for default elements
        int* intBuffer;
        float* floatBuffer;
        char** stringBuffer;

        // Holder variables for each type. These might be put into the buffers above, or passed to XMLFile::setParameter
        int intTemp;
        float floatTemp;

        // Holds the name of the param for custom elements
        char* customParamName;

        // Global state of the PARAMS tag, will equal the last non NONE PARAMS tag
        PrimitiveTagState paramsTagState = CLOSE;

        // Holds the state of each prim tag in each iteration
        PrimitiveTagState elementTag;
        PrimitiveTagState paramsTag;
        PrimitiveTagState childrenTag;

        // Holds the string tag for this iteration
        char* stringTag;
        int stringTagLength;

        // Holds info about the current element being built
        ElementSet::Element* elementInfo;

        // Holds a copy of the XMLFile from elementInfo, that is if its a custom type
        XMLFile* elementXMLFile;

        // This is the hierarchy stack. opening an element pushes, closing pops
        LinkedList<Ui::WindowElement*>* stack = new LinkedList<Ui::WindowElement*>();

        // Flag says if the stack was emptied at any point
        bool poppedLast = false;

        // Holds the last popped element. This is also the return value
        Ui::WindowElement* lastPopped = nullptr;

        // This holds the current element that is being built
        Ui::WindowElement* currentElement = nullptr;

        // This is used to differentiate between a regular return and an error return
        bool error = false;

    };

    VarContainer vars;

    // Buffers for storing PARAMS values
    vars.intBuffer = new int[PARAMS_BUFFER_SIZE];
    vars.floatBuffer = new float[PARAMS_BUFFER_SIZE];
    vars.stringBuffer = new char*[PARAMS_BUFFER_SIZE];

    // Allocate and initialize the strings
    for (int i = 0; i < PARAMS_BUFFER_SIZE; i++) {
        vars.stringBuffer[i] = new char[MAX_TAG_LENGTH];
        memset(vars.stringBuffer[i], '\0', MAX_TAG_LENGTH);
    }


    /*   Loop through the tags   */
    
    for (int i = 0; i < xmlFile->main->stringTagCount; i++) {

        // Get all the values I need
        vars.elementTag = xmlFile->main->getPrimitiveTag(i, ELEMENT);
        vars.paramsTag = xmlFile->main->getPrimitiveTag(i, PARAMS);
        vars.childrenTag = xmlFile->main->getPrimitiveTag(i, CHILDREN);

        vars.stringTag = xmlFile->main->getStringTag(i, &(vars.stringTagLength));

        /*
            Order is important here. 
            - First I check for PARAMS OPEN or PARAMS CLOSE
                - This is the simplest tag, as it just says how to handle the next string tags
            - Second I check if I should create an element
                - the following tags indicate this request:
                    - CHILDREN OPEN
                    - ELEMENT CLOSE_OPEN
                    - ELEMENT DOUBLE_CLOSE
                - If I can create an element, I add it as a child to the element at the top of the stack
            - Third I check if I am opening an element
                - In this case, I match it against the ElementSet to get the cooresponding Element object
                - This essentially just finds the context for how to treat the PARAMS section
            - Fourth I handle CHILDREN tags
                - CHILDREN OPEN pushes the last element to the stack
                - CHILDREN CLOSE pops the top element from the stack
            - Fifth I handle string tags in the params section
        */

        // Step 1: PARAMS tag handling
        switch (vars.paramsTag) {

            // Default value, do nothing
            case NONE:
                break;

            case OPEN: {

                // This would happen if the last params section was not closed
                if (vars.paramsTagState == OPEN) {
                    logError("found a PARAMS OPEN tag while params are already open!", xmlFile, i);
                    vars.error = true;
                    goto end;
                }

                vars.paramsTagState = OPEN;

                break;

            }

            case CLOSE: {

                // This would happen if there is no params section open
                if (vars.paramsTagState == CLOSE) {
                    logError("found a PARAMS CLOSE tag while none was open!", xmlFile, i);
                    vars.error = true;
                    goto end;
                }

                vars.paramsTagState = CLOSE;

                break;

            }
                
            // This should never happen
            default:
                break;

        }

        // Step 2: Create element if possible
        if (  vars.childrenTag == OPEN  ||  vars.elementTag == CLOSE_OPEN  ||  vars.elementTag == DOUBLE_CLOSE) {
            
            if (vars.elementInfo == nullptr) {
                logError("Tried to create en element before finding element context", xmlFile, i);
                vars.error = true;
                goto end;
            }

            // Cant create an element while the PARAMS section is open
            if (vars.paramsTagState == OPEN) {
                logError("is trying to create an element before closing the parameters section!", xmlFile, i);
                vars.error = true;
                goto end;
            }

            bool handled = false;

            switch (vars.elementInfo->type) {

                /*
                    These elements are easier, they dont require any more logic to handle
                */

                // Default elements defined in code
                case ElementSet::DIV:
                    vars.currentElement = new Ui::WindowDiv(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], vars.intBuffer[3]);
                    handled = true;
                    break;

                case ElementSet::LINE:
                    vars.currentElement = new Ui::WindowLine(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], vars.intBuffer[3], vars.intBuffer[4]);
                    handled = true;
                    break;

                case ElementSet::FILLED_RECT:
                    vars.currentElement = new Ui::WindowFilledRect(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], vars.intBuffer[3], vars.intBuffer[4]);
                    handled = true;
                    break;

                case ElementSet::OUTLINED_RECT:
                    vars.currentElement = new Ui::WindowOutlinedRect(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], vars.intBuffer[3], vars.intBuffer[4]);
                    handled = true;
                    break;

                case ElementSet::CIRCLE:
                    vars.currentElement = new Ui::WindowCircle(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], vars.intBuffer[3]);
                    handled = true;
                    break;

                // This is for elements defined in other xml files
                case ElementSet::CUSTOM: {

                    // Try building the element from the cooresponding XMLFile
                    vars.currentElement = this->buildElement(vars.elementXMLFile);

                    // Free the XMLFile that was used to create this element
                    delete vars.elementXMLFile;

                    handled = true;
                    break; 

                }

                // Any other elements are handled in the next block
                default:    
                    break;

            }

            if (!handled) {

                /*
                    The next elements need a new copy of the string argument
                    Otherwise it will be free'd after being passed, causing undefined behaviour
                    it would also reuse the same string pointers between constructor calls, which would just not work without copying
                */

                char* copy = nullptr;
                int length = 0;

                switch (vars.elementInfo->type) {

                    case ElementSet::TEXT_STATIC: {
                        
                        // Find the length of the string argument
                        for (; vars.stringBuffer[2][length] != '\0'; length++) {}

                        // Copy it into a new buffer (including a null terminator)
                        copy = new char[length + 1];
                        memcpy(copy, vars.stringBuffer[2], length);
                        copy[length] = '\0';

                        // Create the element with the copied string
                        vars.currentElement = new Ui::WindowTextStatic(vars.intBuffer[0], vars.intBuffer[1], copy);
                        
                        handled = true;
                        break;
                    
                    }

                    case ElementSet::TEXT_INPUT: {
                        
                        // Find the length of the string argument
                        for (; vars.stringBuffer[3][length] != '\0'; length++) {}

                        // Copy it into a new buffer (including a null terminator)
                        copy = new char[length + 1];
                        memcpy(copy, vars.stringBuffer[3], length);
                        copy[length] = '\0';

                        // Create the element with the copied string
                        vars.currentElement = new Ui::WindowTextInput(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], copy);
                        
                        handled = true;
                        break;
                    
                    }

                    case ElementSet::TEXTURE: {
                        
                        // Find the length of the string argument
                        for (; vars.stringBuffer[4][length] != '\0'; length++) {}

                        // Copy it into a new buffer (including a null terminator)
                        copy = new char[length + 1];
                        memcpy(copy, vars.stringBuffer[4], length);
                        copy[length] = '\0';

                        // Create the element with the copied string
                        vars.currentElement = new Ui::WindowTexture(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], vars.intBuffer[3], copy);
                        
                        handled = true;
                        break;
                    
                    }

                    case ElementSet::BUTTON: {
                        
                        // Find the length of the string argument
                        for (; vars.stringBuffer[4][length] != '\0'; length++) {}

                        // Copy it into a new buffer (including a null terminator)
                        copy = new char[length + 1];
                        memcpy(copy, vars.stringBuffer[4], length);
                        copy[length] = '\0';

                        // Create the element with the copied string
                        vars.currentElement = new Ui::WindowButton(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], vars.intBuffer[3], copy);
                        
                        handled = true;
                        break;
                    
                    }

                    case ElementSet::DRAGABLE: {
                        
                        // Find the length of the string argument
                        for (; vars.stringBuffer[4][length] != '\0'; length++) {}

                        // Copy it into a new buffer (including a null terminator)
                        copy = new char[length + 1];
                        memcpy(copy, vars.stringBuffer[4], length);
                        copy[length] = '\0';

                        // Create the element with the copied string
                        vars.currentElement = new Ui::WindowDragable(vars.intBuffer[0], vars.intBuffer[1], vars.intBuffer[2], vars.intBuffer[3], copy);
                        
                        handled = true;
                        break;
                    
                    }


                    // Should never happen
                    default:
                        break;

                }

            }

            // This means the element was never created
            if (!handled) {
                logError("Failed to create an element!", xmlFile, i);
                logWrite(" -> ElementInfo->type did not match any expected (value was ");
                logWrite( (int) vars.elementInfo->type );
                logWrite(")", true);
                vars.error = true;
                goto end;
            }

            // Add this element as a child to the element at the top of the stack
            // If length == 0, this element is the parent, so do nothing for now
            if (vars.stack->length > 0) {
                vars.stack->getLast()->addChild(vars.currentElement);
            }

            // Wipe the buffers so theres no garbage data
            for (int i = 0; i < PARAMS_BUFFER_SIZE; i++) {
                vars.intBuffer[i] = 0;
                vars.floatBuffer[i] = 0;
                memset(vars.stringBuffer[i], '\0', MAX_TAG_LENGTH);
            }

        }

        // Step 3: Opening a new element
        if (  vars.elementTag == OPEN  ||  vars.elementTag == CLOSE_OPEN  ) {

            // Cant open an element inside the PARAMS section
            if (vars.paramsTagState == OPEN) {
                logError("wants to open an element inside the parameters section!", xmlFile, i);
                logWrite(" -> This is likely a typo in the file", true);
                vars.error = true;
                goto end;
            }

            vars.elementInfo = this->elementSet->matchElement(vars.stringTag);

            if (vars.elementInfo == nullptr) {
                logError("found an unrecognized element name!", xmlFile, i);
                vars.error = true;
                goto end;
            }

            // Make a copy of the inner XMLFile object if its CUSTOM type
            if (vars.elementInfo->type == ElementSet::CUSTOM) {
                vars.elementXMLFile = vars.elementInfo->xmlFile->copy();
            }

            else {
                vars.elementXMLFile = nullptr;
            }

        }

        // Step 4: CHILDREN tag handling
        switch (vars.childrenTag) { 

            // Default value, do nothing
            case NONE:
                break;

            case OPEN: {

                // If currentElement == nullptr, theres a problem in the xml file
                if (vars.currentElement == nullptr) {
                    logError("is trying to open a children section before having a valid element!", xmlFile, i);
                    logWrite(" -> This usually happens if the opening tag for the element has a mistake", true);
                    vars.error = true;
                    goto end;
                }

                // No special handling here, this just always pushes to the stack
                vars.stack->pushBack(vars.currentElement);

                break;

            }

            case CLOSE: {
                
                /*
                    Note: 
                    This code assumes that the closing tags will always match up properly
                    If any dont, the code will still run, but you may get unexpected results
                    Best way to think of this is by treating all closing tags </tag> the same
                */

                // Pop the last item on the stack, and store for further use
                vars.lastPopped = vars.stack->popBack();

                // Check the flag to see if the last element has already been popped
                // In this case, the element creation will not work properly, so log an error
                if (vars.poppedLast) {
                    logError("found more than one parent element in main!", xmlFile, i);
                    logWrite(" -> There should be exactly one parent element holding everything in the <main> tag", true);
                    vars.error = true;
                    goto end;
                }

                // If the length is now 0, the stack has been emptied so set the flag
                if (vars.stack->length == 0) vars.poppedLast = true;

                break;

            }

            // This should never happen
            default:
                break;

        }

        // Step 5: Handle string tags in the PARAMS section
        if (vars.paramsTagState == OPEN) {

            if (vars.elementInfo == nullptr) {
                logError("is trying to parse the PARAMS section before matching an element!", xmlFile, i);
                vars.error = true;
                goto end;
            }

            switch (vars.paramState) {

                case LABEL: {

                    // Handling for CUSTOM elements
                    if (vars.elementInfo->type == ElementSet::CUSTOM) {

                        // Store the param name
                        vars.customParamName = vars.stringTag;

                    }

                    // Handling for default elements
                    else {

                        vars.paramType = vars.elementInfo->params->matchParameter(vars.stringTag, &(vars.paramPosition));

                        if (vars.paramType == TYPE_NONE) {
                            logError("failed to match a parameter name!", xmlFile, i);
                            vars.error = true;
                            goto end;
                        }

                    }

                    vars.paramState = VALUE;

                    break;

                }

                case VALUE: {

                    // Different handling for custom elements PARAMS
                    if (vars.elementInfo->type == ElementSet::CUSTOM) {
                        
                        // Call XMLFile::setParameter
                        vars.elementXMLFile->setParameter(vars.customParamName, vars.stringTag);

                        // Leave early because this block is long
                        vars.paramState = LABEL;
                        break;

                    }

                    // Early return if it will try to put a value in a buffer index out of range
                    if (vars.paramPosition >= PARAMS_BUFFER_SIZE) {
                        logError("wants to put a parameter at a position outside the buffer range!", xmlFile, i);
                        logWrite(" -> Either update XML::initDefaultElements() or XML::PARAMS_BUFFER_SIZE", true);
                        vars.error = true;
                        goto end;
                    }

                    // Need different handling for each type
                    switch (vars.paramType) {

                        case TYPE_INT: {

                            /*   Cast the string value into the temp buffer   */

                            // First try treating as decimal
                            if ( !(stringToInt(vars.stringTag, &(vars.intTemp), MAX_TAG_LENGTH)) ) {

                                // If decimal was invalid, try hex
                                if ( !(stringHexToInt(vars.stringTag, &(vars.intTemp), MAX_TAG_LENGTH)) ) {

                                    // If both were invalid, throw an error
                                    logError("wants to cast a string into an int but cant!", xmlFile, i);
                                    logWrite(" -> String \"");
                                    logWrite(vars.stringTag);
                                    logWrite("\" is interpretable as neither decimal or hex", true);
                                    vars.error = true;
                                    goto end;

                                }

                            }

                            // Store the casted value into the buffer for later use
                            vars.intBuffer[vars.paramPosition] = vars.intTemp;

                            break;

                        }

                        case TYPE_FLOAT: {

                            /*   Cast the string value into the temp buffer   */

                            // First try treating as decimal
                            if ( !(stringToFloat(vars.stringTag, &(vars.floatTemp), MAX_TAG_LENGTH)) ) {

                                // If both were invalid, throw an error
                                logError("wants to cast a string into a float but cant!", xmlFile, i);
                                logWrite(" -> String \"");
                                logWrite(vars.stringTag);
                                logWrite("\" is not interpretable as a float type", true);
                                vars.error = true;
                                goto end;

                            }

                            // Store the casted value into the buffer for later use
                            vars.floatBuffer[vars.paramPosition] = vars.floatTemp;

                            break;

                        }

                        case TYPE_STRING: {

                            /*   Strings are easy because thats the format the data is already in   */

                            // Copy the string tag into the buffer for later use
                            memcpy(vars.stringBuffer[vars.paramPosition], vars.stringTag, vars.stringTagLength);
                            
                            // Null terminate if theres space
                            if (vars.stringTagLength < MAX_TAG_LENGTH) {
                                vars.stringBuffer[vars.paramPosition][vars.stringTagLength + 1] = '\0';
                            }

                            break;

                        }
                        
                        // Unrecognized type
                        default: {
                            logError("failed to match the parameter name to a valid type!", xmlFile, i);
                            vars.error = true;
                            goto end;
                        }

                    }

                    vars.paramState = LABEL;

                    break;

                }

                // Should never happen
                default:
                    break;

            }

        }

    }


    /*   Clean up   */

    end:

    // Free buffers
    delete[] vars.intBuffer;
    delete[] vars.floatBuffer;

    for (int i = 0; i < PARAMS_BUFFER_SIZE; i++)
        delete[] vars.stringBuffer[i];

    delete[] vars.stringBuffer;

    // Delete any items in the stack
    for (vars.stack->iterStart(0); vars.stack->iterHasNext(); vars.stack->iterNext())
        delete vars.stack->iterGetObj();

    delete vars.stack;

    // Decrement the call count now that this function call is done
    this->callCount--;

    // Return nullptr if there was an error
    if (vars.error) return nullptr;

    // Return the last popped element
    // If everything went right, this should have everything else in the file as children elements
    return vars.lastPopped;

}

Ui::Window* XML::buildWindow(const char* fileName) {
    
    Ui::Window* ret = new Ui::Window(0, 0, 0, 0);

    // Build an element from the file
    XMLFile* file = new XMLFile(fileName);
    Ui::WindowElement* contents = this->buildElement(file);
    delete file;

    // Add the element to the window
    ret->addElement(contents);

    return ret;

}
