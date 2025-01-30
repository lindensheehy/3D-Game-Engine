#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"


class Tri2 {

    /*
        Represents a triangle in 2d space.
        Holds 3 Vec2 objects, and has setters.
        This also includes a depth value for each vertex which is optional. 
        Depth is used to hold distance between the 3d vertex and the camera from projection.
    */

    public:

        // Instance variables
        Vec2* v1;
        Vec2* v2;
        Vec2* v3;

        float depth1;
        float depth2;
        float depth3;


        /*   Constructor   */

        // nullPointers determines if the instance variables should be initialized or not.
        // When this is false, all v1, v2, and v3 are set to individual copies of (0, 0)
        Tri2(bool nullPointers = false);


        // Destructor
        ~Tri2();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Tri2* copy() const;

        void log() const;

        // Setters for each vertex. Allowing float or Vec2 inputs
        // The ones which take a Vec2 object will delete the current instance variable, then point to the one given.
        // That means the Vec2 given, should NOT be changed after running this, unless changing the triangle is intended.
        void setv1(float x, float y, float z);
        void setv1(Vec2* vec);

        void setv2(float x, float y, float z);
        void setv2(Vec2* vec);

        void setv3(float x, float y, float z);
        void setv3(Vec2* vec);

        void rotate(float degrees, Vec2* around = nullptr);

};



class Tri3 {

    /*
        Similar to Tri2, but for 3d. This also contains a normal vector.
        There are several other functions here becuase these are the objects used for all the Mesh objects.
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
        Tri3* copy() const;

        void log() const;

        // Setters for each vertex, and the normal. Allowing float or Vec3 inputs
        // The ones which take a Vec3 object will delete the current instance variable, then point to the one given.
        // That means the Vec3 given, should NOT be changed after running this, unless also changing the triangle is intended.
        void setv1(float x, float y, float z);
        void setv1(Vec3* vec);

        void setv2(float x, float y, float z);
        void setv2(Vec3* vec);

        void setv3(float x, float y, float z);
        void setv3(Vec3* vec);

        void setNormal(float x, float y, float z);
        void setNormal(Vec3* normal);

        // Uses cross product to find a normal vector for the existing verticies in the triangle.
        // New normal may be facing either direction from the triangle.
        void updateNormal();

        // Returns true if the triangle should be visible assuming its only opaque on the side the normal sticks out from.
        // This just returns true when the angle between the Vec3 and the normal is >= 90
        bool isFacing(Vec3* vec) const;

        // Returns a Vec3 object defining the center of the triangle. takes the average of each component. This returns a NEW object
        Vec3* getCenter() const;
        
};
