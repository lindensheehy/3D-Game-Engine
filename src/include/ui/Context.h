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

        public:

            // Handles to the windows owned by the NavBar
            WindowHandle** transform;
            WindowHandle** objects;

            ContextNavBar(WindowHandle** transform, WindowHandle** objects) : transform(transform), objects(objects) {
                this->type = Ui::ContextType::NAVBAR;
            }

    };

    class ContextTransform : public Context {

        public:

            // Not owned by this class
            Object* object;

            ContextTransform(Object* object) : object(object) {
                this->type = Ui::ContextType::TRANSFORM;
            }

    };

    class ContextObjects : public Context {

        public:

            // Not owned by this class
            ObjectSet* objectSet;

            ContextObjects(ObjectSet* objectSet) : objectSet(objectSet) {
                this->type = Ui::ContextType::OBJECTS;
            }

    };

}
