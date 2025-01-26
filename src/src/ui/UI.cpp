#include "ui/UI.h"


/* ------------------------ */
/* ---------- UI ---------- */
/* ------------------------ */

// Static declarations
const Vec2* UI::TransformWindowSize = new Vec2(300, 105);
LinkedList<Action*>* UI::actionQueue;


// Constructor
UI::UI() {

    this->windows = new LinkedList<Window*>();

    this->nextWindowPos = new Vec2(100, 100);

    LinkedList<Action*>* queue = new LinkedList<Action*>();

    UI::actionQueue = queue;
    Window::setActionQueue(queue);
    WindowElement::setActionQueue(queue);

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
    
    if (removed->type == UIEnum::WindowType::TRANSFORM) this->transformWindow = nullptr;
    delete removed;

}

bool UI::doInput(State* state) {

    // General declarations for use in loops
    Action* currentAction;
    Window* currentWindow;

    // Handle actions in queue, if any exist
    while (UI::actionQueue->length != 0) {

        currentAction = UI::getNextAction();

        if (currentAction == nullptr) break;

        switch (currentAction->actionType) {

            case UIEnum::ActionType::NONE:
                break;

            case UIEnum::ActionType::CLOSE_WINDOW:

                ActionCloseWindow* castedAction = (ActionCloseWindow*) currentAction;

                // Refactor later, should use an id for scalability
                for (this->windows->iterStart(this->windows->length - 1); !this->windows->iterIsDone(); this->windows->iterLast()) {

                    currentWindow = this->windows->iterGetObj();

                    if (currentWindow->type == castedAction->target) {
                        this->deleteWindow(currentWindow);
                        break;
                    }

                }

                break;

        }

    }

    // Click handling
    if (state->wasLeftJustPressed()) {

        WindowElement* found;   // Stores the clicked element found from the window, or nullptr if none

        for (this->windows->iterStart(this->windows->length - 1); !this->windows->iterIsDone(); this->windows->iterLast()) {

            currentWindow = this->windows->iterGetObj();

            // Skip iteration if the click lands outside the window
            bool clickLandsOnWindow = currentWindow->hitTest(state->mouse->posX, state->mouse->posY);
            if (!clickLandsOnWindow) continue;

            // Since now the click must land on the window, I bring it to the front
            // The list is drawn from front to back, so the back elements appear on top
            this->windows->pop(currentWindow);
            this->windows->pushBack(currentWindow);

            // Now check the children of the found window
            found = currentWindow->doInput(state);

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
    if (this->lastClicked->type == UIEnum::ElementType::DRAGABLE && state->wasLeftHeld()) {

        this->lastClicked->onInput(state);

    }

    // Text box handling
    if (this->lastClicked->type == UIEnum::ElementType::TEXTINPUT) {

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
    newWindow->type = UIEnum::WindowType::TRANSFORM;

    WindowElement* newElement;

    // Top bar
    newWindow->addElement( createTopBar(this, newWindow, "Transform") );

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
        newElement->addChild( createTextBox(85, 4, 35, &(object->pos->x)) );
        newElement->addChild( createTextBox(145, 4, 35, &(object->pos->y)) );
        newElement->addChild( createTextBox(205, 4, 35, &(object->pos->z)) );
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
        newElement->addChild( UI::createTextBox(85, 4, 35, &(object->rotation->x)) );
        newElement->addChild( UI::createTextBox(145, 4, 35, &(object->rotation->y)) );
        newElement->addChild( UI::createTextBox(205, 4, 35, &(object->rotation->z)) );
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
        newElement->addChild( UI::createTextBox(85, 4, 35, &(object->scale->x)) );
        newElement->addChild( UI::createTextBox(145, 4, 35, &(object->scale->y)) );
        newElement->addChild( UI::createTextBox(205, 4, 35, &(object->scale->z)) ); 
    }
    
    newWindow->addElement(newElement);

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


Action* UI::getNextAction() {

    if (UI::actionQueue->length == 0) return nullptr;

    return UI::actionQueue->popFront();

}

// Some high level constructors for specific elements
WindowElement* UI::createTopBar(UI* ui, Window* window, const char* title) {

    // Divider for all the elements
    WindowElement* holder = new WindowDiv(1, 1, window->size->x - 1, 18);

    // Title plus dragable tab
    WindowElement* dragRect = new WindowDragable(0, 0, window->size->x - 19, 18, window->pos, window->endPos);
    WindowElement* topBarColor = new WindowFilledRect(0, 0, window->size->x - 19, 18, Color::LIGHTER);
    WindowElement* titleElement = new WindowTextStatic(6, 6, title);
    
    dragRect->addChild(topBarColor);
    dragRect->addChild(titleElement);

    // The parent element for the close tab button
    WindowElement* CloseButtonElement = new WindowButton(
        window->size->x - 19, 0, 18, 18, 
        new ActionCloseWindow(window->type)
    );
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

WindowElement* UI::createTextBox(int posx, int posy, int width, double* valueToWrite) {

    WindowElement* newElement = new WindowFilledRect(posx, posy, width, 12, Color::DARKER);

    newElement->addChild( new WindowOutlinedRect(0, 0, width, 12, Color::ACCENT) );
    newElement->addChild( new WindowTextInput(0, 0, 35, valueToWrite) );

    return newElement;

}
