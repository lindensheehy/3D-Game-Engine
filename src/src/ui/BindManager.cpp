#include "ui/BindManager.h"

// Constructor
BindManager::BindManager() {

    this->binds = new LinkedList<Bind*>();

    return;

}

// Destructor
BindManager::~BindManager() {

    // List items are stack allocated, no need to free them
    if (this->binds != nullptr) {
        
        // Free any item in the list, as these are heap allocated
        if (this->binds->length != 0) {

            Bind* current;

            for (this->binds->iterStart(0); this->binds->iterHasNext(); this->binds->iterNext()) {
                current = this->binds->iterGetObj();
                delete current;
            }

        }

        delete this->binds;

    }

    return;

}

// Instance Functions
void BindManager::addBind(WindowHandle* windowHandle, BindFunc bindFunc) {
    
    if (windowHandle == nullptr) {
        logWrite("BindManager::addBind(WindowHandle*, BindFunc) was called on a nullptr!", true);
        return;
    }

    Bind* newBind = new Bind(windowHandle, bindFunc);

    this->binds->pushBack(newBind);

}

void BindManager::removeBind(WindowHandle* windowHandle) {

    if (windowHandle == nullptr) {
        logWrite("BindManager::removeBind(WindowHandle*) was called on a nullptr!", true);
        return;
    }

    Bind* toRemove = this->getBind(windowHandle);

    if (toRemove == nullptr) {
        logWrite("BindManager::removeBind(WindowHandle*) found no bind for the given WindowHandle!", true);
        return;
    }

    this->removeBind(toRemove);

}

void BindManager::rebind(WindowHandle* windowHandle) {

    if (windowHandle == nullptr) {
        logWrite("BindManager::rebind(WindowHandle*) was called on a nullptr!", true);
        return;
    }

    Bind* toRebind = this->getBind(windowHandle);

    if (toRebind == nullptr) {
        logWrite("BindManager::rebind(WindowHandle*) found no bind for the given WindowHandle!", true);
        return;
    }

    toRebind->bindFunc(windowHandle);

    return;

}

void BindManager::rebindAll() {

    Bind* current;

    for (this->binds->iterStart(0); this->binds->iterHasNext(); this->binds->iterNext()) {

        current = this->binds->iterGetObj();
        
        // No list item should be nullptr
        if (current == nullptr) {
            logWrite("BindManager::getBind() found a nullptr item in the binds linked list!", true);
            return;
        }

        current->bindFunc(current->windowHandle);

    }

}

BindManager::Bind* BindManager::getBind(WindowHandle* windowHandle) {

    Bind* current;

    for (this->binds->iterStart(0); this->binds->iterHasNext(); this->binds->iterNext()) {

        current = this->binds->iterGetObj();
        
        // No list item should be nullptr
        if (current == nullptr) {
            logWrite("BindManager::getBind() found a nullptr item in the binds linked list!", true);
            return nullptr;
        }

        if (current->windowHandle == windowHandle) return current;

    }

    // None found
    return nullptr;

}

void BindManager::removeBind(Bind* bind) {

    this->binds->pop(bind);

}
