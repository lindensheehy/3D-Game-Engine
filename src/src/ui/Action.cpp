#include "ui/Action.h"

using namespace Ui;


/* --------------------------------------- */
/* ---------- ActionCloseWindow ---------- */
/* --------------------------------------- */

ActionCloseWindow::ActionCloseWindow(WindowID targetWindowId) {

    this->type = ActionType::CLOSE_WINDOW;

    this->targetWindowId = targetWindowId;

    return;

}



/* -------------------------------------- */
/* ---------- ActionOpenWindow ---------- */
/* -------------------------------------- */

ActionOpenWindow::ActionOpenWindow(const char* fileName, WindowHandle** windowHandle, void (*bindFunc)(WindowHandle*)) {

    this->type = ActionType::OPEN_WINDOW;

    this->fileName = fileName;
    this->windowHandle = windowHandle;
    this->bindFunc = bindFunc;

    return;

}



/* ----------------------------------- */
/* ---------- ActionRunFunc ---------- */
/* ----------------------------------- */

ActionCallFunc::ActionCallFunc(void (*func)(Context*), Context** context) {

    this->type = ActionType::CALL_FUNC;

    this->func = func;
    this->context = context;

    return;

}

void ActionCallFunc::callFunc() {

    if (this->context == nullptr) return;

    this->func( *(this->context) );

    return;

}
