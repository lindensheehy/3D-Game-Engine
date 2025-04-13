#pragma once

#include "util/Utility.h"

#include "graphics/drawing/PixelDrawer.h"


namespace Graphics {
namespace Font {

class FontDrawer {

    /*
        This class is responsible for handling the font drawing
        This deals with all the low level intricacies of the font and provides a high level interface
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
        void drawChar(uint32 pixel, char ch, int x, int y);

        // Draws a string to the screen, the top left will be at (x, y)
        void drawString(uint32 pixel, const char* string, int x, int y);

        // Draws an integer value to the screen, the top left will be at (x, y)
        void drawInt(uint32 pixel, int num, int x, int y);


    private:

        // Loads the character pixel arts into memory (called from the constructor)
        void initFont();

        // Draws a set of pixels to the screen. the other draw functions rely on this
        void drawCharPixels(uint32 pixel, bool* pixels, int x, int y);

        // Returns a pointer to the pixels for a character
        bool* getCharRef(char ch) const;
        bool* getCharRef(int num) const;


        /*
            NOTE: This section is temporary until I implement file based fonts (soon hopefully)

            Character Pixel Arts
            This bool* type is a list of bools, subdivided into sections of length 49 (7x7)
            This list stores 40 chars worth of data, which is most of the main printable characters
            This list is filled by running init
        */

        bool* chars;

        // Here you can see the data which is used to create the bool lists
        // underscore is 0 (false) and 0 is 1 (true), the bool values coorespond to if they are shown or not when drawing
        // All the seperate strings here get put together by the compiler into one big string
        // String length is: (7 * 7) * char count (40) = 1960 + nullchar -> 1961
        const int rawCharsCount = 40;
        const int rawCharsSize = 1961;
        const char* rawChars = {

            // A
            "_______"
            "__000__"
            "_0___0_"
            "_00000_"
            "_0___0_"
            "_0___0_"
            "_______"

            // B
            "_______"
            "_0000__"
            "_0___0_"
            "_0000__"
            "_0___0_"
            "_0000__"
            "_______"

            // C
            "_______"
            "__0000_"
            "_0_____"
            "_0_____"
            "_0_____"
            "__0000_"
            "_______"

            // D
            "_______"
            "_0000__"
            "_0___0_"
            "_0___0_"
            "_0___0_"
            "_0000__"
            "_______"

            // E
            "_______"
            "_00000_"
            "_0_____"
            "_0000__"
            "_0_____"
            "_00000_"
            "_______"

            // F
            "_______"
            "_00000_"
            "_0_____"
            "_0000__"
            "_0_____"
            "_0_____"
            "_______"

            // G
            "_______"
            "_00000_"
            "_0_____"
            "_0__00_"
            "_0___0_"
            "_00000_"
            "_______"

            // H
            "_______"
            "_0___0_"
            "_0___0_"
            "_00000_"
            "_0___0_"
            "_0___0_"
            "_______"

            // I
            "_______"
            "_00000_"
            "___0___"
            "___0___"
            "___0___"
            "_00000_"
            "_______"

            // J
            "_______"
            "_00000_"
            "___0___"
            "___0___"
            "___0___"
            "_00____"
            "_______"

            // K
            "_______"
            "_0___0_"
            "_0__0__"
            "_000___"
            "_0__0__"
            "_0___0_"
            "_______"

            // L
            "_______"
            "_0_____"
            "_0_____"
            "_0_____"
            "_0_____"
            "_00000_"
            "_______"

            // M
            "_______"
            "_0___0_"
            "_00000_"
            "_0_0_0_"
            "_0___0_"
            "_0___0_"
            "_______"

            // N
            "_______"
            "_0___0_"
            "_00__0_"
            "_0_0_0_"
            "_0__00_"
            "_0___0_"
            "_______"

            // O
            "_______"
            "__000__"
            "_0___0_"
            "_0___0_"
            "_0___0_"
            "__000__"
            "_______"

            // P
            "_______"
            "_0000__"
            "_0___0_"
            "_0000__"
            "_0_____"
            "_0_____"
            "_______"

            // Q
            "_______"
            "__000__"
            "_0___0_"
            "_0___0_"
            "__000__"
            "____00_"
            "_______"

            // R
            "_______"
            "_0000__"
            "_0___0_"
            "_0000__"
            "_0__0__"
            "_0___0_"
            "_______"

            // S
            "_______"
            "__0000_"
            "_0_____"
            "__000__"
            "_____0_"
            "_0000__"
            "_______"

            // T
            "_______"
            "_00000_"
            "___0___"
            "___0___"
            "___0___"
            "___0___"
            "_______"

            // U
            "_______"
            "_0___0_"
            "_0___0_"
            "_0___0_"
            "_0___0_"
            "__000__"
            "_______"

            // V
            "_______"
            "_0___0_"
            "_0___0_"
            "_0___0_"
            "__0_0__"
            "___0___"
            "_______"

            // W
            "_______"
            "_0___0_"
            "_0___0_"
            "_0_0_0_"
            "_00_00_"
            "_0___0_"
            "_______"

            // X
            "_______"
            "_0___0_"
            "__0_0__"
            "___0___"
            "__0_0__"
            "_0___0_"
            "_______"

            // Y
            "_______"
            "_0___0_"
            "__0_0__"
            "___0___"
            "___0___"
            "___0___"
            "_______"

            // Z
            "_______"
            "_00000_"
            "____0__"
            "___0___"
            "__0____"
            "_00000_"
            "_______"

            // 0
            "_______"
            "__000__"
            "_0__00_"
            "_0_0_0_"
            "_00__0_"
            "__000__"
            "_______"

            // 1
            "_______"
            "__00___"
            "_0_0___"
            "___0___"
            "___0___"
            "_00000_"
            "_______"

            // 2
            "_______"
            "__000__"
            "_0___0_"
            "___00__"
            "__0____"
            "_00000_"
            "_______"

            // 3
            "_______"
            "__000__"
            "_____0_"
            "___00__"
            "_____0_"
            "__000__"
            "_______"

            // 4
            "_______"
            "___0___"
            "__00___"
            "_0_0___"
            "_00000_"
            "___0___"
            "_______"

            // 5
            "_______"
            "_00000_"
            "_0_____"
            "_0000__"
            "_____0_"
            "_0000__"
            "_______"

            // 6
            "_______"
            "__000__"
            "_0_____"
            "_0000__"
            "_0___0_"
            "__000__"
            "_______"

            // 7
            "_______"
            "_00000_"
            "____0__"
            "___0___"
            "__0____"
            "_0_____"
            "_______"
            
            // 8
            "_______"
            "__000__"
            "_0___0_"
            "__000__"
            "_0___0_"
            "__000__"
            "_______"

            // 9
            "_______"
            "__000__"
            "_0___0_"
            "__0000_"
            "_____0_"
            "__000__"
            "_______"

            // Space
            "_______"
            "_______"
            "_______"
            "_______"
            "_______"
            "_______"
            "_______"

            // Minus / Negative sign
            "_______"
            "_______"
            "_______"
            "_00000_"
            "_______"
            "_______"
            "_______"

            // Period / Decimal
            "_______"
            "_______"
            "_______"
            "_______"
            "__00___"
            "__00___"
            "_______"

            // Disallowed char
            "_______"
            "__000__"
            "_0_0_0_"
            "_00_00_"
            "_0_0_0_"
            "__000__"
            "_______"

        };

};

}
}
