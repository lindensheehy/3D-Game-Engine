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

ActionOpenWindow::ActionOpenWindow(const char* fileName) {

    this->actionType = UIEnum::ActionType::OPEN_WINDOW;

    this->fileName = fileName;

}



/* ----------------------------------- */
/* ---------- ActionRunFunc ---------- */
/* ----------------------------------- */

ActionCallFunc::ActionCallFunc(void (*func)()) {

    this->actionType = UIEnum::ActionType::CALL_FUNC;

    this->func = func;

}

void ActionCallFunc::callFunc() {

    this->func();

}
