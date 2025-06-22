#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "graphics/drawing/Drawer.h"
#include "util/LinkedList.h"
#include "physics/ObjectSet.h"

#include "ui/Core.h"
#include "ui/Action.h"


namespace Ui {

class WindowElement {

    /*
        Represents a single visual (or organizational) element in the UI
        This is the lowest level of element in this module, and it makes up all UI features
        
        This class is purely a base class, and should not be used
        Theres no issue with instantiating this class, it just wont do anything and will likely throw warnings/errors
    */

    public:

    
    
        /*   Instance Variables   */
        
        Geometry::Vec2 pos; // Relative to parent
        Geometry::Vec2 size;

        // This is the color the element will show as (only affects certain subclasses)
        uint32 color;

        LinkedList<WindowElement*>* children;

        // This defines what type of class this is
        // These dont map 1-to-1 onto the subclasses, they just define behaviour groupings
        Ui::ElementType type = Ui::ElementType::INVISIBLE;

        // Used for binding interactable elements to data
        // This is nullptr for any non-interactable element
        char* id;
        
        bool selected = false;


        // Constructors
        WindowElement(int posx, int posy, int sizex, int sizey);
        WindowElement(Geometry::Vec2* pos, Geometry::Vec2* size);

        // Destructor
        virtual ~WindowElement();


        /*   Instance Functions   */

        // 'offset' should be the absolute position of the parent, so this elements 'pos' can be added to that
        virtual void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset);

        // This will return the lowest level element in the hierarchy that is interactable
        // If the position does not hit anything interactable, this will return nullptr
        WindowElement* hitTest(int x, int y, Geometry::Vec2* offset);

        void setPos(int x, int y);
        void setPos(Geometry::Vec2* newPos);

        // Adds a child element to this element
        void addChild(WindowElement* child);

        // Handles various input actions, only used in a few subclasses
        virtual void onInput(Graphics::Gui::State* state) {}

        // Runs when the element is no longer selected, only used in a few subclasses
        virtual void onDeselect() {}


        /*   Class Functions   */

        static inline void setActionQueue(LinkedList<Action*>* queue) { WindowElement::actionQueue = queue; }

        static inline void queueAction(Action* action) { WindowElement::actionQueue->pushBack(action); }


    protected:

        /*   Instance Variables   */
        
        // Used for detecting clicks, and drawing for some subclasses
        Geometry::Vec2 endPos;

        // Determines if 'hitTest' should stop after finding this element
        bool isInteractable = false;

        // Reference to a shared Action queue
        static LinkedList<Action*>* actionQueue;


        /*   Instance functions   */

        // This function assumes the given offset already accounts for this->pos
        void drawChildren(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset);

};


class WindowDiv : public WindowElement {

    /*
        Serves no visual purpose, just used to group elements for easier handling
        Similar to an <div> element from HTML
    */

    public:

        // Constructor
        WindowDiv(int posx, int posy, int sizex, int sizey);


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

};


class WindowLine : public WindowElement {

    /*
        Just a straight line from (x1, y1) to (x2, y2)
    */

    public:

        // Constructor
        WindowLine(int x1, int y1, int x2, int y2, uint32 color);


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

};


class WindowFilledRect : public WindowElement {

    public:

        // Constructor
        WindowFilledRect(int posx, int posy, int sizex, int sizey, uint32 color);


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

};


class WindowOutlinedRect : public WindowElement {

    public:

        // Constructor
        WindowOutlinedRect(int posx, int posy, int sizex, int sizey, uint32 color);


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

};


class WindowCircle : public WindowElement {

    public:

        // Constructor
        WindowCircle(int posx, int posy, int size, uint32 color);


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

    private:

        // Used for drawing, stores the center of the circle and the radius
        Geometry::Vec2 middle;
        int radius;

};


class WindowTextStatic : public WindowElement {

    public:

        // Constructor
        WindowTextStatic(int posx, int posy, char* text);

        // Destructor
        ~WindowTextStatic() override;


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

    private:

        char* text;

};


class WindowTextInput : public WindowElement {

    /*
        This is a text input box that can be attached to some value
        This is attached by calling 'bind'. Only ints and floats are supported as of now
    */

    public:

        // Constructor
        WindowTextInput(int posx, int posy, int width, char* id);

        // Destructor
        ~WindowTextInput() override;


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

        void onInput(Graphics::Gui::State* state) override;

        void onDeselect() override;

        // Binds the textInput to a variable
        void bind(int* variable);
        void bind(float* variable);

        // Removes the binding to the variable
        void unbind();

    private:

        // Max length of string this will handle
        static constexpr int BUFFERSIZE = 128;

        enum class BindType {
            NONE,
            INT,
            FLOAT
        };

        // These are the variables the text input can be bound to. only one will be valid at once
        BindType bindType;
        float* boundFloat;
        int* boundInt;

        // Stores the current string being displayed
        char* text;
        int textLength;

        // Stores the placement of the text cursor. 0 is before the first char
        int cursorPos;


        /*   Instance Functions   */
        
        // This writes the value at the binded pointer (if it exists) into 'text'
        // This allows the text box to accurately display the value its bound to
        void updateString();

        // This writes the value in 'text' to the binded pointer (if it exists)
        // This allows the text box to actually interact with the rest of the app
        void writeToValue();

};


class WindowTexture : public WindowElement {

    /*
        --- NOT IMPLEMENTED ---

        This class displays a PNG as a UI element (postponed until V2)
    */

    public:

        // Constructor
        WindowTexture(int posx, int posy, int sizex, int sizey, const char* fileName);

        // Destructor
        ~WindowTexture() override;


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

        // Optional call for this rather than having it in the destructor
        // PNG objects may be shared, so an opt-in destructor is ideal here
        void deleteTexture() {}

    private:

        // PNG* texture;

};


class WindowButton : public WindowElement {

    /*
        Class for buttons which should have some on click effect

        Note: Any buttons which are children of buttons WILL NOT be found as clicked since the search stops once it finds the first button
        This concept also applies to overlapping buttons, whenever clicking two at the same time, only one will act
    */

    public:

        // Constructor
        WindowButton(int posx, int posy, int sizex, int sizey, char* id);
        WindowButton(int posx, int posy, int sizex, int sizey, Action* action);

        // Destructor
        ~WindowButton() override;


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

        void onInput(Graphics::Gui::State* state) override;

        void bind(Action* action);

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

        // Constructors
        WindowDragable(int posx, int posy, int sizex, int sizey, char* id);
        WindowDragable(int posx, int posy, int sizex, int sizey, Geometry::Vec2* posToDrag, Geometry::Vec2* endPosToDrag);


        /*   Instance Functions   */

        void draw(Graphics::Drawing::Drawer* drawer, Geometry::Vec2* offset) override;

        void onInput(Graphics::Gui::State* state) override;

        void bind(Geometry::Vec2* posToDrag, Geometry::Vec2* endPosToDrag);

    private:

        // Pointers to external data. Not owned by this class
        Geometry::Vec2* posToDrag;
        Geometry::Vec2* endPosToDrag;

};

}
