#include "ui/Window.h"


// Static Declarations
LinkedList<Ui::Action*>* Ui::Window::actionQueue;

// Constructors
Ui::Window::Window(int posx, int posy, int sizex, int sizey, int layer /* Default value = 0 */) {

    this->pos = new Vec2(posx, posy);
    this->size = new Vec2(sizex, sizey);
    this->layer = layer;

    this->elements = new LinkedList<WindowElement*>();
    this->bindables = new LinkedList<Bindable*>();

    this->endPos = this->pos->copy()->add(this->size);

}

Ui::Window::Window(Vec2* pos, Vec2* size, int layer /* Default value = 0 */) {

    this->pos = pos;
    this->size = size;
    this->layer = layer;

    this->elements = new LinkedList<WindowElement*>();
    this->bindables = new LinkedList<Bindable*>();

    this->endPos = this->pos->copy()->add(this->size);

}

// Destructor
Ui::Window::~Window() {

    if (this->pos != nullptr) delete this->pos;
    if (this->size != nullptr) delete this->size;
    if (this->endPos != nullptr) delete this->endPos;

    // Free the child elements
    if (this->elements != nullptr) {

        if (this->elements->length > 0) {

            WindowElement* element;

            for (this->elements->iterStart(0); !this->elements->iterIsDone(); this->elements->iterNext()) {
                element = this->elements->iterGetObj();
                if (element != nullptr) delete element;
            }

        }

        delete this->elements;

    }

    // Free the bindables
    if (this->bindables != nullptr) {

        if (this->bindables->length > 0) {

            Bindable* bindable;

            for (this->bindables->iterStart(0); !this->bindables->iterIsDone(); this->bindables->iterNext()) {
                bindable = this->bindables->iterGetObj();
                if (bindable != nullptr) delete bindable;
            }
            
        }

        delete this->bindables;

    }

    return;

}

// Instance Functions
void Ui::Window::draw(Gui::Drawer* drawer) {

    for (this->elements->iterStart(0); !this->elements->iterIsDone(); this->elements->iterNext())
        this->elements->iterGetObj()->draw(drawer, this->pos);

    return;

}

Ui::WindowElement* Ui::Window::hitTest(int x, int y) {

    // Position does not lie within the window
    if (
        x > this->endPos->x || 
        x < this->pos->x ||
        y > this->endPos->y || 
        y < this->pos->y 
    ) return nullptr;

    // Check children
    WindowElement* current;
    WindowElement* found = nullptr;
    for (this->elements->iterStart(0); this->elements->iterHasNext(); this->elements->iterNext()) {

        current = this->elements->iterGetObj();

        found = current->hitTest(x, y, this->pos);

        if (found != nullptr) break;

    }

    return found;

}

void Ui::Window::addElement(WindowElement* element) {

    this->elements->pushBack(element);

    // Reset the flag. This element may be bindable
    this->bindablesUpdated = false;

    return;

}

void Ui::Window::bindButton(const char* id, Action* action) {

    WindowElement* bindable = this->getBindable(id);

    if (bindable == nullptr) {
        logWrite("Window::bindButton() was called on a non existant id!", true);
        logWrite(" -> Tried to find id \"");
        logWrite(id);
        logWrite("\" but failed", true);
        return;  
    }

    // First make sure its actually a WindowButton
    if (bindable->type != Ui::ElementType::BUTTON) return;

    WindowButton* casted = (WindowButton*) bindable;

    casted->bind(action);

    return;

}

void Ui::Window::bindDragable(const char* id, Vec2* posToDrag, Vec2* endPosToDrag) {

    WindowElement* bindable = this->getBindable(id);

    // First make sure its actually a WindowDragable
    if (bindable->type != Ui::ElementType::DRAGABLE) return;

    WindowDragable* casted = (WindowDragable*) bindable;

    casted->bind(posToDrag, endPosToDrag);

    return;

}

void Ui::Window::bindTextInput(const char* id, int* boundValue) {

    WindowElement* bindable = this->getBindable(id);

    // First make sure its actually a WindowDragable
    if (bindable->type != Ui::ElementType::TEXTINPUT) return;

    WindowTextInput* casted = (WindowTextInput*) bindable;

    casted->bind(boundValue);

    return;

}

void Ui::Window::bindTextInput(const char* id, float* boundValue) {

    WindowElement* bindable = this->getBindable(id);

    // First make sure its actually a WindowDragable
    if (bindable->type != Ui::ElementType::TEXTINPUT) return;

    WindowTextInput* casted = (WindowTextInput*) bindable;

    casted->bind(boundValue);

    return;

}

void Ui::Window::setPos(int x, int y) {

    Vec2* temp = this->pos->copy()->sub(x, y);

    this->pos->sub(temp);
    this->endPos->sub(temp);

    delete temp;

    return;

}

void Ui::Window::setPos(Vec2* newPos) {

    Vec2* temp = this->pos->copy()->sub(newPos);

    this->pos->sub(temp);
    this->endPos->sub(temp);

    delete temp;

    return;

}

Ui::WindowElement* Ui::Window::getBindable(const char* id) {

    if (this->bindablesUpdated == false) {
        this->locateBindables();
    }

    Bindable* current;

    for (this->bindables->iterStart(0); this->bindables->iterHasNext(); this->bindables->iterNext()) {

        current = this->bindables->iterGetObj();

        // Compare the id strings
        int i = 0;
        bool mismatch = false;
        while (true) {

            if (current->id[i] == '\0') break;
            if (id[i] == '\0') break;

            if (current->id[i] != id[i]) {
                mismatch = true;
                break;
            } 

            i++;

        }

        // If they mismatched, skip to the next bindable
        if (mismatch) continue;

        // If both strings reached the '\0' char, they match
        if (  current->id[i] == '\0'  &&  id[i] == '\0'  ) {
            return current->element;
        }

    }

    // No match found
    return nullptr;

}

void Ui::Window::locateBindables() {

    if (this->bindables->length != 0) {

        Bindable* bindable;

        for (this->bindables->iterStart(0); !this->bindables->iterIsDone(); this->bindables->iterNext()) {
            bindable = this->bindables->iterGetObj();
            if (bindable != nullptr) delete bindable;
        }

        delete this->bindables;
        this->bindables = new LinkedList<Bindable*>();
        
    }

    WindowElement* current;

    for (this->elements->iterStart(0); this->elements->iterHasNext(); this->elements->iterNext()) {

        current = this->elements->iterGetObj();

        if (current != nullptr)
            this->locateBindables(current);

    }

    // Set flag
    this->bindablesUpdated = true;

    return;

}

void Ui::Window::locateBindables(WindowElement* root) {
    
    // This is the part that adds the bindable if needed
    if (root->id != nullptr) {

        Bindable* newBindable = new Bindable();
        newBindable->id = root->id;
        newBindable->element = root;

        this->bindables->pushBack(newBindable);

    }

    // Recursive part
    WindowElement* current;

    for (root->children->iterStart(0); root->children->iterHasNext(); root->children->iterNext()) {

        current = root->children->iterGetObj();

        if (current != nullptr)
            this->locateBindables(current);

    }

    return;

}

// Class Functions
void Ui::Window::setActionQueue(LinkedList<Action*>* queue) {
    Window::actionQueue = queue;
}

void Ui::Window::queueAction(Action* action) {
    Window::actionQueue->pushBack(action);
}
