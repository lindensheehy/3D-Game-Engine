#pragma once

#include "geometry/Vec.h"


// Forward declaration
namespace Physics {
    class Object;
}


namespace Graphics {
namespace Drawing {

class PixelTracker {

    /*
        This class serves to track which Object is drawing to pixels
        This is how I let the user select objects, instead of raycasting

        Theres not a whole lot going on here, its pretty much just a data container that Drawer uses
        None of the pointers here are owned by this class
    */

    public:

        /*
            Important note: member variables 'currentObject' and 'foundObject' are effectively const
            This class will not touch their internals. They are just used as identifiers for other code
            However, they are not actually const. This is because they are identifiers for non const data
            Making them const would require casting out that const elsewhere, which is avoided for clarity and safety       
        */

        /*   Instance Variables   */

        // The Object that is being drawn
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

        // Sets 'foundObject' to 'currentObject'
        void foundWrite();


};

}
}
