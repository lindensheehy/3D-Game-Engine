#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"


// Forward declare Object to avoid circular dependance
// Also the namespace is nessecary here because the actual Object exists in this namespace
namespace Physics {
    class Object;
}


namespace Graphics {
namespace Drawing {

class PixelTracker {

    /*
        This class serves to track which Object is drawing to pixels
        This is how I let the user select objects, instead of raycasting

        Theres not a whole lot going on here, its pretty much just a container that gets instantiated in Drawer
    */

    public:

        /*   Instance Variables   */

        // The Object that is active
        Physics::Object* currentObject;

        // Contains the Object that last wrote to the requested pixel
        Physics::Object* foundObject;

        // Requested pixel coordinates
        Geometry::Vec2 watchedPixel;

        // Says if the pixels are being watched or not
        bool watchingPixelWrites;

        
        // Constructor
        PixelTracker();

        
        /*   Instance Functions   */

        // Tells this object to set foundObject to SelectedObject
        void foundWrite();


};

}
}
