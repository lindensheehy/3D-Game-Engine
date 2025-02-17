#pragma once

#include "util/Utility.h"

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

class Gui {

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
        Gui(WindowProcFunc windowProcFunc, int windowWidth, int windowHeight, LPCSTR windowTitle = "Window");

        // Destructor
        ~Gui();

        /*   Instance functions   */
        
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
