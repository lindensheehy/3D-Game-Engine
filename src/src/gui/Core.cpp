#include "gui/Core.h"

bool Gui::hasValidChar(KeyCode key) {

    // Letter Keys
    if (key >= KeyCode::NUM_0 && key <= KeyCode::NUM_9) return true;

    // Number Keys
    if (key >= KeyCode::A && key <= KeyCode::Z) return true;

    if (key == KeyCode::PERIOD) return true;
    if (key == KeyCode::MINUS) return true;

    return false;

}

char Gui::keyCodeToChar(KeyCode key) {

    if ( !(hasValidChar(key)) ) return '\0';

    if (key == KeyCode::PERIOD) return '.';
    if (key == KeyCode::MINUS) return '-';

    // Conveinently, the Windows keycodes are the same as the char codes, so direct casting works
    return (char) (key);
}
