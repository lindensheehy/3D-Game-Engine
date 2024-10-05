#include "../include/UI.h"



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

WindowElement* WindowElement::doClick(int x, int y, Vec2* offset) {

    Vec2* newPos = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);

    // If the click lies outside the element, it will (or at least should) lie outside its children
    if (
        x > newEndPos->x || 
        x < newPos->x ||
        y > newEndPos->y || 
        y < newPos->y 
    ) return nullptr;

    // Since now the click must lie inside this element, if this is BUTTON type, I return this and skip checking the children
    if (this->type == BUTTON) return this;

    // Otherwise, I will check the children

    WindowElement* current;        // The window checked on the given iteration
    WindowElement* found;   // Stores the clicked element found from the window, or nullptr if none

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext()) {

        current = this->children->iterGetObj();
        found = current->doClick(x, y, newPos);

        if (found != nullptr) return found;

    }

    // If none of the children were clicked on, I return this
    return this;

}

void WindowElement::onClick() {

    if (this->action != nullptr) this->action->run();

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

    // Parent for all the elements in the top bar
    WindowElement* mainElement = new WindowFilledRect(1, 1, window->size->x - 1, 18);
    mainElement->color = Color::LIGHTER;

    // Text element for the title of the window
    WindowElement* titleElement = new WindowText(6, 6, 0, 0, title);
    titleElement->color = Color::WHITE;

    // The parent element for the close tab button
    WindowElement* CloseButtonElement = new WindowButton(window->size->x - 19, 0, 18, 18);
    CloseButtonElement->color = Color::RED;
    CloseButtonElement->action = new ActionCloseWindow(ui, window);

    // Two white lines to form the X on the close tab button
    WindowElement* line1 = new WindowLine(3, 2, 13, 13);
    WindowElement* line2 = new WindowLine(15, 2, -13, 13);
    line1->color = Color::WHITE;
    line2->color = Color::WHITE;
    line1->action = CloseButtonElement->action;
    line2->action = CloseButtonElement->action;

    // Add the lines to the button
    CloseButtonElement->addChild(line1);
    CloseButtonElement->addChild(line2);

    mainElement->addChild(titleElement);
    mainElement->addChild(CloseButtonElement);

    return mainElement;

}



/* -------------------------------- */
/* ---------- WindowLine ---------- */
/* -------------------------------- */

// Constructor
WindowLine::WindowLine(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {

    this->endPos = new Vec2(posx, posy);
    endPos->add(sizex, sizey);

    this->type = VISUAL;

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
WindowFilledRect::WindowFilledRect(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {

    this->type = VISUAL;

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
WindowOutlinedRect::WindowOutlinedRect(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {

    this->type = VISUAL;

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



/* -------------------------------- */
/* ---------- WindowText ---------- */
/* -------------------------------- */

// Constructor
WindowText::WindowText(int posx, int posy, int sizex, int sizey, const char* text) : WindowElement(posx, posy, sizex, sizey) {
    
    this->text = text;

    this->type = TEXT;

}

// Instance Functions
void WindowText::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    drawer->drawString(this->color, this->text, newOffset);
    this->drawChildren(drawer, newOffset);

    delete newOffset;

}



/* ----------------------------------- */
/* ---------- WindowTexture ---------- */
/* ----------------------------------- */

// Constructor
WindowTexture::WindowTexture(int posx, int posy, int sizex, int sizey, PNG* texture) : WindowElement(posx, posy, sizex, sizey) {
    
    this->texture = texture;

    this->type = VISUAL;

}

// Destructor
WindowTexture::~WindowTexture() {
    
    if (this->texture != nullptr) delete this->texture;

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
WindowButton::WindowButton(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {

    this->type = BUTTON;

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



/* ---------------------------- */
/* ---------- Window ---------- */
/* ---------------------------- */

// Constructors
Window::Window(int posx, int posy, int sizex, int sizey, int layer /* Default value = 0 */) {

    this->pos = new Vec2(posx, posy);
    this->size = new Vec2(sizex, sizey);
    this->layer = layer;

    this->elements = new LinkedList<WindowElement*>();

    this->endPos = this->pos->copy()->add(this->size);

}

Window::Window(Vec2* pos, Vec2* size, int layer /* Default value = 0 */) {

    this->pos = pos;
    this->size = size;
    this->layer = layer;

    this->endPos = this->pos->copy()->add(this->size);

}

// Destructor
Window::~Window() {

    if (this->pos != nullptr) delete this->pos;
    if (this->size != nullptr) delete this->size;
    if (this->endPos != nullptr) delete this->endPos;

    if (this->elements->length > 0) {
        WindowElement* element;
        for (this->elements->iterStart(0); !this->elements->iterIsDone(); this->elements->iterNext()) {
            element = this->elements->iterGetObj();
            if (element != nullptr) delete element;
        }
    }

    if (this->elements != nullptr) delete this->elements;

}

void Window::draw(Drawer* drawer) {

    drawer->drawRectFilled(this->COLOR_BASE, this->pos, this->endPos);
    drawer->drawRect(this->COLOR_ACCENT, this->pos, this->endPos);

    for (this->elements->iterStart(0); !this->elements->iterIsDone(); this->elements->iterNext())
        this->elements->iterGetObj()->draw(drawer, this->pos);

}

WindowElement* Window::doClick(int x, int y) {

    // If the click lies outside the window, it will (or at least should) lie outside its children
    if (
        x > this->endPos->x || 
        x < this->pos->x ||
        y > this->endPos->y || 
        y < this->pos->y 
    ) return nullptr;

    WindowElement* current;        // The window checked on the given iteration
    WindowElement* found;   // Stores the clicked element found from the window, or nullptr if none

    for (this->elements->iterStart(0); !this->elements->iterIsDone(); this->elements->iterNext()) {

        current = this->elements->iterGetObj();
        found = current->doClick(x, y, this->pos);

        if (found != nullptr) return found;

    }

    return nullptr;

}

void Window::addElement(WindowElement* element) {

    this->elements->pushBack(element);
    return;

}



/* ---------------------------- */
/* ---------- Action ---------- */
/* ---------------------------- */

// Constructor
Action::Action() {

}

// Destructor
Action::~Action() {

}



/* ------------------------------------ */
/* ---------- ActionLogWrite ---------- */
/* ------------------------------------ */

// Constructor
ActionLogWrite::ActionLogWrite(const char* message) {

    this->message = message;

}

// Destructor
ActionLogWrite::~ActionLogWrite() {
    // The Window object should be handled manually it doesnt make sense to delete it here.
    // Keeping this in case that changes or I add other instance variables
}

// Instance Functions
void ActionLogWrite::run() {

    logWrite(message, true);

}



/* --------------------------------- */
/* ---------- CloseWindow ---------- */
/* --------------------------------- */

// Constructor
ActionCloseWindow::ActionCloseWindow(UI* ui, Window* window) {

    this->ui = ui;
    this->window = window;

}

// Destructor
ActionCloseWindow::~ActionCloseWindow() {
    // The Window object should be handled manually it doesnt make sense to delete it here.
    // Keeping this in case that changes or I add other instance variables
}

// Instance Functions
void ActionCloseWindow::run() {

    this->ui->deleteWindow(this->window);

}



/* ------------------------ */
/* ---------- UI ---------- */
/* ------------------------ */

// Constructor
UI::UI() {

    this->windows = new LinkedList<Window*>();

}

// Destructor
UI::~UI() {

    if (this->windows->length > 0) {
        Window* window;
        for (this->windows->iterStart(0); !this->windows->iterIsDone(); this->windows->iterNext()) {
            window = this->windows->iterGetObj();
            if (window != nullptr) delete window;
        }
    }

    if (this->windows != nullptr) delete this->windows;

}

// Instance Functions
void UI::draw(Drawer* drawer) {

    for (this->windows->iterStart(0); !this->windows->iterIsDone(); this->windows->iterNext())
        this->windows->iterGetObj()->draw(drawer);

}

void UI::deleteWindow(Window* window) {

    Window* removed = this->windows->pop(window);
    if (removed != nullptr) delete removed;

}

void UI::doInput(State* state) {

    // Click handling
    if (state->mouse->leftButtonIsDown) {

        Window* current;        // The window checked on the given iteration
        WindowElement* found;   // Stores the clicked element found from the window, or nullptr if none

        for (this->windows->iterStart(0); !this->windows->iterIsDone(); this->windows->iterNext()) {

            current = this->windows->iterGetObj();
            found = current->doClick(state->mouse->posX, state->mouse->posY);

            if (found != nullptr) {

                this->lastClicked = found;

                if (found->type == BUTTON) found->onClick();
                
                if (found->type == TEXT) this->selectedTextBox = found;
                else this->selectedTextBox = nullptr;

            }

        }

    }

    // Text box handling
    if (this->selectedTextBox != nullptr) {

    }

}

void UI::createWindowTransform(Object* object) {

    Window* newWindow = new Window(100, 100, 300, 150);

    newWindow->addElement(WindowElement::createTopBar(this, newWindow, "Transform"));

    WindowElement* temp = new WindowButton(50, 50, 50, 50);
    temp->action = new ActionLogWrite("test");
    newWindow->addElement(temp);

    this->addWindow(newWindow);

}

void UI::addWindow(Window* window) {

    this->windows->pushBack(window);

}
