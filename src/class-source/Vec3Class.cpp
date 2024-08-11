#include "../class-headers/Vec3Class.h"


// Constructors
Vec3::Vec3(double inputX, double inputY, double inputZ) {
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
Vec3* Vec3::copy() {
    return new Vec3(this->x, this->y, this->z);
}

void Vec3::log() {

    logWrite("Vec3( ");
    logWrite(this->x);
    logWrite(", ");
    logWrite(this->y);
    logWrite(", ");
    logWrite(this->z);
    logWrite(" )", true);

    return;
    
}

Vec3* Vec3::set(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    return this;
}

bool Vec3::is(Vec3* other) {

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

Vec3* Vec3::add(double dx, double dy, double dz) {
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

Vec3* Vec3::sub(double dx, double dy, double dz) {
    this->x -= dx;
    this->y -= dy;
    this->z -= dz;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::scale(double factor) {
    this->x *= factor;
    this->y *= factor;
    this->z *= factor;
    if (this->magnitudeUpdated) this->magnitudeValue *= factor;
    return this;
}

Vec3* Vec3::scale(double fx, double fy, double fz) {
    this->x *= fx;
    this->y *= fy;
    this->z *= fz;
    this->magnitudeUpdated = false;
    return this;
}

Vec3* Vec3::inverseScale(double factor) {
    return this->scale(1 / factor);
}

Vec3* Vec3::normalise(double toMagnitude /* default value = 1.0 */) {
    double factor = toMagnitude / this->magnitude();
    return this->scale(factor);
}

double Vec3::get(int index) {
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

double* Vec3::toArray() {
    double* array = new double[3];
    array[0] = this->x;
    array[1] = this->y;
    array[2] = this->z;
    return array;
}

double Vec3::magnitude() {

    if (!this->magnitudeUpdated) {
        this->magnitudeValue = distance3(this->x, this->y, this->z);
        this->magnitudeUpdated = true;
    }
    
    return this->magnitudeValue;

}

double Vec3::distanceTo(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->distanceTo(Vec3*) on a null pointer!", true);
        return 0;
    }

    return distance3(this->x, this->y, this->z, other->x, other->y, other->z);

}

Vec3* Vec3::midpoint(Vec3* other) {

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

double Vec3::dotProduct(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->dotProduct(Vec3*) on a null pointer!", true);
        return 0;
    }

    return (this->x * other->x) + (this->y * other->y) + (this->z * other->z);
}

Vec3* Vec3::crossProduct(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->crossProduct(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    double x = (this->y * other->z) - (this->z * other->y);
    double y = (this->z * other->x) - (this->x * other->z);
    double z = (this->x * other->y) - (this->y * other->x);
    return new Vec3(x, y, z);
}

double Vec3::getAngle(Vec3* other) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (other == nullptr) {
        logWrite("Called Vec3->getAngle(Vec3*) on a null pointer!", true);
        return 0;
    }

    double dotProduct = this->dotProduct(other);
    double magnitudeFactor = this->magnitude() * other->magnitude();
    double ratio = dotProduct / magnitudeFactor;

    // These cases shouldnt happen but floating point errors can cause them
    if (ratio < -1) return 180;
    if (ratio > 1)  return 0;

    double radians = arccos(ratio);
    
    return toDegrees(radians);
}

void Vec3::rotate(double yaw, double pitch, double roll, Vec3* around /* default value = nullptr */) {

    // around = nullptr already addressed here, no need for error case

    if (yaw == 0 && pitch == 0 && roll == 0) return;

    double aroundX = 0;
    double aroundY = 0;
    double aroundZ = 0;
    double relativeX = this->x;
    double relativeY = this->y;
    double relativeZ = this->z;

    if (around != nullptr) {
        aroundX = around->x;
        aroundY = around->y;
        aroundZ = around->z;
        relativeX -= aroundX;
        relativeY -= aroundY;
        relativeZ -= aroundZ;
    }

    double radians;

    if (yaw != 0) {
        
        radians = toRadians(yaw);

        double sinValue = sin(radians);
        double cosValue = cos(radians);

        this->x = (cosValue * relativeX) - (sinValue * relativeZ) + aroundX;
        this->z = (cosValue * relativeZ) + (sinValue * relativeX) + aroundZ;

    }

    if (pitch != 0) {

        radians = toRadians(pitch);

        double sinValue = sin(radians);
        double cosValue = cos(radians);

        this->y = (cosValue * relativeY) - (sinValue * relativeZ) + aroundY;
        this->z = (cosValue * relativeZ) + (sinValue * relativeY) + aroundZ;

    }

    if (roll != 0) {

        radians = toRadians(roll);

        double sinValue = sin(radians);
        double cosValue = cos(radians);

        this->y = (cosValue * relativeY) - (sinValue * relativeX) + aroundY;
        this->x = (cosValue * relativeX) + (sinValue * relativeY) + aroundX;

    }

    return;
}
