#pragma once

#include "ui/Core.h"

#include "ui/Context.h"

/*
    These are basically just fancy data containers, that allow certain actions to happen
    The idea is that they can be added to a queue which is shared between everything in the UI
    Window or WindowElement objects can add these to the queue. They are handled later by UI on doInput()

    This is an effort to decouple the action handling from the per class logic
*/

namespace Ui {

class Action {

    public:

        /*   Instance Variables   */

        Ui::ActionType type = ActionType::NONE;
        

        // Constructor
        Action() {}

        // Destructor
        virtual ~Action() {}

};

class ActionCloseWindow : public Action {

    public:

        /*   Instance Variables   */

        WindowID targetWindowId;


        // Constructor
        ActionCloseWindow(WindowID targetWindowId);

};

class ActionOpenWindow : public Action {

    /*
        This class uses a WindowHandle double pointer
        This handle will be populated with the Window information upon creation

        This exists so the window is not left dangling upon creation
        The double pointer allows this action to overwrite the pointer used externally
    */

    public:

        /*   Instance Variables   */

        const char* fileName;
        WindowHandle** windowHandle;
        void (*bindFunc)(WindowHandle*);


        // Constructor
        ActionOpenWindow(const char* fileName, WindowHandle** windowHandle, void (*bindFunc)(WindowHandle*));

};

class ActionCallFunc : public Action {

    public:

        // Constructor
        ActionCallFunc(void (*func)(Context*), Context** context);


        /*   Instance Functions   */

        // Calls the stored function
        void callFunc();

    private:

        /*   Instance Variables   */

        // Function pointer to call
        void (*func)(Context*);

        // Context to call 'func' with
        // Should point to the Context inside the WindowHandle for the Window the WindowElement calling this belongs to
        // Its a double pointer so it can be updated when WindowHandle::setContext() is called
        Context** context;

};

}
