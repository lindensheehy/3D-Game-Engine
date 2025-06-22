#include "geometry/Tri.h"

using namespace Geometry;


/* ------------ */
/* --- Tri2 --- */
/* ------------ */

Tri2::Tri2(bool nullPointers /* default value = false */) {

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
    
    return;

}

void Tri2::freeVecs() {

    delete this->v1;
    delete this->v2;
    delete this->v3;

    return;

}

Tri2* Tri2::copy() const {

    Tri2* ret = new Tri2();

    ret->v1->set(this->v1);
    ret->v2->set(this->v2);
    ret->v3->set(this->v3);

    return ret;
    
}

void Tri2::log() const {

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

void Tri2::rotate(float degrees, Vec2* around) {

    this->v1->rotate(degrees, around);
    this->v2->rotate(degrees, around);
    this->v3->rotate(degrees, around);

    return;

}



/* ------------ */
/* --- Tri3 --- */
/* ------------ */

Tri3::Tri3(bool nullPointers /* default value = false */) {

    if (nullPointers) {
        this->v1 = nullptr;
        this->v2 = nullptr;
        this->v2 = nullptr;
        this->normal = nullptr;
    }

    else {
        this->v1 = new Vec3(0, 0, 0);
        this->v2 = new Vec3(0, 0, 0);
        this->v3 = new Vec3(0, 0, 0);
        this->normal = new Vec3(0, 0, 0);
    }

    return;

}

void Tri3::freeVecs() {

    delete this->v1;
    delete this->v2;
    delete this->v3;
    delete this->normal;

    return;

}

Tri3* Tri3::copy() const {

    Tri3* newCopy = new Tri3();

    newCopy->v1->set(this->v1);
    newCopy->v2->set(this->v2);
    newCopy->v3->set(this->v3);
    newCopy->normal->set(this->normal);

    return newCopy;

}

void Tri3::log() const {

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

void Tri3::updateNormal() {

    if (this->normal == nullptr) {
        logWrite("Tri3::updateNormal() wants to set the normal value, but normal is nullptr!", true);
        return;
    }

    Vec3 vec1to2;
    Vec3 vec1to3;
    Vec3 newNormal;

    vec1to2.set(this->v1).sub(this->v2);
    vec1to3.set(this->v1).sub(this->v3);

    vec1to2.crossProduct( &(vec1to3), this->normal );
    this->normal->normalize();

    return;

}

bool Tri3::isFacing(Vec3* vec) const {

    if (vec == nullptr) {
        logWrite("Called Tri3::isFacing(Vec3*) on a null pointer!", true);
        return false;
    }

    return ( vec->getAngle(this->normal) >= 90 );

}

void Tri3::getCenter(Vec3* out) const {

    if (out == nullptr) {
        logWrite("Called Tri3::getCenter(Vec3*) on a null pointer!", true);
        out->set(0, 0, 0);
        return;
    }

    // Average all 3 components
    float x = (this->v1->x + this->v2->x + this->v3->x) / 3.0f;
    float y = (this->v1->y + this->v2->y + this->v3->y) / 3.0f;
    float z = (this->v1->z + this->v2->z + this->v3->z) / 3.0f;
    
    out->set(x, y, z);

    return;
    
}
