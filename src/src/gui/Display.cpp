#include "gui/Display.h"


// Constructors
Gui::Display::Display(int width, int height) {    
    this->width = width;
    this->height = height;
    this->widthOffset = 0;
    this->heightOffset = 0;
}

Gui::Display::Display(int width, int height, int widthOffset, int heightOffset) {    
    this->width = width;
    this->height = height;
    this->widthOffset = widthOffset;
    this->heightOffset = heightOffset;
}

// Instance functions
void Gui::Display::updateDimensions(int width, int height) {

    if (width > PIXEL_BUFFER_WIDTH) {
        logWrite("Drawer::updateBounds() tried to set the width beyond the max range!", true);
        logWrite(" -> Tried to set ");
        logWrite(width);
        logWrite(" while the max allowed is ");
        logWrite(PIXEL_BUFFER_WIDTH, true);
        return;
    }

    if (height > PIXEL_BUFFER_HEIGHT) {
        logWrite("Drawer::updateBounds() tried to set the height beyond the max range!", true);
        logWrite(" -> Tried to set ");
        logWrite(height);
        logWrite(" while the max allowed is ");
        logWrite(PIXEL_BUFFER_HEIGHT, true);
        return;
    }

    this->width = width;
    this->height = height;

    return;

}

int Gui::Display::middleX() {
    return ((int) (this->width / 2)) + this->widthOffset;
}

int Gui::Display::middleY() {
    return ((int) (this->height / 2)) + this->heightOffset;
}

void Gui::Display::toDisplayPos(Vec2* vec) {
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

void Gui::Display::toDisplayPos(Vec3* vec) {
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

void Gui::Display::toDisplayPos(Mesh* mesh) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called Display->toDisplayPos(Mesh*) on a null pointer!", true);
        return;
    }

    for (int i = 0; i < mesh->vertexCount; i++) {
        this->toDisplayPos(mesh->projectedVerticies[i]);
    }
}
