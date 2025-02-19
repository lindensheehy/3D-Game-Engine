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

    this->xml = new XML();
    this->xml->initDefaultElements();
    this->xml->initCustomElements();
    
    return;

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

<<<<<<< Updated upstream
void UI::deleteWindow(Window* window) {

    Window* removed = this->windows->pop(window);
    if (removed == nullptr) return;
    
    if (removed->type == UIEnum::WindowType::TRANSFORM) this->transformWindow = nullptr;
    delete removed;

}

bool UI::doInput(State* state) {
=======
bool UI::doInput(State* state, CursorState* cursorStateOut /* Default value = nullptr */) {
>>>>>>> Stashed changes

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

                this->destroyWindow(castedAction->targetWindowId);

                break;

        }

    }

<<<<<<< Updated upstream
=======
    // First I check where the mouse is relative to the UI. This is how the cursor state is updated
    // Also store some values to make the logic afterwards more simple
    bool mouseIsOnUi = false;
    Window* hoveredWindow = nullptr;
    WindowElement* hoveredElement = nullptr;

    // Loop backwards so the front windows take priority
    for (this->windows->iterStart(this->windows->length - 1); this->windows->iterHasNext(); this->windows->iterLast()) {

        currentWindow = this->windows->iterGetObj();

        // Find the element in the window that the mouse lies on (if any)
        hoveredElement = currentWindow->hitTest(state->mouse->posX, state->mouse->posY);
        if (hoveredElement == nullptr) continue;

        // Store the window for the next block
        hoveredWindow = currentWindow;

        // Update cursorStateOut if needed
        if (cursorStateOut != nullptr) {

            // Cursor state depends on the type of element that is hovered
            switch (hoveredElement->type) {

                case UIEnum::ElementType::BUTTON:
                    *cursorStateOut = CURSOR_HAND;
                    break;

                case UIEnum::ElementType::TEXTINPUT:
                    *cursorStateOut = CURSOR_TEXT;
                    break;

                default:
                    *cursorStateOut = CURSOR_ARROW;
                    break;

            }

        }

    }

>>>>>>> Stashed changes
    // Click handling
    if (state->wasLeftJustPressed()) {

        WindowElement* foundElement;   // Stores the clicked element found from the window, or nullptr if none
        bool clickLanded = false;

        for (this->windows->iterStart(this->windows->length - 1); !this->windows->iterIsDone(); this->windows->iterLast()) {

            currentWindow = this->windows->iterGetObj();

            // Skip iteration if the click lands outside the window
            clickLanded = currentWindow->hitTest(state->mouse->posX, state->mouse->posY);
            if (!clickLanded) continue;

            // Since now the click must land on the window, I bring it to the front
            // The list is drawn from front to back, so the back elements appear on top
            this->windows->pop(currentWindow);
            this->windows->pushBack(currentWindow);

            // Now check the children of the found window
            foundElement = currentWindow->doInput(state);

            // If nothing was found, nothing interactable was clicked, so reset lastClicked and leave
            if (foundElement == nullptr) break;

            // Otherwise, mark the found element as selected and save it for future reference
            if (this->lastClicked != nullptr) {
                this->lastClicked->onDeselect();
                this->lastClicked->selected = false;
            }
            foundElement->selected = true;
            this->lastClicked = foundElement;

        }

        this->hasFocus = clickLanded;

        // If the click didnt land, remove lastClicked
        if (!clickLanded) {
            if (this->lastClicked != nullptr) {
                this->lastClicked->onDeselect();
                this->lastClicked->selected = false;
            }
            this->lastClicked = nullptr;
        }

    }

    // Cases where the rest of the code shouldnt or cant execute
    if (!this->hasFocus) return false;
    if (this->lastClicked == nullptr) return true;

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

WindowID UI::createWindow(const char* fileName) {

    // Build the Window object from the xml file
    Window* newWindow = this->xml->buildWindow(fileName);

    // The created window will have exaclty one parent element, and this element will be the size of the window
    WindowElement* parentElement = newWindow->elements->getFirst();

    // Tell the window how big it is
    newWindow->size->set(parentElement->size);
    newWindow->endPos->set(parentElement->size);

    // Place the window at the nextWindowPos
    newWindow->pos->set(this->nextWindowPos);
    newWindow->endPos->add(this->nextWindowPos);

    return newWindow->id;

}

void UI::destroyWindow(WindowID windowId) {

    if (windowId == -1) {
        logWrite("UI::destroyWindow(WindowID) Tried to destroy an invalid window!", true);
        return;
    }

    Window* current;

    for (this->windows->iterStart(0); this->windows->iterHasNext(); this->windows->iterNext()) {

        current = this->windows->iterGetObj();

        if (current->id == windowId) {
            this->destroyWindow(current);
            break;
        }

    }

    return;

}

void UI::destroyWindow(Window* window) {

    if (window == nullptr) {
        logWrite("UI::destroyWindow(Window*) was called on a nullptr!", true);
        return;
    }

    Window* removed = this->windows->pop(window);
    if (removed == nullptr) return;
    
    delete removed;

}

void UI::bindWindowTransform(WindowID windowId, Object* object) {

    if (windowId == -1) {
        logWrite("UI::bindWindowTransform(WindowID, Object*) was called on an invalid WindowID!", true);
        return;
    }

    if (object == nullptr) {
        logWrite("UI::bindWindowTransform(WindowID, Object*) was called on a nullptr!", true);
        return;
    }

    // Binding logic

    return;

}


Action* UI::getNextAction() {

    if (UI::actionQueue->length == 0) return nullptr;

    return UI::actionQueue->popFront();

}

void UI::updateNextWindowPos() {
    
    this->nextWindowPos->add(50, 50);

<<<<<<< Updated upstream
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

WindowElement* UI::createTextBox(int posx, int posy, int width, float* valueToWrite) {

    WindowElement* newElement = new WindowFilledRect(posx, posy, width, 12, Color::DARKER);

    newElement->addChild( new WindowOutlinedRect(0, 0, width, 12, Color::ACCENT) );

    WindowTextInput* textInput = new WindowTextInput(0, 0, 35);
    textInput->bind(valueToWrite);
    newElement->addChild( textInput );

    return newElement;
=======
    if (this->nextWindowPos->x > 500) this->nextWindowPos->x = 100;
    if (this->nextWindowPos->y > 300) this->nextWindowPos->y = 100;
>>>>>>> Stashed changes

}
