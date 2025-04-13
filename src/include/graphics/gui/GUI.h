#pragma once

#include "graphics/gui/Core.h"

#include "graphics/gui/State.h"
#include "graphics/gui/Window.h"

#include "util/LinkedList.h"
#include "graphics/rendering/Display.h"
#include "graphics/drawing/Drawer.h"


namespace Graphics {
namespace Gui {

class GUI {

    /*
        This class serves as the entry point for the gui module
        This contains everything you need to open and use a Windows window
        When instantiating this class, a new window will be created
        This instance then allows for drawing to the window, and lets you track input events in a usable interface
    */

    public:

        /*   Instance Variables   */

        // This class is composed mostly of these other classes in this module

        // Holds information about the window dimensions, alongside some utility functions for rendering
        Rendering::Display* display;

        // This is the object that handles all the drawing
        // Contains high level functions to draw various shapes
        Drawing::Drawer* drawer;

        // Holds information about the state of the GUI window
        // Contains data for time, mouse buttons/position, key presses, etc.
        State* state;

        // Holds the actual Windows window
        // This is the main wrapper for all the low level Windows API stuff
        Window* window;

        // Tells if the window has been closed or not
        // When this is set to true, you should free this instance and stop using it
        bool shouldDestroyWindow;


        // Constructor
        GUI(int width, int height, const char* windowName);

        // Destructor
        ~GUI();


        /*   Instance Functions   */

        // This updates the data in this GUI instance based on the message from Windows
        // This will return non 0 if the message was not handled
        LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);



    private:

        /*   Instance Functions   */

};

}
}
