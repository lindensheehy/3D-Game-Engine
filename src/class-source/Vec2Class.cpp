#include "../class-headers/Vec2Class.h"


// Constructor
Vec2::Vec2(double inputX, double inputY) {
    this->x = inputX;
    this->y = inputY;
    this->magnitudeValue = 0;
    this->magnitudeUpdated = false;
}

Vec2::Vec2() {
    this->x = 0;
    this->y = 0;
    this->magnitudeValue = 0;
    this->magnitudeUpdated = false;
}

// Instance functions
Vec2* Vec2::copy() {
    return new Vec2(this->x, this->y);
}

void Vec2::log() {

    logWrite("Vec2( ");
    logWrite(this->x);
    logWrite(", ");
    logWrite(this->y);
    logWrite(" )", true);

    return;
    
}

bool Vec2::is(double x, double y) {

    return (
        this->x == x &&
        this->y == y
    );
}

bool Vec2::is(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->is(Vec2*) on a null pointer!", true);
        return false;
    }

    return (
        this->x == other->x &&
        this->y == other->y
    );
}

Vec2* Vec2::add(double x, double y) {
    this->x += x;
    this->y += y;
    this->magnitudeUpdated = false;
    return this;
}

Vec2* Vec2::add(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->add(Vec2*) on a null pointer!", true);
        return nullptr;
    }

    this->x += other->x;
    this->y += other->y;
    this->magnitudeUpdated = false;
    return this;
}

Vec2* Vec2::sub(double x, double y) {
    this->x -= x;
    this->y -= y;
    this->magnitudeUpdated = false;
    return this;
}

Vec2* Vec2::sub(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->sub(Vec2*) on a null pointer!", true);
        return nullptr;
    }

    this->x -= other->x;
    this->y -= other->y;
    this->magnitudeUpdated = false;
    return this;
}

Vec2* Vec2::scale(double factor) {
    this->x *= factor;
    this->y *= factor;
    if (this->magnitudeUpdated) this->magnitudeValue *= factor;
    return this;
}

Vec2* Vec2::inverseScale(double factor) {
    return this->scale(1 / factor);
}

Vec2* Vec2::normalise(double toMagnitude /* default value = 1.0 */) {
    double factor = toMagnitude / this->magnitude();
    return this->scale(factor);
}

double Vec2::get(int index) {
    switch (index) {
        case 0:
            return this->x;
        case 1:
            return this->y;
        default:
            return 0;
    }
}

double* Vec2::toArray() {
    double* array = new double[2];
    array[0] = this->x;
    array[1] = this->y;
    return array;
}

double Vec2::magnitude() {
    if (!this->magnitudeUpdated) {
        this->magnitudeValue = distance2(this->x, this->y);
        this->magnitudeUpdated = true;
    }
    return this->magnitudeValue;
}

double Vec2::distanceTo(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->distanceTo(Vec2*) on a null pointer!", true);
        return 0;
    }

    return distance2(this->x, this->y, other->x, other->y);

}

Vec2* Vec2::midpoint(Vec2* other) {
    
    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->midpoint(Vec2*) on a null pointer!", true);
        return nullptr;
    }

    return new Vec2(
        (this->x + other->x) / 2,
        (this->y + other->y) / 2
    );

}

double Vec2::dotProduct(Vec2* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->dotProduct(Vec2*) on a null pointer!", true);
        return 0;
    }

    return (this->x * other->x) + (this->y * other->y);

}

void Vec2::rotate(double degrees, Vec2* around /* default value = nullptr */) {
    
    // around = nullptr already addressed here, no need for error case

    if (degrees == 0) return;

    double aroundX = 0;
    double aroundY = 0;
    double relativeX = this->x;
    double relativeY = this->y;

    if (around != nullptr) {
        aroundX = around->x;
        aroundY = around->y;
        relativeX -= aroundX;
        relativeY -= aroundY;
    }

    double radians = toRadians(degrees);

    double sinValue = sin(radians);
    double cosValue = cos(radians);

    this->x = (cosValue * relativeX) - (sinValue * relativeY) + aroundX;
    this->y = (cosValue * relativeY) + (sinValue * relativeX) + aroundY;

    return;
    
}
