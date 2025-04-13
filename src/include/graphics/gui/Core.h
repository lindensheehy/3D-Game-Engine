#pragma once

#include "util/Utility.h"

#include "util/KeyCodes.h"


namespace Graphics {
namespace Gui {

    // This is the default size of any pixel mapped buffer
    // This is intended to be big enough that resizing will never require reallocations
    static constexpr unsigned int PIXEL_BUFFER_WIDTH = 3840;
    static constexpr unsigned int PIXEL_BUFFER_HEIGHT = 2160;


    // Typedef to help pass a WindowProc to the constructor
    typedef LRESULT(CALLBACK* WindowProcFunc)(HWND, UINT, WPARAM, LPARAM);


    // Enum used to help set the mouse cursor state
    enum CursorState {

        // Regular arrow cursor
        CURSOR_ARROW,

        // Clickable hand cursor
        CURSOR_HAND,

        // Edit text cursor
        CURSOR_TEXT

    };

}
}
