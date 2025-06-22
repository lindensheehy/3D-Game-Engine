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

        Ui::ContextType type = Ui::ContextType::NONE;

        Context() {}

        virtual ~Context() {}

};

class ContextNavBar : public Context {

    // navbar.xml

    public:

        // Handles to the windows owned by the NavBar
        WindowHandle** transform;
        WindowHandle** objects;

        ContextNavBar(WindowHandle** transform, WindowHandle** objects) : transform(transform), objects(objects) {
            this->type = Ui::ContextType::NAVBAR;
        }

};

class ContextTransform : public Context {

    // transform.xml

    public:

        // Not owned by this class
        Physics::Object* object;

        ContextTransform(Physics::Object* object) : object(object) {
            this->type = Ui::ContextType::TRANSFORM;
        }

};

class ContextObjects : public Context {

    // objects.xml

    public:

        // Not owned by this class
        Physics::ObjectSet* objectSet;

        ContextObjects(Physics::ObjectSet* objectSet) : objectSet(objectSet) {
            this->type = Ui::ContextType::OBJECTS;
        }

};

}
