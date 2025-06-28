#pragma once

#include "util/Utility.h"

#include "util/KeyCodes.h"


namespace Graphics {
namespace Gui {

    // This is the default size of any pixel mapped buffer
    // This is intended to be big enough that resizing will never require reallocations
    static constexpr unsigned int PIXEL_BUFFER_WIDTH = 3840;
    static constexpr unsigned int PIXEL_BUFFER_HEIGHT = 2160;


    // Typedef to help clarify typing of a WindowProc in the Window constructor
    typedef LRESULT(CALLBACK* WindowProcFunc)(HWND, UINT, WPARAM, LPARAM);


    // Enum used to help set the mouse cursor state
    enum CursorState : char {

        // Regular arrow cursor
        CURSOR_ARROW,

        // Clickable hand cursor
        CURSOR_HAND,

        // Edit text cursor
        CURSOR_TEXT,

    };

}
}
