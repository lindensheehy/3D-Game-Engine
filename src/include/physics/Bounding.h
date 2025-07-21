/*
    --- THIS FILE IS NOT PART OF THE CURRENT BUILD ---

    This file is incomplete, but it’s here on purpose.

    It’s meant to define physics bounding shapes.
    These will be used for physics interaction handling, and will be tied to Object instances

    This code only exists to help layout the project structure.

    Leaving it here to show what was planned. Not forgotten, just deferred.
*/

#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"


namespace Physics {

// Early declaration for Collision namespace
class BoundingShape;

namespace Collision {

    /*
        These functions contain the core collision logic
        The 'collidesWith' overrides dynamically dispatch to these
    */

    // Handles Sphere on Sphere collision
    bool sphereSphere(BoundingShape* sphere1, BoundingShape* sphere2);

    // Handles Rect on Rect collision
    bool rectRect(BoundingShape* rect1, BoundingShape* rect2);

    // Handles Rect on Sphere collision
    bool rectSphere(BoundingShape* rect, BoundingShape* sphere);

};

enum BoundType {
    RECTPRISM,
    SPHERE,
    NONE
};

class BoundingShape {

    public:

        /*   Instance Variables   */

        BoundType type;


        // Constructor
        BoundingShape();

        // Destructor
        virtual ~BoundingShape() {}


        /*   Instance Functions   */

        virtual bool collidesWith(BoundingShape* other);

};

class BoundingRect : public BoundingShape {

    public:

        /*   Instance Variables   */

        Geometry::Vec3 start;
        Geometry::Vec3 end;


        // Constructors
        BoundingRect(Geometry::Vec3* start, Geometry::Vec3* end);
        BoundingRect(float x1, float y1, float z1, float x2, float y2, float z2);


        /*   Instance Functions   */

        bool collidesWith(BoundingShape* other) override;

};

class BoundingSphere : public BoundingShape {

    public:

        /*   Instance Variables   */

        Geometry::Vec3 pos;
        float radius;


        // Constructor
        BoundingSphere(Geometry::Vec3* pos, float radius);
        BoundingSphere(float x, float y, float z, float radius);


        /*   Instance Functions   */

        bool collidesWith(BoundingShape* other) override;

};

}
