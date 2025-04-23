#pragma once

#include "util/Utility.h"

#include "ui/Window.h"
#include "ui/BindFuncs.h"


namespace Ui {

class BindManager {

    public:

        // Constructor
        BindManager();

        // Destructor
        ~BindManager();


        /*   Instance Functions   */

        // Tells this instance that the given WindowHandle should use the given BindFunc
        // This also calls the Bindfunc once
        void addBind(WindowHandle* windowHandle, BindFunc bindFunc);

        // Tells this instance to stop tracking the binds of the given WindowHandle
        void removeBind(WindowHandle* windowHandle);

        // Rebinds the Window given by the WindowHandle
        void rebind(WindowHandle* windowHandle);

        // Rebinds all the stored windows
        void rebindAll();

    private:

        // Holds a WindowHandle and BindFunc pair. Used in the binds linked list
        struct Bind {
            
            // All WindowHandles are stack allocated
            // This is just a pointer because it needs to hold the same data as the passed WindowHandle
            WindowHandle* windowHandle;

            // Pointer to the main binding function for this bind
            BindFunc bindFunc;

            // Simple constructor for the new operator (these are heap allocated)
            Bind(WindowHandle* handle, BindFunc func) : windowHandle(handle), bindFunc(func) {}

        };

        // This holds all the bindings that are being tracked
        LinkedList<Bind*>* binds;

        
        /*   Instance Functions   */

        // This just returns the bind that holds the given WindowHandle
        Bind* getBind(WindowHandle* windowHandle);

        // Tells this instance to stop tracking the given Bind
        void removeBind(Bind* bind);

};

}
