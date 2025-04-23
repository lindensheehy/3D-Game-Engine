#include "ui/BindFuncs.h"

using namespace Ui;


void BindFuncs::NavBar::bind(WindowHandle* windowHandle) {

    if (windowHandle == nullptr) {
        logWrite("BindFuncs::NavBar::bind(WindowHandle*) was called on a nullptr!", true);
        return;
    }

    Window* window = windowHandle->ptr;

    if (window == nullptr) {
        logWrite("BindFuncs::NavBar::bind(WindowHandle*) was called on a handle containing an invalid Window ptr!", true);
        return;
    }

    Context* context = windowHandle->context;

    if (context == nullptr) {
        logWrite("BindFuncs::NavBar::bind(WindowHandle*) was called on a handle containing null Context!", true);
        logWrite(" -> This bind function requires a Context of type NAVBAR (ContextNavBar)", true);
        return;
    }

    if (context->type != ContextType::NAVBAR) {
        logWrite("BindFuncs::NavBar::bind(WindowHandle*) was called on a handle containing the wrong Context!", true);
        logWrite(" -> Expected type ");
        logWrite(contextTypeToString(ContextType::NAVBAR));
        logWrite(" but found type ");
        logWrite(contextTypeToString(context->type), true);
        return;
    }

    ContextNavBar* castedContext = (ContextNavBar*) context;
    WindowHandle** transform = castedContext->transform;
    WindowHandle** objects = castedContext->objects;

    /*   Binding logic   */

    // Transform button
    window->bindButton("ButtonTransform", new ActionOpenWindow(File::TRANSFORM, transform, BindFuncs::Transform::bind));
    window->bindButton("ButtonObjects", new ActionOpenWindow(File::OBJECTS, objects, BindFuncs::Objects::bind));

    return;

}

void BindFuncs::Transform::bind(WindowHandle* windowHandle) {


    /*   First do the binds that do not depend on the Context object   */

    if (windowHandle == nullptr) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a nullptr!", true);
        return;
    }

    Window* window = windowHandle->ptr;

    if (window == nullptr) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a handle containing an invalid Window ptr!", true);
        return;
    }

    // Top bar elements
    window->bindButton("WindowCloseButton", new ActionCloseWindow(windowHandle->id));
    window->bindDragable("WindowDragBar", &(window->pos), &(window->endPos));


    /*   Then try to grab the Context object, and bind the rest if it exists   */

    Context* context = windowHandle->context;

    // Null Context is okay, just the rest of the function cant run
    if (context == nullptr) return;

    if (context->type != ContextType::TRANSFORM) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a handle containing the wrong Context!", true);
        logWrite(" -> Expected type ");
        logWrite(contextTypeToString(ContextType::TRANSFORM));
        logWrite(" but found type ");
        logWrite(contextTypeToString(context->type), true);
        return;
    }

    ContextTransform* castedContext = (ContextTransform*) context;
    Physics::Object* object = castedContext->object;

    if (object == nullptr) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a handle containing invalid Context!", true);
        logWrite(" -> The ContextTransform contained a null Object pointer", true);
        return;
    }

    // Position
    window->bindTextInput("positionx", &(object->pos.x));
    window->bindTextInput("positiony", &(object->pos.y));
    window->bindTextInput("positionz", &(object->pos.z));

    // Rotation
    window->bindTextInput("rotationx", &(object->rotation.x));
    window->bindTextInput("rotationy", &(object->rotation.y));
    window->bindTextInput("rotationz", &(object->rotation.z));

    // Scale
    window->bindTextInput("scalex", &(object->scale.x));
    window->bindTextInput("scaley", &(object->scale.y));
    window->bindTextInput("scalez", &(object->scale.z));

    // Color
    // window->bindTextInput("color", (int*) &(object->mesh->color));

    return;

}

void BindFuncs::Objects::bind(WindowHandle* windowHandle) {


    /*   First do the binds that to not depend on the Context object   */

    if (windowHandle == nullptr) {
        logWrite("BindFuncs::Objects::bind(WindowHandle*) was called on a nullptr!", true);
        return;
    }

    Window* window = windowHandle->ptr;

    if (window == nullptr) {
        logWrite("BindFuncs::Objects::bind(WindowHandle*) was called on a handle containing an invalid Window ptr!", true);
        return;
    }

    // Top bar elements
    window->bindButton("WindowCloseButton", new ActionCloseWindow(windowHandle->id));
    window->bindDragable("WindowDragBar", &(window->pos), &(window->endPos));


    /*   The rest of the binds dont actually need the Context for this function   */

    window->bindButton("createCube", new ActionCallFunc(BindFuncs::Objects::createCube, &(windowHandle->context)));
    window->bindButton("createSphere", new ActionCallFunc(BindFuncs::Objects::createSphere, &(windowHandle->context)));


    return;

}

void BindFuncs::Objects::createCube(Context* contextObjects) {

    /*   Verify the contents of the Context object   */

    // Null Context is okay, just the function cant run this time
    if (contextObjects == nullptr) return;

    if (contextObjects->type != ContextType::OBJECTS) {
        logWrite("BindFuncs::Objects::createCube(Context*) was called on a handle containing the wrong Context!", true);
        logWrite(" -> Expected type ");
        logWrite(contextTypeToString(ContextType::OBJECTS));
        logWrite(" but found type ");
        logWrite(contextTypeToString(contextObjects->type), true);
        return;
    }

    ContextObjects* castedContext = (ContextObjects*) contextObjects;
    Physics::ObjectSet* objectSet = castedContext->objectSet;

    if (objectSet == nullptr) {
        logWrite("BindFuncs::Objects::createCube(Context*) was called on a handle containing invalid Context!", true);
        logWrite(" -> The ContextObjects contained a null ObjectSet pointer", true);
        return;
    }


    /*   Execution logic   */

    // Create the new Object
    Physics::Object* newObject = new Physics::Object();
    newObject->mesh = Geometry::Mesh::cubeMesh->copy();
    objectSet->pushBack(newObject);

    return;

}

void BindFuncs::Objects::createSphere(Context* contextObjects) {

    /*   Verify the contents of the Context object   */

    // Null Context is okay, just the function cant run this time
    if (contextObjects == nullptr) return;

    if (contextObjects->type != ContextType::OBJECTS) {
        logWrite("BindFuncs::Objects::createCube(Context*) was called on a handle containing the wrong Context!", true);
        logWrite(" -> Expected type ");
        logWrite(contextTypeToString(ContextType::OBJECTS));
        logWrite(" but found type ");
        logWrite(contextTypeToString(contextObjects->type), true);
        return;
    }

    ContextObjects* castedContext = (ContextObjects*) contextObjects;
    Physics::ObjectSet* objectSet = castedContext->objectSet;

    if (objectSet == nullptr) {
        logWrite("BindFuncs::Objects::createCube(Context*) was called on a handle containing invalid Context!", true);
        logWrite(" -> The ContextObjects contained a null ObjectSet pointer", true);
        return;
    }


    /*   Execution logic   */

    // Create the new Object
    Physics::Object* newObject = new Physics::Object();
    newObject->mesh = Geometry::Mesh::sphereMesh->copy();
    objectSet->pushBack(newObject);

    return;

}
