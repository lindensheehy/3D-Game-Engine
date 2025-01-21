#include "ui/UI.h"


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

// static Declarations
Vec2* UI::TransformWindowSize = new Vec2(300, 105);

// Constructor
UI::UI() {

    this->windows = new LinkedList<Window*>();

    this->nextWindowPos = new Vec2(100, 100);

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
    if (removed == nullptr) return;
    
    if (removed->type == TRANSFORM) this->transformWindow = nullptr;
    delete removed;

}

bool UI::doInput(State* state) {

    // Click handling
    if (state->wasLeftJustPressed()) {

        Window* current;        // The window checked on the given iteration
        WindowElement* found;   // Stores the clicked element found from the window, or nullptr if none

        for (this->windows->iterStart(this->windows->length - 1); !this->windows->iterIsDone(); this->windows->iterLast()) {

            current = this->windows->iterGetObj();

            // Skip iteration if the click lands outside the window
            bool clickLandsOnWindow = current->hitTest(state->mouse->posX, state->mouse->posY);
            if (!clickLandsOnWindow) continue;

            // Since now the click must land on the window, I bring it to the front
            // The list is drawn from front to back, so the back elements appear on top
            this->windows->pop(current);
            this->windows->pushBack(current);

            // Now check the children of the found window
            found = current->doInput(state);

            // If nothing was found, end
            if (found == nullptr) return false;
            
            // Otherwise, store the clicked element for later use
            this->lastClicked = found;

            return true;

        }

        // If the loop doesnt find anything, then a click landed outside all windows so remove lastClicked
        this->lastClicked = nullptr;

    }

    // The rest of this function doesnt need to run if theres no lastClicked
    if (this->lastClicked == nullptr) return false;

    // Drag handling
    if (this->lastClicked->type == DRAGABLE && state->wasLeftHeld()) {

        this->lastClicked->onInput(state);

    }

    // Text box handling
    if (this->lastClicked->type == TEXTINPUT) {

        this->lastClicked->onInput(state);

    }

    // If the code reaches this point, the focus should be on the UI rather than the camera controls
    return true;

}

Window* UI::createWindowTransform(Object* object) {

    if (this->transformWindow != nullptr) return nullptr;

    Window* ret = this->createWindowTransform(object, this->nextWindowPos->x, this->nextWindowPos->y);
    this->updateNextWindowPos();

    this->transformWindow = ret;
    return ret;

}

Window* UI::createWindowTransform(Object* object, int posx, int posy) {

    if (this->transformWindow != nullptr) return nullptr;

    bool nullObj = object == nullptr;

    Vec2* windowPos = new Vec2(posx, posy);
    Vec2* windowSize = this->TransformWindowSize->copy();
    Window* newWindow = new Window(windowPos, windowSize);
    WindowElement* newElement;

    // Top bar
    newWindow->addElement( WindowElement::createTopBar(this, newWindow, "Transform") );

    // Position
    newElement = new WindowDiv(20, 30, 250, 20);
    newElement->addChild( new WindowTextStatic(0, 7, "Position") );

    newElement->addChild( new WindowTextStatic(75, 7, "X") );
    newElement->addChild( new WindowTextStatic(135, 7, "Y") );
    newElement->addChild( new WindowTextStatic(195, 7, "Z") );

    if (nullObj) {
        newElement->addChild( new WindowOutlinedRect(85, 4, 35, 12, Color::ACCENT) );
        newElement->addChild( new WindowOutlinedRect(145, 4, 35, 12, Color::ACCENT) );
        newElement->addChild( new WindowOutlinedRect(205, 4, 35, 12, Color::ACCENT) );
    }

    else {
        newElement->addChild( WindowElement::createTextBox(85, 4, 35, &(object->pos->x)) );
        newElement->addChild( WindowElement::createTextBox(145, 4, 35, &(object->pos->y)) );
        newElement->addChild( WindowElement::createTextBox(205, 4, 35, &(object->pos->z)) );
        object->pos->log();
    }

    newWindow->addElement(newElement);

    // Rotation
    newElement = new WindowDiv(20, 50, 250, 20);
    newElement->addChild( new WindowTextStatic(0, 7, "Rotation") );

    newElement->addChild( new WindowTextStatic(75, 7, "X") );
    newElement->addChild( new WindowTextStatic(135, 7, "Y") );
    newElement->addChild( new WindowTextStatic(195, 7, "Z") );

    if (nullObj) {
        newElement->addChild( new WindowOutlinedRect(85, 4, 35, 12, Color::ACCENT) );
        newElement->addChild( new WindowOutlinedRect(145, 4, 35, 12, Color::ACCENT) );
        newElement->addChild( new WindowOutlinedRect(205, 4, 35, 12, Color::ACCENT) );
    }

    else {
        newElement->addChild( WindowElement::createTextBox(85, 4, 35, &(object->rotation->x)) );
        newElement->addChild( WindowElement::createTextBox(145, 4, 35, &(object->rotation->y)) );
        newElement->addChild( WindowElement::createTextBox(205, 4, 35, &(object->rotation->z)) );
        object->rotation->log();
    }

    newWindow->addElement(newElement);

    // Scale
    newElement = new WindowDiv(20, 70, 250, 20);
    newElement->addChild( new WindowTextStatic(0, 7, "Scale") );

    newElement->addChild( new WindowTextStatic(75, 7, "X") );
    newElement->addChild( new WindowTextStatic(135, 7, "Y") );
    newElement->addChild( new WindowTextStatic(195, 7, "Z") );

    if (nullObj) {
        newElement->addChild( new WindowOutlinedRect(85, 4, 35, 12, Color::ACCENT) );
        newElement->addChild( new WindowOutlinedRect(145, 4, 35, 12, Color::ACCENT) );
        newElement->addChild( new WindowOutlinedRect(205, 4, 35, 12, Color::ACCENT) );
    }

    else {
        newElement->addChild( WindowElement::createTextBox(85, 4, 35, &(object->scale->x)) );
        newElement->addChild( WindowElement::createTextBox(145, 4, 35, &(object->scale->y)) );
        newElement->addChild( WindowElement::createTextBox(205, 4, 35, &(object->scale->z)) ); 
        object->scale->log(); 
    }
    
    newWindow->addElement(newElement);
    newWindow->type = TRANSFORM;

    this->addWindow(newWindow);

    this->transformWindow = newWindow;
    return newWindow;

}

void UI::updateWindowTransform(Object* object) {

    if (this->transformWindow == nullptr) {
        this->createWindowTransform(object, 100, 100);
    }

    int posx = this->transformWindow->pos->x;
    int posy = this->transformWindow->pos->y;

    this->destroyWindowTransform();
    this->createWindowTransform(object, posx, posy);

}

void UI::destroyWindowTransform() {

    if (this->transformWindow != nullptr) this->deleteWindow(this->transformWindow);
    this->transformWindow = nullptr;

}

void UI::addWindow(Window* window) {

    this->windows->pushBack(window);

}

void UI::updateNextWindowPos() {
    
    this->nextWindowPos->add(50, 50);

    if (this->nextWindowPos->x > 500) this->nextWindowPos->x = 100;
    if (this->nextWindowPos->y > 300) this->nextWindowPos->y = 100;

}
