#pragma once

#include "graphics/gui/Core.h"

#include "geometry/Vec.h"
#include "geometry/Mesh.h"


namespace Graphics {
namespace Rendering {

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

        // Any values not given default to 0
        Display();
        Display(int width, int height);
        Display(int width, int height, int widthOffset, int heightOffset);


        /*   Instance functions   */

        // Deep copies other into this
        void setState(Display* other);

        // Updates this instance with new window dimensions
        void updateDimensions(int width, int height);

        // Returns the center of the display area on the given axis relative to the whole gui window
        int middleX();
        int middleY();

        // The second step of projection. 
        // This takes the fov factor from the output of a projection call, and turns it into a pixel position on the gui window.
        // The return values of this are placed into the components of the input vector. meaning the old values are overwritten
        void toDisplayPos(Geometry::Vec2* vec);

        // Same as above but supports depth in the z value. the z value is upscaled by 2^8 times in this
        void toDisplayPos(Geometry::Vec3* vec);

        // Does the above step for each vertex in a mesh
        void toDisplayPos(Geometry::Mesh* mesh);

};

}
}
