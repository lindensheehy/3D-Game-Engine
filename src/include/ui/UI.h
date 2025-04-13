#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "graphics/drawing/Drawer.h"
#include "graphics/gui/Gui.h"
#include "util/LinkedList.h"

#include "ui/Core.h"
#include "ui/Action.h"
#include "ui/WindowElement.h"
#include "ui/Window.h"
#include "ui/BindManager.h"

#include "xml/XML.h"



namespace Ui {

class UI {

    /*
        The parent class to everything in this file. 
        All the other classes included here will be managed and accessed through this
    */
    
    public:

        /*   Instance Variables   */

        // Will be true if the last click landed within the UI
        bool hasFocus;

        // Contains a BindManager object, owned by this class
        // This handles all the binding logic for the windows
        Ui::BindManager* bindManager;


        // Constructor
        UI();

        // Destructor
        ~UI();


        /*   Instance Functions   */

        // Draws all the windows
        void draw(Graphics::Drawing::Drawer* drawer);

        // Updates the UI based on the input events. Returns true if the input was handled by the UI. 
        // If a variable is passed to cursorStateOut, it will be set to the state the cursor should be in
        bool doInput(Graphics::Gui::State* state, Graphics::Gui::CursorState* cursorStateOut = nullptr);

        // Creates a new window and returns the window identifier
        Ui::WindowHandle* createWindow(const char* fileName);

        // Destroys the given window
        // Also sets the values in the struct to invalid states
        void destroyWindow(Ui::WindowHandle* windowHandle);

        // This ensures that a Window object that the handle refers to exists
        // If it doesnt, it will free the handle and set the pointer to nullptr
        void validateWindowHandle(Ui::WindowHandle** windowHandle);

        // Sets the window to the specified position ( (0, 0) is the top left )
        void setWindowPos(Ui::WindowHandle* windowHandle, int posx, int posy);

        
    private:

        /*   Instance Variables   */

        // Contains an XML object, owned by this class
        // Used for parsing .xml files into UI elements/windows
        Xml::XML* xml;

        LinkedList<Ui::Window*>* windows;

        // Saves the last clicked element to be used with input
        Ui::WindowElement* lastClicked;

        // Stores the location the next window should go, changes on every window made to reduce window overlap
        Geometry::Vec2* nextWindowPos;

        // This is the next free id that will be assigned to a window on creation
        // This is also incremented on each window creation
        int nextFreeWindowId;


        /*   Class Variables   */

        static const Geometry::Vec2* TransformWindowSize;

        // Reference to a shared Action queue
        static LinkedList<Ui::Action*>* actionQueue;


        /*   Instance Functions   */

        void handleActions();

        // Updates the private vector by +(50, 50). Also rolls over x and y if they pass 500 and 300 respectively
        void updateNextWindowPos();

        // Private overloads of destroyWindow
        void destroyWindow(Ui::WindowID windowId);
        void destroyWindow(Ui::Window* window);

        // Returns the Window object with the given id
        Ui::Window* getWindowByHandle(Ui::WindowHandle windowHandle);

        // Returns the next Action object from the actionQueue
        static Ui::Action* getNextAction();
        
};

}
