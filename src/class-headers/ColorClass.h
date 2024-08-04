#pragma once

#include <stdint.h>

#include <SDL2/SDL.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


class Color {

    public:

        // Constant color codes
        // Bytes are [opacity][red][green][blue]
        static const uint32 RED    = 0xFFFF0000;
        static const uint32 GREEN  = 0xFF00FF00;
        static const uint32 BLUE   = 0xFF0000FF;
        static const uint32 BLACK  = 0xFF000000;
        static const uint32 WHITE  = 0xFFFFFFFF;
        static const uint32 GREY   = 0xFF888888;


        /*   Instance variables   */

        // Raw value which was given
        uint32 rawValue;

        // Individual color channels
        uint8 redValue, greenValue, blueValue, opacityValue;


        // Contructors
        Color(uint32 color);
        Color(uint8 o, uint8 r, uint8 g, uint8 b);


        /*   Class functions   */

        // Sets the brightness of a given color (uint32) to a double between 0-1.
        // Values higher than 1 CAN be used, but could cause overflow issues.
        static uint32 setBrightness(uint32 color, double newBrightness);

};
