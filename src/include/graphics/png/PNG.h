/*
    --- THIS FILE IS NOT PART OF THE CURRENT BUILD ---

    This file doesn’t work right now, but it’s here on purpose.
    I brought it over from one of my other projects where PNGs were loaded using 'lodepng' (an external library)

    It’s meant to hold the logic and data for decoding PNG files into a usable format for the engine
    This was (and likely will be) done by loading pixel data into memory for use as textures.

    Since I am not using includes in this project, I removed the external lodepng dependency
    This code only exists to help layout the project structure.

    Leaving it here to show what was planned. Not forgotten, just deferred.
*/

#pragma once

#include "util/Utility.h"


namespace Graphics {
namespace Png {

class PNG {

    /*
        This class holds data to describe a PNG file, and handles decoding
    */

    public:

        class Color;

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
        uint32* pixels;


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
        uint8 getChannel(int x, int y, char channel);
        bool setChannel(int x, int y, char channel, uint8 value);

};

}
}
