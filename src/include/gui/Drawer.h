#pragma once


#include "gui/Core.h"

#include "geometry/Vec.h"
#include "geometry/Tri.h"
#include "geometry/Camera.h"
#include "gui/Display.h"
#include "gui/State.h"
#include "gui/PixelTracker.h"
#include "util/LinkedList.h"


namespace Gui {

    class Drawer {

        /*
            This class acts as a function set to draw to a gui window.
            Everything here writes to a manually allocated pixel buffer, which is then passed to Windows by Gui::Window
            The pixel buffer is simply a single dimension array, and the buffer width represents the length of each 'set' within the array.
            Treating the pixel buffer as a 2d array acts as follows:
            buffer[2][3] = buffer[(2 * bufferHeight) + 3], where 2,3 is x,y
            This class supports the use of depth. When including depth values into function calls, the depthBuffer will be checked before writing pixels
            Depth is optional, and any call where depth is not included will be drawn at depth 0, while NOT updating the depthBuffer values
        */

        public:
            
            /*   Instance variables   */
            
            // This is the pixel buffer
            uint32* buffer;

            // The depth buffer stores the distance between each pixel and the camera. this allows meshes to be drawn in any order while appearing accurately.
            float* depthBuffer;

            // Buffer dimensions. the pixel and depth buffers share these
            unsigned int bufferHeight, bufferWidth;
            unsigned int bufferSize;

            // Used to track what Object drew to a certain pixel
            // This is how the user can select objects by clicking them
            PixelTracker* pixelTracker;


            // Constructors
            Drawer(Display* gui);
            Drawer(uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput);

            // Destructor
            ~Drawer();


            /*   Instance functions   */

            // Takes the bounds of the display object and applies them to this drawer
            void updateDimensions(int width, int height);

            // Sets all the values in the depth buffer to infinity
            void resetDepthBuffer();

            // Returns the 1d index cooresponding to a 2d set of indices
            int bufferIndex(int x, int y) const;

            // Returns true if the coordinate exists in the buffer
            bool inBufferRange(int x, int y) const;

            // Changes the values of the given coordinates to be within the buffer range.
            void clipCoordinates(int* x, int* y) const;

            // Writes a color to a coordinate within the buffer. Foundation for all further drawing functions.
            void writePixel(uint32 pixel, int x, int y);
            void writePixel(uint32 pixel, int x, int y, float depth);
            void writePixel(uint32 pixel, int x, int y, float depth, float opacity);

            // Draws a straight line from (x1, y1) to (x2, y2) in the given color
            void drawLine(uint32 pixel, int x1, int y1, int x2, int y2);
            void drawLine(uint32 pixel, int x1, int y1, int x2, int y2, float depth1, float depth2);
            void drawLine(uint32 pixel, int x1, int y1, int x2, int y2, float depth1, float depth2, float opacity);

            // Same as above, but uses Vec2 objects. These objects are NOT deleted by this function call and must be handled properly
            void drawLine(uint32 pixel, Vec2* from, Vec2* to);
            void drawLine(uint32 pixel, Vec2* from, Vec2* to, float depth1, float depth2);
            void drawLine(uint32 pixel, Vec2* from, Vec2* to, float depth1, float depth2, float opacity);

            // Draws a straight line along a given axis
            void drawVerticalLine(uint32 pixel, int startY, int endY, int x);
            void drawVerticalLine(uint32 pixel, int startY, int endY, int x, float depth1, float depth2);
            void drawVerticalLine(uint32 pixel, int startY, int endY, int x, float depth1, float depth2, float opacity);
            void drawHorizontalLine(uint32 pixel, int startX, int endX, int y);
            void drawHorizontalLine(uint32 pixel, int startX, int endX, int y, float depth1, float depth2);
            void drawHorizontalLine(uint32 pixel, int startX, int endX, int y, float depth1, float depth2, float opacity);

            // Draws a HOLLOW rectangle
            void drawRect(uint32 pixel, int x1, int y1, int x2, int y2);
            void drawRect(uint32 pixel, Vec2* pos1, Vec2* pos2);

            // Draws a FILLED rectangle
            void drawRectFilled(uint32 pixel, int x1, int y1, int x2, int y2);
            void drawRectFilled(uint32 pixel, Vec2* pos1, Vec2* pos2);

            // Fills whole buffer with a given color
            void fillScreen(uint32 pixel);

            // Draws an elipse at a given location, with a given radius along each axis.
            void drawElipse(uint32 pixel, int locationx, int locationy, int radiusx, int radiusy);
            void drawElipse(uint32 pixel, int locationx, int locationy, int radiusx, int radiusy, float depth);

            // Same as above, but only one radius allowed.
            void drawCircle(uint32 pixel, int x, int y, int radius);
            void drawCircle(uint32 pixel, Vec2* pos, int radius);
            void drawCircle(uint32 pixel, int x, int y, int radius, float depth);
            void drawCircle(uint32 pixel, Vec2* pos, int radius, float depth);

            // Draws a FILLED triangle which uses (x1, y1), (x2, y2), and (x3, y3) as vertices
            void drawTriangle(uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3);
            void drawTriangle(uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, float depth1, float depth2, float depth3);
            void drawTriangle(uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, float depth1, float depth2, float depth3, float opacity);

            // Same as above but uses a Tri object. This object is NOT deleted by this function call and must be handled properly. The Tri3 call includes depth.
            void drawTriangle(uint32 pixel, Tri2* tri);
            void drawTriangle(uint32 pixel, Tri3* tri);
            void drawTriangle(uint32 pixel, Tri3* tri, float opacity);

            // Draws a PNG file using a PNG object. the top left corner of the PNG will lie at (x, y)
            // NOT IMPLEMENTED YET!
            // These functions just stand from before i removed the external lib that helped parse .png files

            // void drawpng(PNG* file, int x, int y);
            // void drawpng(PNG* file, Vec2* pos);
            // void drawpng(PNG* file, int x, int y, float depth);
            // void drawpng(PNG* file, Vec2* pos, float depth);

            // Loads the character pixel arts into memory
            void initFont();

            // Draws a character to the screen, the upper left will be at (x, y)
            void drawChar(uint32 pixel, char ch, int x, int y);

            // Draws a string to the screen, the top left will be at (x, y)
            void drawString(uint32 pixel, const char* string, int x, int y);
            void drawString(uint32 pixel, const char* string, Vec2* pos);

            // Draws an integer value to the screen, the top left will be at (x, y)
            void drawInt(uint32 pixel, int num, int x, int y);

            // Draws the fps box in the top left
            void drawFps(State* state, Display* display);

            // Draws the sky based on the camera pitch
            void drawSky(Camera* camera, Display* display);

            // Draws a crosshair in the center of the display
            void drawCrosshair(Display* display);

        private:

            /*   Instance Variables   */

            // This is the actual depth buffer that the public one points to
            // This one is the max allowed size, so the public one just uses a portion of this
            // It is the same pointer, but it represents a different set of data so i seperate them for clarity
            float* fullDepthBuffer;
            
            // This is the maximum allowed index for the buffers
            const unsigned int maxBufferIndex = PIXEL_BUFFER_WIDTH * PIXEL_BUFFER_HEIGHT;


            /*   The following functions dont need to be called outside this class   */

            // Draws a set of pixels to the screen. the other draw functions rely on this
            void drawPixels(uint32 pixel, bool* pixels, int x, int y);

            // Returns a pointer to the pixels for a character
            bool* getCharRef(char ch) const;
            bool* getCharRef(int num) const;

            /*
                Character Pixel Arts
                This bool** type is a list of lists of bools.
                The primary list is length 38 for the amount of chars which can be drawn
                Each of the sub lists is length 49, which gives a 7x7 grid of pixels per char
                This list is filled by running init

                NOTE: This will be replaced with a more proper font renderer in the near future
            */

            bool** chars;

            // Here you can see the data which is used to create the bool lists
            // underscore is 0 (false) and 0 is 1 (true), the bool values coorespond to if they are shown or not when drawing
            // All the seperate strings here get put together by the compiler into one big string, so the /n chars are the seperators
            // | acts as a line end char
            // String length is: ( (7 * 8) + 1 ) * char count (40) = 2280 + nullchar -> 2281
            const int rawCharsCount = 40;
            const int rawCharsSize = 2281;
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

                // Minus / Negative sign
                "_______|"
                "_______|"
                "_______|"
                "_00000_|"
                "_______|"
                "_______|"
                "_______|"
                "\n"

                // Period / Decimal
                "_______|"
                "_______|"
                "_______|"
                "_______|"
                "__00___|"
                "__00___|"
                "_______|"
                "\n"

                // Disallowed char
                "_______|"
                "__000__|"
                "_0_0_0_|"
                "_00_00_|"
                "_0_0_0_|"
                "__000__|"
                "_______|"
                "\n"

            };

    };

}
