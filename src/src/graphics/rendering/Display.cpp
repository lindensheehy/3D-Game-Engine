#include "graphics/rendering/Display.h"

using namespace Graphics::Rendering;


Display::Display() {
    this->width = 0;
    this->height = 0;
    this->widthOffset = 0;
    this->heightOffset = 0;
}

Display::Display(int width, int height) {    
    this->width = width;
    this->height = height;
    this->widthOffset = 0;
    this->heightOffset = 0;
}

Display::Display(int width, int height, int widthOffset, int heightOffset) {    
    this->width = width;
    this->height = height;
    this->widthOffset = widthOffset;
    this->heightOffset = heightOffset;
}

void Display::setState(Display* other) {

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

int Display::middleX() {
    return ((int) (this->width / 2)) + this->widthOffset;
}

int Display::middleY() {
    return ((int) (this->height / 2)) + this->heightOffset;
}

void Display::toDisplayPos(Geometry::Vec2* vec) {
    /*
        Converts factors from 0-1 into display cooridnates given a Display object
        CHANGES THE ACTUAL VALUES OF THE ARGUMENT
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Display->toDisplayPos(Vec2*) on a null pointer!", true);
        return;
    }

    int drawPosx = (int) (vec->x * (float) this->width);
    drawPosx += this->widthOffset;

    int drawPosy = this->height - (int) (vec->y * (float) this->height); // minus because y=0 is at the top
    drawPosy += this->heightOffset;

    vec->x = drawPosx;
    vec->y = drawPosy;

    return;

}

void Display::toDisplayPos(Geometry::Vec3* vec) {
    /*
        Converts factors from 0-1 into display cooridnates given a Display object
        CHANGES THE ACTUAL VALUES OF THE ARGUMENT
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Display->toDisplayPos(Vec2*) on a null pointer!", true);
        return;
    }

    float drawPosx = vec->x * (float) this->width;
    drawPosx += this->widthOffset;

    float drawPosy = this->height - (vec->y * (float) this->height); // minus because y=0 is at the top
    drawPosy += this->heightOffset;

    vec->x = drawPosx;
    vec->y = drawPosy;

    return;

}
