/*
    --- THIS FILE IS NOT PART OF THE CURRENT BUILD ---

    This file is incomplete, but it’s here on purpose.

    It’s meant to define physics bounding shapes.
    These will be used for physics interaction handling, and will be tied to Object instances

    This code only exists to help layout the project structure.

    Leaving it here to show what was planned. Not forgotten, just deferred.
*/

#include "physics/Bounding.h"

using namespace Physics;


/* ----------------- */
/* --- Collision --- */
/* ----------------- */

bool Collision::sphereSphere(BoundingShape* sphere1, BoundingShape* sphere2) {

    if (sphere1 == nullptr) {
        logWrite("Called Collision::sphereSphere(BoundingShape*, BoundingShape*) with arg 1 as a nullptr!", true);
        return false;
    }

    if (sphere2 == nullptr) {
        logWrite("Called Collision::sphereSphere(BoundingShape*, BoundingShape*) with arg 2 as a nullptr!", true);
        return false;
    }

    BoundingSphere* castedSphere1 = (BoundingSphere*) sphere1;
    BoundingSphere* castedSphere2 = (BoundingSphere*) sphere2;

    Geometry::Vec3 distanceVec;
    distanceVec.set(castedSphere1->pos).sub(castedSphere2->pos);
    float distance = distanceVec.magnitude();
    float totalRadius = castedSphere1->radius + castedSphere2->radius;

    return distance < totalRadius;

}

bool Collision::rectRect(BoundingShape* rect1, BoundingShape* rect2) {

    return false;

}

bool Collision::rectSphere(BoundingShape* rect, BoundingShape* sphere) {

    return false;

}



/* --------------------- */
/* --- BoundingShape --- */
/* --------------------- */

BoundingShape::BoundingShape() {

    this->type = BoundType::NONE;

    return;

}

bool BoundingShape::collidesWith(BoundingShape* other) {

    logWrite("Cannot call BoundingShape::collidesWith directly, must be called from a subclass", true);

    return false;

}



/* -------------------- */
/* --- BoundingRect --- */
/* -------------------- */

BoundingRect::BoundingRect(Geometry::Vec3* start, Geometry::Vec3* end) {

    this->type = BoundType::RECTPRISM;

    this->start.set(start);
    this->end.set(end);

    return;

}

BoundingRect::BoundingRect(float x1, float y1, float z1, float x2, float y2, float z2) {

    this->type = BoundType::RECTPRISM;

    this->start.set(x1, y1, z1);
    this->end.set(x2, y2, z2);

    return;

}

bool BoundingRect::collidesWith(BoundingShape* other) {

    if (other == nullptr) {
        logWrite("Called BoundingRect::collidesWith(BoundingShape*) on nullptr!", true);
        return false;
    }

    switch (other->type) {

        case RECTPRISM:
            return Collision::rectRect(this, other);
      
        case SPHERE:
            return Collision::rectSphere(this, other);

        case NONE:
            logWrite("Cannot call BoundingRect::collidesWith(BoundingShape*) on type BoundingShape (must use a subclass type)", true);
            break;

        default:
            logWrite("Invalid BoundType found during BoundingRect::collidesWith(BoundingShape*) call (probably not initialized properly)", true);
            break;

    }

    return false;

}




/* ---------------------- */
/* --- BoundingSphere --- */
/* ---------------------- */

BoundingSphere::BoundingSphere(Geometry::Vec3* pos, float radius) {
    
    this->type = BoundType::SPHERE;

    this->pos.set(pos);
    this->radius = radius;

    return;

}

BoundingSphere::BoundingSphere(float x, float y, float z, float radius) {
    
    this->type = BoundType::SPHERE;

    this->pos.set(x, y, z);
    this->radius = radius;

    return;

}

bool BoundingSphere::collidesWith(BoundingShape* other) {

    if (other == nullptr) {
        logWrite("Called BoundingSphere::collidesWith(BoundingShape*) on nullptr!", true);
        return false;
    }

    switch (other->type) {

        case RECTPRISM:
            return Collision::rectSphere(other, this);
      
        case SPHERE:
            return Collision::sphereSphere(this, other);

        case NONE:
            logWrite("Cannot call BoundingSphere::collidesWith(BoundingShape*) on type BoundingShape (must use a subclass type)", true);
            break;

        default:
            logWrite("Invalid BoundType found during BoundingSphere::collidesWith(BoundingShape*) call (probably not initialized properly)", true);
            break;

    }

    return false;

}
