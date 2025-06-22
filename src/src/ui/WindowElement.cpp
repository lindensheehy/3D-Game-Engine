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

    this->color = Color::BLACK;
    
    this->children = new LinkedList<WindowElement*>();

    this->id = nullptr;

    return;

}

WindowElement::WindowElement(Geometry::Vec2* pos, Geometry::Vec2* size) {

    this->pos.set(pos);
    this->size.set(size);
    this->endPos.set(this->pos).add(this->size);

    this->color = Color::BLACK;

    this->children = new LinkedList<WindowElement*>();

    this->id = nullptr;

    return;

}

WindowElement::~WindowElement() {

    WindowElement* child;

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext()) {
        
        child = this->children->iterGetObj();
        delete child;
    
    }

    delete this->children;


    // All ids should be heap allocated. This will crash otherwise
    // Then again, WindowElement objects should never be created directly without the help of XML
    delete id;
    
    return;

}

void WindowElement::draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    // Log becuase this shouldnt ever be called (should only be called by subclasses)
    logWrite("Called WindowElement->draw()!", true);

    return;

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

void WindowElement::setPos(int x, int y) {

    this->pos.set(x, y);

    this->endPos.set(this->size);
    this->endPos.add(x, y);

    return;

}

void WindowElement::setPos(Geometry::Vec2* newPos) {

    this->setPos((int) newPos->x, (int) newPos->y);

    return;

}

void WindowElement::addChild(WindowElement* child) {

    this->children->pushBack(child);

    return;

}

void WindowElement::drawChildren(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) {

    for (this->children->iterStart(0); this->children->iterHasNext(); this->children->iterNext()) {
        this->children->iterGetObj()->draw(drawer, offset);
    }

    return;

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

    return;

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

    return;

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

    return;

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

    this->type = ElementType::VISUAL;
    this->color = color;

    return;

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

    this->type = ElementType::VISUAL;
    this->color = Color::WHITE;

    return;

}

WindowTextStatic::~WindowTextStatic() {

    // this->text should be heap allocated. This will crash otherwise
    // Then again, WindowElement objects should never be created directly without the help of XML
    delete this->text;

    return;

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
    this->textLength = 0;
    this->cursorPos = -1;

    this->bindType = BindType::NONE;
    this->boundFloat = nullptr;
    this->boundInt = nullptr;

    this->type = ElementType::TEXTINPUT;
    this->color = Color::WHITE;
    
    this->isInteractable = true;

    this->id = id;

    return;

}

WindowTextInput::~WindowTextInput() {

    delete[] this->text;

    return;

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

    if (state->wasLeftJustPressed()) this->cursorPos = this->textLength;

    KeyCode key;
    char keyChar;

    bool textChanged = false;

    for (int i = 0; i < state->newKeyPressesIndex; i++) {
        
        key = state->newKeyPresses[i];

        keyChar = keyCodeToChar(key);

        // If the keyChar is valid, write it to the internal string
        if (keyChar != '\0') {
            
            // Ensure space in the string
            if (this->textLength < this->BUFFERSIZE) {

                // Make space for the new char
                for (int i = this->textLength; i >= this->cursorPos; i--)
                    this->text[i+1] = this->text[i];

                this->text[cursorPos] = keyChar;
                this->textLength++;
                this->cursorPos++;

                textChanged = true;

            }

        }

        switch (key) {

            case KeyCode::ARROWUP:
                this->cursorPos = 0;
                break;

            case KeyCode::ARROWDOWN:
                this->cursorPos = this->textLength;
                break;

            case KeyCode::ARROWLEFT:
                if (this->cursorPos > 0) this->cursorPos--;
                break;

            case KeyCode::ARROWRIGHT:
                if (this->cursorPos < this->textLength) this->cursorPos++;
                break;

            case KeyCode::BACKSPACE:

                if (this->cursorPos < 1) break;

                // Move everything past the cursor left one space
                // This also overwrites the char at the cursor, so this is the 'backspace'
                for (int i = (this->cursorPos - 1); i < this->textLength; i++)
                    this->text[i] = this->text[i+1];

                this->text[this->textLength] = '\0';
                this->textLength--;
                this->cursorPos--;

                textChanged = true;

                break;


        }

    }

    if (textChanged) {
        this->writeToValue();
    }

    return;

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

    this->textLength = newLength;

    return;

}

void WindowTextInput::writeToValue() {

    int intValue;
    float floatValue;

    bool passed;

    switch (this->bindType) {

        case BindType::NONE:
            break;

        case BindType::INT: {
            
            passed = stringToInt(this->text, &intValue, this->BUFFERSIZE);

            if (passed) {
                *(this->boundInt) = intValue;
            }
        
            break;
        
        }


        case BindType::FLOAT: {

            passed = stringToFloat(this->text, &floatValue, this->BUFFERSIZE);
            
            if (passed) {
                *(this->boundFloat) = floatValue;
            }

            break;

        }

        default:
            break;
        
    }

    return;

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

    return;

}

WindowButton::WindowButton(int posx, int posy, int sizex, int sizey, Action* action) : WindowElement(posx, posy, sizex, sizey) {

    this->type = ElementType::BUTTON;
    this->isInteractable = true;

    this->action = action;

    this->id = nullptr;

    return;

}

WindowButton::~WindowButton() {
    
    delete this->action;

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

    if (this->action != nullptr) {
        WindowElement::queueAction(this->action);
    }
    
    return;

}

void WindowButton::bind(Action* action) {

    delete this->action;
    this->action = action;

    return;

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

    return;

}

void WindowDragable::bind(Geometry::Vec2* posToDrag, Geometry::Vec2* endPosToDrag) {

    this->posToDrag = posToDrag;
    this->endPosToDrag = endPosToDrag;

    return;

}
