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

ActionCloseWindow::~ActionCloseWindow() {}
