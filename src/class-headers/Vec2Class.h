#ifndef Vec2Class
#define Vec2Class

#include "../math/math.cpp"

class Vec2 {

    public:

        // Instance variables
        double x;
        double y;

        // Constructors
        Vec2(double inputX, double inputY);
        Vec2();

        // Instance functions
        Vec2* copy();
        bool is(Vec2* other);
        Vec2* add(Vec2* other);
        Vec2* sub(Vec2* other);
        Vec2* scale(double factor);
        Vec2* inverseScale(double factor);
        Vec2* normalise(double toMagnitude = 1);
        double get(int index);
        double* toArray();
        double magnitude();
        double distanceTo(Vec2* other);
        Vec2* midpoint(Vec2* other);
        double dotProduct(Vec2* other);
        void rotate(double degrees, Vec2* around = nullptr);

        // Operator overloads
        bool operator==(Vec2* other);
        bool operator!=(Vec2* other);
        Vec2* operator+=(Vec2* other);
        Vec2* operator-=(Vec2* other);

    private:
    
        // Instance variables
        double magnitudeValue;
        bool magnitudeUpdated;
};

#endif