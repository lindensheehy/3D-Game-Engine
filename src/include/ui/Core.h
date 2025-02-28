#pragma once

/*
    These enums are a way for me to pass information between classes without needing to know anything about the classes
    This allows my UI system to be much more modular, and less coupled

    Its worth noting that the namespace UI overlaps with my class UI
    This is like this becuase logically it makes sense that these enums would exist within the UI class
    but unfortunately to avoid circular dependancies, I need them in a seperate file
*/


// String literals for commonly used file paths
namespace File {

    constexpr const char* TRANSFORM   = "../src/assets/ui/windows/transform.xml";
    constexpr const char* NAVBAR      = "../src/assets/ui/windows/navbar.xml";
    constexpr const char* OBJECT      = "../src/assets/ui/windows/object.xml";

};


// Type def used to identify windows
typedef unsigned int WindowID;


namespace UIEnum {

    enum class ActionType {
        NONE,               // Given to Action objects (not subclasses) as these shouldnt be used directly
        CLOSE_WINDOW,
        OPEN_WINDOW,
        CALL_FUNC
    };

    enum class ElementType {
        INVISIBLE,
        VISUAL,
        BUTTON,
        DRAGABLE,
        TEXTINPUT
    };

}
