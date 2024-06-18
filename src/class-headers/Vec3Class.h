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


        /*   Constructors   */

        // Specified values
        Vec3(double inputX, double inputY, double inputZ);

        // Defaults to (0, 0, 0)
        Vec3();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Vec3* copy();

        // Sets the components of the Vec3 to specific values
        Vec3* set(double x, double y, double z);

        // Acts similar to '=='. Returns true if all components are equal to each other
        bool is(Vec3* other);


        // The following are self transformation functions. they all return 'this' so they can be chained ( ex. this->add(vec)->sub(vec2) )

        // Adds the components of other to those of this.
        Vec3* add(Vec3* other);
        Vec3* add(double dx, double dy, double dz);

        // Subtracts the components of other from those of this.
        Vec3* sub(Vec3* other);
        Vec3* sub(double dx, double dy, double dz);

        // Scalar multiplication by a given factor
        Vec3* scale(double factor);
        Vec3* scale(double fx, double fy, double fz);

        // Same as above, but uses 1/factor
        Vec3* inverseScale(double factor);

        // Sets the magnitude of the vector to a given value, while keeping the ratios between components the same.
        Vec3* normalise(double toMagnitude = 1);


        // Allows these objects to be indexed like an array.
        double get(int index);

        // Converts the Vec3 to an array. [Vec3->x, Vec3->y, Vec3->z]
        double* toArray();

        // Returns the magnitude of the vector
        double magnitude();

        // Returns the distance between this vector and other
        double distanceTo(Vec3* other);

        // Returns the midpoint between this and other as a new Vec3 object.
        Vec3* midpoint(Vec3* other);

        // Returns the dot product of this and other.
        double dotProduct(Vec3* other);

        // Returns the cross product of this and other as a new Vec3 object. This vector is perpendicular to both other and this.
        Vec3* crossProduct(Vec3* other);

        // Find the angle between this and other. This angle will always be between 0-180.
        double getAngle(Vec3* other);

        // Rotates the vector around a certain point (by default (0, 0, 0)) by a given angle on each direction.
        // Each rotation occurs COUNTER CLOCKWISE assuming you are looking down upon the rotation.
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
