#pragma once

#include "DrawerClass.h"
#include "ColorClass.h"

class Font {

    /*
        This class holds data to print text characters to the screen
        Before using, an instance must be made by referencing a drawer instance so that this class can actually draw
        The contructor here loads all the pixel arts for each text character
    */

    public:

        // Instance Variables
        Drawer* drawer;

        // Constructors
        Font();
        Font(Drawer* drawer);

        /*   Instance Functions   */

        // Loads the character pixel arts into memory
        void init();

        // Returns a pointer to the pixels for a character
        bool* getCharRef(char ch);
        bool* getCharRef(int num);

        // Draws a set of pixels to the screen. the other draw functions rely on this
        void drawPixels(bool* pixels, int x, int y, Uint32 color);

        // Draws a character to the screen, the upper left will be at (x, y)
        void drawChar(char ch, int x, int y, Uint32 color);

        // Draws a string to the screen, the top left will be at (x, y)
        void drawString(const char* string, int x, int y, Uint32 color);

        // Draws an integer value to the screen, the top left will be at (x, y)
        void drawInt(int num, int x, int y, Uint32 color);
    
    private:

        /*
            Character Pixel Arts
            This bool** type is a list of lists of bools.
            The primary list is length 38 for the amount of chars which can be drawn
            Each of the sub lists is length 49, which gives a 7x7 grid of pixels per char
            This list is filled by running init
        */

        bool** chars;

        // Here you can see the data which is used to create the bool lists
        // underscore is 0 (false) and 0 is 1 (true), the bool values coorespond to if they are shown or not when drawing
        // All the seperate strings here get put together by the compiler into one big string, so the /n chars are the seperators
        // | acts as a line end char
        // String length is: char size + 1 * char count + 1 = length 2110 
        const char* rawChars =

        // A
        "_______|"
        "__000__|"
        "_0___0_|"
        "_00000_|"
        "_0___0_|"
        "_0___0_|"
        "_______|"
        "\n"

        // B
        "_______|"
        "_0000__|"
        "_0___0_|"
        "_0000__|"
        "_0___0_|"
        "_0000__|"
        "_______|"
        "\n"

        // C
        "_______|"
        "__0000_|"
        "_0_____|"
        "_0_____|"
        "_0_____|"
        "__0000_|"
        "_______|"
        "\n"

        // D
        "_______|"
        "_0000__|"
        "_0___0_|"
        "_0___0_|"
        "_0___0_|"
        "_0000__|"
        "_______|"
        "\n"

        // E
        "_______|"
        "_00000_|"
        "_0_____|"
        "_0000__|"
        "_0_____|"
        "_00000_|"
        "_______|"
        "\n"

        // F
        "_______|"
        "_00000_|"
        "_0_____|"
        "_0000__|"
        "_0_____|"
        "_0_____|"
        "_______|"
        "\n"

        // G
        "_______|"
        "_00000_|"
        "_0_____|"
        "_0__00_|"
        "_0___0_|"
        "_00000_|"
        "_______|"
        "\n"

        // H
        "_______|"
        "_0___0_|"
        "_0___0_|"
        "_00000_|"
        "_0___0_|"
        "_0___0_|"
        "_______|"
        "\n"

        // I
        "_______|"
        "_00000_|"
        "___0___|"
        "___0___|"
        "___0___|"
        "_00000_|"
        "_______|"
        "\n"

        // J
        "_______|"
        "_00000_|"
        "___0___|"
        "___0___|"
        "___0___|"
        "_00____|"
        "_______|"
        "\n"

        // K
        "_______|"
        "_0___0_|"
        "_0__0__|"
        "_000___|"
        "_0__0__|"
        "_0___0_|"
        "_______|"
        "\n"

        // L
        "_______|"
        "_0_____|"
        "_0_____|"
        "_0_____|"
        "_0_____|"
        "_00000_|"
        "_______|"
        "\n"

        // M
        "_______|"
        "_0___0_|"
        "_00000_|"
        "_0_0_0_|"
        "_0___0_|"
        "_0___0_|"
        "_______|"
        "\n"

        // N
        "_______|"
        "_0___0_|"
        "_00__0_|"
        "_0_0_0_|"
        "_0__00_|"
        "_0___0_|"
        "_______|"
        "\n"

        // O
        "_______|"
        "__000__|"
        "_0___0_|"
        "_0___0_|"
        "_0___0_|"
        "__000__|"
        "_______|"
        "\n"

        // P
        "_______|"
        "_0000__|"
        "_0___0_|"
        "_0000__|"
        "_0_____|"
        "_0_____|"
        "_______|"
        "\n"

        // Q
        "_______|"
        "__000__|"
        "_0___0_|"
        "_0___0_|"
        "__000__|"
        "____00_|"
        "_______|"
        "\n"

        // R
        "_______|"
        "_0000__|"
        "_0___0_|"
        "_0000__|"
        "_0__0__|"
        "_0___0_|"
        "_______|"
        "\n"

        // S
        "_______|"
        "__0000_|"
        "_0_____|"
        "__000__|"
        "_____0_|"
        "_0000__|"
        "_______|"
        "\n"

        // T
        "_______|"
        "_00000_|"
        "___0___|"
        "___0___|"
        "___0___|"
        "___0___|"
        "_______|"
        "\n"

        // U
        "_______|"
        "_0___0_|"
        "_0___0_|"
        "_0___0_|"
        "_0___0_|"
        "__000__|"
        "_______|"
        "\n"

        // V
        "_______|"
        "_0___0_|"
        "_0___0_|"
        "_0___0_|"
        "__0_0__|"
        "___0___|"
        "_______|"
        "\n"

        // W
        "_______|"
        "_0___0_|"
        "_0___0_|"
        "_0_0_0_|"
        "_00_00_|"
        "_0___0_|"
        "_______|"
        "\n"

        // X
        "_______|"
        "_0___0_|"
        "__0_0__|"
        "___0___|"
        "__0_0__|"
        "_0___0_|"
        "_______|"
        "\n"

        // Y
        "_______|"
        "_0___0_|"
        "__0_0__|"
        "___0___|"
        "___0___|"
        "___0___|"
        "_______|"
        "\n"

        // Z
        "_______|"
        "_00000_|"
        "____0__|"
        "___0___|"
        "__0____|"
        "_00000_|"
        "_______|"
        "\n"

        // 0
        "_______|"
        "__000__|"
        "_0__00_|"
        "_0_0_0_|"
        "_00__0_|"
        "__000__|"
        "_______|"
        "\n"

        // 1
        "_______|"
        "__00___|"
        "_0_0___|"
        "___0___|"
        "___0___|"
        "_00000_|"
        "_______|"
        "\n"

        // 2
        "_______|"
        "__000__|"
        "_0___0_|"
        "___00__|"
        "__0____|"
        "_00000_|"
        "_______|"
        "\n"

        // 3
        "_______|"
        "__000__|"
        "_____0_|"
        "___00__|"
        "_____0_|"
        "__000__|"
        "_______|"
        "\n"

        // 4
        "_______|"
        "___0___|"
        "__00___|"
        "_0_0___|"
        "_00000_|"
        "___0___|"
        "_______|"
        "\n"

        // 5
        "_______|"
        "_00000_|"
        "_0_____|"
        "_0000__|"
        "_____0_|"
        "_0000__|"
        "_______|"
        "\n"

        // 6
        "_______|"
        "__000__|"
        "_0_____|"
        "_0000__|"
        "_0___0_|"
        "__000__|"
        "_______|"
        "\n"

        // 7
        "_______|"
        "_00000_|"
        "____0__|"
        "___0___|"
        "__0____|"
        "_0_____|"
        "_______|"
        "\n"
        
        // 8
        "_______|"
        "__000__|"
        "_0___0_|"
        "__000__|"
        "_0___0_|"
        "__000__|"
        "_______|"
        "\n"

        // 9
        "_______|"
        "__000__|"
        "_0___0_|"
        "__0000_|"
        "_____0_|"
        "__000__|"
        "_______|"
        "\n"

        // Space
        "_______|"
        "_______|"
        "_______|"
        "_______|"
        "_______|"
        "_______|"
        "_______|"
        "\n"

        // Disallowed char
        "_______|"
        "_00000_|"
        "_00_00_|"
        "_0_0_0_|"
        "_00_00_|"
        "_00000_|"
        "_______|"
        "\n"

        ;
};