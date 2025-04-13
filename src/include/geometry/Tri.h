#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"


namespace Geometry {

class Tri2 {

    /*
        Represents a triangle in 2d space by storing 3 Vec2 pointers

        The member variables of this class are not nessecarily owned by this class
        For this reason they are not freed in a destructor, and are optionally freed by calling Tri3::freeVecs()
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


        /*   Instance functions   */

        // This is the optional destructor for this class. 
        // The Vec3 objects may not need to be freed for all instances so its handled manually
        void freeVecs();

        // Deep copy
        Tri2* copy() const;

        // Logs the Tri2 object in a readable format
        void log() const;

        // Rotates the triangle in 2d space
        void rotate(float degrees, Vec2* around = nullptr);

};



class Tri3 {

    /*
        Similar to Tri2, but for 3d. This also contains a normal vector.
        There are several other functions here becuase these are the objects used for all the Mesh objects.
    
        The member variables of this class are not nessecarily owned by this class
        For this reason they are not freed in a destructor, and are optionally freed by calling Tri3::freeVecs()
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


        /*   Instance functions   */

        // This is the optional destructor for this class. 
        // The Vec3 objects may not need to be freed for all instances so its handled manually
        void freeVecs();

        // Deep copy
        Tri3* copy() const;

        // Logs the Tri3 object in a readable format
        void log() const;

        // Uses cross product to find a normal vector for the existing verticies in the triangle.
        // New normal may be facing either direction from the triangle.
        // In the context of a Mesh, use Mesh::updateNormals for better normal prediction
        void updateNormal();

        // Returns true if the triangle should be visible assuming its only opaque on the side the normal sticks out from.
        // This just returns true when the angle between the Vec3 and the normal is >= 90
        bool isFacing(Vec3* vec) const;

        // Outputs the center of the triangle to the 'out' Vec3. This will overwrite anything existing in this vector
        void getCenter(Vec3* out) const;
        
};

}
