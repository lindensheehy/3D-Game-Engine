#ifndef Vec3Class
#define Vec3Class

#include "../math/math.h"

class Vec3 {
    public:

        // Instance variables
        double x;
        double y;
        double z;

        // Constructors
        Vec3(double inputX, double inputY, double inputZ);
        Vec3();

        // Instance functions
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

        // Instance variables
        double magnitudeValue;
        bool magnitudeUpdated;
};

#endif