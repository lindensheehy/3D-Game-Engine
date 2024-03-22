#ifndef Tri2Class
#define Tri2Class

#include "Vec2Class.h"

class Tri2 {
    public:

        // Instance variables
        Vec2* v1;
        Vec2* v2;
        Vec2* v3;

        // Constructor
        Tri2(bool nullPointers = false) {
            /*
                Stores a set of 3 vectors
                nullPointers flag allows the pointers to be manually set instead of autocreating objects
            */

            if (nullPointers) {
                this->v1 = NULL;
                this->v2 = NULL;
                this->v3 = NULL;
            }

            else {
                this->v1 = new Vec2(0, 0);
                this->v2 = new Vec2(0, 0);
                this->v3 = new Vec2(0, 0);
            }
        }

        ~Tri2() {
            delete this->v1;
            delete this->v2;
            delete this->v3;
        }

        // Instance functions
        void setv1(double x, double y, double z) {
            this->v1->x = x;
            this->v1->y = y;
        }

        void setv1(Vec2* vec) {
            delete this->v1;
            this->v1 = vec->copy();
        }

        void setv2(double x, double y, double z) {
            this->v2->x = x;
            this->v2->y = y;
        }

        void setv2(Vec2* vec) {
            delete this->v2;
            this->v2 = vec->copy();
        }

        void setv3(double x, double y, double z) {
            this->v3->x = x;
            this->v3->y = y;
        }

        void setv3(Vec2* vec) {
            delete this->v3;
            this->v3 = vec->copy();
        }

};

#endif