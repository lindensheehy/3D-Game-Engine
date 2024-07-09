#pragma once

#include "Vec3Class.h"

// For logging error cases
#include "../log/log.h"


class Tri3 {

    /*
        Similar to Tri2, but for 3d. This also contains a normal vector.
        There are several other functions here becuase these are the objects used for all program physics items items.
    */

    public:

        // Instance variables
        Vec3* v1;
        Vec3* v2;
        Vec3* v3;
        Vec3* normal;


        /*   Constructor   */

        // nullPointers determines if the instance variables should be initialized or not.
        // When this is false, all v1, v2, v3, and normal are set to individual copies of (0, 0, 0)
        Tri3(bool nullPointers = false);


        // Destructor
        ~Tri3();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Tri3* copy();

        // Setters for each vertex, and the normal. Allowing double or Vec3 inputs
        // The ones which take a Vec3 object will delete the current instance variable, then point to the one given.
        // That means the Vec3 given, should NOT be changed after running this, unless also changing the triangle is intended.
        void setv1(double x, double y, double z);
        void setv1(Vec3* vec);

        void setv2(double x, double y, double z);
        void setv2(Vec3* vec);

        void setv3(double x, double y, double z);
        void setv3(Vec3* vec);

        void setNormal(double x, double y, double z);
        void setNormal(Vec3* normal);

        // Uses cross product to find a normal vector for the existing verticies in the triangle.
        // New normal may be facing either direction from the triangle.
        void updateNormal();

        // Returns true if the triangle should be visible assuming its only opaque on the side the normal sticks out from.
        // This just returns true when the angle between the Vec3 and the normal is >= 90
        bool isFacing(Vec3* vec);

        // Returns a Vec3 object defining the center of the triangle. takes the average of each component.
        Vec3* getCenter();
        
};
