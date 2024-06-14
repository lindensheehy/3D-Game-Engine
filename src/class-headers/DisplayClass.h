#ifndef DisplayClass
#define DisplayClass

#include "Vec2Class.h"
#include "MeshClass.h"

class Display {
    public:

        // Instance variables
        int width;
        int height;
        int widthOffset;
        int heightOffset;

        // Constructors
        Display(int width, int height);
        Display(int width, int height, int widthOffset, int heightOffset);

        // Instance functions
        int middleX();
        int middleY();
        void toDisplayPos(Vec2* vec);
        void toDisplayPos(Mesh* mesh);

};

#endif