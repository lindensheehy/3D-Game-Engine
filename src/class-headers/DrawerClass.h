#pragma once

#include <SDL2/SDL.h>

#include "PNGClass.h"
#include "Vec2Class.h"
#include "Tri2Class.h"
#include "../math/math.h"
#include "../log/log.h"

class Drawer {

    /*
        This class acts as a function set to draw to a gui window.
        A pixel buffer is the only SDL2 functionality I allowed myself to do, so this class implements all the drawing functions I need.
        The pixel buffer is simply a single dimension array, and the buffer width represents the length of each 'set' within the array.
        Treating the pixel buffer as a 2d array acts as follows:
        buffer[2][3] = buffer[(2 * bufferHeight) + 3], where 2,3 is x,y
    */

    public:
        
        // Instance variables
        Uint32* buffer;
        unsigned int bufferHeight, bufferWidth;
        unsigned int bufferSize;


        // Constructor
        Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput);


        /*   Instance functions   */

        // Writes a color to a coordinate within the buffer. Foundation for all further drawing functions.
        void writePixel(Uint32 pixel, int x, int y);

        // Draws a straight line from (x1, y1) to (x2, y2) in the given color
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2);

        // Same as above, but uses Vec2 objects. These objects are NOT deleted by this function call and must be handled properly
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to);

        // Draws a straight line along a given axis. Similar to drawLine, but less complex.
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y);

        // Draws a FILLED rectangle from (x1, y1) to (x2, y2)
        void drawRect(Uint32 pixel, int x1, int y1, int x2, int y2);

        // Fills whole buffer with a given color
        void fillScreen(Uint32 pixel);

        // Draws an elipse at a given location, with a given radius along each axis.
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy);

        // Same as above, but only one radius allowed.
        void drawCircle(Uint32 pixel, int locationx, int locationy, int radius);

        // Draws a FILLED triangle which uses (x1, y1), (x2, y2), and (x3, y3) as vertices
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3);

        // Same as above but uses a Tri2 object. This object is NOT deleted by this function call and must be handled properly
        void drawTriangle(Uint32 pixel, Tri2* tri);

        // Draws a PNG file using a PNG object. the top left corner of the PNG will lie at (x, y)
        void drawpng(PNG* file, int x, int y);

};
