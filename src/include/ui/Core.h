#pragma once

/*
    These enums are a way for me to pass information between classes without needing to know anything about the classes
    This allows my UI system to be much more modular, and less coupled

    Its worth noting that the namespace UI overlaps with my class UI
    This is like this becuase logically it makes sense that these enums would exist within the UI class
    but unfortunately to avoid circular dependancies, I need them in a seperate file
*/


// Forward declare WindowHandle globally
// This module is pretty entangled, so this helps with circular dependancy issues
class WindowHandle;


// String literals for commonly used file paths
namespace File {

    constexpr const char* TRANSFORM   = "../src/assets/ui/windows/transform.xml";
    constexpr const char* NAVBAR      = "../src/assets/ui/windows/navbar.xml";
    constexpr const char* OBJECTS     = "../src/assets/ui/windows/objects.xml";

};


// Type def used to identify windows
typedef unsigned int WindowID;


namespace UIEnum {

    enum class ActionType {
        NONE,               // Given to Action objects (not subclasses) as these shouldnt be used
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

    enum class ContextType {
        NONE,               // Given to Context objects (not subclasses) as these shouldnt be used
        NAVBAR,
        TRANSFORM,
        OBJECTS
    };


    // Some utility functions to help log the above enums
    const char* actionTypeToString(ActionType type);
    const char* elementTypeToString(ElementType type);
    const char* contextTypeToString(ContextType type);


    // String constants that are returned by the above utility functions
    namespace ActionTypeString {
        constexpr const char* NONE          = "NONE";
        constexpr const char* CLOSE_WINDOW  = "CLOSE_WINDOW";
        constexpr const char* OPEN_WINDOW   = "OPEN_WINDOW";
        constexpr const char* CALL_FUNC     = "CALL_FUNC";
    }

    namespace ElementTypeString {
        constexpr const char* INVISIBLE     = "INVISIBLE";
        constexpr const char* VISUAL        = "VISUAL";
        constexpr const char* BUTTON        = "BUTTON";
        constexpr const char* DRAGABLE      = "DRAGABLE";
        constexpr const char* TEXTINPUT     = "TEXTINPUT";
    }

    namespace ContextTypeString {
        constexpr const char* NONE          = "NONE";
        constexpr const char* NAVBAR        = "NAVBAR";
        constexpr const char* TRANSFORM     = "TRANSFORM";
        constexpr const char* OBJECTS       = "OBJECTS";
    }

    constexpr const char* UNKNOWN_TYPE = "UNKNOWN??";

}


