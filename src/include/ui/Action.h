#pragma once

#include "ui/Core.h"

#include "ui/Context.h"

/*
    These are basically just glorified variables.
    The idea of this is that they can be added to a queue which is global across everything in the UI
    Window or WindowElement objects can add these to the queue, 
    then they will later be handled by the UI object when doInput() is called
*/

class Action {

    public:

        /*   Instance Variables   */

        UIEnum::ActionType actionType;
        

        // Constructor
        Action();

        // Destructor
        virtual ~Action();

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
        This class takes an optional WindowHandle pointer
        This handle will be populated with the Window information upon creation
    */

    public:

        /*   Instance Variables   */

        const char* fileName;
        WindowHandle* windowHandle;


        // Constructor
        ActionOpenWindow(const char* fileName, WindowHandle* windowHandle);

};

class ActionCallFunc : public Action {

    public:

        // Constructor
        ActionCallFunc(void (*func)(Context*), Context* context);


        /*   Instance Functions   */

        // Calls the stored function
        void callFunc();

    private:

        /*   Instance Variables   */

        // Function pointer to call
        void (*func)(Context*);

        // Context to call with
        // This should be a shared pointer, so it can be modified from a WindowHandle object
        Context* context;

};
