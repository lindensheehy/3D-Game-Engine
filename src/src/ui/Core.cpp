#include "ui/Core.h"

const char* UIEnum::actionTypeToString(ActionType type) {

    switch (type) {

        case UIEnum::ActionType::NONE:
            return UIEnum::ActionTypeString::NONE;

        case UIEnum::ActionType::CLOSE_WINDOW:
            return UIEnum::ActionTypeString::CLOSE_WINDOW;

        case UIEnum::ActionType::OPEN_WINDOW:
            return UIEnum::ActionTypeString::OPEN_WINDOW;

        case UIEnum::ActionType::CALL_FUNC:
            return UIEnum::ActionTypeString::CALL_FUNC;

        default:
            return UIEnum::UNKNOWN_TYPE;

    }

}

const char* UIEnum::elementTypeToString(ElementType type) {

    switch (type) {

        case UIEnum::ElementType::INVISIBLE:
            return UIEnum::ElementTypeString::INVISIBLE;

        case UIEnum::ElementType::VISUAL:
            return UIEnum::ElementTypeString::VISUAL;

        case UIEnum::ElementType::BUTTON:
            return UIEnum::ElementTypeString::BUTTON;

        case UIEnum::ElementType::DRAGABLE:
            return UIEnum::ElementTypeString::DRAGABLE;

        case UIEnum::ElementType::TEXTINPUT:
            return UIEnum::ElementTypeString::TEXTINPUT;

        default:
            return UIEnum::UNKNOWN_TYPE;

    }

}

const char* UIEnum::contextTypeToString(ContextType type) {

    switch (type) {

        case UIEnum::ContextType::NONE:
            return UIEnum::ContextTypeString::NONE;

        case UIEnum::ContextType::NAVBAR:
            return UIEnum::ContextTypeString::NAVBAR;

        case UIEnum::ContextType::TRANSFORM:
            return UIEnum::ContextTypeString::TRANSFORM;

        case UIEnum::ContextType::OBJECTS:
            return UIEnum::ContextTypeString::OBJECTS;

        default:
            return UIEnum::UNKNOWN_TYPE;

    }

}
