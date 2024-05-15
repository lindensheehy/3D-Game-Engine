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
        Color(Uint32 color) {

            this->rawValue = color;

            // This gets the sub values at each 8 bit interval of the 32 bit input
            this->opacityValue = (Uint8) (color >> 24);
            this->redValue = (Uint8) (color >> 16);
            this->greenValue = (Uint8) (color >> 8);
            this->blueValue = (Uint8) (color);
        }

        Color(Uint8 o, Uint8 r, Uint8 g, Uint8 b) {

            this->redValue = r;
            this->greenValue = g;
            this->blueValue = b;
            this->opacityValue = o;
            
            // Load each 8 sub bits into a bigger variable
            this->rawValue = 0x00000000;
            this->rawValue |= o;
            this->rawValue <<= 8;
            this->rawValue |= r;
            this->rawValue <<= 8;
            this->rawValue |= g;
            this->rawValue <<= 8;
            this->rawValue |= b;
        }

        // Class functions
        static Uint32 reduceBrightness(Uint32 color, double newBrightness) {

            // Unpack color code
            Uint8 opacityValue = (Uint8) (color >> 24);
            Uint8 redValue = (Uint8) (color >> 16);
            Uint8 greenValue = (Uint8) (color >> 8);
            Uint8 blueValue = (Uint8) (color);

            // Update values
            redValue *= newBrightness;
            greenValue *= newBrightness;
            blueValue *= newBrightness;

            // Repack color code
            Uint32 newColor = 0x00000000;
            newColor |= opacityValue;
            newColor <<= 8;
            newColor |= redValue;
            newColor <<= 8;
            newColor |= greenValue;
            newColor <<= 8;
            newColor |= blueValue;

            return newColor;

        }

    private:

};

#endif