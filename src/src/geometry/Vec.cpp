#include "geometry/Vec.h"

using namespace Geometry;


/* ------------ */
/* --- Vec2 --- */
/* ------------ */

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

bool Vec2::is(float x, float y) const {

    return (
        this->x == x &&
        this->y == y
    );

}

bool Vec2::is(const Vec2& other) const {
    
    return (
        this->x == other.x &&
        this->y == other.y
    );

}

bool Vec2::is(const Vec2* other) const {

    if (other == nullptr) {
        logWrite("Called Vec2->is(Vec2*) on a null pointer!", true);
        return false;
    }

    return (
        this->x == other->x &&
        this->y == other->y
    );

}

Vec2& Vec2::set(float x, float y) {

    this->x = x;
    this->y = y;

    return *(this);

}

Vec2& Vec2::set(const Vec2& other) {

    this->x = other.x;
    this->y = other.y;

    return *(this);

}

Vec2& Vec2::set(const Vec2* other) {

    if (other == nullptr) {
        logWrite("Called Vec2->set(Vec2*) on a null pointer!", true);
        return *(this);
    }

    this->x = other->x;
    this->y = other->y;

    return *(this);

}

Vec2& Vec2::add(float x, float y) {

    this->x += x;
    this->y += y;

    return *(this);

}

Vec2& Vec2::add(const Vec2& other) {

    this->x += other.x;
    this->y += other.y;

    return *(this);

}

Vec2& Vec2::add(const Vec2* other) {

    if (other == nullptr) {
        logWrite("Called Vec2->add(Vec2*) on a null pointer!", true);
        return *(this);
    }

    this->x += other->x;
    this->y += other->y;

    return *(this);

}

Vec2& Vec2::sub(float x, float y) {

    this->x -= x;
    this->y -= y;

    return *(this);

}

Vec2& Vec2::sub(const Vec2& other) {

    this->x -= other.x;
    this->y -= other.y;

    return *(this);

}

Vec2& Vec2::sub(const Vec2* other) {

    if (other == nullptr) {
        logWrite("Called Vec2->sub(Vec2*) on a null pointer!", true);
        return *(this);
    }

    this->x -= other->x;
    this->y -= other->y;

    return *(this);

}

Vec2& Vec2::scale(float factor) {

    this->x *= factor;
    this->y *= factor;

    return *(this);
}

Vec2& Vec2::inverseScale(float factor) {
    
    this->x /= factor;
    this->y /= factor;

    return *(this);

}

Vec2& Vec2::normalize(float toMagnitude /* default value = 1.0 */) {
    float factor = toMagnitude / this->magnitude();
    return this->scale(factor);
}

float Vec2::magnitude() {
    return distance2(this->x, this->y);
}

float Vec2::distanceTo(float x, float y) const {

    return distance2(
        this->x, this->y, 
        x, y
    );

}

float Vec2::distanceTo(const Vec2& other) const {

    return distance2(
        this->x, this->y, 
        other.x, other.y
    );

}

float Vec2::distanceTo(const Vec2* other) const {

    if (other == nullptr) {
        logWrite("Called Vec2->distanceTo(Vec2*) on a null pointer!", true);
        return 0;
    }

    return distance2(
        this->x, this->y, 
        other->x, other->y
    );

}

void Vec2::midpoint(float x, float y, Vec2* out) const {

    if (out == nullptr) {
        logWrite("Called Vec2->midpoint(float, float, Vec2*) on a nullptr!", true);
        return;
    }

    out->set(
        (this->x + x) / 2.0,
        (this->y + y) / 2.0
    );

    return;

}

void Vec2::midpoint(const Vec2& other, Vec2* out) const {

    if (out == nullptr) {
        logWrite("Called Vec2->midpoint(Vec2&, Vec2*) on a nullptr!", true);
        return;
    }

    out->set(
        (this->x + other.x) / 2.0,
        (this->y + other.y) / 2.0
    );

    return;

}

void Vec2::midpoint(const Vec2* other, Vec2* out) const {
    
    if (other == nullptr) {
        logWrite("Called Vec2->midpoint(Vec2*, Vec2*) with arg1 as nullptr!", true);
        return;
    }

    if (out == nullptr) {
        logWrite("Called Vec2->midpoint(Vec2*, Vec2*) with arg2 as nullptr!", true);
        return;
    }

    out->set(
        (this->x + other->x) / 2.0,
        (this->y + other->y) / 2.0
    );

    return;

}

float Vec2::dotProduct(float x, float y) const {

    return (this->x * x) + (this->y * y);

}

float Vec2::dotProduct(const Vec2& other) const {

    return (this->x * other.x) + (this->y * other.y);

}

float Vec2::dotProduct(const Vec2* other) const {

    if (other == nullptr) {
        logWrite("Called Vec2->dotProduct(Vec2*) on a null pointer!", true);
        return 0;
    }

    return (this->x * other->x) + (this->y * other->y);

}

void Vec2::rotate(float degrees, const Vec2* around /* default value = nullptr */) {
    
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

void Vec2::rotate(float degrees, const Vec2& around) {
    this->rotate(degrees, &(around));
}



/* ------------ */
/* --- Vec3 --- */
/* ------------ */

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

bool Vec3::is(float x, float y, float z) const {

    return (
        this->x == x &&
        this->y == y &&
        this->z == z
    );

}

bool Vec3::is(const Vec3& other) const {

    return (
        this->x == other.x &&
        this->y == other.y &&
        this->z == other.z
    );

}

bool Vec3::is(const Vec3* other) const {

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

Vec3& Vec3::set(float x, float y, float z) {

    this->x = x;
    this->y = y;
    this->z = z;

    return *(this);

}

Vec3& Vec3::set(const Vec3& other) {

    this->x = other.x;
    this->y = other.y;
    this->z = other.z;

    return *(this);

}

Vec3& Vec3::set(const Vec3* other) {

    if (other == nullptr) {
        logWrite("Called Vec3->set(Vec3*) on a null pointer!", true);
        return *(this);
    }

    this->x = other->x;
    this->y = other->y;
    this->z = other->z;

    return *(this);

}

Vec3& Vec3::add(float dx, float dy, float dz) {

    this->x += dx;
    this->y += dy;
    this->z += dz;

    return *(this);

}

Vec3& Vec3::add(const Vec3& other) {

    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *(this);

}

Vec3& Vec3::add(const Vec3* other) {

    if (other == nullptr) {
        logWrite("Called Vec3->add(Vec3*) on a null pointer!", true);
        return *(this);
    }

    this->x += other->x;
    this->y += other->y;
    this->z += other->z;

    return *(this);

}

Vec3& Vec3::sub(float dx, float dy, float dz) {

    this->x -= dx;
    this->y -= dy;
    this->z -= dz;

    return *(this);

}

Vec3& Vec3::sub(const Vec3& other) {

    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *(this);

}

Vec3& Vec3::sub(const Vec3* other) {

    if (other == nullptr) {
        logWrite("Called Vec3->sub(Vec3*) on a null pointer!", true);
        return *(this);
    }

    this->x -= other->x;
    this->y -= other->y;
    this->z -= other->z;

    return *(this);

}

Vec3& Vec3::scale(float factor) {

    this->x *= factor;
    this->y *= factor;
    this->z *= factor;

    return *(this);

}

Vec3& Vec3::scale(float fx, float fy, float fz) {

    this->x *= fx;
    this->y *= fy;
    this->z *= fz;

    return *(this);

}

Vec3& Vec3::inverseScale(float factor) {

    this->x /= factor;
    this->y /= factor;
    this->z /= factor;

    return *(this);

}

Vec3& Vec3::normalize(float toMagnitude /* default value = 1.0 */) {
    float factor = toMagnitude / this->magnitude();
    return this->scale(factor);
}

float Vec3::magnitude() {
    return distance3(this->x, this->y, this->z);
}

float Vec3::distanceTo(float x, float y, float z) const {

    return distance3(
        this->x, this->y, this->z,
        x, y, z
    );

}

float Vec3::distanceTo(const Vec3& other) const {

    return distance3(
        this->x, this->y, this->z,
        other.x, other.y, other.z
    );

}

float Vec3::distanceTo(const Vec3* other) const {

    if (other == nullptr) {
        logWrite("Called Vec3->distanceTo(Vec3*) on a null pointer!", true);
        return 0;
    }

    return distance3(
        this->x, this->y, this->z, 
        other->x, other->y, other->z
    );

}

void Vec3::midpoint(float x, float y, float z, Vec3* out) const {

    if (out == nullptr) {
        logWrite("Called Vec3->midpoint(float, float, float, Vec3*) on a nullptr!", true);
        return;
    }

    out->set(
        (this->x + x) / 2,
        (this->y + y) / 2,
        (this->z + z) / 2
    );

    return;

}

void Vec3::midpoint(const Vec3& other, Vec3* out) const {

    if (out == nullptr) {
        logWrite("Called Vec3->midpoint(Vec3&, Vec3*) on a nullptr!", true);
        return;
    }

    out->set(
        (this->x + other.x) / 2,
        (this->y + other.y) / 2,
        (this->z + other.z) / 2
    );

    return;

}

void Vec3::midpoint(const Vec3* other, Vec3* out) const {

    if (other == nullptr) {
        logWrite("Called Vec3->midpoint(Vec3*, Vec3*) with arg1 as nullptr!", true);
        return;
    }

    if (out == nullptr) {
        logWrite("Called Vec3->midpoint(Vec3*, Vec3*) with arg2 as nullptr!", true);
        return;
    }

    out->set(
        (this->x + other->x) / 2,
        (this->y + other->y) / 2,
        (this->z + other->z) / 2
    );

    return;

}

float Vec3::dotProduct(float x, float y, float z) const {

    return (this->x * x) + (this->y * y) + (this->z * z);

}

float Vec3::dotProduct(const Vec3& other) const {

    return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);

}

float Vec3::dotProduct(const Vec3* other) const {

    if (other == nullptr) {
        logWrite("Called Vec3->dotProduct(Vec3*) on a null pointer!", true);
        return 0;
    }

    return (this->x * other->x) + (this->y * other->y) + (this->z * other->z);

}

void Vec3::crossProduct(float x, float y, float z, Vec3* out) const {

    if (out == nullptr) {
        logWrite("Called Vec3->midpoint(float, float, float, Vec3*) on a nullptr!", true);
        return;
    }

    float xOut = (this->y * z) - (this->z * y);
    float yOut = (this->z * x) - (this->x * z);
    float zOut = (this->x * y) - (this->y * x);
    out->set(xOut, yOut, zOut);

    return;

}

void Vec3::crossProduct(const Vec3& other, Vec3* out) const {

    if (out == nullptr) {
        logWrite("Called Vec3->midpoint(Vec3&, Vec3*) on a nullptr!", true);
        return;
    }

    float x = (this->y * other.z) - (this->z * other.y);
    float y = (this->z * other.x) - (this->x * other.z);
    float z = (this->x * other.y) - (this->y * other.x);
    out->set(x, y, z);

    return;

}

void Vec3::crossProduct(const Vec3* other, Vec3* out) const {

    if (other == nullptr) {
        logWrite("Called Vec3->crossProduct(Vec3*, Vec3*) with arg1 as nullptr!", true);
        return;
    }

    if (out == nullptr) {
        logWrite("Called Vec3->crossProduct(Vec3*, Vec3*) with arg2 as nullptr!", true);
        return;
    }

    float x = (this->y * other->z) - (this->z * other->y);
    float y = (this->z * other->x) - (this->x * other->z);
    float z = (this->x * other->y) - (this->y * other->x);
    out->set(x, y, z);

    return;

}

float Vec3::getAngle(float x, float y, float z) const {

    Vec3 thisCopy;
    thisCopy.set(this);

    Vec3 otherCopy;
    otherCopy.set(x, y, z);

    thisCopy.normalize();
    otherCopy.normalize();

    float dotProduct = thisCopy.dotProduct(otherCopy);

    // These cases shouldnt happen but floating point errors can cause them
    if (dotProduct < -1) return 180;
    if (dotProduct > 1)  return 0;

    float radians = arccos(dotProduct);
    
    return toDegrees(radians);

}

float Vec3::getAngle(const Vec3& other) const {

    // This functions pretty big, so the float version is just called
    return this->getAngle(other.x, other.y, other.z);

}

float Vec3::getAngle(const Vec3* other) const {

    if (other == nullptr) {
        logWrite("Called Vec3->getAngle(Vec3*) on a null pointer!", true);
        return 0;
    }

    // This functions pretty big, so the float version is just called
    return this->getAngle(other->x, other->y, other->z);

}

void Vec3::rotate(float yaw, float pitch, float roll, Vec3* around /* default value = nullptr */) {

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

void Vec3::rotate(float yaw, float pitch, float roll, Vec3& around) {

    this->rotate(yaw, pitch, roll, &(around));

    return;

}

void Vec3::project() {

    /*
        Find a 2d coordinate coorsponding to a 3d point.
        The z component is left untouched
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

    this->x = (this->x * focalLengthX) / this->z;
    this->y = (this->y * focalLengthY) / this->z;

    // adjust so its relative to the top left rather than middle
    this->x += 0.5;
    this->y += 0.5;

    return;

}
