#include "graphics/rendering/Display.h"

using namespace Graphics::Rendering;


Display::Display(int width, int height, int widthOffset, int heightOffset) {

    this->width = width;
    this->height = height;
    this->widthOffset = widthOffset;
    this->heightOffset = heightOffset;

    return;

}

void Display::setState(const Display* other) {

    this->width = other->width;
    this->height = other->height;
    this->widthOffset = other->widthOffset;
    this->heightOffset = other->heightOffset;

    return;

}

void Display::updateDimensions(int width, int height) {

    this->width = width;
    this->height = height;

    return;

}

int Display::middleX() const {
    return ( (this->width / 2) + this->widthOffset );
}

int Display::middleY() const {
    return ( (this->height / 2) + this->heightOffset );
}

void Display::toDisplayPos(Geometry::Vec3* out) const {

    if (out == nullptr) {
        logWrite("Called Display->toDisplayPos(Vec3*) on a null pointer!", true);
        return;
    }

    float drawPosx = out->x * (float) this->width;
    drawPosx += this->widthOffset;

    float drawPosy = this->height - (out->y * (float) this->height); // minus because y=0 is at the top
    drawPosy += this->heightOffset;

    out->x = drawPosx;
    out->y = drawPosy;

    return;

}
