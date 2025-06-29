#pragma once

#include "util/Utility.h"
#include "util/Log.h"
#include "geometry/Vec.h"


namespace Graphics {
namespace Rendering {

class Display {

    /*
        This class IS NOT directly related to window handling (see gui/Window.h for that).
        This class simply defines an area within an existing window where things should be drawn.
        You can define areas of any size and position which can act as the whole window.

        The 'Offset' values are the distances from the top left of the screen along each axis.
        All values are in pixels.
    */

    public:

        /*   Instance Variables   */

        int width, height;
        int widthOffset, heightOffset;


        // Constructor
        Display(int width, int height, int widthOffset = 0, int heightOffset = 0);


        /*   Instance Functions   */

        // Basically a 'set all' function
        void setState(const Display* other);

        // Updates this instance with new window dimensions. Should be called on window resize
        void updateDimensions(int width, int height);

        // Returns the center of the display rect on the given axis relative to the whole gui window
        int middleX() const;
        int middleY() const;

        // This converts FOV normalized values into pixel positions, overwriting the old values
        // This only affects the x and y components. z is left untouched
        void toDisplayPos(Geometry::Vec3* out) const;

};

}
}
