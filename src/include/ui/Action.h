#pragma once

#include "ui/UIEnums.h"

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

        // Destructor
        ~ActionCloseWindow();

};
