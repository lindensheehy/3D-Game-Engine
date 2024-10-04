#pragma once

#include "Window.h"
#include "LinkedList.h"
#include "ObjectSet.h"
#include "State.h"


class UI {
    
    public:

        /*   Instance Variables   */

        WindowElement* selectedTextBox; // Saves the last clicked textbox to type in
        WindowElement* lastClicked; // Used for dragging elements with the mouse


        // Constructor
        UI();

        // Destructor
        ~UI();


        /*   Instance Functions   */

        // Draws all the windows
        void draw(Drawer* drawer);

        // Removes a window object from the interal linked list
        void deleteWindow(Window* window);

        // Checks all the ui elements against the inputs for the frame
        void doInput(State* state);

        // Creates a new "Transform" window linked to the given Object
        void createWindowTransform(Object* object);

    private:

        /*   Instance Variables   */

        LinkedList<Window*>* windows;


        /*   Instance Functions   */

        // Adds a window object to the interal linked list
        void addWindow(Window* window);

};
