#pragma once

#include "util/Utility.h"

#include "physics/ObjectSet.h"


enum class BindContextType {
    NONE,
    TRANSFORM,
    OBJECTS
};


class BindContext {

    public:

        BindContextType type;

        BindContext() : type(BindContextType::NONE) {}

        virtual ~BindContext() {}

};

class BindContextTransform : public BindContext {

    public:

        // Not owned by this class
        Object* object;

        BindContextTransform(Object* object) : object(object) {}

};

class BindContextObjects : public BindContext {

    public:

        // Not owned by this class
        ObjectSet* objectSet;

        BindContextObjects(ObjectSet* objectSet) : objectSet(objectSet) {}

};
