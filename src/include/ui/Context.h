#pragma once

/*
    This file does not have a cooresponding .cpp file
    These are just data containers with no real functions
*/

#include "util/Utility.h"

#include "ui/Core.h"

#include "physics/ObjectSet.h"


namespace Ui {

class Context {

    public:

        /*   Instance Variables   */

        Ui::ContextType type = Ui::ContextType::NONE;


        // Constructor
        Context() {}

        // Destructor
        virtual ~Context() {}

};

class ContextNavBar : public Context {

    // navbar.xml

    public:

        /*   Instance Variables   */

        // Handles to the windows owned by the NavBar
        WindowHandle** transform;
        WindowHandle** objects;

        
        // Constructor
        ContextNavBar(WindowHandle** transform, WindowHandle** objects) : transform(transform), objects(objects) {
            this->type = Ui::ContextType::NAVBAR;
        }

};

class ContextTransform : public Context {

    // transform.xml

    public:

        /*   Instance Variables   */

        // Not owned by this class
        Physics::Object* object;


        // Constructor
        ContextTransform(Physics::Object* object) : object(object) {
            this->type = Ui::ContextType::TRANSFORM;
        }

};

class ContextObjects : public Context {

    // objects.xml

    public:

        /*   Instance Variables   */

        // Not owned by this class
        Physics::ObjectSet* objectSet;


        // Constructor
        ContextObjects(Physics::ObjectSet* objectSet) : objectSet(objectSet) {
            this->type = Ui::ContextType::OBJECTS;
        }

};

}
