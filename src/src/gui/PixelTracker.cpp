#include "gui/PixelTracker.h"

Gui::PixelTracker::PixelTracker() {

    this->currentObject = nullptr;
    this->watchedPixel = new Vec2(0, 0);

    this->watchingPixelWrites = false;

}

Gui::PixelTracker::~PixelTracker() {

    if (this->watchedPixel != nullptr) delete this->watchedPixel;

}

void Gui::PixelTracker::foundWrite() {

    if (this->currentObject != nullptr) this->foundObject = this->currentObject;

    return;

}
