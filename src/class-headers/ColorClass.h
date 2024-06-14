#ifndef ColorClass
#define ColorClass

#include <SDL2/SDL.h>

class Color {

    public:

        // Constants
        static const Uint32 RED    = 0xFFFF0000;
        static const Uint32 GREEN  = 0xFF00FF00;
        static const Uint32 BLUE   = 0xFF0000FF;
        static const Uint32 BLACK  = 0xFF000000;
        static const Uint32 WHITE  = 0xFFFFFFFF;
        static const Uint32 GREY   = 0xFF888888;

        // Instance variables
        Uint32 rawValue;  // raw value which was given
        Uint8 redValue;
        Uint8 greenValue;
        Uint8 blueValue;
        Uint8 opacityValue;

        // Contructors
        Color(Uint32 color);
        Color(Uint8 o, Uint8 r, Uint8 g, Uint8 b);

        // Class functions
        static Uint32 setBrightness(Uint32 color, double newBrightness);

};

#endif