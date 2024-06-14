#ifndef DrawerClass
#define DrawerClass

#include <SDL2/SDL.h>

#include "PNGClass.h"
#include "Vec2Class.h"
#include "Tri2Class.h"
#include "../math/math.cpp"
#include "../log/log.cpp"

class Drawer {
    public:
        
        // Instance variables
        Uint32* buffer;
        unsigned int bufferHeight;
        unsigned int bufferWidth;
        unsigned int bufferSize;

        // Constructor
        Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput);

        // Instance functions
        void writePixel(Uint32 pixel, int x, int y);
        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2);
        void drawLine(Uint32 pixel, Vec2* from, Vec2* to);
        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x);
        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y);
        void drawRect(Uint32 pixel, int startx, int starty, int endx, int endy);
        void fillScreen(Uint32 pixel);
        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy);
        void drawCircle(Uint32 pixel, int locationx, int locationy, int radius);
        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3);
        void drawTriangle(Uint32 pixel, Tri2* tri);
        void drawpng(PNG* file, int x, int y);

};

#endif