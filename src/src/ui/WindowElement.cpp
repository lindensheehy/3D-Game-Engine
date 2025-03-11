#include "ui/WindowElement.h"

/* ----------------------------------- */
/* ---------- WindowElement ---------- */
/* ----------------------------------- */

// Static declarations
LinkedList<Ui::Action*>* Ui::WindowElement::actionQueue;

// Constructor
Ui::WindowElement::WindowElement(int posx, int posy, int sizex, int sizey) {

    this->pos = new Vec2(posx, posy);
    this->size = new Vec2(sizex, sizey);

    this->endPos = this->pos->copy()->add(this->size);

    this->children = new LinkedList<WindowElement*>();

    this->id = nullptr;

}

Ui::WindowElement::WindowElement(Vec2* pos, Vec2* size) {

    this->pos = pos->copy();
    this->size = size->copy();

    this->endPos = this->pos->copy()->add(this->size);

    this->children = new LinkedList<WindowElement*>();

}

// Destrcutor
Ui::WindowElement::~WindowElement() {

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

    // All ids should be heap allocated. This will crash otherwise
    // Then again, WindowElement objects should never be created directly without the help of XML
    if (this->id != nullptr) delete id;

}

// Instance Functions
void Ui::WindowElement::draw(Gui::Drawer* drawer, Vec2* offset) {

    // Log becuase this shouldnt ever be called
    logWrite("Called WindowElement->draw()!", true);

}

Ui::WindowElement* Ui::WindowElement::hitTest(int x, int y, Vec2* offset) {

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
        this->type == Ui::ElementType::BUTTON ||
        this->type == Ui::ElementType::DRAGABLE ||
        this->type == Ui::ElementType::TEXTINPUT
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

Ui::WindowElement* Ui::WindowElement::doInput(Gui::State* state, Vec2* offset) {

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

void Ui::WindowElement::setPos(int x, int y) {

    this->pos->set(x, y);

    this->endPos->set(this->size);
    this->endPos->add(x, y);

}

void Ui::WindowElement::setPos(Vec2* newPos) {
    this->setPos( (int) newPos->x, (int) newPos->y );
}

void Ui::WindowElement::addChild(WindowElement* child) {

    this->children->pushBack(child);
    return;

}

void Ui::WindowElement::drawChildren(Gui::Drawer* drawer, Vec2* offset) {

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext())
        this->children->iterGetObj()->draw(drawer, offset);

}

void Ui::WindowElement::setActionQueue(LinkedList<Action*>* queue) {
    WindowElement::actionQueue = queue;
}

void Ui::WindowElement::queueAction(Action* action) {
    WindowElement::actionQueue->pushBack(action);
}



/* ------------------------------- */
/* ---------- WindowDiv ---------- */
/* ------------------------------- */

// Constructor
Ui::WindowDiv::WindowDiv(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {}

// Instance Functions
void Ui::WindowDiv::draw(Gui::Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    this->drawChildren(drawer, newOffset);

    delete newOffset;

}



/* -------------------------------- */
/* ---------- WindowLine ---------- */
/* -------------------------------- */

// Constructor
Ui::WindowLine::WindowLine(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = Ui::ElementType::VISUAL;

    this->color = color;

}

// Instance Functions
void Ui::WindowLine::draw(Gui::Drawer* drawer, Vec2* offset) {

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
Ui::WindowFilledRect::WindowFilledRect(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = Ui::ElementType::VISUAL;

    this->color = color;

}

// Instance Functions
void Ui::WindowFilledRect::draw(Gui::Drawer* drawer, Vec2* offset) {

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
Ui::WindowOutlinedRect::WindowOutlinedRect(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = Ui::ElementType::VISUAL;

    this->color = color;

}

// Instance Functions
void Ui::WindowOutlinedRect::draw(Gui::Drawer* drawer, Vec2* offset) {

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
Ui::WindowCircle::WindowCircle(int posx, int posy, int size, uint32 color) : WindowElement(posx, posy, size, size) {

    this->middle = this->size->copy()->scale(0.5)->add(this->pos);
    this->radius = size;

    this->color = color;

    this->type = Ui::ElementType::VISUAL;

}

// Destructor
Ui::WindowCircle::~WindowCircle() {
    
    if (this->middle != nullptr) delete this->middle;

}

// Instance Functions
void Ui::WindowCircle::draw(Gui::Drawer* drawer, Vec2* offset) {

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
Ui::WindowTextStatic::WindowTextStatic(int posx, int posy, char* text) : WindowElement(posx, posy, 0, 0) {
    
    this->text = text;
    this->color = Color::WHITE;

    this->type = Ui::ElementType::VISUAL;

}

// Destructor
Ui::WindowTextStatic::~WindowTextStatic() {

    // this->text should be heap allocated. This will crash otherwise
    // Then again, WindowElement objects should never be created directly without the help of XML
    if (this->text != nullptr) delete this->text;

}

// Instance Functions
void Ui::WindowTextStatic::draw(Gui::Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    drawer->drawString(this->color, this->text, newOffset);
    this->drawChildren(drawer, newOffset);

    delete newOffset;

}



/* ------------------------------------- */
/* ---------- WindowTextInput ---------- */
/* ------------------------------------- */

// Constructor
Ui::WindowTextInput::WindowTextInput(int posx, int posy, int width, char* id) : WindowElement(posx, posy, width, 12) {

    this->text = new char[this->BUFFERSIZE];
    memset(this->text, '\0', this->BUFFERSIZE); // Initialize all to null chars
    this->length = 0;
    this->cursorPos = -1;

    this->bindType = BindType::NONE;
    this->boundFloat = nullptr;
    this->boundInt = nullptr;

    this->color = Color::WHITE;

    this->type = Ui::ElementType::TEXTINPUT;
    this->isInteractable = true;

    this->id = id;

}

// Destructor
Ui::WindowTextInput::~WindowTextInput() {
    delete[] this->text;
}

// Instance Functions
void Ui::WindowTextInput::draw(Gui::Drawer* drawer, Vec2* offset) {

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

void Ui::WindowTextInput::onInput(Gui::State* state) {

    if (state->wasLeftJustPressed()) this->cursorPos = this->length;

    KeyCode key;
    char keyChar;

    bool textChanged = false;

    for (int i = 0; i < state->newKeyPressesIndex; i++) {
        
        key = state->newKeyPresses[i];

        keyChar = Gui::keyCodeToChar(key);

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

            case KeyCode::ARROWUP:
                this->cursorPos = 0;
                break;

            case KeyCode::ARROWDOWN:
                this->cursorPos = this->length;
                break;

            case KeyCode::ARROWLEFT:
                if (this->cursorPos > 0) this->cursorPos--;
                break;

            case KeyCode::ARROWRIGHT:
                if (this->cursorPos < this->length) this->cursorPos++;
                break;

            case KeyCode::BACKSPACE:

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

void Ui::WindowTextInput::onDeselect() {

    // Hides the cursor
    this->cursorPos = -1;

    return;

}

void Ui::WindowTextInput::bind(int* variable) {
    
    this->unbind();

    this->bindType = BindType::INT;
    this->boundInt = variable;

    return;

}

void Ui::WindowTextInput::bind(float* variable) {
    
    this->unbind();

    this->bindType = BindType::FLOAT;
    this->boundFloat = variable;

    return;

}

void Ui::WindowTextInput::unbind() {

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

void Ui::WindowTextInput::updateString() {

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

void Ui::WindowTextInput::writeToValue() {

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
Ui::WindowTexture::WindowTexture(int posx, int posy, int sizex, int sizey, const char* fileName) : WindowElement(posx, posy, sizex, sizey) {

    this->type = Ui::ElementType::VISUAL;

    /*   Insert PNG handling here   */

    return;

}

// Destructor
Ui::WindowTexture::~WindowTexture() {

}

// Instance Functions
void Ui::WindowTexture::draw(Gui::Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    /* Insert PNG drawing logic here */

    this->drawChildren(drawer, newOffset);

    delete newOffset;

}



/* ---------------------------------- */
/* ---------- WindowButton ---------- */
/* ---------------------------------- */

// Constructors
Ui::WindowButton::WindowButton(int posx, int posy, int sizex, int sizey, char* id) : WindowElement(posx, posy, sizex, sizey) {
    
    this->type = Ui::ElementType::BUTTON;
    this->isInteractable = true;

    this->action = nullptr;

    this->id = id;

}

Ui::WindowButton::WindowButton(int posx, int posy, int sizex, int sizey, Action* action) : WindowElement(posx, posy, sizex, sizey) {

    this->type = Ui::ElementType::BUTTON;
    this->isInteractable = true;

    this->action = action;

    this->id = nullptr;

}

// Destructor
Ui::WindowButton::~WindowButton() {
    
    if (this->action != nullptr) delete this->action;

    return;

}

// Instance Functions
void Ui::WindowButton::draw(Gui::Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);
    
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newEndPos;

}

void Ui::WindowButton::onInput(Gui::State* state) {

    if (state->wasLeftJustPressed()) {

        if (this->action != nullptr) {
            WindowElement::queueAction(this->action);
        }

    }
    
    return;

}

void Ui::WindowButton::bind(Action* action) {

    // Free old action if there was one
    if (this->action != nullptr) delete this->action;

    this->action = action;

}



/* ------------------------------------ */
/* ---------- WindowDragable ---------- */
/* ------------------------------------ */

// Constructors
Ui::WindowDragable::WindowDragable(int posx, int posy, int sizex, int sizey, char* id) : WindowElement(posx, posy, sizex, sizey) {

    this->type = Ui::ElementType::DRAGABLE;
    this->isInteractable = true;

    this->posToDrag = nullptr;
    this->endPosToDrag = nullptr;

    this->id = id;

    return;

}

Ui::WindowDragable::WindowDragable(int posx, int posy, int sizex, int sizey, Vec2* posToDrag, Vec2* endPosToDrag) : WindowElement(posx, posy, sizex, sizey) {

    this->type = Ui::ElementType::DRAGABLE;
    this->isInteractable = true;

    this->posToDrag = posToDrag;
    this->endPosToDrag = endPosToDrag;

    this->id = nullptr;

    return;

}

// Instance Functions
void Ui::WindowDragable::draw(Gui::Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    this->drawChildren(drawer, newOffset);

    delete newOffset;

}

void Ui::WindowDragable::onInput(Gui::State* state) {

    if (this->posToDrag == nullptr || this->endPosToDrag == nullptr) return;

    int dx = state->deltaMousePosX();
    int dy = state->deltaMousePosY();

    this->posToDrag->add(dx, dy);
    this->endPosToDrag->add(dx, dy);

}

void Ui::WindowDragable::bind(Vec2* posToDrag, Vec2* endPosToDrag) {

    this->posToDrag = posToDrag;
    this->endPosToDrag = endPosToDrag;

}
