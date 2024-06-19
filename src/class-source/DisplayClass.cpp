#include "../class-headers/DisplayClass.h"

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

    int drawPosx = (int) (vec->x * (double) this->width);
    drawPosx += this->widthOffset;

    int drawPosy = this->height - (int) (vec->y * (double) this->height); // display->height - because y=0 is at the top
    drawPosy += this->heightOffset;

    vec->x = drawPosx;
    vec->y = drawPosy;

    return;
}

void Display::toDisplayPos(Mesh* mesh) {
    for (int i = 0; i < mesh->vertexCount; i++) {
        this->toDisplayPos(mesh->projectedVerticies[i]);
    }
}
