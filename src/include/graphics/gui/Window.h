#pragma once

#include "graphics/gui/Core.h"


namespace Graphics {
namespace Gui {

class Window {

    /*
        This class just wraps window creation/maintenance with the WinAPI
        The constructor creates the window, and then 'buffer' holds the pixel data of the window.
        Calling flip() will write the pixels in the buffer to the window.
    */

    public:

        /*   Instance Variables   */

        int windowWidth, windowHeight;

        LPCSTR windowTitle;

        // Pixel buffer
        uint32* buffer;

        HWND hwnd;                      // Handle to created window
        HINSTANCE hInstance;            // Handle to main (this app in Windows)


        // Constructor
        Window(WindowProcFunc windowProcFunc, int windowWidth, int windowHeight, LPCSTR windowTitle = "Window");

        // Destructor
        ~Window();


        /*   Instance functions   */

        // Updates this instance with new window dimensions
        void updateDimensions(int width, int height);
        
        // Tells Windows to redraw the window
        void flip() const;

        // Sends all the messages from Windows to the WindowProc function. Should be called every frame
        void handleMessages() const;

        // Updates the cursor state
        void setCursorState(CursorState cursorState);

    private:

        /*   Instance Variables   */

        HDC hdc;
        HDC memDC;
        HBITMAP hBitmap;

        // Stores info to help windows translate the pixel buffer to a bitmap
        BITMAPINFO bitmapInfo;

        // Stores the different cursor type handles (loaded on construction)
        HCURSOR hCursorArrow;
        HCURSOR hCursorHand;
        HCURSOR hCursorText;
        
};

}
}
