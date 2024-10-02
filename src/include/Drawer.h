#pragma once


#include <SDL2/SDL.h>
#include "../lodepng/lodepng.h"

#include "Vec.h"
#include "Tri.h"
#include "Camera.h"
#include "State.h"
#include "LinkedList.h"

#include "Math.h"
#include "Log.h"


class Color {

    public:

        // Constant color codes
        // Bytes are [opacity][red][green][blue]
        static const Uint32 RED         = 0xFFFF0000;
        static const Uint32 GREEN       = 0xFF00FF00;
        static const Uint32 BLUE        = 0xFF0000FF;
        static const Uint32 BLACK       = 0xFF000000;
        static const Uint32 WHITE       = 0xFFFFFFFF;
        static const Uint32 GREY        = 0xFF888888;
        static const Uint32 DARKGREY    = 0xFF333333;

        // For UI drawing
        static const Uint32 BACKGROUND  = 0xFF303030;
        static const Uint32 LIGHTER     = 0xFF505050;
        static const Uint32 DARKER      = 0xFF181818;
        static const Uint32 ACCENT      = 0xFFA78BFA;


        /*   Instance variables   */

        // Raw value which was given
        Uint32 rawValue;

        // Individual color channels
        Uint8 redValue, greenValue, blueValue, opacityValue;


        // Contructors
        Color(Uint32 color);
        Color(Uint8 o, Uint8 r, Uint8 g, Uint8 b);


        /*   Class functions   */

        // Sets the brightness of a given color (Uint32) to a double between 0-1.
        // Values higher than 1 CAN be used, but could cause overflow issues.
        static Uint32 setBrightness(Uint32 color, double newBrightness);

        // Merges the rgb values of two colors based on opacity values. The sum of opacity1 and opacity2 should be 1
        static Uint32 merge(Uint32 color1, double opacity1, Uint32 color2, double opacity2);

};



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
        
        /*   Instance variables   */
        
        Uint32* buffer;
        unsigned int bufferHeight, bufferWidth;
        unsigned int bufferSize;

        // The depth buffer stores the distance between each pixel and the camera. this allows meshes to be drawn in any order while appearing accurately.
        double* depthBuffer;


        // Constructors
        Drawer(unsigned int bufferWidthInput, unsigned int bufferHeightInput);
        Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput);

        // Destructor
        ~Drawer();


        /*   Instance functions   */

        // Sets all the values in the depth buffer to infinity
        void resetDepthBuffer();

        // Returns the 1d index cooresponding to a 2d set of indices
        int bufferIndex(int x, int y);

        // Returns true if the coordinate exists in the buffer
        bool inBufferRange(int x, int y);

        // Writes a color to a coordinate within the buffer. Foundation for all further drawing functions.
        void writePixel(Uint32 pixel, int x, int y);
        void writePixel(Uint32 pixel, int x, int y, double depth);
        void writePixel(Uint32 pixel, int x, int y, double depth, double opacity);

        // Draws a straight line from (x1, y1) to (x2, y2) in the given color
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2);
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2, double depth1, double depth2);
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2, double depth1, double depth2, double opacity);

        // Same as above, but uses Vec2 objects. These objects are NOT deleted by this function call and must be handled properly
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to);
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to, double depth1, double depth2);
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to, double depth1, double depth2, double opacity);

        // Draws a straight line along a given axis
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x);
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x, double depth1, double depth2);
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x, double depth1, double depth2, double opacity);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y, double depth1, double depth2);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y, double depth1, double depth2, double opacity);

        // Draws a HOLLOW rectangle
        void drawRect(Uint32 pixel, int x1, int y1, int x2, int y2);
        void drawRect(Uint32 pixel, Vec2* pos1, Vec2* pos2);

        // Draws a FILLED rectangle
        void drawRectFilled(Uint32 pixel, int x1, int y1, int x2, int y2);
        void drawRectFilled(Uint32 pixel, Vec2* pos1, Vec2* pos2);

        // Fills whole buffer with a given color
        void fillScreen(Uint32 pixel);

        // Draws an elipse at a given location, with a given radius along each axis.
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy);
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy, double depth);

        // Same as above, but only one radius allowed.
        void drawCircle(Uint32 pixel, int x, int y, int radius);
        void drawCircle(Uint32 pixel, Vec2* pos, int radius);
        void drawCircle(Uint32 pixel, int x, int y, int radius, double depth);
        void drawCircle(Uint32 pixel, Vec2* pos, int radius, double depth);

        // Draws a FILLED triangle which uses (x1, y1), (x2, y2), and (x3, y3) as vertices
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3);
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, double depth1, double depth2, double depth3);
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, double depth1, double depth2, double depth3, double opacity);

        // Same as above but uses a Tri object. This object is NOT deleted by this function call and must be handled properly. The Tri3 call includes depth.
        void drawTriangle(Uint32 pixel, Tri2* tri);
        void drawTriangle(Uint32 pixel, Tri3* tri);
        void drawTriangle(Uint32 pixel, Tri3* tri, double opacity);

        // Draws a PNG file using a PNG object. the top left corner of the PNG will lie at (x, y)
        void drawpng(PNG* file, int x, int y);
        void drawpng(PNG* file, Vec2* pos);
        void drawpng(PNG* file, int x, int y, double depth);
        void drawpng(PNG* file, Vec2* pos, double depth);

        // Loads the character pixel arts into memory
        void initFont();

        // Draws a character to the screen, the upper left will be at (x, y)
        void drawChar(Uint32 pixel, char ch, int x, int y);

        // Draws a string to the screen, the top left will be at (x, y)
        void drawString(Uint32 pixel, const char* string, int x, int y);
        void drawString(Uint32 pixel, const char* string, Vec2* pos);

        // Draws an integer value to the screen, the top left will be at (x, y)
        void drawInt(Uint32 pixel, int num, int x, int y);

        // Draws the fps box in the top left
        void drawFps(State* state, Display* display);

        // Draws the sky based on the camera pitch
        void drawSky(Camera* camera, Display* display);

        // Draws a crosshair in the center of the display
        void drawCrosshair(Display* display);

    private:   

        /*   The following functions dont need to be called outside this class   */

        // Draws a set of pixels to the screen. the other draw functions rely on this
        void drawPixels(Uint32 pixel, bool* pixels, int x, int y);

        // Returns a pointer to the pixels for a character
        bool* getCharRef(char ch);
        bool* getCharRef(int num);

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
        // String length is: ( (7 * 8) + 1 ) * char count = 2166 + nullchar -> 2167
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
