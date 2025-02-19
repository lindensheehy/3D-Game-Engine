#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "gui/Drawer.h"
#include "util/LinkedList.h"
#include "physics/ObjectSet.h"

#include "ui/UIEnums.h"
#include "ui/Action.h"
#include "ui/WindowElement.h"
#include "ui/Window.h"

#include "xml/XML.h"



class UI {

    /*
        The parent class to everything in this file. 
        All the other classes included here will be managed and accessed through this
    */
    
    public:

        /*   Instance Variables   */

        WindowElement* lastClicked; // Saves the last clicked element to be used with input

        // Will be true if the last click landed within the UI
        bool hasFocus;


        // Constructor
        UI();

        // Destructor
        ~UI();


        /*   Instance Functions   */

        // Draws all the windows
        void draw(Drawer* drawer);

<<<<<<< Updated upstream
        // Removes a window object from the interal linked list
        void deleteWindow(Window* window);

        // Checks all the ui elements against the inputs for the frame. Returns true if the click lands on a window
        bool doInput(State* state);
=======
        // Updates the UI based on the input events. Returns true if the input was handled by the UI. 
        // If a variable is passed to cursorStateOut, it will be set to the state the cursor should be in
        bool doInput(State* state, CursorState* cursorStateOut = nullptr);
>>>>>>> Stashed changes

        // Creates a new window and returns the window identifier
        WindowID createWindow(const char* fileName);

        // Destroys the given window
        void destroyWindow(WindowID windowId);
        void destroyWindow(Window* window);

        // Binds the window to the object. Assumes the passed id references a transform window
        // If the passed window is not a transform window, this will log warnings and have undefined behaviour
        void bindWindowTransform(WindowID windowId, Object* object);

        // Returns the next Action object from the actionQueue
        static Action* getNextAction();

        
    private:

        /*   Instance Variables   */

        // Contains an XML object, owned by this class
        XML* xml;

        LinkedList<Window*>* windows;

        // Stores the location the next window should go, changes on every window made to reduce window overlap
        Vec2* nextWindowPos;


        /*   Class Variables   */

        static const Vec2* TransformWindowSize;

        // Reference to a shared Action queue
        static LinkedList<Action*>* actionQueue;


        /*   Instance Functions   */

        // Updates the private vector by +(50, 50). Also rolls over x and y if they pass 500 and 300 respectively
        void updateNextWindowPos();
        
};
