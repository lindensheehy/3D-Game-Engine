#pragma once

#include "Utility.h"

// For logging error cases
#include "Log.h"

// Typedef to help pass a WindowProc to the constructor
typedef LRESULT(CALLBACK* WindowProcFunc)(HWND, UINT, WPARAM, LPARAM);


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

        const wchar_t* windowTitle;

        // Pixel buffer
        uint32* buffer;


        // Constructor
        Gui(WindowProcFunc windowProcFunc, int windowWidth, int windowHeight, const wchar_t* windowTitle = L"Window");

        // Destructor
        ~Gui();

        /*   Instance functions   */
        
        // Tells Windows to redraw the window
        void flip();

    private:

        /*   Instance Variables   */

        HWND hwnd;                      // Handle to created window
        HINSTANCE hInstance;            // Handle to main

        BITMAPINFO bitmapInfo;          // Stores info to help windows translate the pixel buffer into Uint32 format

        WindowProcFunc windowProcFunc;  // This is the event handler for the window. Gets passed in the constructor

        /*   Instance Functions   */

        void handleMessages();

};
