#include "ui/Action.h"


/* ---------------------------- */
/* ---------- Action ---------- */
/* ---------------------------- */

Action::Action() {
    this->actionType = UIEnum::ActionType::NONE;
}

Action::~Action() {}



/* --------------------------------------- */
/* ---------- ActionCloseWindow ---------- */
/* --------------------------------------- */

ActionCloseWindow::ActionCloseWindow(WindowID targetWindowId) {

    this->actionType = UIEnum::ActionType::CLOSE_WINDOW;

    this->targetWindowId = targetWindowId;
    
}



/* -------------------------------------- */
/* ---------- ActionOpenWindow ---------- */
/* -------------------------------------- */

ActionOpenWindow::ActionOpenWindow(const char* fileName, WindowHandle** windowHandle, void (*bindFunc)(WindowHandle*)) {

    this->actionType = UIEnum::ActionType::OPEN_WINDOW;

    this->fileName = fileName;
    this->windowHandle = windowHandle;
    this->bindFunc = bindFunc;

}



/* ----------------------------------- */
/* ---------- ActionRunFunc ---------- */
/* ----------------------------------- */

ActionCallFunc::ActionCallFunc(void (*func)(Context*), Context** context) {

    this->actionType = UIEnum::ActionType::CALL_FUNC;

    this->func = func;
    this->context = context;

}

void ActionCallFunc::callFunc() {

    if (this->context == nullptr) return;

    this->func( *(this->context) );

}
