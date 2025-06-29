#pragma once

#include "util/Utility.h"
#include "util/Log.h"

#include "graphics/gui/Core.h"
#include "graphics/drawing/PixelDrawer.h"
#include "graphics/font/FontDrawer.h"

#include "graphics/rendering/Camera.h"
#include "graphics/rendering/Display.h"
#include "graphics/gui/State.h"

#include "geometry/Vec.h"
#include "geometry/Tri.h"


namespace Graphics {
namespace Drawing {

class Drawer {

    /*
        This class acts as a function set to draw to a gui window.
        This is really just a high level wrapper for the underlying systems. For more low level information/control, see PixelDrawer

        This class optionally supports the use of depth (z-buffering)
        Any call where depth is not included will be force drawn, while NOT updating any depthBuffer values

        All function calls that include depth use linear depth interpolation. 
        This is not super accurate, so if accuracy is a concern, then manual interpolation is preferred
        Better interpolation is not implemented here because it requires passing way more values (and some of these functions already pass a ton)
    
        Opacity is also an optional paramater. This uses alpha blending (mixes the RGB with the pixel behind)
        This is only offered on calls using depth, because opacity doesnt make much sense without depth
    */

    public:
        
        /*   Instance variables   */
        
        // Handles per-pixel drawing
        PixelDrawer pixelDrawer;

        // Handles font drawing
        Font::FontDrawer fontDrawer;


        // Constructor
        Drawer(int width, int height) : pixelDrawer(width, height), fontDrawer( &(this->pixelDrawer) ) {}


        /*   Instance functions   */

        // Updates the width and height that PixelDrawer uses. This needs to be called when the GUI window is resized
        void updateDimensions(int width, int height);

        // Sets the buffer to the given pointer (assumes array size of PIXEL_BUFFER_WIDTH * PIXEL_BUFFER_HEIGHT)
        void setBuffer(uint32* buffer);

        // Draws a straight line from (x1, y1) to (x2, y2)
        void drawLine(uint32 color, int x1, int y1, int x2, int y2);
        void drawLine(uint32 color, int x1, int y1, int x2, int y2, float depth1, float depth2, float opacity = 1.0);

        // Draws a straight line along a given axis
        // The first and second coordinates may be in any order (y1>y2 and y1<y2 are both valid calls)
        void drawVerticalLine(uint32 color, int y1, int y2, int x);
        void drawVerticalLine(uint32 color, int y1, int y2, int x, float depth1, float depth2, float opacity = 1.0);
        void drawHorizontalLine(uint32 color, int x1, int x2, int y);
        void drawHorizontalLine(uint32 color, int x1, int x2, int y, float depth1, float depth2, float opacity = 1.0);

        // Draws a HOLLOW rectangle
        void drawRect(uint32 color, int x1, int y1, int x2, int y2);

        // Draws a FILLED rectangle
        void drawRectFilled(uint32 color, int x1, int y1, int x2, int y2);

        // Fills whole active section of the pixel buffer with a given color
        void fillScreen(uint32 color);

        // Draws an elipse at a given position, with a given radius along each axis
        void drawElipse(uint32 color, int x, int y, int radiusX, int radiusY);

        // Same as above, but with a single radius
        void drawCircle(uint32 color, int x, int y, int radius);

        // Draws a FILLED triangle which uses (x1, y1), (x2, y2), and (x3, y3) as vertices
        void drawTriangle(uint32 color, int x1, int y1, int x2, int y2, int x3, int y3);
        void drawTriangle(uint32 color, int x1, int y1, int x2, int y2, int x3, int y3, float depth1, float depth2, float depth3, float opacity = 1.0);

        // Same as above but uses a Tri object. The Tri3 version uses the z coordinates for depth.
        void drawTriangle(uint32 color, const Geometry::Tri2* tri);
        void drawTriangle(uint32 color, const Geometry::Tri3* tri, float opacity = 1.0);

        // Draws the fps box in the top left
        void drawFps(const Gui::State* state, const Rendering::Display* display);

        // Draws the sky based on the camera pitch
        void drawSky(const Rendering::Camera* camera, const Rendering::Display* display);

        // Draws a crosshair in the center of the display
        void drawCrosshair(const Rendering::Display* display);

};

}
}
