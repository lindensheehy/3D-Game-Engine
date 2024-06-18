#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "ColorClass.h"
#include "../lodepng/lodepng.h"

class PNG {

    /*
        This class holds data to describe a PNG file.
        This class makes use of the library 'lodepng', which was NOT written by me.
    */

    public:

        // Indexes for color channels of each pixel in the buffer array returned by lodepng
        // I just used char becuase they dont need to be big
        static const char RED = 0;
        static const char GREEN = 1;
        static const char BLUE = 2;
        static const char OPACITY = 3;


        /*   Instance variables   */

        // This is the filename of the PNG file which was loaded for this instance.
        const char* fileName;

        // Size of the PNG
        unsigned int width, height;

        // Raw data returned from lodepng. This is an array of length (width * height * 4 color channels)
        Uint8* rawData;

        // This holds the same data as rawData, but parsed by my constructor to be more usable.
        Color** pixels;


        /*   Contructors   */

        // Takes a filename/filepath and uses a function from lodepng to get its pixel data.
        PNG(const char* filename);

        // Allows taking an existing PNG object, and pulling a subset of pixels from it.
        PNG(PNG* input, int startx, int starty, int endx, int endy);

        // Destructor
        ~PNG();


        /*   Instance Functions   */

        // Returns a Color object represeting the pixel data at (x, y) in the PNG
        Color* getPixel(int x, int y);

        // Sets the pixel value at (x, y)
        bool setPixel(int x, int y, Color* pixel);

        // Same as above, but for single color channels
        Uint8 getChannel(int x, int y, char channel);
        bool setChannel(int x, int y, char channel, Uint8 value);

};
