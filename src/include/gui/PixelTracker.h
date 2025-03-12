#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"


// Declare Object rather than including
// This is done because if I include, theres a circular dependance
// Plus this class doesnt care whats inside Object, just needs a reference
class Object;


namespace Gui {

    class PixelTracker {

        /*
            This class serves to track which Object is drawing to pixels
            This is how I let the user select objects, instead of raycasting

            Theres not a whole lot going on here, its pretty much just a container that gets instantiated in Drawer
        */

        public:

            /*   Instance Variables   */

            // The Object that is active
            Object* currentObject;

            // Contains the Object that last wrote to the requested pixel
            Object* foundObject;

            // Requested pixel coordinates
            Vec2* watchedPixel;

            // Says if the pixels are being watched or not
            bool watchingPixelWrites;

            
            // Constructor
            PixelTracker();

            // Destructor
            ~PixelTracker();

            
            /*   Instance Functions   */

            // Tells this object to set foundObject to SelectedObject
            void foundWrite();


    };

}
