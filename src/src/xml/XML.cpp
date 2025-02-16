#include "xml/XML.h"

// Constructor
XML::XML(UI* ui) {

    this->ui = ui;
    this->elementSet = new ElementSet();

    return;

}

// Destructor
XML::~XML() {

    if (this->elementSet != nullptr) delete this->elementSet;

    return;

}

// Instance functions
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

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("textInput", parameterInfo, ElementSet::TEXT_INPUT);


    /*   WindowTexture   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);
    builder->addParameter("color", TYPE_INT, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("texture", parameterInfo, ElementSet::TEXTURE);


    /*   WindowButton   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);
    builder->addParameter("id", TYPE_STRING, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("texture", parameterInfo, ElementSet::TEXTURE);


    /*   WindowDragable   */
    builder->addParameter("posx", TYPE_INT, 0);
    builder->addParameter("posy", TYPE_INT, 1);
    builder->addParameter("sizex", TYPE_INT, 2);
    builder->addParameter("sizey", TYPE_INT, 3);
    builder->addParameter("color", TYPE_INT, 4);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("texture", parameterInfo, ElementSet::TEXTURE);


    // Clean up
    delete builder;

    return;

}

void XML::initCustomElements() {

}

WindowElement* XML::buildElement(XMLFile* xmlFile) {

    /*
        Yes this function is extremely long
        Yes it is mostly error logging
        Thats just the price of having specific error logging I suppose
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

        // Buffers for holding PARAMS
        int* intBuffer;
        float* floatBuffer;
        char** stringBuffer;

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

        // This is the hierarchy stack. opening an element pushes, closing pops
        LinkedList<WindowElement*>* stack = new LinkedList<WindowElement*>();

        // Flag says if the stack was emptied at any point
        bool poppedLast = false;

        // Holds the last popped element. This is also the return value
        WindowElement* lastPopped = nullptr;

        // This holds the current element that is being built
        WindowElement* currentElement = nullptr;

        // This is used to differentiate between a regular return and an error return
        bool error = false;

    };

    VarContainer* vars = new VarContainer();

    // Buffers for storing PARAMS values
    vars->intBuffer = new int[PARAMS_BUFFER_SIZE];
    vars->floatBuffer = new float[PARAMS_BUFFER_SIZE];
    vars->stringBuffer = new char*[PARAMS_BUFFER_SIZE];

    // Allocate and initialize the strings
    for (int i = 0; i < PARAMS_BUFFER_SIZE; i++) {
        vars->stringBuffer[i] = new char[MAX_TAG_LENGTH];
        memset(vars->stringBuffer[i], '\0', MAX_TAG_LENGTH);
    }


    /*   Loop through the tags   */
    
    for (int i = 0; i < xmlFile->main->stringTagCount; i++) {

        // Get all the values I need
        vars->elementTag = xmlFile->main->getPrimitiveTag(i, ELEMENT);
        vars->paramsTag = xmlFile->main->getPrimitiveTag(i, PARAMS);
        vars->childrenTag = xmlFile->main->getPrimitiveTag(i, CHILDREN);

        vars->stringTag = xmlFile->main->getStringTag(i, &(vars->stringTagLength));

        /*
            Order is important here. 
            - First I check for PARAMS OPEN or PARAMS CLOSE
                - This is the simplest tag, as it just says how to handle the next string tags
            - Second I check if I am opening an element
                - In this case, I match it against the ElementSet to get the ParameterInfo
                - This essentially just finds the context for how to treat the PARAMS section
            - Third I check if I should create an element
                - the following tags indicate this request:
                    - CHILDREN OPEN
                    - ELEMENT CLOSE_OPEN
                    - ELEMENT DOUBLE_CLOSE
                - If I can create an element, I add it as a child to the element at the top of the stack
            - Fourth I handle CHILDREN tags
                - CHILDREN OPEN pushes the last element to the stack
                - CHILDREN CLOSE pops the top element from the stack
            - Fifth I handle string tags in the params section
        */

        // Step 1: PARAMS tag handling
        switch (vars->paramsTag) {

            // Default value, do nothing
            case NONE:
                break;

            case OPEN: {

                // This would happen if the last params section was not closed
                if (vars->paramsTagState == OPEN) {
                    logError("found a PARAMS OPEN tag while params are already open!", xmlFile, i);
                    vars->error = true;
                    goto end;
                }

                vars->paramsTagState = OPEN;

                break;

            }

            case CLOSE: {

                // This would happen if there is no params section open
                if (vars->paramsTagState == CLOSE) {
                    logError("found a PARAMS CLOSE tag while none was open!", xmlFile, i);
                    vars->error = true;
                    goto end;
                }

                vars->paramsTagState = CLOSE;

                break;

            }
                
            // This should never happen
            default:
                break;

        }

        // Step 2: Opening a new element
        if (  vars->elementTag == OPEN  ||  vars->elementTag == CLOSE_OPEN  ) {

            // Cant open an element inside the PARAMS section
            if (vars->paramsTagState == OPEN) {
                logError("wants to open an element inside the parameters section!", xmlFile, i);
                logWrite(" -> This is likely a typo in the file", true);
                vars->error = true;
                goto end;
            }

            vars->elementInfo = this->elementSet->matchElement(vars->stringTag);

            if (vars->elementInfo == nullptr) {
                logError("found an unrecognized element name!", xmlFile, i);
                vars->error = true;
                goto end;
            }

        }

        // Step 3: Create element if possible
        if (  vars->childrenTag == OPEN  ||  vars->elementTag == CLOSE_OPEN  ||  vars->elementTag == DOUBLE_CLOSE) {
            
            // Cant create an element while the PARAMS section is open
            if (vars->paramsTagState == OPEN) {
                logError("is trying to create an element before closing the parameters section!", xmlFile, i);
                vars->error = true;
                goto end;
            }

            switch (vars->elementInfo->type) {

                // Default elements defined in code
                case ElementSet::DIV:
                    vars->currentElement = new WindowDiv(intBuffer[0], intBuffer[1], intBuffer[2], intBuffer[3]);
                    break;

                case ElementSet::LINE:
                    vars->currentElement = new WindowLine(intBuffer[0], intBuffer[1], intBuffer[2], intBuffer[3], intBuffer[4]);
                    break;

                case ElementSet::FILLED_RECT:
                    vars->currentElement = new WindowFilledRect(intBuffer[0], intBuffer[1], intBuffer[2], intBuffer[3], intBuffer[4]);
                    break;

                case ElementSet::OUTLINED_RECT:
                    vars->currentElement = new WindowOutlinedRect(intBuffer[0], intBuffer[1], intBuffer[2], intBuffer[3], intBuffer[4]);
                    break;

                case ElementSet::CIRCLE:
                    vars->currentElement = new WindowCircle(intBuffer[0], intBuffer[1], intBuffer[2], intBuffer[3]);
                    break;

                case ElementSet::TEXT_STATIC:
                    vars->currentElement = new WindowTextStatic(intBuffer[0], intBuffer[1], stringBuffer[2]);
                    break;

                case ElementSet::TEXT_INPUT:
                    vars->currentElement = new WindowTextInput(intBuffer[0], intBuffer[1], intBuffer[2], stringBuffer[3]);
                    break;

                case ElementSet::TEXTURE:
                    vars->currentElement = new WindowTexture(intBuffer[0], intBuffer[1], intBuffer[2], intBuffer[3], stringBuffer[4]);
                    break;

                case ElementSet::BUTTON:
                    vars->currentElement = new WindowButton(intBuffer[0], intBuffer[1], intBuffer[2], intBuffer[3], stringBuffer[4]);
                    break;

                case ElementSet::DRAGABLE:
                    vars->currentElement = new WindowDragable(intBuffer[0], intBuffer[1], intBuffer[2], intBuffer[3], stringBuffer[4]);
                    break;
                

                // This is for elements defined in other xml files
                case ElementSet::CUSTOM:
                    vars->currentElement = this->buildElement(vars->elementInfo->xmlFile);
                    break; 


                // Should never happen
                default:
                    break;

            }

        }

        // Step 4: CHILDREN tag handling
        switch (vars->childrenTag) { 

            // Default value, do nothing
            case NONE:
                break;

            case OPEN: {

                // If currentElement == nullptr, theres a problem in the xml file
                if (vars->currentElement == nullptr) {
                    logError("is trying to open a children section before having a valid element!", xmlFile, i);
                    logWrite(" -> This usually happens if the opening tag for the element has a mistake", true);
                    vars->error = true;
                    goto end;
                }

                // No special handling here, this just always pushes to the stack
                vars->stack->pushBack(vars->currentElement);

                break;

            }

            case CLOSE: {

                // Pop the last item on the stack, and store for further use
                vars->lastPopped = vars->stack->popBack();

                // Check the flag to see if the last element has already been popped
                // In this case, the element creation will not work properly, so log an error
                if (vars->poppedLast) {
                    logError("found more than one parent element in main!", xmlFile, i);
                    logWrite(" -> There should be exactly one parent element holding everything in the <main> tag", true);
                    vars->error = true;
                    goto end;
                }

                // If the length is now 0, the stack has been emptied so set the flag
                if (vars->stack->length == 0) vars->poppedLast = true;

                break;

            }

            // This should never happen
            default:
                break;

        }

        // Step 5: Handle string tags in the PARAMS section
        if (vars->paramsTagState == OPEN) {

            // This is the part where i handle traits
            // there will be a flag that flips back and forth, being 'label' or 'value'
            // Labels should be matched against ParameterInfo
            // Values should be casted into thier types based on the previous match, and stored in the type buffers

            if (vars->elementInfo == nullptr) {
                logError("is trying to parse the PARAMS section before matching an element!", xmlFile, i);
                vars->error = true;
                goto end;
            }

            switch (vars->paramState) {

                case LABEL: {

                    // Different handling for custom elements PARAMS
                    if (vars->elementInfo->type == ElementSet::CUSTOM) {

                        break;

                    }

                    vars->paramType = vars->elementInfo->params->matchParameter(vars->stringTag, &(vars->paramPosition));

                    if (vars->paramType == TYPE_NONE) {
                        logError("failed to match a parameter name!", xmlFile, i);
                        vars->error = true;
                        goto end;
                    }

                    vars->paramState = VALUE;

                    break;

                }

                case VALUE: {

                    // Different handling for custom elements PARAMS
                    if (vars->elementInfo->type == ElementSet::CUSTOM) {

                        break;

                    }

                    if (vars->paramPosition >= PARAMS_BUFFER_SIZE) {
                        logError("wants to put a parameter at a position outside the buffer range!", xmlFile, i);
                        logWrite(" -> Either update XML::initDefaultElements() or XML::PARAMS_BUFFER_SIZE", true);
                        vars->error = true;
                        goto end;
                    }

                    switch (vars->paramType) {

                        case TYPE_INT: {

                            break;

                        }

                        case TYPE_FLOAT: {

                            break;

                        }

                        case TYPE_STRING: {

                            break;

                        }
                        
                        // Unrecognized type
                        default: {
                            logError("failed to match the parameter name to a valid type!", xmlFile, i);
                            vars->error = true;
                            goto end;
                        }

                    }

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
    delete[] vars->intBuffer;
    delete[] vars->floatBuffer;

    for (int i = 0; i < PARAMS_BUFFER_SIZE; i++)
        delete[] vars->stringBuffer[i];

    delete[] vars->stringBuffer;

    // Delete any items in the stack
    for (vars->stack->iterStart(0); vars->stack->iterHasNext(); vars->stack->iterNext())
        delete vars->stack->iterGetObj();

    delete vars->stack;

    // Return nullptr if there was an error
    if (vars->error) return nullptr;

    // Return the last popped element
    // If everything went right, this should have everything else in the file as children elements
    return vars->lastPopped;

}

Window* XML::buildWindow(const char* fileName) {
    return nullptr;
}
