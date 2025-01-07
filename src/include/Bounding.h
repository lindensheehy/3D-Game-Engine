#pragma once

#include "Log.h"
#include "Vec.h"

// Early declaration for Collision namespace
class BoundingShape;

enum BoundType {
    RECT,
    SPHERE,
    NONE
};

namespace Collision {

    // Handles Sphere on Sphere collision
    bool sphereSphere(BoundingShape* sphere1, BoundingShape* sphere2);

    // Handles Rect on Rect collision
    bool rectRect(BoundingShape* rect1, BoundingShape* rect2);

    // Handles Rect on Sphere collision
    bool rectSphere(BoundingShape* rect, BoundingShape* sphere);

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

        Vec3* start;
        Vec3* end;


        // Constructor
        BoundingRect(Vec3* start, Vec3* end);
        BoundingRect(double x1, double y1, double z1, double x2, double y2, double z2);

        // Destructor
        ~BoundingRect() override;

        /*   Instance Functions   */

        bool collidesWith(BoundingShape* other) override;

};

class BoundingSphere : public BoundingShape {

    public:

        /*   Instance Variables   */

        Vec3* pos;
        double radius;


        // Constructor
        BoundingSphere(Vec3* pos, double radius);
        BoundingSphere(double x, double y, double z, double radius);

        // Destructor
        ~BoundingSphere() override;

        /*   Instance Functions   */

        bool collidesWith(BoundingShape* other) override;

};
