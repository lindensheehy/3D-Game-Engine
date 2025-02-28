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

    this->binding = new Binding();
    
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

    if (this->binding != nullptr) delete this->binding;

}

// Instance Functions
void UI::draw(Drawer* drawer) {

    for (this->windows->iterStart(0); !this->windows->iterIsDone(); this->windows->iterNext())
        this->windows->iterGetObj()->draw(drawer);

}

bool UI::doInput(State* state, CursorState* cursorStateOut /* Default value = nullptr */) {

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

            case UIEnum::ActionType::CLOSE_WINDOW: {

                ActionCloseWindow* castedAction = (ActionCloseWindow*) currentAction;

                this->destroyWindow(castedAction->targetWindowId);

                break;

            }

            case UIEnum::ActionType::OPEN_WINDOW: {

                ActionOpenWindow* castedAction = (ActionOpenWindow*) currentAction;

                this->createWindow(castedAction->fileName);

                break;

            }

            case UIEnum::ActionType::CALL_FUNC: {

                ActionCallFunc* castedAction = (ActionCallFunc*) currentAction;

                castedAction->callFunc();

                break;

            }

        }

    }

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

        // Break out of the loop reaches this
        break;

    }

    // Click handling
    if (state->wasLeftJustPressed()) {

        /*   Window level handling   */

        // If a window was clicked on
        if (hoveredWindow != nullptr) {

            // Since now the click must land on the window, I bring it to the front
            // The list is drawn from front to back, so the back elements appear on top
            this->windows->pop(currentWindow);
            this->windows->pushBack(currentWindow);

            // Tell the UI it has focus
            this->hasFocus = true;

        }

        // If no window was clicked on
        else {
            this->hasFocus = false;
        }


        /*   Element level handling   */

        // If an element was clicked on
        if (hoveredElement != nullptr) {

            // Deselect last clicked if there is any
            if (this->lastClicked != nullptr) {
                this->lastClicked->onDeselect();
                this->lastClicked->selected = false;
            }

            // Mark the found element as selected and save it for future reference
            hoveredElement->selected = true;
            this->lastClicked = hoveredElement;

        }

        // If no element was clicked on
        else {

            // Deselect last clicked if there is any
            if (this->lastClicked != nullptr) {
                this->lastClicked->onDeselect();
                this->lastClicked->selected = false;
            }

            // Reset lastClicked
            this->lastClicked = nullptr;

        }

    }

    // Cases where the rest of the code shouldnt or cant execute
    if (!this->hasFocus) return false;
    if (this->lastClicked == nullptr) return true;

    // Button handling
    if (this->lastClicked->type == UIEnum::ElementType::BUTTON) {

        this->lastClicked->onInput(state);

    }

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

WindowHandle UI::createWindow(const char* fileName) {

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

    this->windows->pushBack(newWindow);

    newWindow->id = this->nextFreeWindowId;
    this->nextFreeWindowId++;

    WindowHandle ret(newWindow->id, newWindow);

    return ret;

}

void UI::destroyWindow(WindowHandle* pWindowHandle) {

    if (pWindowHandle == nullptr) {
        logWrite("UI::destroyWindow(WindowHandle*) Was called on a nullptr!", true);
        return;
    }

    Window* window = (*pWindowHandle).ptr;

    if (window == nullptr) {
        logWrite("UI::destroyWindow(WindowHandle*) Tried to destroy an invalid window!", true);
        return;
    }

    this->destroyWindow(window);

    return;

}

void UI::validateWindowHandle(WindowHandle* pWindowHandle) {

    if (pWindowHandle == nullptr) {
        logWrite("UI::validateWindowHandle(WindowHandle*) Was called on a nullptr!", true);
        return;
    }

    Window* window = (*pWindowHandle).ptr;

    // Set the arg to -1 if it was not found
    if (window == nullptr) {
        (*pWindowHandle).id = -1;
        (*pWindowHandle).ptr = nullptr;
    }

}

void UI::setWindowPos(WindowHandle windowHandle, int posx, int posy) {

    Window* window = windowHandle.ptr;

    if (window == nullptr) {
        logWrite("UI::setWindowPos() Wants to set the position of an invalid window!", true);
        return;
    }

    window->setPos(posx, posy);

    return;

}

void UI::updateNextWindowPos() {
    
    this->nextWindowPos->add(50, 50);

    if (this->nextWindowPos->x > 500) this->nextWindowPos->x = 100;
    if (this->nextWindowPos->y > 300) this->nextWindowPos->y = 100;

}

void UI::destroyWindow(WindowID windowId) {

    Window* current;

    for (this->windows->iterStart(0); this->windows->iterHasNext(); this->windows->iterNext()) {

        current = this->windows->iterGetObj();

        if (current->id == windowId) {
            this->destroyWindow(current);
            return;
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

Action* UI::getNextAction() {

    if (UI::actionQueue->length == 0) return nullptr;

    return UI::actionQueue->popFront();

}

