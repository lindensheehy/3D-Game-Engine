#include "../class-headers/FontClass.h"

Font::Font() {
    this->drawer = nullptr;
}

Font::Font(Drawer* drawer) {
    this->drawer = drawer;
}

void Font::init() {

    this->chars = new bool*[38];

    for (int i = 0; i < 38; i++) {
        this->chars[i] = new bool[49];
    }

    int index1 = 0;
    int index2 = 0;

    for (int i = 0; i < 2167; i++) {

        switch (this->rawChars[i]) {
            
            // false pixel
            case '_':
                this->chars[index1][index2] = false;
                index2++;
                break;

            // true pixel
            case '0':
                this->chars[index1][index2] = true;
                index2++;
                break;

            // End of the horizontal line of pixels
            case '|':
                // Just realised theres no reason for these
                break;

            // End of the char
            case '\n':
                index2 = 0;
                index1++;
                break;

            // This is the string end char
            case '\0':
                return;

        }

    }

    return;

}

bool* Font::getCharRef(char ch) {

    switch (ch) {

        case 'a':
        case 'A':
            return this->chars[0];

        case 'b':
        case 'B':
            return this->chars[1];

        case 'c':
        case 'C':
            return this->chars[2];

        case 'd':
        case 'D':
            return this->chars[3];

        case 'e':
        case 'E':
            return this->chars[4];

        case 'f':
        case 'F':
            return this->chars[5];

        case 'g':
        case 'G':
            return this->chars[6];

        case 'h':
        case 'H':
            return this->chars[7];

        case 'i':
        case 'I':
            return this->chars[8];

        case 'j':
        case 'J':
            return this->chars[9];

        case 'k':
        case 'K':
            return this->chars[10];

        case 'l':
        case 'L':
            return this->chars[11];

        case 'm':
        case 'M':
            return this->chars[12];

        case 'n':
        case 'N':
            return this->chars[13];

        case 'o':
        case 'O':
            return this->chars[14];

        case 'p':
        case 'P':
            return this->chars[15];

        case 'q':
        case 'Q':
            return this->chars[16];

        case 'r':
        case 'R':
            return this->chars[17];

        case 's':
        case 'S':
            return this->chars[18];

        case 't':
        case 'T':
            return this->chars[19];

        case 'u':
        case 'U':
            return this->chars[20];

        case 'v':
        case 'V':
            return this->chars[21];

        case 'w':
        case 'W':
            return this->chars[22];

        case 'x':
        case 'X':
            return this->chars[23];

        case 'y':
        case 'Y':
            return this->chars[24];

        case 'z':
        case 'Z':
            return this->chars[25];

        case '0':
            return this->chars[26];

        case '1':
            return this->chars[27];

        case '2':
            return this->chars[28];

        case '3':
            return this->chars[29];

        case '4':
            return this->chars[30];

        case '5':
            return this->chars[31];

        case '6':
            return this->chars[32];

        case '7':
            return this->chars[33];

        case '8':
            return this->chars[34];

        case '9':
            return this->chars[35];      

        case ' ':
            return this->chars[36];

        default:
            return this->chars[37];
        
    }

}

bool* Font::getCharRef(int num) {

    switch (num) {

        case 0:
            return this->chars[26];

        case 1:
            return this->chars[27];

        case 2:
            return this->chars[28];

        case 3:
            return this->chars[29];

        case 4:
            return this->chars[30];

        case 5:
            return this->chars[31];

        case 6:
            return this->chars[32];

        case 7:
            return this->chars[33];

        case 8:
            return this->chars[34];

        case 9:
            return this->chars[35];      

        default:
            return this->chars[37];
        
    }

}

void Font::drawPixels(bool* pixels, int x, int y, Uint32 color) {

    if (pixels == nullptr) return;
    
    int dx = 0;
    int dy = 0;

    for (int i = 0; i < 49; i++) {

        if (pixels[i])
            this->drawer->writePixel(color, x + dx, y + dy);

        dx++;
        if (dx > 6) {
            dx = 0;
            dy++;
        }

    }

}

void Font::drawChar(char ch, int x, int y, Uint32 color) {

    if (this->drawer == nullptr) return;

    bool* pixels = this->getCharRef(ch);

    this->drawPixels(pixels, x, y, color);

}

void Font::drawString(const char* string, int x, int y, Uint32 color) {

    if (this->drawer == nullptr) return;

    int dx = 0;

    for (int i = 0; string[i] != '\0'; i++) {

        this->drawChar(string[i], x + dx, y, color);
        dx += 6;

    }
    
}

void Font::drawInt(int num, int x, int y, Uint32 color) {

    double a = (double) num;
    int b; // for casting a into
    int counter = 0;

    int dx = 0;

    while (a > 1) {
        a /= 10;
        counter++;
    }

    for (; counter != 0; counter--) {

        // Add the next digit of num
        a *= 10;
        b = (int) a;

        // Get last digit
        b %= 10;

        bool* pixels = this->getCharRef(b);

        this->drawPixels(pixels, x + dx, y, color);
        dx += 6;

    }

}
