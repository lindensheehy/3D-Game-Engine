#include "../include/UI.h"


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

    newWindow->addElement(WindowElement::createTopBar(newWindow, "Transform"));

    WindowElement* temp = new WindowButton(50, 50, 50, 50);
    temp->action = new ActionLogWrite("test");
    newWindow->addElement(temp);

    this->addWindow(newWindow);

}

void UI::addWindow(Window* window) {

    this->windows->pushBack(window);

}
