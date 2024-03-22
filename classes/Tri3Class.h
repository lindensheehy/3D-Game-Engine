#ifndef Tri3Class
#define Tri3Class

#include "Vec3Class.h"

class Tri3 {
    public:

        // Instance variables
        Vec3* v1;
        Vec3* v2;
        Vec3* v3;
        Vec3* normal;

        // Constructor
        Tri3(bool nullPointers = false) {
            /*
                Stores a set of 3 vectors as well as their normal, the normal can be updated using the instance function but this may be facing the wrong way
                nullPointers flag allows the pointers to be manually set instead of autocreating objects
            */

            if (nullPointers) {
                this->v1 = NULL;
                this->v2 = NULL;
                this->v2 = NULL;
                this->normal = NULL;
                return;
            }

            else {
                this->v1 = new Vec3(0, 0, 0);
                this->v2 = new Vec3(0, 0, 0);
                this->v3 = new Vec3(0, 0, 0);
                this->normal = new Vec3(0, 0, 0);
                return;
            }

        }

        ~Tri3() {
            delete this->v1;
            delete this->v2;
            delete this->v3;
            delete this->normal;
        }

        // Instance functions
        Tri3* copy() {
            Tri3* newCopy = new Tri3(true);
            newCopy->v1 = this->v1->copy();
            newCopy->v2 = this->v2->copy();
            newCopy->v3 = this->v3->copy();
            newCopy->normal = this->normal->copy();
            return newCopy;
        }

        void setv1(double x, double y, double z) {
            this->v1->x = x;
            this->v1->y = y;
            this->v1->z = z;
        }

        void setv1(Vec3* vec) {
            delete this->v1;
            this->v1 = vec->copy();
        }

        void setv2(double x, double y, double z) {
            this->v2->x = x;
            this->v2->y = y;
            this->v2->z = z;
        }

        void setv2(Vec3* vec) {
            delete this->v2;
            this->v2 = vec->copy();
        }

        void setv3(double x, double y, double z) {
            this->v3->x = x;
            this->v3->y = y;
            this->v3->z = z;
        }

        void setv3(Vec3* vec) {
            delete this->v3;
            this->v3 = vec->copy();
        }

        void setNormal(double x, double y, double z) {
            this->normal->x = x;
            this->normal->y = y;
            this->normal->z = z;
        }

        void setNormal(Vec3* normal) {
            delete this->normal;
            this->normal = normal->copy();
        }

        void updateNormal() {

            Vec3* vec1to2 = new Vec3(
                this->v1->x - this->v2->x,
                this->v1->y - this->v2->y,
                this->v1->z - this->v2->z 
            );
            Vec3* vec1to3 = new Vec3(
                this->v1->x - this->v3->x,
                this->v1->y - this->v3->y,
                this->v1->z - this->v3->z 
            );

            Vec3* newNormal = vec1to2->crossProduct(vec1to3);
            newNormal->normalise();
            
            delete this->normal;
            delete vec1to2, vec1to3;

            this->normal = newNormal;

            return;

        }

        bool isFacing(Vec3* vec) {
            return this->normal->getAngle(vec) >= (pi / 2); // 90 degrees
        }

};

#endif