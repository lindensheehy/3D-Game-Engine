#include "ui/Core.h"


const char* Ui::actionTypeToString(ActionType type) {

    switch (type) {

        case Ui::ActionType::NONE:
            return Ui::ActionTypeString::NONE;

        case Ui::ActionType::CLOSE_WINDOW:
            return Ui::ActionTypeString::CLOSE_WINDOW;

        case Ui::ActionType::OPEN_WINDOW:
            return Ui::ActionTypeString::OPEN_WINDOW;

        case Ui::ActionType::CALL_FUNC:
            return Ui::ActionTypeString::CALL_FUNC;

        default:
            return Ui::UNKNOWN_TYPE;

    }

}

const char* Ui::elementTypeToString(ElementType type) {

    switch (type) {

        case Ui::ElementType::INVISIBLE:
            return Ui::ElementTypeString::INVISIBLE;

        case Ui::ElementType::VISUAL:
            return Ui::ElementTypeString::VISUAL;

        case Ui::ElementType::BUTTON:
            return Ui::ElementTypeString::BUTTON;

        case Ui::ElementType::DRAGABLE:
            return Ui::ElementTypeString::DRAGABLE;

        case Ui::ElementType::TEXTINPUT:
            return Ui::ElementTypeString::TEXTINPUT;

        default:
            return Ui::UNKNOWN_TYPE;

    }

}

const char* Ui::contextTypeToString(ContextType type) {

    switch (type) {

        case Ui::ContextType::NONE:
            return Ui::ContextTypeString::NONE;

        case Ui::ContextType::NAVBAR:
            return Ui::ContextTypeString::NAVBAR;

        case Ui::ContextType::TRANSFORM:
            return Ui::ContextTypeString::TRANSFORM;

        case Ui::ContextType::OBJECTS:
            return Ui::ContextTypeString::OBJECTS;

        default:
            return Ui::UNKNOWN_TYPE;

    }

}
