#pragma once

#include "../math/math.h"

class Vec3 {

    /*
        Class encapsulating 3 double values so that they are treated as a vector.
        Wide array of functions to act upon these vector.
        These are the base for everything 3d in this program.
    */

    public:

        // Instance variables
        double x, y, z;


        // Constructors
        Vec3(double inputX, double inputY, double inputZ);
        Vec3();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Vec3* copy();
        Vec3* set(double x, double y, double z);
        bool is(Vec3* other);
        Vec3* add(Vec3* other);
        Vec3* add(double dx, double dy, double dz);
        Vec3* sub(Vec3* other);
        Vec3* sub(double dx, double dy, double dz);
        Vec3* scale(double factor);
        Vec3* scale(double fx, double fy, double fz);
        Vec3* inverseScale(double factor);
        Vec3* normalise(double toMagnitude = 1);
        double get(int index);
        double* toArray();
        double magnitude();
        double distanceTo(Vec3* other);
        Vec3* midpoint(Vec3* other);
        double dotProduct(Vec3* other);
        Vec3* crossProduct(Vec3* other);
        double getAngle(Vec3* other);
        void rotate(double yaw, double pitch, double roll, Vec3* around = nullptr);

    private:

        /*   Instance variables   */

        // This is the length of the vector in 3d space.
        // This value is private because it is not always accurate, and is only update when requested.
        // Doing this means there wont be unnesecary updates to the magnitude when it wont even be read.
        double magnitudeValue;

        // Flag showing if the above value is accurate. This allows the function call which returns the magnitude to only do the math when nessecary.
        bool magnitudeUpdated;
};
