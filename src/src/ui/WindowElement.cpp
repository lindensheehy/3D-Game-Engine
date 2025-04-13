#include "ui/WindowElement.h"

using namespace Ui;


/* ----------------------------------- */
/* ---------- WindowElement ---------- */
/* ----------------------------------- */

LinkedList<Action*>* WindowElement::actionQueue;

WindowElement::WindowElement(int posx, int posy, int sizex, int sizey) {

    this->pos.set(posx, posy);
    this->size.set(sizex, sizey);

    this->endPos.set(this->pos).add(this->size);

    this->children = new LinkedList<WindowElement*>();

    this->id = nullptr;

}

WindowElement::WindowElement(Geometry::Vec2* pos, Geometry::Vec2* size) {

    this->pos.set(pos);
    this->size.set(size);

    this->endPos.set(this->pos).add(this->size);

    this->children = new LinkedList<WindowElement*>();

}

WindowElement::~WindowElement() {

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

void WindowElement::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    // Log becuase this shouldnt ever be called
    logWrite("Called WindowElement->draw()!", true);

}

WindowElement* WindowElement::hitTest(int x, int y, Geometry::Vec2* offset) {

    Geometry::Vec2 newPos;
    newPos.set(this->pos);
    newPos.add(offset);

    Geometry::Vec2 newEndPos;
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
        this->type == ElementType::BUTTON ||
        this->type == ElementType::DRAGABLE ||
        this->type == ElementType::TEXTINPUT
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

WindowElement* WindowElement::doInput(Graphics::Gui::State* state, Geometry::Vec2* offset) {

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
    Geometry::Vec2 nextOffset;
    nextOffset.set(offset).add(this->pos);

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext()) {

        current = this->children->iterGetObj();
        found = current->doInput(state, &(nextOffset));

        if (found != nullptr) return found;

    }

    // If the loop completes, return nullptr
    return nullptr;

}

void WindowElement::setPos(int x, int y) {

    this->pos.set(x, y);

    this->endPos.set(this->size);
    this->endPos.add(x, y);

}

void WindowElement::setPos(Geometry::Vec2* newPos) {
    this->setPos( (int) newPos->x, (int) newPos->y );
}

void WindowElement::addChild(WindowElement* child) {

    this->children->pushBack(child);
    return;

}

void WindowElement::drawChildren(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

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

WindowDiv::WindowDiv(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {}

void WindowDiv::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    this->drawChildren(drawer, &(newOffset));

    return;

}



/* -------------------------------- */
/* ---------- WindowLine ---------- */
/* -------------------------------- */

WindowLine::WindowLine(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = ElementType::VISUAL;

    this->color = color;

}

void WindowLine::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    Geometry::Vec2 newEndPos;
    newEndPos.set(this->endPos).add(offset);

    drawer->drawLine(this->color, newOffset.x, newOffset.y, newEndPos.x, newEndPos.y);
    this->drawChildren(drawer, &(newOffset));

    return;

}



/* -------------------------------------- */
/* ---------- WindowFilledRect ---------- */
/* -------------------------------------- */

WindowFilledRect::WindowFilledRect(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = ElementType::VISUAL;

    this->color = color;

}

void WindowFilledRect::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    Geometry::Vec2 newEndPos;
    newEndPos.set(this->endPos).add(offset);

    drawer->drawRectFilled(this->color, newOffset.x, newOffset.y, newEndPos.x, newEndPos.y);
    this->drawChildren(drawer, &(newOffset));

    return;

}



/* ---------------------------------------- */
/* ---------- WindowOutlinedRect ---------- */
/* ---------------------------------------- */

WindowOutlinedRect::WindowOutlinedRect(int posx, int posy, int sizex, int sizey, uint32 color) : WindowElement(posx, posy, sizex, sizey) {

    this->type = ElementType::VISUAL;

    this->color = color;

}

void WindowOutlinedRect::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    Geometry::Vec2 newEndPos;
    newEndPos.set(this->endPos).add(offset);

    drawer->drawRect(this->color, newOffset.x, newOffset.y, newEndPos.x, newEndPos.y);
    this->drawChildren(drawer, &(newOffset));

    return;

}



/* ---------------------------------- */
/* ---------- WindowCircle ---------- */
/* ---------------------------------- */

WindowCircle::WindowCircle(int posx, int posy, int size, uint32 color) : WindowElement(posx, posy, size, size) {

    this->middle.set(this->size).scale(0.5).add(this->pos);
    this->radius = size;

    this->color = color;

    this->type = ElementType::VISUAL;

}

void WindowCircle::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    Geometry::Vec2 newMiddle;
    newMiddle.set(this->middle).add(offset);

    drawer->drawCircle(this->color, newMiddle.x, newMiddle.y, this->radius);
    this->drawChildren(drawer, &(newOffset));

    return;

}



/* -------------------------------------- */
/* ---------- WindowTextStatic ---------- */
/* -------------------------------------- */

WindowTextStatic::WindowTextStatic(int posx, int posy, char* text) : WindowElement(posx, posy, 0, 0) {
    
    this->text = text;
    this->color = Color::WHITE;

    this->type = ElementType::VISUAL;

}

WindowTextStatic::~WindowTextStatic() {

    // this->text should be heap allocated. This will crash otherwise
    // Then again, WindowElement objects should never be created directly without the help of XML
    if (this->text != nullptr) delete this->text;

}

void WindowTextStatic::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    drawer->fontDrawer.drawString(this->color, this->text, newOffset.x, newOffset.y);
    this->drawChildren(drawer, &(newOffset));

    return;

}



/* ------------------------------------- */
/* ---------- WindowTextInput ---------- */
/* ------------------------------------- */

WindowTextInput::WindowTextInput(int posx, int posy, int width, char* id) : WindowElement(posx, posy, width, 12) {

    this->text = new char[this->BUFFERSIZE];
    memset(this->text, '\0', this->BUFFERSIZE); // Initialize all to null chars
    this->length = 0;
    this->cursorPos = -1;

    this->bindType = BindType::NONE;
    this->boundFloat = nullptr;
    this->boundInt = nullptr;

    this->color = Color::WHITE;

    this->type = ElementType::TEXTINPUT;
    this->isInteractable = true;

    this->id = id;

}

WindowTextInput::~WindowTextInput() {
    delete[] this->text;
}

void WindowTextInput::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    // Update the internal string
    this->updateString();
    
    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    // Give the text some padding
    newOffset.add(3, 3);
    drawer->fontDrawer.drawString(this->color, this->text, newOffset.x, newOffset.y);

    // Draw cursor if needed
    if (this->cursorPos != -1) {

        Geometry::Vec2 start;
        start.set(newOffset).add( (this->cursorPos * 6), 0 );

        Geometry::Vec2 end;
        end.set(start).add(1, 7);

        drawer->drawRectFilled(this->color, start.x, start.y, end.x, end.y);

    }

    // Remove the padding before drawing children
    newOffset.sub(3, 3);
    this->drawChildren(drawer, &(newOffset));

    return;

}

void WindowTextInput::onInput(Graphics::Gui::State* state) {

    if (state->wasLeftJustPressed()) this->cursorPos = this->length;

    KeyCode key;
    char keyChar;

    bool textChanged = false;

    for (int i = 0; i < state->newKeyPressesIndex; i++) {
        
        key = state->newKeyPresses[i];

        keyChar = keyCodeToChar(key);

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

WindowTexture::WindowTexture(int posx, int posy, int sizex, int sizey, const char* fileName) : WindowElement(posx, posy, sizex, sizey) {

    this->type = ElementType::VISUAL;

    /*   Insert PNG handling here   */

    return;

}

WindowTexture::~WindowTexture() {

}

void WindowTexture::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    /* Insert PNG drawing logic here */

    this->drawChildren(drawer, &(newOffset));

    return;

}



/* ---------------------------------- */
/* ---------- WindowButton ---------- */
/* ---------------------------------- */

WindowButton::WindowButton(int posx, int posy, int sizex, int sizey, char* id) : WindowElement(posx, posy, sizex, sizey) {
    
    this->type = ElementType::BUTTON;
    this->isInteractable = true;

    this->action = nullptr;

    this->id = id;

}

WindowButton::WindowButton(int posx, int posy, int sizex, int sizey, Action* action) : WindowElement(posx, posy, sizex, sizey) {

    this->type = ElementType::BUTTON;
    this->isInteractable = true;

    this->action = action;

    this->id = nullptr;

}

WindowButton::~WindowButton() {
    
    if (this->action != nullptr) delete this->action;

    return;

}

void WindowButton::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    Geometry::Vec2 newEndPos;
    newEndPos.set(this->endPos).add(offset);
    
    this->drawChildren(drawer, &(newOffset));

    return;

}

void WindowButton::onInput(Graphics::Gui::State* state) {

    if (state->wasLeftJustPressed()) {

        if (this->action != nullptr) {
            WindowElement::queueAction(this->action);
        }

    }
    
    return;

}

void WindowButton::bind(Action* action) {

    // Free old action if there was one
    if (this->action != nullptr) delete this->action;

    this->action = action;

}



/* ------------------------------------ */
/* ---------- WindowDragable ---------- */
/* ------------------------------------ */

WindowDragable::WindowDragable(int posx, int posy, int sizex, int sizey, char* id) : WindowElement(posx, posy, sizex, sizey) {

    this->type = ElementType::DRAGABLE;
    this->isInteractable = true;

    this->posToDrag = nullptr;
    this->endPosToDrag = nullptr;

    this->id = id;

    return;

}

WindowDragable::WindowDragable(int posx, int posy, int sizex, int sizey, Geometry::Vec2* posToDrag, Geometry::Vec2* endPosToDrag) : WindowElement(posx, posy, sizex, sizey) {

    this->type = ElementType::DRAGABLE;
    this->isInteractable = true;

    this->posToDrag = posToDrag;
    this->endPosToDrag = endPosToDrag;

    this->id = nullptr;

    return;

}

void WindowDragable::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    Geometry::Vec2 newOffset;
    newOffset.set(this->pos).add(offset);

    this->drawChildren(drawer, &(newOffset));

    return;

}

void WindowDragable::onInput(Graphics::Gui::State* state) {

    if (this->posToDrag == nullptr || this->endPosToDrag == nullptr) return;

    int dx = state->deltaMousePosX();
    int dy = state->deltaMousePosY();

    this->posToDrag->add(dx, dy);
    this->endPosToDrag->add(dx, dy);

}

void WindowDragable::bind(Geometry::Vec2* posToDrag, Geometry::Vec2* endPosToDrag) {

    this->posToDrag = posToDrag;
    this->endPosToDrag = endPosToDrag;

}
