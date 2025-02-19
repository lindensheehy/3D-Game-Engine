#include "ui/WindowElement.h"

/* ----------------------------------- */
/* ---------- WindowElement ---------- */
/* ----------------------------------- */

// Static declarations
LinkedList<Action*>* WindowElement::actionQueue;

// Constructor
WindowElement::WindowElement(int posx, int posy, int sizex, int sizey) {

    this->pos = new Vec2(posx, posy);
    this->size = new Vec2(sizex, sizey);

    this->endPos = this->pos->copy()->add(this->size);

    this->children = new LinkedList<WindowElement*>();

    this->id = nullptr;

}

WindowElement::WindowElement(Vec2* pos, Vec2* size) {

    this->pos = pos->copy();
    this->size = size->copy();

    this->endPos = this->pos->copy()->add(this->size);

    this->children = new LinkedList<WindowElement*>();

}

// Destrcutor
WindowElement::~WindowElement() {

    if (this->pos != nullptr) delete this->pos;
    if (this->size != nullptr) delete this->size;

    if (this->endPos != nullptr) delete this->endPos;

    if (this->children != nullptr) {

        if (this->children->length > 0) {
            WindowElement* child;
            for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext()) {
                child = this->children->iterGetObj();
                if (child != nullptr) delete child;
            }
        }
        
        delete this->children;

    }

}

// Instance Functions
void WindowElement::draw(Drawer* drawer, Vec2* offset) {

    // Log becuase this shouldnt ever be called
    logWrite("Called WindowElement->draw()!", true);

}

WindowElement* WindowElement::hitTest(int x, int y, Vec2* offset) {

    Vec2 newPos;
    newPos.set(this->pos);
    newPos.add(offset);

    Vec2 newEndPos;
    newEndPos.set(this->endPos);
    newEndPos.add(offset);

    // Position does not lie within the element
    if (
        x > newEndPos.x ||
        x < newPos.x ||
        y > newEndPos.y ||
        y < newPos.y 
    ) return nullptr;

    // Return this if its interactable
    if (
        this->type == UIEnum::ElementType::BUTTON ||
        this->type == UIEnum::ElementType::DRAGABLE ||
        this->type == UIEnum::ElementType::TEXTINPUT
    ) return this;

    // Check children
    WindowElement* current;
    WindowElement* found = nullptr;
    for (this->children->iterStart(0); this->children->iterHasNext(); this->children->iterNext()) {

        current = this->children->iterGetObj();

        found = current->hitTest(x, y, &newPos);

        if (found != nullptr) break;

    }

    // This may be nullptr if nothing interactable was found, but thats the expected behaviour
    return found;

}

WindowElement* WindowElement::doInput(State* state, Vec2* offset) {

    int x = state->mouse->posX;
    int y = state->mouse->posY;

    bool clickLands = this->hitTest(x, y, offset);
    if (!clickLands) return nullptr;

    // Run the input action (this is nothing for most elements)
    this->onInput(state);

    // Since now the click must lie inside this element, if this is any interactable type, I return this and skip checking the children
    if (this->isInteractable) return this;

    // Otherwise, I will check the children

    WindowElement* current; // The child element checked on the given iteration
    WindowElement* found;   // Stores the clicked element found from the window, or nullptr if none
    Vec2* nextOffset = offset->copy()->add(this->pos);

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext()) {

        current = this->children->iterGetObj();
        found = current->doInput(state, nextOffset);

        if (found != nullptr) return found;

    }

    // If the loop completes, return nullptr
    return nullptr;

}

void WindowElement::addChild(WindowElement* child) {

    this->children->pushBack(child);
    return;

}

void WindowElement::drawChildren(Drawer* drawer, Vec2* offset) {

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext())
        this->children->iterGetObj()->draw(drawer, offset);

}

void WindowElement::setActionQueue(LinkedList<Action*>* queue) {
    WindowElement::actionQueue = queue;
}

void WindowElement::queueAction(Action* action) {
    WindowElement::actionQueue->pushBack(action);
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

    this->type = UIEnum::ElementType::VISUAL;

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

    this->type = UIEnum::ElementType::VISUAL;

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

    this->type = UIEnum::ElementType::VISUAL;

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
WindowCircle::WindowCircle(int posx, int posy, int size, uint32 color) : WindowElement(posx, posy, size, size) {

    this->middle = this->size->copy()->scale(0.5)->add(this->pos);
    this->radius = size;

    this->color = color;

    this->type = UIEnum::ElementType::VISUAL;

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

    this->type = UIEnum::ElementType::VISUAL;

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
WindowTextInput::WindowTextInput(int posx, int posy, int width, const char* id) : WindowElement(posx, posy, width, 12) {

    this->text = new char[this->BUFFERSIZE];
    memset(this->text, '\0', this->BUFFERSIZE); // Initialize all to null chars
    this->length = 0;
    this->cursorPos = -1;

    this->bindType = BindType::NONE;
    this->boundFloat = nullptr;
    this->boundInt = nullptr;

    this->color = Color::WHITE;

    this->type = UIEnum::ElementType::TEXTINPUT;
    this->isInteractable = true;

    this->id = id;

}

// Destructor
WindowTextInput::~WindowTextInput() {
    delete[] this->text;
}

// Instance Functions
void WindowTextInput::draw(Drawer* drawer, Vec2* offset) {

    // Update the internal string
    this->updateString();
    
    Vec2* newOffset = this->pos->copy()->add(offset);

    // Give the text some padding
    newOffset->add(3, 3);
    drawer->drawString(this->color, this->text, newOffset);

    // Draw cursor if needed
    if (this->cursorPos != -1) {

        Vec2* cursorDrawPos = newOffset->copy()->add( (this->cursorPos * 6), 0 );
        Vec2* cursorDrawEndPos = cursorDrawPos->copy()->add(1, 7);

        drawer->drawRectFilled(this->color, cursorDrawPos, cursorDrawEndPos);

        delete cursorDrawPos;
        delete cursorDrawEndPos;

    }

    // Remove the padding before drawing children
    newOffset->sub(3, 3);
    this->drawChildren(drawer, newOffset);

    delete newOffset;

    return;

}

void WindowTextInput::onInput(State* state) {

    if (state->wasLeftJustPressed()) this->cursorPos = this->length;

    KeyCode key;
    char keyChar;

    bool textChanged = false;

    for (int i = 0; i < state->newKeyPressesIndex; i++) {
        
        key = state->newKeyPresses[i];

        keyChar = State::keyCodeToChar(key);

        // If the keyChar is valid, write it to the internal string
        if (keyChar != '\0') {
            
            // Ensure space in the string
            if (this->length < this->BUFFERSIZE) {

                // Make space for the new char
                for (int i = this->length; i >= this->cursorPos; i--)
                    this->text[i+1] = this->text[i];

                this->text[cursorPos] = keyChar;
                this->length++;
                this->cursorPos++;

                textChanged = true;

            }

        }

        switch (key) {

            case KEY_ARROWUP:
                this->cursorPos = 0;
                break;

            case KEY_ARROWDOWN:
                this->cursorPos = this->length;
                break;

            case KEY_ARROWLEFT:
                if (this->cursorPos > 0) this->cursorPos--;
                break;

            case KEY_ARROWRIGHT:
                if (this->cursorPos < this->length) this->cursorPos++;
                break;

            case KEY_BACKSPACE:

                if (this->cursorPos < 1) break;

                // Move everything past the cursor left one space
                // This also overwrites the char at the cursor, so this is the 'backspace'
                for (int i = (this->cursorPos - 1); i < this->length; i++)
                    this->text[i] = this->text[i+1];

                this->text[this->length] = '\0';
                this->length--;
                this->cursorPos--;

                textChanged = true;

                break;


        }

    }

    if (textChanged)
        this->writeToValue();

}

void WindowTextInput::onDeselect() {

    // Hides the cursor
    this->cursorPos = -1;

    return;

}

void WindowTextInput::bind(int* variable) {
    
    this->unbind();

    this->bindType = BindType::INT;
    this->boundInt = variable;

    return;

}

void WindowTextInput::bind(float* variable) {
    
    this->unbind();

    this->bindType = BindType::FLOAT;
    this->boundFloat = variable;

    return;

}

void WindowTextInput::unbind() {

    switch (this->bindType) {

        case BindType::NONE:
            return;

        case BindType::INT:
            this->boundInt = nullptr;
            break;

        case BindType::FLOAT:
            this->boundFloat = nullptr;
            break;

    }

    this->bindType = BindType::NONE;
    return;

}

void WindowTextInput::updateString() {

    if (this->selected) return;

    switch (this->bindType) {

        case BindType::NONE:
            break;

        case BindType::INT:
            intToString(*(this->boundInt), this->text, 128);
            break;

        case BindType::FLOAT:
            floatToString(*(this->boundFloat), this->text, 128, 1);
            break;

    }

    int newLength = 0;
    for (; this->text[newLength] != '\0'; newLength++);

    this->length = newLength;

    return;

}

void WindowTextInput::writeToValue() {

    int intValue;
    float floatValue;

    bool passed;

    switch (this->bindType) {

        case BindType::NONE:
            break;

        case BindType::INT:
            passed = stringToInt(this->text, &intValue, this->BUFFERSIZE);
            if (passed) *(this->boundInt) = intValue;

        case BindType::FLOAT:
            passed = stringToFloat(this->text, &floatValue, this->BUFFERSIZE);
            if (passed) *(this->boundFloat) = floatValue;


    }

}



/* ----------------------------------- */
/* ---------- WindowTexture ---------- */
/* ----------------------------------- */

// Constructor
WindowTexture::WindowTexture(int posx, int posy, int sizex, int sizey, const char* fileName) : WindowElement(posx, posy, sizex, sizey) {
    
    this->texture = texture;

    this->type = UIEnum::ElementType::VISUAL;

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

// Constructors
WindowButton::WindowButton(int posx, int posy, int sizex, int sizey, const char* id) : WindowElement(posx, posy, sizex, sizey) {
    
    this->type = UIEnum::ElementType::BUTTON;
    this->isInteractable = true;

    this->action = nullptr;

    this->id = id;

}

WindowButton::WindowButton(int posx, int posy, int sizex, int sizey, Action* action) : WindowElement(posx, posy, sizex, sizey) {

    this->type = UIEnum::ElementType::BUTTON;
    this->isInteractable = true;

    this->action = action;

    this->id = nullptr;

}

// Destructor
WindowButton::~WindowButton() {
    
    if (this->action != nullptr) delete this->action;

    return;

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

    if (this->action != nullptr) {
        WindowElement::queueAction(this->action);
    }

    return;

}



/* ------------------------------------ */
/* ---------- WindowDragable ---------- */
/* ------------------------------------ */

// Constructors
WindowDragable::WindowDragable(int posx, int posy, int sizex, int sizey, const char* id) : WindowElement(posx, posy, sizex, sizey) {

    this->type = UIEnum::ElementType::DRAGABLE;
    this->isInteractable = true;

    this->posToDrag = nullptr;
    this->endPosToDrag = nullptr;

    this->id = id;

    return;

}

WindowDragable::WindowDragable(int posx, int posy, int sizex, int sizey, Vec2* posToDrag, Vec2* endPosToDrag) : WindowElement(posx, posy, sizex, sizey) {

    this->type = UIEnum::ElementType::DRAGABLE;
    this->isInteractable = true;

    this->posToDrag = posToDrag;
    this->endPosToDrag = endPosToDrag;

    this->id = nullptr;

    return;

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

    this->posToDrag->add(dx, dy);
    this->endPosToDrag->add(dx, dy);

}
