#include "ui/Window.h"


// Static declarations
LinkedList<Action*>* Window::actionQueue;

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

    this->elements = new LinkedList<WindowElement*>();

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

bool Window::hitTest(int x, int y) {

    return (
        x < this->endPos->x && 
        x > this->pos->x &&
        y < this->endPos->y && 
        y > this->pos->y 
    );

}

void Window::addElement(WindowElement* element) {

    this->elements->pushBack(element);
    return;

}

WindowElement* Window::doInput(State* state) {

    bool insideWindow = this->hitTest(state->mouse->posX, state->mouse->posY);

    // Return nullptr if the click lies outside the bounds of the window
    if (!insideWindow) return nullptr;

    WindowElement* current; // The element checked on the given iteration
    WindowElement* found;   // Stores the element which was clicked on, or nullptr if none

    for (this->elements->iterStart(0); !this->elements->iterIsDone(); this->elements->iterNext()) {

        current = this->elements->iterGetObj();
        found = current->doInput(state, this->pos);

        if (found != nullptr) return found;

    }

    // If the loop completes, nothing inside
    return nullptr;

}

void Window::setActionQueue(LinkedList<Action*>* queue) {
    Window::actionQueue = queue;
}

void Window::queueAction(Action* action) {
    Window::actionQueue->pushBack(action);
}
