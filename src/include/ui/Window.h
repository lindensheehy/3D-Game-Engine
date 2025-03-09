#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "gui/Drawer.h"
#include "util/LinkedList.h"
#include "physics/ObjectSet.h"

#include "ui/Core.h"
#include "ui/Action.h"
#include "ui/WindowElement.h"
#include "ui/Context.h"



// Struct used in the Window::bindables linked list
// This maps const char* strings to WindowElement objects
struct Bindable {
    const char* id;
    WindowElement* element;
};


// Forward declare Window for WindowHandle
class Window;


// Handle class for Window objects
// This gives a reference to a Window object without being able to access it
// Also stores a Context object, which holds any data the window needs to reference
class WindowHandle {

    // BindFuncs and UI are allowed to access the ptr instance variable
    friend class BindFuncs;
    friend class UI;

    public:

        /*   Instance Variables   */
        
        WindowID id;

        // Constructors
        WindowHandle() : id(-1), ptr(nullptr), context(nullptr) {}
        WindowHandle(WindowID id, Window* ptr) : id(id), ptr(ptr), context(nullptr) {}

        // Destructor
        ~WindowHandle() {
            if (this->context != nullptr) delete this->context;
            // this->ptr is not owned by this class, so does not need to be deleted
        }


        /*   Instance Functions   */
        
        // Sets the context, while accounting for old context if it exists
        void setContext(Context* context) {
            if (this->context != nullptr) delete this->context;
            this->context = context;
        }

    private:

        Window* ptr;

        // This will contain one of the Context subclasses
        // May also be nullptr if the window does not require context
        Context* context;
    
};


class Window {

    /*
        Mid step between the individual WindowElement objects and the UI object.
        Serves to seperate the elements into groups for input handling and actions like moving or closing windows
    */

    public:

        /*   Instance Variables   */

        Vec2* pos;
        Vec2* endPos; // Used for drawing, stores the coordinates of pos + size
        Vec2* size;
        int layer; // Front to back - 0 is at the front, 1 behind, and so on

        WindowID id;

        // These are the elements that make up the window
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

        // Binds the WindowButton element with the given id to the given action
        void bindButton(const char* id, Action* action);

        // Binds the WindowDragable element with the given id to the given pos and endPos
        void bindDragable(const char* id, Vec2* posToDrag, Vec2* endPosToDrag);

        // Binds the WindowTextInput element with the given id to the given variable
        void bindTextInput(const char* id, int* boundValue);
        void bindTextInput(const char* id, float* boundValue);

        // Moves the window to the given position
        void setPos(int x, int y);
        void setPos(Vec2* newPos);


        /*   Class Functions   */

        static void setActionQueue(LinkedList<Action*>* queue);

        static void queueAction(Action* action);

    private:

        /*   Instance Variables   */

        // This is an easy way to reference all the bindable elements in the window
        LinkedList<Bindable*>* bindables;

        // This is true when the bindables list is accurate
        // When its false, locateBindables will be called before binding anything
        bool bindablesUpdated;

        // Reference to a shared Action queue
        static LinkedList<Action*>* actionQueue;


        /*   Instance Functions   */

        // Helper function for the binding functions (bindButton, etc.)
        WindowElement* getBindable(const char* id);

        // This locates every bindable element, and stores them in this->bindables
        void locateBindables();

        // This is the recursive caller for locateBindables
        void locateBindables(WindowElement* root);

};
