#include "../class-headers/Tri2Class.h"


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
