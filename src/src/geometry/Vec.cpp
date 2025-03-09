#include "geometry/Vec.h"


/* ------------ */
/* --- Vec2 --- */
/* ------------ */

// Constructor
Vec2::Vec2(float inputX, float inputY) {
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
Vec2* Vec2::copy() const {
    return new Vec2(this->x, this->y);
}

void Vec2::log() const {

    logWrite("Vec2( ");
    logWrite(this->x);
    logWrite(", ");
    logWrite(this->y);
    logWrite(" )");

    return;
    
}

Vec2* Vec2::set(Vec2* other) {

    if (other == nullptr) {
        logWrite("Called Vec2->set(Vec2*) on a null pointer!", true);
        return this;
    }

    this->x = other->x;
    this->y = other->y;
    return this;

}

Vec2* Vec2::set(float x, float y) {

    this->x = x;
    this->y = y;
    return this;

}

bool Vec2::is(float x, float y) const {

    return (
        this->x == x &&
        this->y == y
    );
}

bool Vec2::is(Vec2* other) const {

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

Vec2* Vec2::add(float x, float y) {
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

Vec2* Vec2::sub(float x, float y) {
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

Vec2* Vec2::scale(float factor) {
    this->x *= factor;
    this->y *= factor;
    if (this->magnitudeUpdated) this->magnitudeValue *= factor;
    return this;
}

Vec2* Vec2::inverseScale(float factor) {
    return this->scale(1 / factor);
}

Vec2* Vec2::normalise(float toMagnitude /* default value = 1.0 */) {
    float factor = toMagnitude / this->magnitude();
    return this->scale(factor);
}

float Vec2::get(int index) const {
    switch (index) {
        case 0:
            return this->x;
        case 1:
            return this->y;
        default:
            return 0;
    }
}

float* Vec2::toArray() const {
    float* array = new float[2];
    array[0] = this->x;
    array[1] = this->y;
    return array;
}

float Vec2::magnitude() {
    if (!this->magnitudeUpdated) {
        this->magnitudeValue = distance2(this->x, this->y);
        this->magnitudeUpdated = true;
    }
    return this->magnitudeValue;
}

float Vec2::distanceTo(Vec2* other) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->distanceTo(Vec2*) on a null pointer!", true);
        return 0;
    }

    return distance2(this->x, this->y, other->x, other->y);

}

Vec2* Vec2::midpoint(Vec2* other) const {
    
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

float Vec2::dotProduct(Vec2* other) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec2->dotProduct(Vec2*) on a null pointer!", true);
        return 0;
    }

    return (this->x * other->x) + (this->y * other->y);

}

void Vec2::rotate(float degrees, Vec2* around /* default value = nullptr */) {
    
    // around = nullptr already addressed here, no need for error case

    if (degrees == 0) return;

    float aroundX = 0;
    float aroundY = 0;
    float relativeX = this->x;
    float relativeY = this->y;

    if (around != nullptr) {
        aroundX = around->x;
        aroundY = around->y;
        relativeX -= aroundX;
        relativeY -= aroundY;
    }

    float radians = toRadians(degrees);

    float sinValue = sin(radians);
    float cosValue = cos(radians);

    this->x = (cosValue * relativeX) - (sinValue * relativeY) + aroundX;
    this->y = (cosValue * relativeY) + (sinValue * relativeX) + aroundY;

    return;
    
}



/* ------------ */
/* --- Vec3 --- */
/* ------------ */

// Constructors
Vec3::Vec3(float inputX, float inputY, float inputZ) {
    this->x = inputX;
    this->y = inputY;
    this->z = inputZ;
    this->magnitudeValue = 0;
    this->magnitudeUpdated = false;
}

Vec3::Vec3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->magnitudeValue = 0;
    this->magnitudeUpdated = false;
}

// Instance functions
Vec3* Vec3::copy() const {
    return new Vec3(this->x, this->y, this->z);
}

void Vec3::log() const {

    logWrite("Vec3( ");
    logWrite(this->x);
    logWrite(", ");
    logWrite(this->y);
    logWrite(", ");
    logWrite(this->z);
    logWrite(" )");

    return;
    
}

Vec3* Vec3::set(Vec3* other) {

    if (other == nullptr) {
        logWrite("Called Vec3->set(Vec3*) on a null pointer!", true);
        return this;
    }

    this->x = other->x;
    this->y = other->y;
    this->z = other->z;
    return this;

}

Vec3* Vec3::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    return this;
}

bool Vec3::is(Vec3* other) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->is(Vec3*) on a null pointer!", true);
        return false;
    }

    return (
        this->x == other->x &&
        this->y == other->y &&
        this->z == other->z
    );
}

bool Vec3::is(float x, float y, float z) const {

    return (
        this->x == x &&
        this->y == y &&
        this->z == z
    );

}

Vec3* Vec3::add(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->add(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    this->x += other->x;
    this->y += other->y;
    this->z += other->z;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::add(float dx, float dy, float dz) {
    this->x += dx;
    this->y += dy;
    this->z += dz;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::sub(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->sub(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    this->x -= other->x;
    this->y -= other->y;
    this->z -= other->z;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::sub(float dx, float dy, float dz) {
    this->x -= dx;
    this->y -= dy;
    this->z -= dz;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::scale(float factor) {
    this->x *= factor;
    this->y *= factor;
    this->z *= factor;
    if (this->magnitudeUpdated) this->magnitudeValue *= factor;
    return this;
}

Vec3* Vec3::scale(float fx, float fy, float fz) {
    this->x *= fx;
    this->y *= fy;
    this->z *= fz;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::inverseScale(float factor) {
    return this->scale(1 / factor);
}

Vec3* Vec3::normalise(float toMagnitude /* default value = 1.0 */) {
    float factor = toMagnitude / this->magnitude();
    return this->scale(factor);
}

float Vec3::get(int index) const {
    switch (index) {
        case 0:
            return this->x;
        case 1:
            return this->y;
        case 2:
            return this->z;
        default:
            return 0;
    }
}

float* Vec3::toArray() const {
    float* array = new float[3];
    array[0] = this->x;
    array[1] = this->y;
    array[2] = this->z;
    return array;
}

float Vec3::magnitude() {

    if (!this->magnitudeUpdated) {
        this->magnitudeValue = distance3(this->x, this->y, this->z);
        this->magnitudeUpdated = true;
    }
    
    return this->magnitudeValue;

}

float Vec3::distanceTo(Vec3* other) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->distanceTo(Vec3*) on a null pointer!", true);
        return 0;
    }

    return distance3(this->x, this->y, this->z, other->x, other->y, other->z);

}

Vec3* Vec3::midpoint(Vec3* other) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->midpoint(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    return new Vec3(
        (this->x + other->x) / 2,
        (this->y + other->y) / 2,
        (this->z + other->z) / 2
    );
}

float Vec3::dotProduct(Vec3* other) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->dotProduct(Vec3*) on a null pointer!", true);
        return 0;
    }

    return (this->x * other->x) + (this->y * other->y) + (this->z * other->z);
}

Vec3* Vec3::crossProduct(Vec3* other) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->crossProduct(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    float x = (this->y * other->z) - (this->z * other->y);
    float y = (this->z * other->x) - (this->x * other->z);
    float z = (this->x * other->y) - (this->y * other->x);
    return new Vec3(x, y, z);
}

float Vec3::getAngle(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->getAngle(Vec3*) on a null pointer!", true);
        return 0;
    }

    float dotProduct = this->dotProduct(other);
    float magnitudeFactor = this->magnitude() * other->magnitude();
    float ratio = dotProduct / magnitudeFactor;

    // These cases shouldnt happen but floating point errors can cause them
    if (ratio < -1) return 180;
    if (ratio > 1)  return 0;

    float radians = arccos(ratio);
    
    return toDegrees(radians);
}

void Vec3::rotate(float yaw, float pitch, float roll, Vec3* around /* default value = nullptr */) {

    // around = nullptr already addressed here, no need for error case

    if (yaw == 0 && pitch == 0 && roll == 0) return;

    float aroundX = 0;
    float aroundY = 0;
    float aroundZ = 0;
    float relativeX = this->x;
    float relativeY = this->y;
    float relativeZ = this->z;

    if (around != nullptr) {
        aroundX = around->x;
        aroundY = around->y;
        aroundZ = around->z;
        relativeX -= aroundX;
        relativeY -= aroundY;
        relativeZ -= aroundZ;
    }

    float radians;

    if (yaw != 0) {
        
        radians = toRadians(yaw);

        float sinValue = sin(radians);
        float cosValue = cos(radians);

        this->x = (cosValue * relativeX) - (sinValue * relativeZ) + aroundX;
        this->z = (cosValue * relativeZ) + (sinValue * relativeX) + aroundZ;

    }

    // Reset relative values
    relativeX = this->x - aroundX;
    relativeZ = this->z - aroundZ;

    if (pitch != 0) {

        radians = toRadians(pitch);

        float sinValue = sin(radians);
        float cosValue = cos(radians);

        this->y = (cosValue * relativeY) - (sinValue * relativeZ) + aroundY;
        this->z = (cosValue * relativeZ) + (sinValue * relativeY) + aroundZ;

    }

    // Reset relative values
    relativeY = this->y - aroundY;
    relativeZ = this->z - aroundZ;

    if (roll != 0) {

        radians = toRadians(roll);

        float sinValue = sin(radians);
        float cosValue = cos(radians);

        this->y = (cosValue * relativeY) - (sinValue * relativeX) + aroundY;
        this->x = (cosValue * relativeX) + (sinValue * relativeY) + aroundX;

    }

    return;
}

void Vec3::project() {

    /*
        Find a 2d coordinate coorsponding to a 3d point.
        depth (length of the vector, which represents distance from camera in drawing) goes in the z component
    */

    // Constant. Is currently proportional to display size
    float focalLengthX = 0.6;
    float focalLengthY = 1;

    // If the point is behind the camera
    if (this->z < 0) {
        this->x = -1;
        this->y = -1;
        this->z = inf;
        return;
    }

    float depth = this->magnitude();

    this->x = (this->x * focalLengthX) / this->z;
    this->y = (this->y * focalLengthY) / this->z;

    // adjust so its relative to the top left rather than middle
    this->x += 0.5;
    this->y += 0.5;

    this->z = depth;

    return;

}
