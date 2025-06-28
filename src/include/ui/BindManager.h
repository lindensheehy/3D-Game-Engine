#pragma once

#include "util/Utility.h"

#include "ui/Window.h"
#include "ui/BindFuncs.h"


namespace Ui {

class BindManager {

    /*
        This class abstracts the binding logic away from the external code

        It serves two main purposes:
        - Keeping everything in one place. All Windows that require binding can be stored here
        - "Set it and forget it". You designate the bind function once, then call it again later with ease (via 'rebind')
    */

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
        void rebind(WindowHandle* windowHandle) const;

        // Rebinds all the stored windows
        void rebindAll() const;

    private:

        // Holds a WindowHandle and BindFunc pair. Used in 'binds' (see below)
        struct Bind {
            
            // This WindowHandle is not owned by this object. Its simply a copy of 'windowHandle' from 'addBind'
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
        Bind* getBind(WindowHandle* windowHandle) const;

        // Tells this instance to stop tracking the given Bind (helper function)
        void removeBind(Bind* bind);

};

}
