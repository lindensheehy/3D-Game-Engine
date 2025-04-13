#pragma once

#include "util/Utility.h"

#include "graphics/rendering/Camera.h"
#include "graphics/rendering/Display.h"
#include "graphics/drawing/PixelDrawer.h"
#include "graphics/font/FontDrawer.h"
#include "graphics/gui/Core.h"
#include "graphics/gui/State.h"

#include "geometry/Vec.h"
#include "geometry/Tri.h"
#include "util/LinkedList.h"


namespace Graphics {
namespace Drawing {

class Drawer {

    /*
        This class acts as a function set to draw to a gui window.
        Everything here writes to a manually allocated pixel buffer, which is then passed to Windows by Gui::Window
        The pixel buffer is simply a single dimension array, and the buffer width represents the length of each 'set' within the array.
        Treating the pixel buffer as a 2d array acts as follows:
        buffer[2][3] = buffer[(2 * bufferHeight) + 3], where 2,3 is x,y
        This class supports the use of depth. When including depth values into function calls, the depthBuffer will be checked before writing pixels
        Depth is optional, and any call where depth is not included will be force drawn, while NOT updating any depthBuffer values
    */

    public:
        
        /*   Instance variables   */
        
        // Handles the low level per-pixel drawing
        PixelDrawer pixelDrawer;

        // Handles all font drawing
        Font::FontDrawer fontDrawer;


        // Constructor
        Drawer(int width, int height);


        /*   Instance functions   */

        // Updates the width and height that PixelDrawer uses
        void updateDimensions(int width, int height);

        // Sets the buffer to the given pointer (assumes size of PIXEL_BUFFER_WIDTH * PIXEL_BUFFER_HEIGHT)
        void setBuffer(uint32* buffer);

        // Draws a straight line from (x1, y1) to (x2, y2) in the given color
        void drawLine(uint32 pixel, int x1, int y1, int x2, int y2);
        void drawLine(uint32 pixel, int x1, int y1, int x2, int y2, float depth1, float depth2, float opacity = 1.0);

        // Draws a straight line along a given axis
        void drawVerticalLine(uint32 pixel, int startY, int endY, int x);
        void drawVerticalLine(uint32 pixel, int startY, int endY, int x, float depth1, float depth2, float opacity);
        void drawHorizontalLine(uint32 pixel, int startX, int endX, int y);
        void drawHorizontalLine(uint32 pixel, int startX, int endX, int y, float depth1, float depth2, float opacity);

        // Draws a HOLLOW rectangle
        void drawRect(uint32 pixel, int x1, int y1, int x2, int y2);

        // Draws a FILLED rectangle
        void drawRectFilled(uint32 pixel, int x1, int y1, int x2, int y2);

        // Fills whole buffer with a given color
        void fillScreen(uint32 pixel);

        // Draws an elipse at a given location, with a given radius along each axis.
        void drawElipse(uint32 pixel, int locationx, int locationy, int radiusx, int radiusy);

        // Same as above, but only one radius allowed.
        void drawCircle(uint32 pixel, int x, int y, int radius);

        // Draws a FILLED triangle which uses (x1, y1), (x2, y2), and (x3, y3) as vertices
        void drawTriangle(uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3);
        void drawTriangle(uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, float depth1, float depth2, float depth3, float opacity = 1.0);

        // Same as above but uses a Tri object. This object is NOT deleted by this function call and must be handled properly. The Tri3 call includes depth.
        void drawTriangle(uint32 pixel, Geometry::Tri2* tri);
        void drawTriangle(uint32 pixel, Geometry::Tri3* tri, float opacity);

        // Draws the fps box in the top left
        void drawFps(Gui::State* state, Rendering::Display* display);

        // Draws the sky based on the camera pitch
        void drawSky(Rendering::Camera* camera, Rendering::Display* display);

        // Draws a crosshair in the center of the display
        void drawCrosshair(Rendering::Display* display);

};

}
}
