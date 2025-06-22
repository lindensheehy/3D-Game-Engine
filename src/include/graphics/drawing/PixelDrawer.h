#pragma once

#include "util/Utility.h"

#include "graphics/drawing/PixelTracker.h"

#include "graphics/gui/Core.h"


namespace Graphics {
namespace Drawing {
    
class PixelDrawer {

    /*
        This class is the heart of the drawing system
        This handles per-pixel drawing, and abstracts all the low level handling
        Depth based drawing is also handled at this level

        The pixel buffer is owned by Gui::Window, because its needed outside of drawing
        The depth buffer is owned by this class, because its inherently tied to drawing
    */

    public:

        /*   Instance variables   */
        
        // This is the pixel buffer
        uint32* buffer;

        // The depth buffer stores the distance between each pixel and the camera
        // This allows textures to be correctly ordered with respect to their distance from the camera
        float* depthBuffer;

        // Buffer dimensions. the pixel and depth buffers share these
        // The real buffers are much bigger (see graphics/gui/Core.h), but these dimensions are based on the window size
        unsigned int bufferHeight, bufferWidth;
        unsigned int bufferSize;

        // Used to track what Object drew to a certain pixel
        // This is how the user can select objects by clicking them
        PixelTracker pixelTracker;


        // Constructor
        PixelDrawer(int width, int height);

        // Destructor
        ~PixelDrawer();


        /*   Instance Functions   */

        // This updates how the pixel and depth buffers are indexed. Must be called on window resize for accurate drawing
        // 'width' and 'height' should not exceed Gui::PIXEL_BUFFER_WIDTH and Gui::PIXEL_BUFFER_HEIGHT respectively
        void updateDimensions(int width, int height);

        // Sets all the values in the depth buffer to infinity ('inf' from Math.h)
        void resetDepthBuffer();

        // Returns the 1d index cooresponding to a 2d set of indices
        int bufferIndex(int x, int y) const;

        // Returns true if the coordinate exists in the buffer
        bool inBufferRange(int x, int y) const;

        // Changes the values of the given coordinates to be within the buffer range.
        void clipCoordinates(int* x, int* y) const;


        /*
            Drawing can be done with or without depth
            When rendering with depth, an opacity value can also be given
            When drawing with sub 1.0 opacity, the pixel will be alpha blended with the pixel behind it
        */

        // Sets the pixel at the given coordinates to the uint32 value given
        void drawPixel(uint32 pixel, int x, int y);

        // Sets the pixel at the given coordinates to the uint32 value given
        // Also checks against the depth buffer, with optional opacity for alpha blending
        // Any non-opaque pixels will not update the depth buffer with their depth
        void drawPixel(uint32 pixel, int x, int y, float depth, float opacity = 1.0);

    private:

        // This is the maximum allowed index for the buffers
        static constexpr unsigned int maxBufferSize = Gui::PIXEL_BUFFER_WIDTH * Gui::PIXEL_BUFFER_HEIGHT;

};

}
}
