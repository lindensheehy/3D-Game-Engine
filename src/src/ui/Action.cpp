#include "ui/Action.h"


/* ---------------------------- */
/* ---------- Action ---------- */
/* ---------------------------- */

Ui::Action::Action() {
    this->type = Ui::ActionType::NONE;
}

Ui::Action::~Action() {}



/* --------------------------------------- */
/* ---------- ActionCloseWindow ---------- */
/* --------------------------------------- */

Ui::ActionCloseWindow::ActionCloseWindow(WindowID targetWindowId) {

    this->type = Ui::ActionType::CLOSE_WINDOW;

    this->targetWindowId = targetWindowId;
    
}



/* -------------------------------------- */
/* ---------- ActionOpenWindow ---------- */
/* -------------------------------------- */

Ui::ActionOpenWindow::ActionOpenWindow(const char* fileName, WindowHandle** windowHandle, void (*bindFunc)(WindowHandle*)) {

    this->type = Ui::ActionType::OPEN_WINDOW;

    this->fileName = fileName;
    this->windowHandle = windowHandle;
    this->bindFunc = bindFunc;

}



/* ----------------------------------- */
/* ---------- ActionRunFunc ---------- */
/* ----------------------------------- */

Ui::ActionCallFunc::ActionCallFunc(void (*func)(Context*), Context** context) {

    this->type = Ui::ActionType::CALL_FUNC;

    this->func = func;
    this->context = context;

}

void Ui::ActionCallFunc::callFunc() {

    if (this->context == nullptr) return;

    this->func( *(this->context) );

}
