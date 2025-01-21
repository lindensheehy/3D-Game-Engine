#include "ui/WindowElement.h"

/* ----------------------------------- */
/* ---------- WindowElement ---------- */
/* ----------------------------------- */

// Constructor
WindowElement::WindowElement(int posx, int posy, int sizex, int sizey) {

    this->pos = new Vec2(posx, posy);
    this->size = new Vec2(sizex, sizey);

    this->endPos = this->pos->copy()->add(this->size);

    this->children = new LinkedList<WindowElement*>();

}

// Destrcutor
WindowElement::~WindowElement() {

    if (this->pos != nullptr) delete this->pos;
    if (this->size != nullptr) delete this->size;

    if (this->endPos != nullptr) delete this->endPos;

    if (this->children->length > 0) {
        WindowElement* child;
        for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext()) {
            child = this->children->iterGetObj();
            if (child != nullptr) delete child;
        }
    }
    
    if (this->children != nullptr) delete this->children;

}

// Instance Functions
void WindowElement::draw(Drawer* drawer, Vec2* offset) {

    // Log becuase this shouldnt be called ever
    logWrite("Called WindowElement->draw()!", true);

}

bool WindowElement::hitTest(int x, int y, Vec2* offset) {

    Vec2* newPos = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);

    bool returnValue =  (
        x < newEndPos->x && 
        x > newPos->x &&
        y < newEndPos->y && 
        y > newPos->y 
    );

    delete newPos;
    delete newEndPos;

    return returnValue;

}

WindowElement* WindowElement::doInput(State* state, Vec2* offset) {

    int x = state->mouse->posX;
    int y = state->mouse->posY;

    bool clickLands = this->hitTest(x, y, offset);
    if (!clickLands) return nullptr;

    // Run the input action (this is nothing for most elements)
    this->onInput(state);

    // Since now the click must lie inside this element, if this is any interactable type, I return this and skip checking the children
    if (this->type == BUTTON) return this;
    if (this->type == DRAGABLE) return this;
    if (this->type == TEXTINPUT) return this;

    // Otherwise, I will check the children

    WindowElement* current; // The child element checked on the given iteration
    WindowElement* found;   // Stores the clicked element found from the window, or nullptr if none
    Vec2* nextOffset = offset->copy()->add(this->pos);

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext()) {

        current = this->children->iterGetObj();
        found = current->doInput(state, nextOffset);

        if (found != nullptr) return found;

    }

    // If the loop completes, just return this
    return this;

}

void WindowElement::addChild(WindowElement* child) {

    this->children->pushBack(child);
    return;

}

void WindowElement::drawChildren(Drawer* drawer, Vec2* offset) {

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext())
        this->children->iterGetObj()->draw(drawer, offset);

}

// Class Functions
WindowElement* WindowElement::createTopBar(UI* ui, Window* window, const char* title) {

    // Divider for all the elements
    WindowElement* holder = new WindowDiv(1, 1, window->size->x - 1, 18);

    // Title plus dragable tab
    WindowElement* dragRect = new WindowDragable(0, 0, window->size->x - 19, 18, window);
    WindowElement* topBarColor = new WindowFilledRect(0, 0, window->size->x - 19, 18, Color::LIGHTER);
    WindowElement* titleElement = new WindowTextStatic(6, 6, title);
    
    dragRect->addChild(topBarColor);
    dragRect->addChild(titleElement);

    // The parent element for the close tab button
    WindowElement* CloseButtonElement = new WindowButton(window->size->x - 19, 0, 18, 18, new ActionCloseWindow(ui, window));
    CloseButtonElement->color = Color::RED;

    // Two white lines to form the X on the close tab button
    WindowElement* line1 = new WindowLine(3, 2, 13, 13, Color::WHITE);
    WindowElement* line2 = new WindowLine(15, 2, -13, 13, Color::WHITE);

    // Add the lines to the button
    CloseButtonElement->addChild(line1);
    CloseButtonElement->addChild(line2);

    holder->addChild(dragRect);
    holder->addChild(CloseButtonElement);

    return holder;

}

WindowElement* WindowElement::createTextBox(int posx, int posy, int width, double* valueToWrite) {

    WindowElement* newElement = new WindowFilledRect(posx, posy, width, 12, Color::DARKER);

    newElement->addChild( new WindowOutlinedRect(0, 0, width, 12, Color::ACCENT) );
    newElement->addChild( new WindowTextInput(0, 0, 35, valueToWrite) );

    return newElement;

}



/* ------------------------------- */
/* ---------- WindowDiv ---------- */
/* ------------------------------- */

// Constructor
WindowDiv::WindowDiv(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {}

// Instance Functions
void WindowDiv::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    this->drawChildren(drawer, newOffset);

    delete newOffset;

}



/* -------------------------------- */
/* ---------- WindowLine ---------- */
/* -------------------------------- */

// Constructor
WindowLine::WindowLine(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = VISUAL;

    this->color = color;

}

// Instance Functions
void WindowLine::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);

    drawer->drawLine(this->color, newOffset, newEndPos);
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newEndPos;

}



/* -------------------------------------- */
/* ---------- WindowFilledRect ---------- */
/* -------------------------------------- */

// Constructor
WindowFilledRect::WindowFilledRect(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = VISUAL;

    this->color = color;

}

// Instance Functions
void WindowFilledRect::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);

    drawer->drawRectFilled(this->color, newOffset, newEndPos);
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newEndPos;

}



/* ---------------------------------------- */
/* ---------- WindowOutlinedRect ---------- */
/* ---------------------------------------- */

// Constructor
WindowOutlinedRect::WindowOutlinedRect(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = VISUAL;

    this->color = color;

}

// Instance Functions
void WindowOutlinedRect::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);

    drawer->drawRect(this->color, newOffset, newEndPos);
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newEndPos;

}



/* ---------------------------------- */
/* ---------- WindowCircle ---------- */
/* ---------------------------------- */

// Constructor
WindowCircle::WindowCircle(int posx, int posy, int size) : WindowElement(posx, posy, size, size) {

    this->middle = this->size->copy()->scale(0.5)->add(this->pos);
    this->radius = size;

    this->type = VISUAL;

}

// Destructor
WindowCircle::~WindowCircle() {
    
    if (this->middle != nullptr) delete this->middle;

}

// Instance Functions
void WindowCircle::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newMiddle = this->middle->copy()->add(offset);

    drawer->drawCircle(this->color, newMiddle, this->radius);
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newMiddle;

}



/* -------------------------------------- */
/* ---------- WindowTextStatic ---------- */
/* -------------------------------------- */

// Constructor
WindowTextStatic::WindowTextStatic(int posx, int posy, const char* text) : WindowElement(posx, posy, 0, 0) {
    
    this->text = text;
    this->color = Color::WHITE;

    this->type = VISUAL;

}

// Instance Functions
void WindowTextStatic::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    drawer->drawString(this->color, this->text, newOffset);
    this->drawChildren(drawer, newOffset);

    delete newOffset;

}



/* ------------------------------------- */
/* ---------- WindowTextInput ---------- */
/* ------------------------------------- */

// Constructor
WindowTextInput::WindowTextInput(int posx, int posy, int width, double* valueToWrite) : WindowElement(posx, posy, width, 12) {

    this->text = new char[this->BUFFERSIZE];
    this->length = 0;
    this->valueToWrite = valueToWrite;

    this->color = Color::WHITE;

}

// Destructor
WindowTextInput::~WindowTextInput() {
    delete[] this->text;
}

// Instance Functions
void WindowTextInput::draw(Drawer* drawer, Vec2* offset) {

    doubleToString(*(this->valueToWrite), this->text, 128, 1);
    
    Vec2* newOffset = this->pos->copy()->add(offset);

    // Give the text some padding
    newOffset->add(3, 3);
    drawer->drawString(this->color, this->text, newOffset);

    // Remove the padding before drawing children
    newOffset->sub(3, 3);
    this->drawChildren(drawer, newOffset);

    delete newOffset;

}

void WindowTextInput::onInput(State* state) {

    if (state->wasLeftJustPressed()) this->cursorPos = this->length;

}

void WindowTextInput::hideCursor() {

    this->cursorPos = -1;

}

void WindowTextInput::writeToValue() {

}



/* ----------------------------------- */
/* ---------- WindowTexture ---------- */
/* ----------------------------------- */

// Constructor
WindowTexture::WindowTexture(int posx, int posy, int sizex, int sizey, PNG* texture) : WindowElement(posx, posy, sizex, sizey) {
    
    this->texture = texture;

    this->type = VISUAL;

}

// Instance Functions
void WindowTexture::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    drawer->drawpng(this->texture, newOffset);
    this->drawChildren(drawer, newOffset);

    delete newOffset;

}



/* ---------------------------------- */
/* ---------- WindowButton ---------- */
/* ---------------------------------- */

// Constructor
WindowButton::WindowButton(int posx, int posy, int sizex, int sizey, Action* action) : WindowElement(posx, posy, sizex, sizey) {

    this->type = BUTTON;

    this->action = action;

}

// Instance Functions
void WindowButton::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);

    drawer->drawRectFilled(this->color, newOffset, newEndPos);
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newEndPos;

}

void WindowButton::onInput(State* state) {

    if (state->wasLeftJustPressed())
        this->action->run();

}



/* ------------------------------------ */
/* ---------- WindowDragable ---------- */
/* ------------------------------------ */

// Constructor
WindowDragable::WindowDragable(int posx, int posy, int sizex, int sizey, Window* windowToDrag) : WindowElement(posx, posy, sizex, sizey) {

    this->type = DRAGABLE;

    this->windowToDrag = windowToDrag;

}

// Instance Functions
void WindowDragable::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    this->drawChildren(drawer, newOffset);

    delete newOffset;

}

void WindowDragable::onInput(State* state) {

    int dx = state->deltaMousePosX();
    int dy = state->deltaMousePosY();

    this->windowToDrag->pos->add(dx, dy);
    this->windowToDrag->endPos->add(dx, dy);

}