#pragma once

#include "util/Utility.h"

#include "ui/Window.h"
#include "ui/BindContext.h"

#include "physics/ObjectSet.h"


typedef void (*BindFunc)(WindowHandle*, BindContext*);


class BindManager {

    public:

        BindManager();

        ~BindManager();

        void addBind(WindowHandle* windowHandle, BindContext* context, BindFunc bindFunc);

        void removeBind(WindowHandle* windowHandle);

        void rebindAll();

    private:

        struct BindInfo {
            
            // All WindowHandles are stack allocated
            // This is just a pointer because it needs to hold the same data as the passed WindowHandle
            WindowHandle* windowHandle;

            // This holds all the variables that the binding function needs
            // This essentially holds global variables for all the binding logic for the given window
            BindContext* bindContext;

            // Pointer to the main binding function for this bind
            BindFunc bindFunc;

        };

        // This holds all the bindings that are being tracked
        LinkedList<BindInfo>* binds;

};


namespace UIBinding {
        
        // transform.xml
        namespace Transform {
            void bind(WindowHandle windowHandle, BindContext* bindContextTransform);
        }

        // navbar.xml
        namespace NavBar {
            void bind(WindowHandle windowHandle, BindContext* UNUSED);
        }

        // objects.xml
        namespace Objects {

            void bind(WindowHandle windowHandle, BindContext* bindContextObjects);    
            
            // Button functions
            void createCube(BindContext* bindContextObjects);
            void createSphere(BindContext* bindContextObjects);

        }

        // More bindings

}


class Binding {

    /*
        Functionally this is just a namespace, its only a class because it needs to be a friend class to WindowHandle
        Notice that all the functions are static, and there is not constructor/destructor
        Since it needs to be a class anyway, this is also instantiated in each UI instance for easy access

        Each function takes a WindowHandle object for the window it should act upon
        Some have extra args, used to bind the UI elements to various data

        There are some subclasses to hold functions and variables that are used on button pressed (via ActionCallFunc)
        Everything in these is private, as they are not intended to be reached from outside
    */

    public:

        // transform.xml
        static void bindTransform(WindowHandle windowHandle, Object* object);

        // navbar.xml
        static void bindNavBar(WindowHandle windowHandle);

        // objects.xml
        static void bindObjects(WindowHandle windowHandle, ObjectSet objectSet);
        class Objects {

            friend class Binding;

            private:

                // The ObjectSet that this window works with
                static ObjectSet objectSet;
                
                static void createCube();
                static void createSphere();

        };

};
