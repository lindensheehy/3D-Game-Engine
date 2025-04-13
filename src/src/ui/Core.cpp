#include "ui/Core.h"

using namespace Ui;


const char* Ui::actionTypeToString(ActionType type) {

    switch (type) {

        case ActionType::NONE:
            return ActionTypeString::NONE;

        case ActionType::CLOSE_WINDOW:
            return ActionTypeString::CLOSE_WINDOW;

        case ActionType::OPEN_WINDOW:
            return ActionTypeString::OPEN_WINDOW;

        case ActionType::CALL_FUNC:
            return ActionTypeString::CALL_FUNC;

        default:
            return UNKNOWN_TYPE;

    }

}

const char* Ui::elementTypeToString(ElementType type) {

    switch (type) {

        case ElementType::INVISIBLE:
            return ElementTypeString::INVISIBLE;

        case ElementType::VISUAL:
            return ElementTypeString::VISUAL;

        case ElementType::BUTTON:
            return ElementTypeString::BUTTON;

        case ElementType::DRAGABLE:
            return ElementTypeString::DRAGABLE;

        case ElementType::TEXTINPUT:
            return ElementTypeString::TEXTINPUT;

        default:
            return UNKNOWN_TYPE;

    }

}

const char* Ui::contextTypeToString(ContextType type) {

    switch (type) {

        case ContextType::NONE:
            return ContextTypeString::NONE;

        case ContextType::NAVBAR:
            return ContextTypeString::NAVBAR;

        case ContextType::TRANSFORM:
            return ContextTypeString::TRANSFORM;

        case ContextType::OBJECTS:
            return ContextTypeString::OBJECTS;

        default:
            return UNKNOWN_TYPE;

    }

}
