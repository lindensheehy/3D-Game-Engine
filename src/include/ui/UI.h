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



class UI {

    /*
        The parent class to everything in this file. 
        All the other classes included here will be managed and accessed through this
    */
    
    public:

        /*   Instance Variables   */

        WindowElement* lastClicked; // Saves the last clicked element to be used with input

        // Windows currently open. will be nullptr if theyre not open
        Window* transformWindow;


        // Constructor
        UI();

        // Destructor
        ~UI();


        /*   Instance Functions   */

        // Draws all the windows
        void draw(Drawer* drawer);

        // Removes a window object from the interal linked list
        void deleteWindow(Window* window);

        // Checks all the ui elements against the inputs for the frame. Returns true if the click lands on a window
        bool doInput(State* state);

        // Creates a new "Transform" window linked to the given Object
        Window* createWindowTransform(Object* object);
        Window* createWindowTransform(Object* object, int posx, int posy);

        void updateWindowTransform(Object* object);

        void destroyWindowTransform();

        /*   Class Functions   */

        static Action* getNextAction();
        
        // Returns a NEW WindowElement for the top bar of a window containing the window title, and the buttons
        static WindowElement* createTopBar(UI* ui, Window* window, const char* title);

        static WindowElement* createSlider(int width);

        static WindowElement* createTextBox(int posx, int posy, int width, float* valueToWrite);

    private:

        /*   Instance Variables   */

        LinkedList<Window*>* windows;

        // Stores the location the next window should go, changes on every window made to mitigate window overlap
        Vec2* nextWindowPos;

        /*   Class Variables   */

        static const Vec2* TransformWindowSize;

        // Reference to a shared Action queue
        static LinkedList<Action*>* actionQueue;


        /*   Instance Functions   */

        // Adds a window object to the internal linked list
        void addWindow(Window* window);

        // Updates the private vector by +(50, 50). Also rolls over x and y if they pass 500 and 300 respectively
        void updateNextWindowPos();
        
};
