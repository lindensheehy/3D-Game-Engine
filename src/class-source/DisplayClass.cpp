#include "../class-headers/DisplayClass.h"

#include "../log/log.h"
#include "../class-headers/Vec2Class.h"
#include "../class-headers/MeshClass.h"


// Constructors
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

// Instance functions
int Display::middleX() {
    return ((int) (this->width / 2)) + this->widthOffset;
}

int Display::middleY() {
    return ((int) (this->height / 2)) + this->heightOffset;
}

void Display::toDisplayPos(Vec2* vec) {
    /*
        Converts factors from 0-1 into display cooridnates given a Display object
        CHANGES THE ACTUAL VALUES OF THE ARGUMENT
    */

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Display->toDisplayPos(Vec2*) on a null pointer!", true);
        return;
    }

    int drawPosx = (int) (vec->x * (double) this->width);
    drawPosx += this->widthOffset;

    int drawPosy = this->height - (int) (vec->y * (double) this->height); // minus because y=0 is at the top
    drawPosy += this->heightOffset;

    vec->x = drawPosx;
    vec->y = drawPosy;

    return;
}

void Display::toDisplayPos(Mesh* mesh) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called Display->toDisplayPos(Mesh*) on a null pointer!", true);
        return;
    }

    for (int i = 0; i < mesh->vertexCount; i++) {
        this->toDisplayPos(mesh->projectedVerticies[i]);
    }
}
