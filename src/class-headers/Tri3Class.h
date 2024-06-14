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
        Tri3(bool nullPointers = false);

        // Destructor
        ~Tri3();

        // Instance functions
        Tri3* copy();
        void setv1(double x, double y, double z);
        void setv1(Vec3* vec);
        void setv2(double x, double y, double z);
        void setv2(Vec3* vec);
        void setv3(double x, double y, double z);
        void setv3(Vec3* vec);
        void setNormal(double x, double y, double z);
        void setNormal(Vec3* normal);
        void updateNormal();
        bool isFacing(Vec3* vec);
        Vec3* getCenter();
        
};

#endif