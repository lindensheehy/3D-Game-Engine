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

    // This is the global state of PARAMS tag. 
    // This tells how to treat the string tags and helps validate PARAMS OPEN and CLOSE tags
    PrimitiveTagState paramsTagState = CLOSE;

    // Holds the state of each prim tag for this index
    PrimitiveTagState elementTag;
    PrimitiveTagState paramsTag;
    PrimitiveTagState childrenTag;

    // Holds the string tag for this index
    char* stringTag;
    int stringTagLength;

    // Holds the parameter info for the current element type
    ParameterInfo* parameterInfo;

    // This is the hierarchy stack. opening an element pushes, closing pops
    LinkedList<WindowElement*>* stack = new LinkedList<WindowElement*>();

    // Flag says if the stack was emptied at any point
    // This is okay if it happens once, otherwise theres an issue with the xml file
    // Everything in the <main> section should be inside a single parent element
    bool poppedLast = false;

    // Holds the last popped element. This is also the return value
    WindowElement* lastPopped = nullptr;

    // This holds the current element that is being built
    // Gets built on any of CHILDREN OPEN, ELEMENT CLOSE_OPEN, ELEMENT DOUBLE_CLOSE
    WindowElement* currentElement = nullptr;

    // Loop through tags
    for (int i = 0; i < xmlFile->main->stringTagCount; i++) {

        // Get all the values I need
        elementTag = xmlFile->main->getPrimitiveTag(i, ELEMENT);
        paramsTag = xmlFile->main->getPrimitiveTag(i, PARAMS);
        childrenTag = xmlFile->main->getPrimitiveTag(i, CHILDREN);

        stringTag = xmlFile->main->getStringTag(i, &stringTagLength);

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
        switch (paramsTag) {

            // Default value, do nothing
            case NONE:
                break;

            case OPEN: {

                // This would happen if the last params section was not closed
                if (paramsTagState == OPEN) {
                    logWrite("XMLFile::buildElement() found a PARAMS OPEN tag while params are already open!", true);
                    logWrite(" -> In file \"");
                    logWrite(xmlFile->fileName);
                    logWrite("\" at index ");
                    logWrite(i, true);
                    break;
                }

                paramsTagState = OPEN;

                break;

            }

            case CLOSE: {

                // This would happen if there is no params section open
                if (paramsTagState == CLOSE) {
                    logWrite("XMLFile::buildElement() found a PARAMS CLOSE tag while none was open!", true);
                    logWrite(" -> In file \"");
                    logWrite(xmlFile->fileName);
                    logWrite("\" at index ");
                    logWrite(i, true);
                    break;
                }

                paramsTagState = CLOSE;

                break;

            }
                
            // This could be CLOSE_OPEN, DOUBLE_CLOSE, or an unrecognized tag
            // Regardless, its not allowed
            default: {
                logWrite("XMLFile::buildElement() found an unrecognized tag state!", true);
                logWrite(" -> Type PARAMS = ");
                logWrite( (int) paramsTag, true );
                logWrite(" -> See PrimitiveTagState in \"xml/Core.h\" for details", true);
                break;
            }

        }

        // Step 2: Opening a new element
        if (  elementTag == OPEN  ||  elementTag == CLOSE_OPEN  ) {

            // 

            parameterInfo = this->elementSet->matchElement(stringTag);

            if (parameterInfo == nullptr) {
                // Log error
            }

        }

        // Step 3: Create element if possible
        if (  childrenTag == OPEN  ||  elementTag == CLOSE_OPEN  ||  elementTag == DOUBLE_CLOSE) {
            
            // Cant create an element while the PARAMS section is open
            if (paramsTagState == OPEN) {

            }

            // This is the part where i create the WindowElement object for the xml element
            // This is done by using the data stored in the type buffers, along with the data in ParameterInfo
            // Most elements have in-code constructors, which is all i will be handling for now
            // In the future, custom elements will be created using this same function called on other XMLFile obejcts
            // This can get a bit nested, because its possible for a custom element to contain a custom element, and so on

        }

        // Step 4: CHILDREN tag handling
        switch (childrenTag) {

            // Default value, do nothing
            case NONE:
                break;

            case OPEN: {

                // If currentElement == nullptr, theres a problem in the xml file
                if (currentElement == nullptr) {
                    logWrite("XML::buildElement() is trying to open a children section before having a valid element!", true);
                    logWrite(" -> In file \"");
                    logWrite(xmlFile->fileName);
                    logWrite("\"", true);
                    logWrite(" -> This usually happens if the opening tag for the element has a mistake", true);
                    break;
                }

                // No special handling here, this just always pushes to the stack
                stack->pushBack(currentElement);

                break;

            }

            case CLOSE: {

                // Pop the last item on the stack, and store for further use
                lastPopped = stack->popBack();

                // Check the flag to see if the last element has already been popped
                // In this case, the element creation will not work properly, so log an error
                if (poppedLast) {
                    logWrite("XML::buildElement() found more than one parent element in main!", true);
                    logWrite(" -> In file \"");
                    logWrite(xmlFile->fileName);
                    logWrite("\"", true);
                    logWrite(" -> There should be exactly one parent element holding everything in the <main> tag", true);
                    break;
                }

                // If the length is now 0, the stack has been emptied so set the flag
                if (stack->length == 0) poppedLast = true;

                break;

            }

            // This could be CLOSE_OPEN, DOUBLE_CLOSE, or an unrecognized tag
            // Regardless, its not allowed
            default: {
                logWrite("XMLFile::buildElement() found an unrecognized tag state!", true);
                logWrite(" -> Type CHILDREN = ");
                logWrite( (int) childrenTag, true );
                logWrite(" -> See PrimitiveTagState in \"xml/Core.h\" for details", true);
                break;
            }

        }

        // Step 5: Handle string tags in the PARAMS section
        if (paramsTagState == OPEN) {

            // This is the part where i handle traits
            // there will be a flag that flips back and forth, being 'label' or 'value'
            // Labels should be matched against ParameterInfo
            // Values should be casted into thier types based on the previous match, and stored in the type buffers

        }

    }

    // If lastPopped == nullptr, there was a problem with missing closing tags in the file
    if (lastPopped == nullptr) {

    }

    /*   Clean up   */

    // The stack should be empty by the end
    if (stack->length > 0) {
        // Log error
    }

    delete stack;

    // Return the last popped element
    // If everything went right, this should have everything else in the file as children elements
    return lastPopped;

}

Window* XML::buildWindow(const char* fileName) {
    return nullptr;
}
