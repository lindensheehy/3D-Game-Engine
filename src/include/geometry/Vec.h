#pragma once

#include "util/Utility.h"


namespace Geometry {

class Vec2 {

    /*
        Class encapsulating 2 float values so that they are treated as a vector.
        Wide array of functions to act upon these vectors.
        These are the base for everything 2d in this program.
    */

    public:

        // Instance variables
        float x, y;


        /*   Constructors   */

        // Specified values
        Vec2(float inputX, float inputY);

        // Defaults to (0, 0)
        Vec2(); 


        /*   Instance functions   */

        // Deep copy. Returns a NEW heap object
        Vec2* copy() const;

        // Logs the vector in the format "Vec2( x, y )"
        void log() const;
        
        // Equivalent to a '==' overload. Returns true if all components are equal to each other
        bool is(float x, float y) const;
        bool is(const Vec2& other) const;
        bool is(const Vec2* other) const;

        // Sets the values of the components
        Vec2& set(float x, float y);
        Vec2& set(const Vec2& other);
        Vec2& set(const Vec2* other);

        // Adds the components of other to those of this.
        Vec2& add(float x, float y);
        Vec2& add(const Vec2& other);
        Vec2& add(const Vec2* other);

        // Subtracts the components of other from those of this.
        Vec2& sub(float x, float y);
        Vec2& sub(const Vec2& other);
        Vec2& sub(const Vec2* other);

        // Scalar multiplication by a given factor
        Vec2& scale(float factor);

        // Same as scale, but uses 1/factor
        Vec2& inverseScale(float factor);

        // Sets the magnitude of the vector to a given value, while keeping the ratios between components the same.
        Vec2& normalize(float toMagnitude = 1.0);


        // Allows these objects to be indexed like an array.
        float get(int index) const;

        // Converts the Vec2 to an array. [Vec2->x, Vec2->y]
        float* toArray() const;

        // Returns the magnitude of the vector
        float magnitude();

        // Returns the distance between this vector and other
        float distanceTo(float x, float y) const;
        float distanceTo(const Vec2& other) const;
        float distanceTo(const Vec2* other) const;

        // Returns the midpoint between this and other as a new Vec2 object.
        void midpoint(float x, float y, Vec2* out) const;
        void midpoint(const Vec2& other, Vec2* out) const;
        void midpoint(const Vec2* other, Vec2* out) const;

        // Returns the dot product of this and other.
        float dotProduct(float x, float y) const;
        float dotProduct(const Vec2& other) const;
        float dotProduct(const Vec2* other) const;

        // Rotates the vector around a given point (by default (0, 0)) by a given angle.
        // Vector will be rotated COUNTER CLOCKWISE
        void rotate(float degrees, const Vec2* around = nullptr);
        void rotate(float degrees, const Vec2& around);

    private:
    
        /*   Instance variables   */

        // This is the length of the vector in 2d space.
        // This value is private because it is not always accurate, and is only update when requested.
        // Doing this means there wont be unnesecary updates to the magnitude when it wont even be read.
        float magnitudeValue;

        // Flag showing if the above value is accurate. This allows the function call which returns the magnitude to only do the math when nessecary.
        // Any instance function which can change the magnitude, will set this to false.
        bool magnitudeUpdated;
        
};


class Vec3 {

    /*
        Class encapsulating 3 float values so that they are treated as a vector.
        Wide array of functions to act upon these vectors.
        These are the base for everything 3d in this program.
    */

    public:

        // Instance variables
        float x, y, z;


        /*   Constructors   */

        // Specified values
        Vec3(float inputX, float inputY, float inputZ);

        // Defaults to (0, 0, 0)
        Vec3();


        /*   Instance functions   */

        // Deep copy. Returns a NEW heap object
        Vec3* copy() const;

        // Logs the vector in the format "Vec3( x, y, z )"
        void log() const;

        // Equivalent to a '==' overload. Returns true if all components are equal to each other
        bool is(const Vec3* other) const;
        bool is(const Vec3& other) const;
        bool is(float x, float y, float z) const;

        // Sets the values of the components
        Vec3& set(float x, float y, float z);
        Vec3& set(const Vec3& other);
        Vec3& set(const Vec3* other);

        // Adds the components of other to those of this.
        Vec3& add(float dx, float dy, float dz);
        Vec3& add(const Vec3& other);
        Vec3& add(const Vec3* other);

        // Subtracts the components of other from those of this.
        Vec3& sub(float dx, float dy, float dz);
        Vec3& sub(const Vec3& other);
        Vec3& sub(const Vec3* other);

        // Scalar multiplication by a given factor
        Vec3& scale(float factor);
        Vec3& scale(float fx, float fy, float fz);

        // Same as above, but uses 1/factor
        Vec3& inverseScale(float factor);

        // Sets the magnitude of the vector to a given value, while keeping the ratios between components the same.
        Vec3& normalize(float toMagnitude = 1.0);


        // Allows these objects to be indexed like an array.
        float get(int index) const;

        // Converts the Vec3 to an array. [Vec3->x, Vec3->y, Vec3->z]
        float* toArray() const;

        // Returns the magnitude of the vector
        float magnitude();

        // Returns the distance between this vector and other
        float distanceTo(float x, float y, float z) const;
        float distanceTo(const Vec3& other) const;
        float distanceTo(const Vec3* other) const;

        // Returns the midpoint between this and other as a new Vec3 object.
        void midpoint(float x, float y, float z, Vec3* out) const;
        void midpoint(const Vec3& other, Vec3* out) const;
        void midpoint(const Vec3* other, Vec3* out) const;

        // Returns the dot product of this and other.
        float dotProduct(float x, float y, float z) const;
        float dotProduct(const Vec3& other) const;
        float dotProduct(const Vec3* other) const;

        // Returns the cross product of this and other as a new Vec3 object. This vector is perpendicular to both other and this.
        void crossProduct(float x, float y, float z, Vec3* out) const;
        void crossProduct(const Vec3& other, Vec3* out) const;
        void crossProduct(const Vec3* other, Vec3* out) const;

        // Find the angle in degrees between this and other. This angle will always be between 0-180.
        float getAngle(float x, float y, float z) const;
        float getAngle(const Vec3& other) const;
        float getAngle(const Vec3* other) const;

        // Rotates the vector around a certain point (by default (0, 0, 0)) by a given angle on each direction.
        // Each rotation occurs COUNTER CLOCKWISE assuming you are looking down upon the rotation.
        void rotate(float yaw, float pitch, float roll, Vec3* around = nullptr);
        void rotate(float yaw, float pitch, float roll, Vec3& around);

        // Projects the point to 2d space. The z value becomes the depth. The values of the components are changed
        void project();

    private:

        /*   Instance variables   */

        // This is the length of the vector in 3d space.
        // This value is private because it is not always accurate, and is only update when requested.
        // Doing this means there wont be unnesecary updates to the magnitude when it wont even be read.
        float magnitudeValue;

        // Flag showing if the above value is accurate. This allows the function call which returns the magnitude to only do the math when nessecary.
        bool magnitudeUpdated;

};

}
