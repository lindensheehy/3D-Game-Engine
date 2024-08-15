#pragma once


#include <stdint.h>
#include <SDL2/SDL.h>
#include "../lodepng/lodepng.h"

#include "Vec.h"
#include "Tri.h"

#include "Math.h"
#include "Log.h"


typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


class Color {

    public:

        // Constant color codes
        // Bytes are [opacity][red][green][blue]
        static const uint32 RED    = 0xFFFF0000;
        static const uint32 GREEN  = 0xFF00FF00;
        static const uint32 BLUE   = 0xFF0000FF;
        static const uint32 BLACK  = 0xFF000000;
        static const uint32 WHITE  = 0xFFFFFFFF;
        static const uint32 GREY   = 0xFF888888;


        /*   Instance variables   */

        // Raw value which was given
        uint32 rawValue;

        // Individual color channels
        uint8 redValue, greenValue, blueValue, opacityValue;


        // Contructors
        Color(uint32 color);
        Color(uint8 o, uint8 r, uint8 g, uint8 b);


        /*   Class functions   */

        // Sets the brightness of a given color (uint32) to a double between 0-1.
        // Values higher than 1 CAN be used, but could cause overflow issues.
        static uint32 setBrightness(uint32 color, double newBrightness);

};



class PNG {

    /*
        This class holds data to describe a PNG file.
        This class makes use of the library 'lodepng', which was NOT written by me.
    */

    public:

        // Indexes for color channels of each pixel in the buffer array returned by lodepng
        // I just used char becuase they dont need to be big, values are 0-3
        static const char RED, GREEN, BLUE, OPACITY;


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



class Drawer {

    /*
        This class acts as a function set to draw to a gui window.
        A pixel buffer is the only SDL2 functionality I allowed myself to do, so this class implements all the drawing functions I need.
        The pixel buffer is simply a single dimension array, and the buffer width represents the length of each 'set' within the array.
        Treating the pixel buffer as a 2d array acts as follows:
        buffer[2][3] = buffer[(2 * bufferHeight) + 3], where 2,3 is x,y
        This class supports the use of depth. When including depth values into function calls, the depthBuffer will be checked before writing pixels
        Depth is optional, and any call where depth is not included will be drawn at depth 0, while NOT updating the depthBuffer values
    */

    public:
        
        // Instance variables
        Uint32* buffer;
        double* depthBuffer;
        unsigned int bufferHeight, bufferWidth;
        unsigned int bufferSize;


        // Constructor
        Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput);


        /*   Instance functions   */

        // Returns the 1d index cooresponding to a 2d set of indices
        int bufferIndex(int x, int y);

        // Writes a color to a coordinate within the buffer. Foundation for all further drawing functions.
        void writePixel(Uint32 pixel, int x, int y);
        void writePixel(Uint32 pixel, int x, int y, double depth);

        // Draws a straight line from (x1, y1) to (x2, y2) in the given color
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2);
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2, double depth1, double depth2);

        // Same as above, but uses Vec2 objects. These objects are NOT deleted by this function call and must be handled properly
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to);
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to, double depth1, double depth2);

        // Draws a straight line along a given axis. Similar to drawLine, but less complex.
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x);
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x, double depth1, double depth2);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y, double depth1, double depth2);

        // Draws a FILLED rectangle from (x1, y1) to (x2, y2)
        void drawRect(Uint32 pixel, int x1, int y1, int x2, int y2);

        // Fills whole buffer with a given color
        void fillScreen(Uint32 pixel);

        // Draws an elipse at a given location, with a given radius along each axis.
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy);
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy, double depth);

        // Same as above, but only one radius allowed.
        void drawCircle(Uint32 pixel, int locationx, int locationy, int radius);
        void drawCircle(Uint32 pixel, int locationx, int locationy, int radius, double depth);

        // Draws a FILLED triangle which uses (x1, y1), (x2, y2), and (x3, y3) as vertices
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3);
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, double depth1, double depth2, double depth3);

        // Same as above but uses a Tri2 object. This object is NOT deleted by this function call and must be handled properly
        void drawTriangle(Uint32 pixel, Tri2* tri);
        void drawTriangle(Uint32 pixel, Tri2* tri, double depth1, double depth2, double depth3);

        // Draws a PNG file using a PNG object. the top left corner of the PNG will lie at (x, y)
        void drawpng(PNG* file, int x, int y);
        void drawpng(PNG* file, int x, int y, double depth);

};



class Font {

    /*
        This class holds data to print text characters to the screen
        Before using, an instance must be made by referencing a drawer instance so that this class can actually draw
        The contructor here loads all the pixel arts for each text character
    */

    public:

        // Instance Variables
        Drawer* drawer;

        // Constructors
        Font();
        Font(Drawer* drawer);

        /*   Instance Functions   */

        // Loads the character pixel arts into memory
        void init();

        // Returns a pointer to the pixels for a character
        bool* getCharRef(char ch);
        bool* getCharRef(int num);

        // Draws a set of pixels to the screen. the other draw functions rely on this
        void drawPixels(bool* pixels, int x, int y, Uint32 color);

        // Draws a character to the screen, the upper left will be at (x, y)
        void drawChar(char ch, int x, int y, Uint32 color);

        // Draws a string to the screen, the top left will be at (x, y)
        void drawString(const char* string, int x, int y, Uint32 color);

        // Draws an integer value to the screen, the top left will be at (x, y)
        void drawInt(int num, int x, int y, Uint32 color);
    
    private:

        /*
            Character Pixel Arts
            This bool** type is a list of lists of bools.
            The primary list is length 38 for the amount of chars which can be drawn
            Each of the sub lists is length 49, which gives a 7x7 grid of pixels per char
            This list is filled by running init
        */

        bool** chars;

        // Here you can see the data which is used to create the bool lists
        // underscore is 0 (false) and 0 is 1 (true), the bool values coorespond to if they are shown or not when drawing
        // All the seperate strings here get put together by the compiler into one big string, so the /n chars are the seperators
        // | acts as a line end char
        // String length is: char size + 1 * char count + 1 = length 2110 
        const char* rawChars = {

            // A
            "_______|"
            "__000__|"
            "_0___0_|"
            "_00000_|"
            "_0___0_|"
            "_0___0_|"
            "_______|"
            "\n"

            // B
            "_______|"
            "_0000__|"
            "_0___0_|"
            "_0000__|"
            "_0___0_|"
            "_0000__|"
            "_______|"
            "\n"

            // C
            "_______|"
            "__0000_|"
            "_0_____|"
            "_0_____|"
            "_0_____|"
            "__0000_|"
            "_______|"
            "\n"

            // D
            "_______|"
            "_0000__|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "_0000__|"
            "_______|"
            "\n"

            // E
            "_______|"
            "_00000_|"
            "_0_____|"
            "_0000__|"
            "_0_____|"
            "_00000_|"
            "_______|"
            "\n"

            // F
            "_______|"
            "_00000_|"
            "_0_____|"
            "_0000__|"
            "_0_____|"
            "_0_____|"
            "_______|"
            "\n"

            // G
            "_______|"
            "_00000_|"
            "_0_____|"
            "_0__00_|"
            "_0___0_|"
            "_00000_|"
            "_______|"
            "\n"

            // H
            "_______|"
            "_0___0_|"
            "_0___0_|"
            "_00000_|"
            "_0___0_|"
            "_0___0_|"
            "_______|"
            "\n"

            // I
            "_______|"
            "_00000_|"
            "___0___|"
            "___0___|"
            "___0___|"
            "_00000_|"
            "_______|"
            "\n"

            // J
            "_______|"
            "_00000_|"
            "___0___|"
            "___0___|"
            "___0___|"
            "_00____|"
            "_______|"
            "\n"

            // K
            "_______|"
            "_0___0_|"
            "_0__0__|"
            "_000___|"
            "_0__0__|"
            "_0___0_|"
            "_______|"
            "\n"

            // L
            "_______|"
            "_0_____|"
            "_0_____|"
            "_0_____|"
            "_0_____|"
            "_00000_|"
            "_______|"
            "\n"

            // M
            "_______|"
            "_0___0_|"
            "_00000_|"
            "_0_0_0_|"
            "_0___0_|"
            "_0___0_|"
            "_______|"
            "\n"

            // N
            "_______|"
            "_0___0_|"
            "_00__0_|"
            "_0_0_0_|"
            "_0__00_|"
            "_0___0_|"
            "_______|"
            "\n"

            // O
            "_______|"
            "__000__|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "__000__|"
            "_______|"
            "\n"

            // P
            "_______|"
            "_0000__|"
            "_0___0_|"
            "_0000__|"
            "_0_____|"
            "_0_____|"
            "_______|"
            "\n"

            // Q
            "_______|"
            "__000__|"
            "_0___0_|"
            "_0___0_|"
            "__000__|"
            "____00_|"
            "_______|"
            "\n"

            // R
            "_______|"
            "_0000__|"
            "_0___0_|"
            "_0000__|"
            "_0__0__|"
            "_0___0_|"
            "_______|"
            "\n"

            // S
            "_______|"
            "__0000_|"
            "_0_____|"
            "__000__|"
            "_____0_|"
            "_0000__|"
            "_______|"
            "\n"

            // T
            "_______|"
            "_00000_|"
            "___0___|"
            "___0___|"
            "___0___|"
            "___0___|"
            "_______|"
            "\n"

            // U
            "_______|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "__000__|"
            "_______|"
            "\n"

            // V
            "_______|"
            "_0___0_|"
            "_0___0_|"
            "_0___0_|"
            "__0_0__|"
            "___0___|"
            "_______|"
            "\n"

            // W
            "_______|"
            "_0___0_|"
            "_0___0_|"
            "_0_0_0_|"
            "_00_00_|"
            "_0___0_|"
            "_______|"
            "\n"

            // X
            "_______|"
            "_0___0_|"
            "__0_0__|"
            "___0___|"
            "__0_0__|"
            "_0___0_|"
            "_______|"
            "\n"

            // Y
            "_______|"
            "_0___0_|"
            "__0_0__|"
            "___0___|"
            "___0___|"
            "___0___|"
            "_______|"
            "\n"

            // Z
            "_______|"
            "_00000_|"
            "____0__|"
            "___0___|"
            "__0____|"
            "_00000_|"
            "_______|"
            "\n"

            // 0
            "_______|"
            "__000__|"
            "_0__00_|"
            "_0_0_0_|"
            "_00__0_|"
            "__000__|"
            "_______|"
            "\n"

            // 1
            "_______|"
            "__00___|"
            "_0_0___|"
            "___0___|"
            "___0___|"
            "_00000_|"
            "_______|"
            "\n"

            // 2
            "_______|"
            "__000__|"
            "_0___0_|"
            "___00__|"
            "__0____|"
            "_00000_|"
            "_______|"
            "\n"

            // 3
            "_______|"
            "__000__|"
            "_____0_|"
            "___00__|"
            "_____0_|"
            "__000__|"
            "_______|"
            "\n"

            // 4
            "_______|"
            "___0___|"
            "__00___|"
            "_0_0___|"
            "_00000_|"
            "___0___|"
            "_______|"
            "\n"

            // 5
            "_______|"
            "_00000_|"
            "_0_____|"
            "_0000__|"
            "_____0_|"
            "_0000__|"
            "_______|"
            "\n"

            // 6
            "_______|"
            "__000__|"
            "_0_____|"
            "_0000__|"
            "_0___0_|"
            "__000__|"
            "_______|"
            "\n"

            // 7
            "_______|"
            "_00000_|"
            "____0__|"
            "___0___|"
            "__0____|"
            "_0_____|"
            "_______|"
            "\n"
            
            // 8
            "_______|"
            "__000__|"
            "_0___0_|"
            "__000__|"
            "_0___0_|"
            "__000__|"
            "_______|"
            "\n"

            // 9
            "_______|"
            "__000__|"
            "_0___0_|"
            "__0000_|"
            "_____0_|"
            "__000__|"
            "_______|"
            "\n"

            // Space
            "_______|"
            "_______|"
            "_______|"
            "_______|"
            "_______|"
            "_______|"
            "_______|"
            "\n"

            // Disallowed char
            "_______|"
            "_00000_|"
            "_00_00_|"
            "_0_0_0_|"
            "_00_00_|"
            "_00000_|"
            "_______|"
            "\n"

        };

};
