#include "../include/Bounding.h"

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

    Vec3* distanceVec = castedSphere1->pos->copy()->sub(castedSphere2->pos);
    double distance = distanceVec->magnitude();
    double totalRadius = castedSphere1->radius + castedSphere2->radius;

    delete distanceVec;

    return distance < totalRadius;

}

bool Collision::rectRect(BoundingShape* rect1, BoundingShape* rect2) {

}

bool Collision::rectSphere(BoundingShape* rect, BoundingShape* sphere) {

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

    return;

}



/* -------------------- */
/* --- BoundingRect --- */
/* -------------------- */

BoundingRect::BoundingRect(Vec3* start, Vec3* end) {

    this->type = BoundType::RECT;

    this->start = start->copy();
    this->end = end->copy();

    return;

}

BoundingRect::BoundingRect(double x1, double y1, double z1, double x2, double y2, double z2) {

    this->type = BoundType::RECT;

    this->start = new Vec3(x1, y1, z1);
    this->end = new Vec3(x2, y2, z2);

    return;

}

BoundingRect::~BoundingRect() {

    if (this->start != nullptr) delete this->start;
    if (this->end != nullptr) delete this->end;

    return;

}

bool BoundingRect::collidesWith(BoundingShape* other) {

    if (other == nullptr) {
        logWrite("Called BoundingRect::collidesWith(BoundingShape*) on nullptr!", true);
        return false;
    }

    switch (other->type) {

        case RECT:
            return Collision::rectRect(this, other);
      
        case SPHERE:
            return Collision::rectSphere(this, other);

        case NONE:
            logWrite("Cannot call BoundingRect::collidesWith(BoundingShape*) on type BoundingShape (must use a subclass type)", true);
            return false;

        default:
            logWrite("Invalid BoundType found during BoundingRect::collidesWith(BoundingShape*) call (probably not initialized properly)", true);
            return false;

    }

}




/* ---------------------- */
/* --- BoundingSphere --- */
/* ---------------------- */

BoundingSphere::BoundingSphere(Vec3* pos, double radius) {
    
    this->type = BoundType::SPHERE;

    this->pos = pos->copy();
    this->radius = radius;

    return;

}

BoundingSphere::BoundingSphere(double x, double y, double z, double radius) {
    
    this->type = BoundType::SPHERE;

    this->pos = new Vec3(x, y, z);
    this->radius = radius;

    return;

}

BoundingSphere::~BoundingSphere() {

    if (this->pos != nullptr) delete this->pos;

    return;

}

bool BoundingSphere::collidesWith(BoundingShape* other) {

    if (other == nullptr) {
        logWrite("Called BoundingSphere::collidesWith(BoundingShape*) on nullptr!", true);
        return false;
    }

    switch (other->type) {

        case RECT:
            return Collision::rectSphere(other, this);
      
        case SPHERE:
            return Collision::sphereSphere(this, other);

        case NONE:
            logWrite("Cannot call BoundingSphere::collidesWith(BoundingShape*) on type BoundingShape (must use a subclass type)", true);
            return false;

        default:
            logWrite("Invalid BoundType found during BoundingSphere::collidesWith(BoundingShape*) call (probably not initialized properly)", true);
            return false;

    }

}
