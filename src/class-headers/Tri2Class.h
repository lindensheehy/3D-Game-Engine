#pragma once

#include "Vec2Class.h"

class Tri2 {

    /*
        Represents a triangle in 2d space.
        Simply holds 3 Vec2 objects, and has setters.
        Theres really not all that much to do in 2d.
    */

    public:

        // Instance variables
        Vec2* v1;
        Vec2* v2;
        Vec2* v3;


        /*   Constructor   */

        // nullPointers determines if the instance variables should be initialized or not.
        // When this is false, all v1, v2, and v3 are set to individual copies of (0, 0)
        Tri2(bool nullPointers = false);


        // Destructor
        ~Tri2();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Tri2* copy();

        // Setters for each vertex. Allowing double or Vec2 inputs
        void setv1(double x, double y, double z);
        void setv1(Vec2* vec);

        void setv2(double x, double y, double z);
        void setv2(Vec2* vec);

        void setv3(double x, double y, double z);
        void setv3(Vec2* vec);

};
