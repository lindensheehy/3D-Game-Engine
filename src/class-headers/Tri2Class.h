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
        Tri2(bool nullPointers = false);

        // Destructor
        ~Tri2();

        // Instance functions
        void setv1(double x, double y, double z);
        void setv1(Vec2* vec);
        void setv2(double x, double y, double z);
        void setv2(Vec2* vec);
        void setv3(double x, double y, double z);
        void setv3(Vec2* vec);

};

#endif