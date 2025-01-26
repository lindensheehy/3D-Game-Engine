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

ActionCloseWindow::ActionCloseWindow() {
    this->actionType = UIEnum::ActionType::CLOSE_WINDOW;
}

ActionCloseWindow::~ActionCloseWindow() {}