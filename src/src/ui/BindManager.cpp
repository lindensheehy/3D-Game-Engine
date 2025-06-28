#include "ui/BindManager.h"

using namespace Ui;


BindManager::BindManager() {

    this->binds = new LinkedList<Bind*>();

    return;

}

BindManager::~BindManager() {

    Bind* current;

    for (this->binds->iterStart(0); this->binds->iterHasNext(); this->binds->iterNext()) {

        current = this->binds->iterGetObj();
        delete current;

    }

    delete this->binds;

    return;

}

void BindManager::addBind(WindowHandle* windowHandle, BindFunc bindFunc) {
    
    if (windowHandle == nullptr) {
        logWrite("BindManager::addBind(WindowHandle*, BindFunc) was called on a nullptr!", true);
        return;
    }

    Bind* newBind = new Bind(windowHandle, bindFunc);

    this->binds->pushBack(newBind);

    // Call the bind func
    bindFunc(windowHandle);

    return;

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

    return;

}

void BindManager::rebind(WindowHandle* windowHandle) const {

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

void BindManager::rebindAll() const {

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

    return;

}

BindManager::Bind* BindManager::getBind(WindowHandle* windowHandle) const {

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

    return;

}
