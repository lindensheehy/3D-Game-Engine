#pragma once

#include "util/Utility.h"

#include "ui/Core.h"
#include "ui/Window.h"

#include "physics/ObjectSet.h"


typedef void (*BindFunc)(WindowHandle*);
typedef void (*ButtonFunc)(Context*);

class BindFuncs {

    /*
        This is functionally a namespace
        It just needs to be a class so WindowHandle can grant it friend access to private members
    */
    
public:

    // navbar.xml
    struct NavBar {
        static void bind(WindowHandle* windowHandle);
    };

    // transform.xml
    struct Transform {
        static void bind(WindowHandle* windowHandle);
    };

    // objects.xml
    struct Objects {

        static void bind(WindowHandle* windowHandle);    
        
        // Button functions
        static void createCube(Context* contextObjects);
        static void createSphere(Context* contextObjects);

    };

    // More bindings

};
