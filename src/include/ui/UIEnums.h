#pragma once

/*
    These enums are a way for me to pass information between classes without needing to know anything about the classes
    This allows my UI system to be much more modular, and less coupled

    Its worth noting that the namespace UI overlaps with my class UI
    This is like this becuase logically it makes sense that these enums would exist within the UI class
    but unfortunately to avoid circular dependancies, I need them in a seperate file
*/


namespace UIEnum {

    enum class ActionType {
        NONE,               // Given to Action objects (not subclasses) as these shouldnt be used directly
        CLOSE_WINDOW
    };

    enum class ElementType {
        INVISIBLE,
        VISUAL,
        BUTTON,
        DRAGABLE,
        TEXTINPUT
    };

    enum class WindowType {
        UNKNOWN,
        TRANSFORM
    };

}
