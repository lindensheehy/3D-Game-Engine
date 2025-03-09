#include "ui/BindFuncs.h"

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

    /*   Binding logic   */

    // Transform button
    window->bindButton("ButtonTransform", new ActionOpenWindow(File::TRANSFORM, nullptr));

    return;

}

void BindFuncs::Transform::bind(WindowHandle* windowHandle) {

    if (windowHandle == nullptr) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a nullptr!", true);
        return;
    }

    Window* window = windowHandle->ptr;

    if (window == nullptr) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a handle containing an invalid Window ptr!", true);
        return;
    }

    Context* context = windowHandle->context;

    if (context == nullptr) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a handle containing null Context!", true);
        logWrite(" -> This bind function requires a Context of type TRANSFORM (ContextTransform)", true);
        return;
    }

    if (context->type != UIEnum::ContextType::TRANSFORM) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a handle containing the wrong Context!", true);
        logWrite(" -> Expected type ");
        logWrite(UIEnum::contextTypeToString(UIEnum::ContextType::TRANSFORM));
        logWrite(" but found type ");
        logWrite(UIEnum::contextTypeToString(context->type), true);
        return;
    }

    ContextTransform* castedContext = (ContextTransform*) context;
    Object* object = castedContext->object;

    if (object == nullptr) {
        logWrite("BindFuncs::Transform::bind(WindowHandle*) was called on a handle containing invalid Context!", true);
        logWrite(" -> The ContextTransform contained a null Object pointer", true);
        return;
    }

    /*   Binding logic   */

    // Top bar elements
    window->bindButton("WindowCloseButton", new ActionCloseWindow(windowHandle->id));
    window->bindDragable("WindowDragBar", window->pos, window->endPos);

    // Position
    window->bindTextInput("positionx", &(object->pos->x));
    window->bindTextInput("positiony", &(object->pos->y));
    window->bindTextInput("positionz", &(object->pos->z));

    // Rotation
    window->bindTextInput("rotationx", &(object->rotation->x));
    window->bindTextInput("rotationy", &(object->rotation->y));
    window->bindTextInput("rotationz", &(object->rotation->z));

    // Scale
    window->bindTextInput("scalex", &(object->scale->x));
    window->bindTextInput("scaley", &(object->scale->y));
    window->bindTextInput("scalez", &(object->scale->z));

    return;

}

void BindFuncs::Objects::bind(WindowHandle* windowHandle) {

}

void BindFuncs::Objects::createCube(Context* contextObjects) {

}

void BindFuncs::Objects::createSphere(Context* contextObjects) {
    
}
