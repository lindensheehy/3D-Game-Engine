#pragma once

#include "Vec.h"
#include "Drawer.h"
#include "LinkedList.h"
#include "ObjectSet.h"


// Early declarations becuase theres some circular dependancy here
class Window;
class Action;
class UI;


// Type specifier for WindowElement objects. Used for handling input to decide what to do
enum ElementType {
    NONE,
    TEXT,
    VISUAL,
    BUTTON,
    DRAGABLE
};



// Window Element + Sub Classes

class WindowElement {

    /*
        Individual graphical elements of windows.
        This class should not be used, one of the subclasses should instead as they all have thier own functions.
    */

    public:

        /*   Pre Defined Variables   */

        Uint32 color;


        /*   Instance Variables   */

        Vec2* pos; // Relative to parent
        Vec2* size;

        Action* action;

        LinkedList<WindowElement*>* children;

        ElementType type = NONE;


        // Constructor
        WindowElement(int posx, int posy, int sizex, int sizey);
        WindowElement(Vec2* pos, Vec2* size);

        // Destructor
        virtual ~WindowElement();


        /*   Instance Functions   */

        // Offset should be the position of the parent, since all elements are stored in relative positions
        virtual void draw(Drawer* drawer, Vec2* offset);

        // Returns the child element that the click lies on. Returns this if this does but no children do. Returns nullptr if none do
        WindowElement* doClick(int x, int y, Vec2* offset);

        // Runs the action associated with the element. Does nothing if no action has been associated.
        void onClick();

        // Adds a child element to this element
        void addChild(WindowElement* child);


        /*   Class Functions   */
        
        // Returns a NEW WindowElement for the top bar of a window containing the window title, and the buttons
        static WindowElement* createTopBar(UI* ui, Window* window, const char* title);

        static WindowElement* createSlider(int width);

        static WindowElement* createTextBox(int width);

    protected:

        /*   Instance Variables   */
        
        // Used for detecting clicks, and drawing for some subclasses
        Vec2* endPos;


        /*   Instance functions   */

        // This function assumes the given offset already accounts for this->pos
        void drawChildren(Drawer* drawer, Vec2* offset);

};


class WindowDiv : public WindowElement {

    /*
        Serves no visual purpose, just used to group elements for easier handling
        Similar to an HTML div
    */

    public:

        // Constructor
        WindowDiv(int posx, int posy, int sizex, int sizey);


        // Instance Function

        // Override draw to just draw children
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowLine : public WindowElement {

    public:

        // Constructor
        WindowLine(int x1, int y1, int x2, int y2);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowFilledRect : public WindowElement {

    public:

        // Constructor
        WindowFilledRect(int posx, int posy, int sizex, int sizey);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowOutlinedRect : public WindowElement {

    public:

        // Constructor
        WindowOutlinedRect(int posx, int posy, int sizex, int sizey);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowCircle : public WindowElement {

    public:

        // Constructor
        WindowCircle(int posx, int posy, int size);

        // Destructor
        ~WindowCircle() override;

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        // Used for drawing, stores the center of the circle and the radius
        Vec2* middle;
        int radius;

};


class WindowText : public WindowElement {

    public:

        // Constructor
        WindowText(int posx, int posy, const char* text);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        const char* text;

};


class WindowTexture : public WindowElement {

    public:

        // Constructor
        WindowTexture(int posx, int posy, int sizex, int sizey, PNG* texture);

        // Destructor
        ~WindowTexture() override;

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        PNG* texture;

};


class WindowButton : public WindowElement {

    /*
        Class for buttons which should have some on click effect
        Note: Any buttons which are children of buttons WILL NOT be found as clicked since the search stops once it finds the first button
        This concept also applies to overlapping buttons, whenever clicking two at the same time, only one will act
    */

    public:

        // Constructor
        WindowButton(int posx, int posy, int sizex, int sizey);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};



// Action + Sub Classes

class Action {

    /*
        Super class for all actions that buttons should do.
        This class does nothing on its own and shouldnt be used, the subclasses are the useful part
    */

    public:

        /*   Instance Variables   */

        // Constructor
        Action();

        // Destructor
        virtual ~Action();

        /*   Instance Functions   */

        virtual void run() {}

};


class ActionLogWrite : public Action {

    public:

        /*   Instance Variables   */

        const char* message;

        // Constructor
        ActionLogWrite(const char* message);

        // Destructor
        ~ActionLogWrite() override;

        /*   Instance Functions   */

        void run() override;

};


class ActionCloseWindow : public Action {

    public:

        /*   Instance Variables   */

        UI* ui; 
        Window* window; // Window to close

        // Constructor
        ActionCloseWindow(UI* ui, Window* window);

        // Destructor
        ~ActionCloseWindow() override;

        /*   Instance Functions   */

        void run() override;

};


template<typename type>
class ActionWriteToValue : public Action {

    public:

        // Constructor
        ActionWriteToValue(type* pointer);

        // Destructor
        ~ActionWriteToValue();

        /*   Instance Functions   */



};



// Window

class Window {

    /*
        Mid step between the individual WindowElement objects and the UI object.
        Serves to seperate the elements into groups for input handling and actions like moving or closing windows
    */

    public:

        /*   Pre Defined Variables   */

        Uint32 COLOR_BASE = Color::BACKGROUND;
        Uint32 COLOR_ACCENT = Color::ACCENT;
        Uint32 COLOR_TEXT = Color::BLACK;

        /*   Instance Variables   */

        Vec2* pos;
        Vec2* size;
        int layer; // Front to back - 0 is at the front, 1 behind, and so on

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
        bool hitTest(int x, int y);

        // Returns the element that covers the click location. Return nullptr if none do
        WindowElement* doClick(int x, int y);

        // Adds an element to the window
        void addElement(WindowElement* element);

    private:

        Vec2* endPos; // Used for drawing, stores the coordinates of pos + size

};



// UI

class UI {

    /*
        The parent class to everything in this file. 
        All the other classes included here will be managed and accessed through this
    */
    
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

        /*   Constants   */

        static Vec2* TransformWindowSize;

        /*   Instance Variables   */

        LinkedList<Window*>* windows;

        // Stores the location the next window should go, changes on every window made to mitigate window overlap
        Vec2* nextWindowPos;


        /*   Instance Functions   */

        // Adds a window object to the interal linked list
        void addWindow(Window* window);

        // Updates the private vector by +(50, 50). Also rolls over x and y if they pass 500 and 300 respectively
        void updateNextWindowPos();

};
