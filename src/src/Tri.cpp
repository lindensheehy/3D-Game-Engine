#include "../include/Tri.h"


/* ------------ */
/* --- Tri2 --- */
/* ------------ */

// Constructor
Tri2::Tri2(bool nullPointers /* default value = false */) {
    /*
        Stores a set of 3 vectors
        nullPointers flag allows the pointers to be manually set instead of autocreating objects
    */

    if (nullPointers) {
        this->v1 = nullptr;
        this->v2 = nullptr;
        this->v3 = nullptr;
    }

    else {
        this->v1 = new Vec2(0, 0);
        this->v2 = new Vec2(0, 0);
        this->v3 = new Vec2(0, 0);
    }
}

Tri2::~Tri2() {
    delete this->v1;
    delete this->v2;
    delete this->v3;
}

// Instance functions
Tri2* Tri2::copy() {

    Tri2* ret = new Tri2(true);

    Vec2* v1 = this->v1->copy();
    Vec2* v2 = this->v2->copy();
    Vec2* v3 = this->v3->copy();

    ret->setv1(v1);
    ret->setv2(v2);
    ret->setv3(v3);

    return ret;
    
}

void Tri2::log() {

    logWrite("Tri2(", true);
    logWrite("  ");

    if (this->v1 == nullptr)
        logWrite("null", true);
    else
        this->v1->log();

    logWrite("  ");

    if (this->v2 == nullptr)
        logWrite("null", true);
    else
        this->v2->log();

    logWrite("  ");

    if (this->v3 == nullptr)
        logWrite("null", true);
    else
        this->v3->log();

    logWrite(")", true);

    return;

}

void Tri2::setv1(double x, double y, double z) {
    this->v1->x = x;
    this->v1->y = y;
}

void Tri2::setv1(Vec2* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri2->setv1(Vec2*) on a null pointer!", true);
        return;
    }

    if (this->v1 != nullptr) delete this->v1;
    this->v1 = vec->copy();
}

void Tri2::setv2(double x, double y, double z) {
    this->v2->x = x;
    this->v2->y = y;
}

void Tri2::setv2(Vec2* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri2->setv2(Vec2*) on a null pointer!", true);
        return;
    }

    if (this->v2 != nullptr) delete this->v2;
    this->v2 = vec->copy();
}

void Tri2::setv3(double x, double y, double z) {
    this->v3->x = x;
    this->v3->y = y;
}

void Tri2::setv3(Vec2* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri2->setv3(Vec2*) on a null pointer!", true);
        return;
    }

    if (this->v3 != nullptr) delete this->v3;
    this->v3 = vec->copy();
}



/* ------------ */
/* --- Tri3 --- */
/* ------------ */

// Constructor
Tri3::Tri3(bool nullPointers /* default value = false */) {
    /*
        Stores a set of 3 vectors as well as their normal, the normal can be updated using the instance function but this may be facing the wrong way
        nullPointers flag allows the pointers to be manually set instead of autocreating objects
    */

    if (nullPointers) {
        this->v1 = nullptr;
        this->v2 = nullptr;
        this->v2 = nullptr;
        this->normal = nullptr;
        return;
    }

    else {
        this->v1 = new Vec3(0, 0, 0);
        this->v2 = new Vec3(0, 0, 0);
        this->v3 = new Vec3(0, 0, 0);
        this->normal = new Vec3(0, 0, 0);
        return;
    }

}

Tri3::~Tri3() {
    delete this->v1;
    delete this->v2;
    delete this->v3;
    delete this->normal;
}

// Instance functions
Tri3* Tri3::copy() {
    Tri3* newCopy = new Tri3(true);
    newCopy->v1 = this->v1->copy();
    newCopy->v2 = this->v2->copy();
    newCopy->v3 = this->v3->copy();
    newCopy->normal = this->normal->copy();
    return newCopy;
}

void Tri3::log() {

    logWrite("Tri3(", true);
    logWrite("  ");

    if (this->v1 == nullptr)
        logWrite("null", true);
    else
        this->v1->log();

    logWrite("  ");

    if (this->v2 == nullptr)
        logWrite("null", true);
    else
        this->v2->log();

    logWrite("  ");

    if (this->v3 == nullptr)
        logWrite("null", true);
    else
        this->v3->log();

    logWrite(")", true);

    return;

}

void Tri3::setv1(double x, double y, double z) {
    this->v1->x = x;
    this->v1->y = y;
    this->v1->z = z;
}

void Tri3::setv1(Vec3* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri3->setv1(Vec3*) on a null pointer!", true);
        return;
    }

    if (this->v1 != nullptr) delete this->v1;
    this->v1 = vec->copy();
}

void Tri3::setv2(double x, double y, double z) {
    this->v2->x = x;
    this->v2->y = y;
    this->v2->z = z;
}

void Tri3::setv2(Vec3* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri3->setv2(Vec3*) on a null pointer!", true);
        return;
    }

    if (this->v2 != nullptr) delete this->v2;
    this->v2 = vec->copy();
}

void Tri3::setv3(double x, double y, double z) {
    this->v3->x = x;
    this->v3->y = y;
    this->v3->z = z;
}

void Tri3::setv3(Vec3* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri3->setv3(Vec3*) on a null pointer!", true);
        return;
    }

    if (this->v3 != nullptr) delete this->v3;
    this->v3 = vec->copy();
}

void Tri3::setNormal(double x, double y, double z) {
    this->normal->x = x;
    this->normal->y = y;
    this->normal->z = z;
}

void Tri3::setNormal(Vec3* normal) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (normal == nullptr) {
        logWrite("Called Tri3->setNormal(Vec3*) on a null pointer!", true);
        return;
    }

    delete this->normal;
    this->normal = normal->copy();
}

void Tri3::updateNormal() {

    Vec3* vec1to2 = this->v1->copy()->sub(this->v2);
    Vec3* vec1to3 = this->v1->copy()->sub(this->v3);

    Vec3* newNormal = vec1to2->crossProduct(vec1to3);
    newNormal->normalise();
    
    if (this->normal != nullptr) delete this->normal;
    delete vec1to2, vec1to3;

    this->normal = newNormal;

    return;

}

bool Tri3::isFacing(Vec3* vec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Tri3->isFacing(Vec3*) on a null pointer!", true);
        return false;
    }

    return vec->getAngle(this->normal) >= 90;
}

Vec3* Tri3::getCenter() {

    // Average all 3 components
    double x = this->v1->x + this->v2->x + this->v3->x;
    double y = this->v1->y + this->v2->y + this->v3->y;
    double z = this->v1->z + this->v2->z + this->v3->z;
    x /= 3; y /= 3; z /= 3;

    return new Vec3(x, y, z);
    
}
