#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "gui/Drawer.h"
#include "util/LinkedList.h"
#include "physics/ObjectSet.h"

#include "ui/UIEnums.h"
#include "ui/Action.h"
#include "ui/WindowElement.h"


// Declarations because of circular dependancy (should probably be refactored)
class Window;
class Action;
class UI;


class Window {

    /*
        Mid step between the individual WindowElement objects and the UI object.
        Serves to seperate the elements into groups for input handling and actions like moving or closing windows
    */

    public:

        /*   Pre Defined Variables   */

        uint32 COLOR_BASE = Color::BACKGROUND;
        uint32 COLOR_ACCENT = Color::ACCENT;
        uint32 COLOR_TEXT = Color::BLACK;

        /*   Instance Variables   */

        Vec2* pos;
        Vec2* endPos; // Used for drawing, stores the coordinates of pos + size
        Vec2* size;
        int layer; // Front to back - 0 is at the front, 1 behind, and so on

        UIEnum::WindowType type;

        LinkedList<WindowElement*>* elements;

        // Constructors
        Window(int posx, int posy, int sizex, int sizey, int layer = 0);
        Window(Vec2* pos, Vec2* size, int layer = 0); // References are stored, the Vec2's should not be deleted after calling this

        // Destructor
        ~Window();

        /*   Instance Functions   */

        // Draws the window and all its elements
        void draw(Drawer* drawer);

        // Returns true if the click lies within the bounds of the window
        WindowElement* hitTest(int x, int y);

        // Adds an element to the window
        void addElement(WindowElement* element);

        // Checks all the children elements against the inputs for the frame. Also brings window to front is its clicked. Returns the element clicked on, or nullptr if none
        WindowElement* doInput(State* state);


        /*   Class Functions   */

        static void setActionQueue(LinkedList<Action*>* queue);

        static void queueAction(Action* action);

    protected:

        /*   Instance Variables   */

        // Reference to a shared Action queue
        static LinkedList<Action*>* actionQueue;

};
