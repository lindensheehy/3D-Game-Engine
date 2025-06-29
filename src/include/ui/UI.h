#pragma once

#include "util/Utility.h"
#include "util/Log.h"

#include "ui/Core.h"
#include "ui/Action.h"
#include "ui/WindowElement.h"
#include "ui/Window.h"
#include "ui/BindManager.h"

#include "xml/XML.h"

#include "geometry/Vec.h"
#include "graphics/gui/Gui.h"
#include "util/LinkedList.h"


// Forward declaration
namespace Graphics {
    namespace Drawing {
        class Drawer;
    }
}


namespace Ui {

class UI {

    /*
        This class serves as the entry point for the ui module
        All the other classes in this directory are accessed and managed through this class
    */
    
    public:

        /*   Instance Variables   */

        // Will be true if the last click landed within the UI
        bool hasMouseFocus;

        // Contains a BindManager object, owned by this class
        // This handles all the binding logic for the windows
        Ui::BindManager* bindManager;


        // Constructor
        UI();

        // Destructor
        ~UI();


        /*   Instance Functions   */

        // Draws all the currently existing windows
        void draw(Graphics::Drawing::Drawer* drawer);

        // Updates the UI based on the input events. Returns true if the input was handled by the UI. 
        // 'cursorStateOut' will be given the state the cursor should be in, after querying what element is hovered (if any)
        bool doInput(const Graphics::Gui::State* state, Graphics::Gui::CursorState* cursorStateOut = nullptr);

        // Creates a new window and returns a WindowHandle for it
        Ui::WindowHandle* createWindow(const char* fileName);

        // Destroys the given window
        // Also sets the WindowHandle to an invalid state
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

        // Master Window list (this class owns the list items)
        LinkedList<Ui::Window*>* windows;

        // Saves the last clicked element to be used by 'doInput'
        Ui::WindowElement* lastClicked;

        // Stores the location the next window should go, changes on every window made to reduce window overlap
        Geometry::Vec2 nextWindowPos;

        // This is the next free id that will be assigned to a window on creation
        // This is incremented on each window creation (unless youre creating >2^31 windows, this is fine)
        int nextFreeWindowId;

        // Reference to a shared Action queue (this class owns the list, but NOT the list items)
        static LinkedList<Ui::Action*>* actionQueue;


        /*   Instance Functions   */

        // This will execute the actions in 'actionQueue', if any exist
        void handleActions();

        // Updates the private vector by +(50, 50). Also rolls over x and y if they pass 500 and 300 respectively
        void updateNextWindowPos();

        // Private overloads of destroyWindow
        void destroyWindow(Ui::WindowID windowId);
        void destroyWindow(Ui::Window* window);

        // Returns the next Action object from the actionQueue
        static Ui::Action* getNextAction();
        
};

}
