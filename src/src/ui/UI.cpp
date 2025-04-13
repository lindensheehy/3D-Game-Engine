#include "ui/UI.h"

using namespace Ui;


/* ------------------------ */
/* ---------- UI ---------- */
/* ------------------------ */

const Geometry::Vec2* UI::TransformWindowSize = new Geometry::Vec2(300, 105);
LinkedList<Action*>* UI::actionQueue;

UI::UI() {

    this->windows = new LinkedList<Window*>();

    this->nextWindowPos = new Geometry::Vec2(100, 100);

    LinkedList<Action*>* queue = new LinkedList<Action*>();

    UI::actionQueue = queue;
    Window::setActionQueue(queue);
    WindowElement::setActionQueue(queue);

    this->xml = new Xml::XML();
    this->xml->initDefaultElements();
    this->xml->initCustomElements();

    this->bindManager = new BindManager();
    
    return;

}

UI::~UI() {

    if (this->windows->length > 0) {
        Window* window;
        for (this->windows->iterStart(0); !this->windows->iterIsDone(); this->windows->iterNext()) {
            window = this->windows->iterGetObj();
            if (window != nullptr) delete window;
        }
    }

    if (this->windows != nullptr) delete this->windows;

    if (this->bindManager != nullptr) delete this->bindManager;

}

void UI::draw(Graphics::Drawing::Drawer* drawer) {

    for (this->windows->iterStart(0); !this->windows->iterIsDone(); this->windows->iterNext())
        this->windows->iterGetObj()->draw(drawer);

}

bool UI::doInput(Graphics::Gui::State* state, Graphics::Gui::CursorState* cursorStateOut /* Default value = nullptr */) {
    
    // Handle actions before starting
    this->handleActions();

    Window* currentWindow;

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

                case ElementType::BUTTON:
                    *cursorStateOut = Graphics::Gui::CURSOR_HAND;
                    break;

                case ElementType::TEXTINPUT:
                    *cursorStateOut = Graphics::Gui::CURSOR_TEXT;
                    break;

                default:
                    *cursorStateOut = Graphics::Gui::CURSOR_ARROW;
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
    if (this->lastClicked->type == ElementType::BUTTON) {

        this->lastClicked->onInput(state);

    }

    // Drag handling
    if (this->lastClicked->type == ElementType::DRAGABLE && state->wasLeftHeld()) {

        this->lastClicked->onInput(state);

    }

    // Text box handling
    if (this->lastClicked->type == ElementType::TEXTINPUT) {

        this->lastClicked->onInput(state);

    }

    // If the code reaches this point, the focus should be on the UI rather than the camera controls
    return true;

}

WindowHandle* UI::createWindow(const char* fileName) {

    // Build the Window object from the xml file
    Window* newWindow = this->xml->buildWindow(fileName);

    // The created window will have exaclty one parent element, and this element will be the actual visible window
    WindowElement* parentElement = newWindow->elements->getFirst();

    // Tell the window how big it is
    newWindow->size.set(parentElement->size);
    newWindow->endPos.set(parentElement->size);

    // Place the window at the nextWindowPos if position was not specified (flag is -1)
    if (parentElement->pos.is(-1, -1)) {

        newWindow->pos.set(this->nextWindowPos);
        newWindow->endPos.add(this->nextWindowPos);

        this->updateNextWindowPos();

    }

    // If it was specified, use the values from parentElement
    else {

        newWindow->pos.set(parentElement->pos);
        newWindow->endPos.add(parentElement->pos);

        // Reset parentElement->pos as this is a relative position
        parentElement->setPos(0, 0);

    }

    this->windows->pushBack(newWindow);

    newWindow->id = this->nextFreeWindowId;
    this->nextFreeWindowId++;

    WindowHandle* ret = new WindowHandle(newWindow->id, newWindow);

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

void UI::validateWindowHandle(WindowHandle** pWindowHandle) {

    if (pWindowHandle == nullptr) {
        logWrite("UI::validateWindowHandle(WindowHandle**) Was called on a nullptr!", true);
        return;
    }

    // This is actually fine, just the rest of the code cant execute in this case
    if ((*pWindowHandle) == nullptr) return;

    Window* window = (*pWindowHandle)->ptr;

    // Check the Window list to see if it actually exists
    Window* current;
    for (this->windows->iterStart(0); this->windows->iterHasNext(); this->windows->iterNext()) {

        current = this->windows->iterGetObj();

        // If it is found, theres nothing left to do
        if (window == current) return;

    }

    // Invalidate the WindowHandle if it was not found
    // NOTE: Theres no need to free the Window ptr as this would have been handled when the window was destroyed
    delete (*pWindowHandle);
    (*pWindowHandle) = nullptr;
    
    return;

}

void UI::setWindowPos(WindowHandle* windowHandle, int posx, int posy) {

    if (windowHandle == nullptr) {
        logWrite("UI::setWindowPos(WindowHandle*, int, int) was called on a nullptr!", true);
        return;
    }

    Window* window = windowHandle->ptr;

    if (window == nullptr) {
        logWrite("UI::setWindowPos() Wants to set the position of an invalid window!", true);
        return;
    }

    window->setPos(posx, posy);

    return;

}

void UI::handleActions() {

    // Handle actions in queue, if any exist
    Action* currentAction;
    while (UI::actionQueue->length != 0) {

        currentAction = UI::getNextAction();

        if (currentAction == nullptr) break;

        switch (currentAction->type) {

            case ActionType::NONE:
                break;

            case ActionType::CLOSE_WINDOW: {

                ActionCloseWindow* castedAction = (ActionCloseWindow*) currentAction;

                this->destroyWindow(castedAction->targetWindowId);

                break;

            }

            case ActionType::OPEN_WINDOW: {

                ActionOpenWindow* castedAction = (ActionOpenWindow*) currentAction;

                // First I make sure the window isnt already open
                this->validateWindowHandle( (castedAction->windowHandle) );

                // If the window is open, I dont execute the rest of the block
                if ( *(castedAction->windowHandle) != nullptr ) break;

                *(castedAction->windowHandle) = this->createWindow(castedAction->fileName);

                this->bindManager->addBind( *(castedAction->windowHandle), castedAction->bindFunc );

                break;

            }

            case ActionType::CALL_FUNC: {

                ActionCallFunc* castedAction = (ActionCallFunc*) currentAction;

                castedAction->callFunc();

                break;

            }

            default: {

                logWrite("UI is trying to handle an unrecognized Action!", true);

                logWrite(" -> Action type ");
                logWrite(actionTypeToString(currentAction->type));
                logWrite(" cannot be matched", true);

                break;

            }

        }

    }

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
