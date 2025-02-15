#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "gui/Drawer.h"
#include "util/LinkedList.h"
#include "physics/ObjectSet.h"

#include "ui/UIEnums.h"
#include "ui/Action.h"



class WindowElement {

    /*
        Individual graphical elements of windows.
        This class should not be used, one of the subclasses should instead as they all have thier own functions.
    */

    public:

        /*   Pre Defined Variables   */

        uint32 color;


        /*   Instance Variables   */

        Vec2* pos; // Relative to parent
        Vec2* size;
        const char* tag;

        LinkedList<WindowElement*>* children;
        
        // Holds any tags that exist within this elements children. 
        // This includes children furher down the hierarchy (ie. will inherit any tag values AS WELL as any values in childTags)
        LinkedList<const char*> childTags;

        UIEnum::ElementType type = UIEnum::ElementType::INVISIBLE;
        
        bool selected = false;


        // Constructors
        WindowElement(int posx, int posy, int sizex, int sizey);

        // Does NOT delete or directly use these vectors. they need to be handled correctly after this call
        WindowElement(Vec2* pos, Vec2* size);

        // Destructor
        virtual ~WindowElement();


        /*   Instance Functions   */

        // Offset should be the position of the parent, since all elements are stored in relative positions
        virtual void draw(Drawer* drawer, Vec2* offset);

        virtual bool hitTest(int x, int y, Vec2* offset);

        // Returns the child element that the click lies on. Returns this if this does but no children do. Returns nullptr if none do
        WindowElement* doInput(State* state, Vec2* offset);

        // Adds a child element to this element
        void addChild(WindowElement* child);

        // Handles various input actions, only used in a few subclasses
        virtual void onInput(State* state) {}

        // Runs when the element is no longer selected, only used in a few subclasses
        virtual void onDeselect() {}


        /*   Class Functions   */

        static void setActionQueue(LinkedList<Action*>* queue);

        static void queueAction(Action* action);


    protected:

        /*   Instance Variables   */
        
        // Used for detecting clicks, and drawing for some subclasses
        Vec2* endPos;

        // Determines if doInput should stop after finding this element
        bool isInteractable = false;

        // Reference to a shared Action queue
        static LinkedList<Action*>* actionQueue;


        /*   Instance functions   */

        // This function assumes the given offset already accounts for this->pos
        void drawChildren(Drawer* drawer, Vec2* offset);

};


class WindowDiv : public WindowElement {

    /*
        Serves no visual purpose, just used to group elements for easier handling
        Similar to an <div> element from HTML
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
        WindowLine(int x1, int y1, int x2, int y2, uint32 color);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowFilledRect : public WindowElement {

    public:

        // Constructor
        WindowFilledRect(int posx, int posy, int sizex, int sizey, uint32 color);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowOutlinedRect : public WindowElement {

    public:

        // Constructor
        WindowOutlinedRect(int posx, int posy, int sizex, int sizey, uint32 color);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

};


class WindowCircle : public WindowElement {

    public:

        // Constructor
        WindowCircle(int posx, int posy, int size, uint32 color);

        // Destructor
        ~WindowCircle() override;

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        // Used for drawing, stores the center of the circle and the radius
        Vec2* middle;
        int radius;

};


class WindowTextStatic : public WindowElement {

    /*
        
    */

    public:

        // Constructor
        WindowTextStatic(int posx, int posy, const char* text);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        const char* text;

};


class WindowTextInput : public WindowElement {

    /*
        Class for a text input box which should be attached to some value
        This is attached via a class setter, which allows class specific behaviour to be handled class-side
        Since this is an interactive element, there is a lot more logic required
    */

    public:

        enum class BindType {
            NONE,
            INT,
            FLOAT
        };

        // Constructor
        WindowTextInput(int posx, int posy, int width);

        // Destructor
        ~WindowTextInput() override;

        // Instance Functions
        void draw(Drawer* drawer, Vec2* offset) override;

        void onInput(State* state) override;

        void onDeselect() override;

        // Binds the textInput to a variable
        void bind(int* variable);
        void bind(float* variable);

        // Removes the binding to the variable
        void unbind();

        void hideCursor();

    private:

        // Max length of string this will handle
        const int BUFFERSIZE = 128;

        // Instance Variables
        char* text;         // Stores the current string being displayed
        int length;         // Stores the length of the current 'text' string

        int cursorPos;      // Stores the placement of the text cursor. 0 is before the first char

        // These are the variables the text input can be bound to. only one will be valid at once
        BindType bindType;
        float* boundFloat;
        int* boundInt;
        
        // Instance Functions
        void updateString();

        void writeToValue();

};


class WindowTexture : public WindowElement {

    public:

        // Constructor
        WindowTexture(int posx, int posy, int sizex, int sizey, const char* fileName);


        /*   Instance Functions   */

        void draw(Drawer* drawer, Vec2* offset) override;

        // Optional call for this rather than having it in the destructor. Sometimes you might not want the PNG deleted if its used elsewhere
        void deleteTexture() { delete this->texture; }

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
        WindowButton(int posx, int posy, int sizex, int sizey, Action* action);

        // Instance Functions
        void draw(Drawer* drawer, Vec2* offset) override;

        void onInput(State* state) override;

    private:

        Action* action;

};


class WindowDragable : public WindowElement {

    /*
        Class for elements which should move something when dragged. 
        For example, the top bar of a window.
        This element is INVISIBLE, just like WindowDiv
    */

    public:

        // Constructor
        WindowDragable(int posx, int posy, int sizex, int sizey, Vec2* posToDrag, Vec2* endPosToDrag);

        /*   Instance Functions   */

        void draw(Drawer* drawer, Vec2* offset) override;

        void onInput(State* state) override;

    private:

        Vec2* posToDrag;
        Vec2* endPosToDrag;

};
