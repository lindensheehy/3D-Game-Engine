#include "../class-headers/ColorClass.h"


// Contructors
Color::Color(uint32 color) {

    this->rawValue = color;

    // This gets the sub values at each 8 bit interval of the 32 bit input
    this->opacityValue = (uint8) (color >> 24);
    this->redValue = (uint8) (color >> 16);
    this->greenValue = (uint8) (color >> 8);
    this->blueValue = (uint8) (color);
}

Color::Color(uint8 o, uint8 r, uint8 g, uint8 b) {

    this->redValue = r;
    this->greenValue = g;
    this->blueValue = b;
    this->opacityValue = o;
    
    // Load each 8 sub bits into a bigger variable
    this->rawValue = 0x00000000;
    this->rawValue |= o;
    this->rawValue <<= 8;
    this->rawValue |= r;
    this->rawValue <<= 8;
    this->rawValue |= g;
    this->rawValue <<= 8;
    this->rawValue |= b;
}

// Class functions
uint32 Color::setBrightness(uint32 color, double newBrightness) {

    // Unpack color code
    uint8 opacityValue = (uint8) (color >> 24);
    uint8 redValue = (uint8) (color >> 16);
    uint8 greenValue = (uint8) (color >> 8);
    uint8 blueValue = (uint8) (color);

    // Update values
    redValue *= newBrightness;
    greenValue *= newBrightness;
    blueValue *= newBrightness;

    // Repack color code
    uint32 newColor = 0x00000000;
    newColor |= opacityValue;
    newColor <<= 8;
    newColor |= redValue;
    newColor <<= 8;
    newColor |= greenValue;
    newColor <<= 8;
    newColor |= blueValue;

    return newColor;

}
