#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "geometry/Mesh.h"


class Display {

    /*
        This class IS NOT the same as Gui.
        Gui is used for making an actual window and drawing to it.
        This class simply defines an area within an existing window where things should be drawn.
        Think of it like a way to do split screen. you can define areas of any size and position which can act as the whole window.

        width and height are straightforward. the offsets are the distance from the top left for each.
        every length is in pixels.
    */

    public:

        // Instance variables
        int width, height;
        int widthOffset, heightOffset;


        /*   Constructors   */

        // No offset values. Sets both to 0.
        Display(int width, int height);

        // Given offset values
        Display(int width, int height, int widthOffset, int heightOffset);


        /*   Instance functions   */

        // Updates this instance with new window dimensions
        void updateDimensions(int width, int height);

        // Returns the center of the display area on the given axis relative to the whole gui window
        int middleX();
        int middleY();

        // The second step of projection. 
        // This takes the fov factor from the output of a projection call, and turns it into a pixel position on the gui window.
        // The return values of this are placed into the components of the input vector. meaning the old values are overwritten
        void toDisplayPos(Vec2* vec);

        // Same as above but supports depth in the z value. the z value is upscaled by 2^8 times in this
        void toDisplayPos(Vec3* vec);

        // Does the above step for each vertex in a mesh
        void toDisplayPos(Mesh* mesh);

};
