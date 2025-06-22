#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "graphics/drawing/Drawer.h"
#include "util/LinkedList.h"
#include "physics/ObjectSet.h"

#include "ui/Core.h"
#include "ui/Action.h"
#include "ui/WindowElement.h"
#include "ui/Context.h"


namespace Ui {

// Forward declare Window for WindowHandle
class Window;


class WindowHandle {

    /*
        Handle class for Window objects (similar in concept to HANDLE types in Windows)
        This gives an immutable reference to a Window object. This helps avoid accidental modifications

        Also stores a Context object, which holds any data the window needs to reference (see Context.h)
    */

    // BindFuncs and UI are allowed to access 'ptr' and 'context'
    friend class BindFuncs;
    friend class UI;

    public:

        /*   Instance Variables   */
        
        // Unique ID for this Window
        WindowID id;

        // Constructors
        WindowHandle() : id(-1), ptr(nullptr), context(nullptr) {}
        WindowHandle(WindowID id, Window* ptr) : id(id), ptr(ptr), context(nullptr) {}

        // Destructor
        inline ~WindowHandle() { delete this->context; }


        /*   Instance Functions   */
        
        // Sets the context, while accounting for old context if it exists
        inline void setContext(Context* context) {
            delete this->context;
            this->context = context;
        }
        
        inline bool hasValidContext() { return (this->context != nullptr); }
        inline bool hasNoContext() { return (this->context == nullptr); }

    private:

        // Not owned by this class
        Window* ptr;

        // Owned by this class
        // This will contain one of the Context subclasses (may also be nullptr)
        Context* context;
    
};


class Window {

    /*
        Intermediate class between UI and WindowElement
        Serves to seperate the elements into groups for input handling
    */

    public:

        /*   Instance Variables   */

        Geometry::Vec2 pos;
        Geometry::Vec2 endPos; // Used for drawing, stores the coordinates of pos + size
        Geometry::Vec2 size;

        // Z-order. Front to back, so 0 is at the front, 1 is behind, and so on
        int layer;

        WindowID id;

        // These are the elements that make up the window
        LinkedList<WindowElement*>* elements;


        // Constructors
        Window(int posx, int posy, int sizex, int sizey, int layer = 0);
        Window(Geometry::Vec2* pos, Geometry::Vec2* size, int layer = 0);

        // Destructor
        ~Window();


        /*   Instance Functions   */

        // Draws the window and all its elements
        void draw(Graphics::Drawing::Drawer* drawer);

        // Returns true if the click lies within the bounds of the window
        WindowElement* hitTest(int x, int y);

        // Adds an element to the window
        void addElement(WindowElement* element);

        // Binds the WindowButton element with the given id to the given action
        // Does nothing if the id is not valid, or is linked to a non WindowButton element
        void bindButton(const char* id, Action* action);

        // Binds the WindowDragable element with the given id to the given pos and endPos
        // Does nothing if the id is not valid, or is linked to a non WindowDragable element
        void bindDragable(const char* id, Geometry::Vec2* posToDrag, Geometry::Vec2* endPosToDrag);

        // Binds the WindowTextInput element with the given id to the given variable
        // Does nothing if the id is not valid, or is linked to a non WindowTextInput element
        void bindTextInput(const char* id, int* boundValue);
        void bindTextInput(const char* id, float* boundValue);

        // Moves the window to the given position
        void setPos(int x, int y);
        void setPos(Geometry::Vec2* newPos);


        /*   Class Functions   */

        static inline void setActionQueue(LinkedList<Action*>* queue) { Window::actionQueue = queue; }

        static inline void queueAction(Action* action) { Window::actionQueue->pushBack(action); }

    private:

        /*   Instance Variables   */

        // Struct used in the 'bindables' LinkedList below
        // This maps const char* strings to WindowElement objects
        struct Bindable {
            const char* id;
            WindowElement* element;
        };

        // This is an easy way to reference all the bindable elements in the window
        LinkedList<Bindable*>* bindables;

        // This is true when the 'bindables' list is accurate
        // When its false, 'locateBindables' will be called before binding anything
        bool bindablesUpdated;

        // Reference to a shared Action queue (populated upon instantiation of UI)
        static LinkedList<Action*>* actionQueue;


        /*   Instance Functions   */

        // Helper function for the binding functions ('bindButton', etc.)
        WindowElement* getBindable(const char* id);

        // This locates every bindable element, and stores them in this->bindables
        void locateBindables();

        // This is the recursive caller for locateBindables
        void locateBindables(WindowElement* root);

};

}
