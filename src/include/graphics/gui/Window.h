#pragma once

#include "graphics/gui/Core.h"


namespace Graphics {
namespace Gui {

class Window {

    /*
        This class is basically just a wrapper for the windows API. 
        It serves to simplify and abstract away from the low level aspects of window handling.
        The constructor creates the window, and then the instance variable "buffer" holds the pixel data of the window.
        Calling flip() will write the pixels in the buffer to the window.
    */

    public:

        /* --- Instance variables --- */

        // Window size
        int windowWidth, windowHeight;

        LPCSTR windowTitle;

        // Pixel buffer
        uint32* buffer;

        HWND hwnd;                      // Handle to created window
        HINSTANCE hInstance;            // Handle to main


        // Constructor
        Window(WindowProcFunc windowProcFunc, int windowWidth, int windowHeight, LPCSTR windowTitle = "Window");

        // Destructor
        ~Window();

        /*   Instance functions   */

        // Updates this instance with new window dimensions
        void updateDimensions(int width, int height);
        
        // Tells Windows to redraw the window
        void flip() const;

        // Sends all the messages from Windows to the WindowProc function. Will break on a WM_PAINT message so the main loop can execute before drawing
        void handleMessages() const;

        // Updates the cursor state
        void setCursorState(CursorState cursorState);

    private:

        /*   Instance Variables   */

        HDC hdc;
        HDC memDC;
        HBITMAP hBitmap;

        BITMAPINFO bitmapInfo;          // Stores info to help windows translate the pixel buffer into Uint32 format

        // Stores the different cursor type handles
        HCURSOR hCursorArrow;
        HCURSOR hCursorHand;
        HCURSOR hCursorText;
        
};

}
}
