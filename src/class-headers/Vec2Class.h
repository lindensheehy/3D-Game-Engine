#pragma once

#include "../math/math.h"

class Vec2 {

    /*
        Class encapsulating 2 double values so that they are treated as a vector.
        Wide array of functions to act upon these vector.
        These are the base for everything 2d in this program.
    */

    public:

        // Instance variables
        double x, y;


        // Constructors
        Vec2(double inputX, double inputY);
        Vec2();


        /*   Instance functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Vec2* copy();

        // Acts similar to '=='. Returns true if all components are equal to each other
        bool is(Vec2* other);

        // The following are self transformation functions. they all return 'this' so they can be chained ( ex. this->add(vec)->sub(vec2) )
        // Adds the components of other to those of this, and returns this.
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

    private:
    
        /*   Instance variables   */

        // This is the length of the vector in 2d space.
        // This value is private because it is not always accurate, and is only update when requested.
        // Doing this means there wont be unnesecary updates to the magnitude when it wont even be read.
        double magnitudeValue;

        // Flag showing if the above value is accurate. This allows the function call which returns the magnitude to only do the math when nessecary.
        bool magnitudeUpdated;
};
