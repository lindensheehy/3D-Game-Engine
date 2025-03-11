#include "gui/GUI.h"


/*
    The following code is here to route Windows messages to the right GUI instance
    This is not accessible from GUI.h, and it doesnt need to be
*/

namespace Gui {

    // List of all existing GUI instances
    LinkedList<GUI*>* windowList = nullptr;

    // Generic WindowProc function that routes messages to their respective GUI instance
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

        // Find the GUI instance that matches the HWND
        GUI* current;
        for (windowList->iterStart(0); windowList->iterHasNext(); windowList->iterNext()) {
    
            current = windowList->iterGetObj();
    
            // Found match
            if (current->window->hwnd == hwnd) {
                return current->handleMessage(uMsg, wParam, lParam);
            }
    
        }
    
        // None found, just do default handling
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    
    }

}


/*
    Everything else is for the actual GUI class
*/

// Constructor
GUI::GUI(int width, int height, const char* windowName) {

    // First i instantiate the windowList if it hasnt already been
    if (Gui::windowList == nullptr) Gui::windowList = new LinkedList<GUI*>();

    this->window = new Gui::Window(Gui::WindowProc, width, height, windowName);

    // Ensure the window was properly created and has a HWND
    if (this->window->hwnd == nullptr) {
        logWrite("GUI failed to create window \"");
        logWrite(windowName);
        logWrite("\"!", true);
        return;
    }

    this->state = new Gui::State(this->window->hwnd);

    this->display = new Gui::Display(width, height);

    this->drawer = new Gui::Drawer(this->display);
    this->drawer->initFont();
    this->drawer->buffer = this->window->buffer;

    this->shouldDestroyWindow = false;

    Gui::windowList->pushBack(this);

    return;

}

// Destructor
GUI::~GUI() {

    if (this->display != nullptr) delete this->display;
    if (this->drawer != nullptr) delete this->drawer;
    if (this->state != nullptr) delete this->state;
    if (this->window != nullptr) delete this->window;

}

// Instance Functions
LRESULT GUI::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {

    // Skip if state does not exist. state is where the input events are tracked
    if (this->state == nullptr) return 1;

    int status = this->state->handleMessage(uMsg, wParam, lParam);

    switch (status) {

        // Message was properly handled
        case 0:
            return 0;

        // Message was a quit message, leave main loop
        case 1:
            this->shouldDestroyWindow = true;
            return 0;

        // Message was not handled, continue the rest of the function
        default:
            break;

    }

    int newWidth;
    int newHeight;

    switch (uMsg) {

        case WM_SIZE: {

            // Skip if gui, display, or drawer are not instantiated yet
            if (this->window == nullptr) break;
            if (this->display == nullptr) break;
            if (this->drawer == nullptr) break;

            newWidth = LOWORD(lParam);
            newHeight = HIWORD(lParam);

            // Tell display about the new dimensions
            this->display->updateDimensions(newWidth, newHeight);

            // Tell gui about the new dimensions
            this->window->updateDimensions(newWidth, newHeight);
            
            // Tell drawer about the new dimensions
            this->drawer->updateDimensions(newWidth, newHeight);

            // Also do default handling
            return 0;

        }

        // Default handling
        default:
            break;

    }

    return DefWindowProc(this->window->hwnd, uMsg, wParam, lParam);

}
