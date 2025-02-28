#pragma once

#include "Window.h"

#include "physics/ObjectSet.h"

/*
    This file contains functions to bind UI windows to various actions and data
    Each window has its own bind function, so if you create a new window in XML, you need to add a bind function to make it interactable
*/


class Binding {

    /*
        Functionally this is just a namespace, its only a class because it needs to be a friend class to WindowHandle
        Notice that all the functions are static, and there is not constructor/destructor
        Since it needs to be a class anyway, this is also instantiated in each UI instance for easy access

        Each function takes a WindowHandle object for the window it should act upon
        Some have extra args, used to bind the UI elements to various data
    */

    public:

        // transform.xml
        static void bindTransform(WindowHandle windowHandle, Object* object);

        // navbar.xml
        static void bindNavBar(WindowHandle windowHandle);

};
