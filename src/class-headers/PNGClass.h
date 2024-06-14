#ifndef PNGClass
#define PNGClass

#include <iostream>
#include <SDL2/SDL.h>

#include "ColorClass.h"
#include "../lodepng/lodepng.cpp"

class PNG {

    public:

        static const char RED = 0;
        static const char GREEN = 1;
        static const char BLUE = 2;
        static const char OPACITY = 3;

        // Instance variables
        const char* fileName;
        unsigned int width;
        unsigned int height;
        Uint8* rawData;
        Color** pixels;

        // Contructors
        PNG(const char* filename);
        PNG(PNG* input, int startx, int starty, int endx, int endy);

        // Destructor
        ~PNG();

        // Instance Functions
        Color* getPixel(int x, int y);
        bool setPixel(int x, int y, Color* pixel);
        Uint8 getChannel(int x, int y, char channel);
        bool setChannel(int x, int y, char channel, Uint8 value);

};

#endif