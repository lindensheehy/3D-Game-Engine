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
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("sizex", TYPE_INT);
    builder->addParameter("sizey", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("div", parameterInfo, ElementSet::DIV);


    /*   WindowLine   */
    builder->addParameter("x1", TYPE_INT);
    builder->addParameter("y1", TYPE_INT);
    builder->addParameter("x2", TYPE_INT);
    builder->addParameter("y2", TYPE_INT);
    builder->addParameter("color", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("line", parameterInfo, ElementSet::LINE);


    /*   WindowFilledRect   */
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("sizex", TYPE_INT);
    builder->addParameter("sizey", TYPE_INT);
    builder->addParameter("color", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("filledRect", parameterInfo, ElementSet::FILLED_RECT);


    /*   WindowOutlinedRect   */
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("sizex", TYPE_INT);
    builder->addParameter("sizey", TYPE_INT);
    builder->addParameter("color", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("outlinedRect", parameterInfo, ElementSet::OUTLINED_RECT);


    /*   WindowCircle   */
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("size", TYPE_INT);
    builder->addParameter("color", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("circle", parameterInfo, ElementSet::CIRCLE);


    /*   WindowTextStatic   */
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("text", TYPE_STRING);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("textStatic", parameterInfo, ElementSet::TEXT_STATIC);


    /*   WindowTextInput   */
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("width", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("textInput", parameterInfo, ElementSet::TEXT_INPUT);


    /*   WindowTexture   */
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("sizex", TYPE_INT);
    builder->addParameter("sizey", TYPE_INT);
    builder->addParameter("color", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("texture", parameterInfo, ElementSet::TEXTURE);


    /*   WindowButton   */
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("sizex", TYPE_INT);
    builder->addParameter("sizey", TYPE_INT);
    builder->addParameter("color", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("texture", parameterInfo, ElementSet::TEXTURE);


    /*   WindowDragable   */
    builder->addParameter("posx", TYPE_INT);
    builder->addParameter("posy", TYPE_INT);
    builder->addParameter("sizex", TYPE_INT);
    builder->addParameter("sizey", TYPE_INT);
    builder->addParameter("color", TYPE_INT);

    parameterInfo = builder->build();
    this->elementSet->addDefaultElement("texture", parameterInfo, ElementSet::TEXTURE);


    // Clean up
    delete builder;

    return;

}

void XML::initCustomElements() {

}

int XML::loadWindow(const char* fileName) {

}
