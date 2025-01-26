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

ActionCloseWindow::ActionCloseWindow(UIEnum::WindowType targetWindow) {

    this->actionType = UIEnum::ActionType::CLOSE_WINDOW;

    this->target = targetWindow;
    
}

ActionCloseWindow::~ActionCloseWindow() {}