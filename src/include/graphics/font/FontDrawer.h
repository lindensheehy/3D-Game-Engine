#pragma once

#include "util/Utility.h"
#include "util/Log.h"

#include "graphics/drawing/PixelDrawer.h"


namespace Graphics {
namespace Font {

class FontDrawer {

    /*
        This class is responsible for handling the font drawing
        This deals with all the low level intricacies and provides a high level interface
    */

    public:

        /*   Instance Variables   */

        // Not owned by this class
        Drawing::PixelDrawer* pixelDrawer;


        // Constructor
        FontDrawer(Drawing::PixelDrawer* pixelDrawer);

        // Destructor
        ~FontDrawer();


        /*   Instance Functions   */

        // Draws a character to the screen, the upper left will be at (x, y)
        void drawChar(uint32 color, char ch, int x, int y);

        // Draws a string to the screen, the top left will be at (x, y)
        void drawString(uint32 color, const char* string, int x, int y);

        // Draws an integer value to the screen, the top left will be at (x, y)
        void drawInt(uint32 color, int num, int x, int y);


    private:

        // Loads the character pixel arts into memory (called from the constructor)
        void initFont();

        // Draws a set of pixels to the screen. the other draw functions depend on this
        void drawCharPixels(uint32 color, const bool* pixels, int x, int y);

        // Returns a pointer to the pixels for a character
        bool* getCharRef(char ch) const;
        bool* getCharRef(int num) const;


        /*
            NOTE: This section is temporary until I implement file based fonts (postponed until V2)

            Character Pixel Arts
            This bool* type is a list of bools, subdivided into sections of length 49 (7x7)
            This list stores 40 chars worth of data, which is most of the main printable characters
            This list is filled by running init
        */

        bool* chars;

        // Here you can see the data which is used to create the bool lists
        // spaces are 0 (false) and zeros are 1 (true), the bool values coorespond to pixel states (on/off)
        // All the seperate strings here get put together by the compiler into one big string
        // String length is: (7 * 7) * char count (40) = 1960 + nullchar -> 1961
        static constexpr int rawCharsCount = 40;
        static constexpr int rawCharsSize = 1961;
        static constexpr const char* rawChars = {

            // A
            "       "
            "  000  "
            " 0   0 "
            " 00000 "
            " 0   0 "
            " 0   0 "
            "       "

            // B
            "       "
            " 0000  "
            " 0   0 "
            " 0000  "
            " 0   0 "
            " 0000  "
            "       "

            // C
            "       "
            "  0000 "
            " 0     "
            " 0     "
            " 0     "
            "  0000 "
            "       "

            // D
            "       "
            " 0000  "
            " 0   0 "
            " 0   0 "
            " 0   0 "
            " 0000  "
            "       "

            // E
            "       "
            " 00000 "
            " 0     "
            " 0000  "
            " 0     "
            " 00000 "
            "       "

            // F
            "       "
            " 00000 "
            " 0     "
            " 0000  "
            " 0     "
            " 0     "
            "       "

            // G
            "       "
            " 00000 "
            " 0     "
            " 0  00 "
            " 0   0 "
            " 00000 "
            "       "

            // H
            "       "
            " 0   0 "
            " 0   0 "
            " 00000 "
            " 0   0 "
            " 0   0 "
            "       "

            // I
            "       "
            " 00000 "
            "   0   "
            "   0   "
            "   0   "
            " 00000 "
            "       "

            // J
            "       "
            " 00000 "
            "   0   "
            "   0   "
            "   0   "
            " 00    "
            "       "

            // K
            "       "
            " 0   0 "
            " 0  0  "
            " 000   "
            " 0  0  "
            " 0   0 "
            "       "

            // L
            "       "
            " 0     "
            " 0     "
            " 0     "
            " 0     "
            " 00000 "
            "       "

            // M
            "       "
            " 0   0 "
            " 00000 "
            " 0 0 0 "
            " 0   0 "
            " 0   0 "
            "       "

            // N
            "       "
            " 0   0 "
            " 00  0 "
            " 0 0 0 "
            " 0  00 "
            " 0   0 "
            "       "

            // O
            "       "
            "  000  "
            " 0   0 "
            " 0   0 "
            " 0   0 "
            "  000  "
            "       "

            // P
            "       "
            " 0000  "
            " 0   0 "
            " 0000  "
            " 0     "
            " 0     "
            "       "

            // Q
            "       "
            "  000  "
            " 0   0 "
            " 0   0 "
            "  000  "
            "    00 "
            "       "

            // R
            "       "
            " 0000  "
            " 0   0 "
            " 0000  "
            " 0  0  "
            " 0   0 "
            "       "

            // S
            "       "
            "  0000 "
            " 0     "
            "  000  "
            "     0 "
            " 0000  "
            "       "

            // T
            "       "
            " 00000 "
            "   0   "
            "   0   "
            "   0   "
            "   0   "
            "       "

            // U
            "       "
            " 0   0 "
            " 0   0 "
            " 0   0 "
            " 0   0 "
            "  000  "
            "       "

            // V
            "       "
            " 0   0 "
            " 0   0 "
            " 0   0 "
            "  0 0  "
            "   0   "
            "       "

            // W
            "       "
            " 0   0 "
            " 0   0 "
            " 0 0 0 "
            " 00 00 "
            " 0   0 "
            "       "

            // X
            "       "
            " 0   0 "
            "  0 0  "
            "   0   "
            "  0 0  "
            " 0   0 "
            "       "

            // Y
            "       "
            " 0   0 "
            "  0 0  "
            "   0   "
            "   0   "
            "   0   "
            "       "

            // Z
            "       "
            " 00000 "
            "    0  "
            "   0   "
            "  0    "
            " 00000 "
            "       "

            // 0
            "       "
            "  000  "
            " 0  00 "
            " 0 0 0 "
            " 00  0 "
            "  000  "
            "       "

            // 1
            "       "
            "  00   "
            " 0 0   "
            "   0   "
            "   0   "
            " 00000 "
            "       "

            // 2
            "       "
            "  000  "
            " 0   0 "
            "   00  "
            "  0    "
            " 00000 "
            "       "

            // 3
            "       "
            "  000  "
            "     0 "
            "   00  "
            "     0 "
            "  000  "
            "       "

            // 4
            "       "
            "   0   "
            "  00   "
            " 0 0   "
            " 00000 "
            "   0   "
            "       "

            // 5
            "       "
            " 00000 "
            " 0     "
            " 0000  "
            "     0 "
            " 0000  "
            "       "

            // 6
            "       "
            "  000  "
            " 0     "
            " 0000  "
            " 0   0 "
            "  000  "
            "       "

            // 7
            "       "
            " 00000 "
            "    0  "
            "   0   "
            "  0    "
            " 0     "
            "       "
            
            // 8
            "       "
            "  000  "
            " 0   0 "
            "  000  "
            " 0   0 "
            "  000  "
            "       "

            // 9
            "       "
            "  000  "
            " 0   0 "
            "  0000 "
            "     0 "
            "  000  "
            "       "

            // Space
            "       "
            "       "
            "       "
            "       "
            "       "
            "       "
            "       "

            // Minus / Negative sign
            "       "
            "       "
            "       "
            " 00000 "
            "       "
            "       "
            "       "

            // Period / Decimal
            "       "
            "       "
            "       "
            "       "
            "  00   "
            "  00   "
            "       "

            // Disallowed char
            "       "
            "  000  "
            " 0 0 0 "
            " 00 00 "
            " 0 0 0 "
            "  000  "
            "       "

        };

};

}
}
