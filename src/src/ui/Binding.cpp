#include "ui/Binding.h"

void Binding::bindTransform(WindowHandle windowHandle, Object* object) {

    if (object == nullptr) {
        logWrite("UI::bindWindowTransform(WindowID, Object*) was called on a nullptr!", true);
        return;
    }

    Window* window = windowHandle.ptr;

    if (window == nullptr) {
        logWrite("UI::bindWindowTransform(WindowID, Object*) was called on an invalid WindowID!", true);
        return;
    }

    /*   Binding logic   */

    // Top bar elements
    window->bindButton("WindowCloseButton", new ActionCloseWindow(windowHandle.id));
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

void Binding::bindNavBar(WindowHandle windowHandle) {

    Window* window = windowHandle.ptr;

    if (window == nullptr) {
        logWrite("UI::bindWindowTransform(WindowID, Object*) was called on an invalid WindowID!", true);
        return;
    }

    /*   Binding logic   */

    // Transform button
    window->bindButton("ButtonTransform", new ActionOpenWindow(File::TRANSFORM));

    return;

}
