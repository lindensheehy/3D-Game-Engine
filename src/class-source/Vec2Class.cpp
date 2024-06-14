#include "../class-headers/Vec2Class.h"

#include "../math/math.h"

class Vec2 {
    public:
        // Instance variables
        double x;
        double y;

        // Constructor
        Vec2(double inputX, double inputY) {
            this->x = inputX;
            this->y = inputY;
            this->magnitudeValue = 0;
            this->magnitudeUpdated = false;
        }

        Vec2() {
            this->x = 0;
            this->y = 0;
            this->magnitudeValue = 0;
            this->magnitudeUpdated = false;
        }

        // Instance functions
        Vec2* copy() {
            return new Vec2(this->x, this->y);
        }

        bool is(Vec2* other) {
            return (
                this->x == other->x &&
                this->y == other->y
            );
        }

        Vec2* add(Vec2* other) {
            this->x += other->x;
            this->y += other->y;
            this->magnitudeUpdated = false;
            return this;
        }

        Vec2* sub(Vec2* other) {
            this->x -= other->x;
            this->y -= other->y;
            this->magnitudeUpdated = false;
            return this;
        }

        Vec2* scale(double factor) {
            this->x *= factor;
            this->y *= factor;
            if (this->magnitudeUpdated) this->magnitudeValue *= factor;
            return this;
        }

        Vec2* inverseScale(double factor) {
            return this->scale(1 / factor);
        }

        Vec2* normalise(double toMagnitude = 1) {
            double factor = toMagnitude / this->magnitude();
            return this->scale(factor);
        }

        double get(int index) {
            switch (index) {
                case 0:
                    return this->x;
                case 1:
                    return this->y;
                default:
                    return 0;
            }
        }

        double* toArray() {
            double* array = new double[2];
            array[0] = this->x;
            array[1] = this->y;
            return array;
        }

        double magnitude() {
            if (!this->magnitudeUpdated) {
                this->magnitudeValue = sqrt( (this->x * this->x) + (this->y * this->y) );
                this->magnitudeUpdated = true;
            }
            return this->magnitudeValue;
        }

        double distanceTo(Vec2* other) {
            double dx = this->x - other->x;
            double dy = this->y - other->y;
            return sqrt( (dx * dx) + (dy * dy) );
        }

        Vec2* midpoint(Vec2* other) {
            return new Vec2(
                (this->x + other->x) / 2,
                (this->y + other->y) / 2
            );
        }

        double dotProduct(Vec2* other) {
            return (this->x * other->x) + (this->y * other->y);
        }

        void rotate(double degrees, Vec2* around = nullptr) {

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

            double sinValue = sin(toRadians(degrees));
            double cosValue = cos(toRadians(degrees));

            this->x = (cosValue * relativeX) - (sinValue * relativeY) + aroundX;
            this->y = (cosValue * relativeY) + (sinValue * relativeX) + aroundY;

            return;
        }

        // Operator overloads
        bool operator==(Vec2* other) {
            return this->is(other);
        }

        bool operator!=(Vec2* other) {
            return !this->is(other);
        }

        Vec2* operator+=(Vec2* other) {
            // Calls Vec2.add()
            return this->add(other);
        }

        Vec2* operator-=(Vec2* other) {
            // Calls Vec2.sub()
            return this->sub(other);
        }

    private:
        // Instance variables
        double magnitudeValue;
        bool magnitudeUpdated;
};