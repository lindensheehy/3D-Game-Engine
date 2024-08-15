#include "../include/Drawer.h"


/* --------------------------- */
/* ---------- Color ---------- */
/* --------------------------- */

// Contructors
Color::Color(Uint32 color) {

    this->rawValue = color;

    // This gets the sub values at each 8 bit interval of the 32 bit input
    this->opacityValue = (Uint8) (color >> 24);
    this->redValue = (Uint8) (color >> 16);
    this->greenValue = (Uint8) (color >> 8);
    this->blueValue = (Uint8) (color);
}

Color::Color(Uint8 o, Uint8 r, Uint8 g, Uint8 b) {

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
Uint32 Color::setBrightness(Uint32 color, double newBrightness) {

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



/* ------------------------- */
/* ---------- PNG ---------- */
/* ------------------------- */

// Color indexes. Used to parse the return data from lodepng
const char PNG::RED = 0;
const char PNG::GREEN = 1;
const char PNG::BLUE = 2;
const char PNG::OPACITY = 3;

// Constructor from filename
PNG::PNG(const char* filename) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (fileName == nullptr) {
        logWrite("Called PNG->PNG(const char*) on a null pointer!", true);
        return;
    }

    std::vector<unsigned char> returnData;
    unsigned int failed = lodepng::decode(returnData, this->width, this->height, filename);

    if (failed) {
        std::cerr << "Error loading PNG file: " << lodepng_error_text(failed) << std::endl;
        return;
    }

    this->fileName = filename;
    int size = this->width * this->height;
    this->rawData = new Uint8[size * 4];
    this->pixels = new Color*[size];

    for (int i = 0; i < size * 4; i += 4) {

        Uint8 r = (Uint8) returnData[i];
        Uint8 g = (Uint8) returnData[i + 1];
        Uint8 b = (Uint8) returnData[i + 2];
        Uint8 o = (Uint8) returnData[i + 3];

        this->rawData[i] = r;
        this->rawData[i + 1] = g;
        this->rawData[i + 2] = b;
        this->rawData[i + 3] = o;

        this->pixels[i / 4] = new Color(o, r, g, b);

    }
    
    return;

}

// Constructor from other PNG object
PNG::PNG(PNG* input, int startx, int starty, int endx, int endy) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (input == nullptr) {
        logWrite("Called PNG->PNG(PNG*, int, int, int, int) on a null pointer!", true);
        return;
    }

    this->width = (endx - startx);
    this->height = (endy - starty);

    this->fileName = nullptr;
    int size = this->width * this->height;
    this->rawData = new Uint8[size * 4];
    this->pixels = new Color*[size];

    for (int i = 0; i < size; i += 1) {

        int x = ((i % this->width) + startx);
        int y = (int) (i / this->width) + (starty);

        Uint8 r = input->getChannel( x, y, RED);
        Uint8 g = input->getChannel( x, y, GREEN);
        Uint8 b = input->getChannel( x, y, BLUE);
        Uint8 o = input->getChannel( x, y, OPACITY);

        if (r == -1 || g == -1 || b == -1 || o == -1) {
            std::cout << "color channel failed to get" << std::endl;
            system("pause");
            return;
        }

        this->rawData[i * 4] = r;
        this->rawData[(i * 4) + 1] = g;
        this->rawData[(i * 4) + 2] = b;
        this->rawData[(i * 4) + 3] = o;

        this->pixels[i] = new Color(o, r, g, b);

    }
    
    return;

}

// Destructor
PNG::~PNG() {

    for (int i = 0; i < this->width * this-> height; i++) {
        delete this->pixels[i];
    }

    delete[] this->rawData;
    delete[] this->pixels;

    return;

}

// Instance Functions
Color* PNG::getPixel(int x, int y) {

    if (x >= this->width || y >= this->height) return nullptr;

    return this->pixels[ (this->width * y) + x ];

}

bool PNG::setPixel(int x, int y, Color* pixel) {

    if (x >= this->width || y >= this->height) return false;

    if (pixel == nullptr) return false;

    this->pixels[ (this->width * y) + x ] = pixel;

    return true;

}

Uint8 PNG::getChannel(int x, int y, char channel) {

    if (x >= this->width || y >= this->height) return -1;

    if (channel > 3 || channel < 0) return -1;

    return this->rawData[ (((this->width * y) + x) * 4) + channel];

}

bool PNG::setChannel(int x, int y, char channel, Uint8 value) {
    
    if (x >= this->width || y >= this->height) return false;

    if (channel > 3 || channel < 0) return false;

    this->rawData[ (((this->width * y) + x) * 4) + channel] = value;

    return true;

}



/* ---------------------------- */
/* ---------- Drawer ---------- */
/* ---------------------------- */

// Constructor
Drawer::Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput) {

    this->buffer = buffer;
    this->bufferWidth = bufferWidthInput;
    this->bufferHeight = bufferHeightInput;
    this->bufferSize = bufferHeightInput * bufferWidthInput;

    // Depth buffer
    this->depthBuffer = new double[this->bufferSize];
    for (int i = 0; i < this->bufferSize; i++) {
        this->depthBuffer[i] = inf;
    }

}

// Instance functions
int Drawer::bufferIndex(int x, int y) {

    if (x >= this->bufferWidth || x < 0) return -1;
    if (y >= this->bufferHeight || y < 0) return -1;

    return (y * this->bufferWidth) + x;

}

void Drawer::writePixel(Uint32 pixel, int x, int y) {

    if (this->buffer == nullptr) {
        return;
    }

    // Get index, and skip if its outside the buffer size
    int index = this->bufferIndex(x, y);
    if (index == -1) return;

    buffer[index] = pixel;

    return;
}

void Drawer::writePixel(Uint32 pixel, int x, int y, double depth) {

    if (this->buffer == nullptr) {
        return;
    }

    int index = this->bufferIndex(x, y);

    // Skip cases
    if (index == -1) return;
    if (depth > this->depthBuffer[index]) return;

    buffer[index] = pixel;

    return;
}

void Drawer::drawLine(Uint32 pixel, int x1, int y1, int x2, int y2) {

    if (this->buffer == nullptr) {
        return;
    }
    
    int distx = x2 - x1;
    int disty = y2 - y1;

    int totalDist = max(abs(distx), abs(disty));

    for (int i = 0; i < totalDist; i++) {
        int x = floor( (x1) + (distx * ( (double) i / totalDist)) );
        int y = floor( (y1) + (disty * ( (double) i / totalDist)) );
        this->writePixel(pixel, x, y);
    }

    return;

}

void Drawer::drawLine(Uint32 pixel, int x1, int y1, int x2, int y2, double depth1, double depth2) {

    if (this->buffer == nullptr) {
        return;
    }
    
    int distx = x2 - x1;
    int disty = y2 - y1;
    double distDepth = depth2 - depth1;

    int totalDist = max(abs(distx), abs(disty));

    for (int i = 0; i < totalDist; i++) {
        int x = floor( (x1) + (distx * ( (double) i / totalDist)) );
        int y = floor( (y1) + (disty * ( (double) i / totalDist)) );
        double d = (depth1) + (distDepth * ( (double) i / totalDist ));
        this->writePixel(pixel, x, y, d);
    }

    return;

}

void Drawer::drawLine(Uint32 pixel, Vec2* from, Vec2* to) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (from == nullptr) {
        logWrite("Called Drawer->drawLine(Uint32, Vec2*, Vec2*) with 'from' as a null pointer!", true);
        return;
    }

    if (to == nullptr) {
        logWrite("Called Drawer->drawLine(Uint32, Vec2*, Vec2*) with 'to' as a null pointer!", true);
        return;
    }

    this->drawLine(pixel, from->x, from->y, to->x, to->y);
    return;

}

void Drawer::drawLine(Uint32 pixel, Vec2* from, Vec2* to, double depth1, double depth2) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (from == nullptr) {
        logWrite("Called Drawer->drawLine(Uint32, Vec2*, Vec2*) with 'from' as a null pointer!", true);
        return;
    }

    if (to == nullptr) {
        logWrite("Called Drawer->drawLine(Uint32, Vec2*, Vec2*) with 'to' as a null pointer!", true);
        return;
    }

    this->drawLine(pixel, from->x, from->y, to->x, to->y, depth1, depth2);
    return;

}

void Drawer::drawVerticalLine(Uint32 pixel, int startY, int endY, int x) {
    for (int i = startY; i <= endY; i++) {
        this->writePixel(pixel, x, i);
    }
}

void Drawer::drawVerticalLine(Uint32 pixel, int startY, int endY, int x, double depth1, double depth2) {

    double distDepth = depth2 - depth1;

    for (int i = startY; i <= endY; i++) {
        double d = depth1 + (distDepth * ( (i - startY) / (endY - startY) ));
        this->writePixel(pixel, x, i, d);
    }
}

void Drawer::drawHorizontalLine(Uint32 pixel, int startX, int endX, int y) {
    for (int i = startX; i <= endX; i++) {
        this->writePixel(pixel, i, y);
    }
}

void Drawer::drawHorizontalLine(Uint32 pixel, int startX, int endX, int y, double depth1, double depth2) {

    double distDepth = depth2 - depth1;

    for (int i = startX; i <= endX; i++) {
        double d = depth1 + (distDepth * ( (i - startX) / (endX - startX) ));
        this->writePixel(pixel, i, y, d);
    }
}

void Drawer::drawRect(Uint32 pixel, int startx, int starty, int endx, int endy) {

    if (this->buffer == nullptr) {
        return;
    }

    int incerementI = 1;
    int incerementJ = 1;

    if ( startx > endx ) incerementI = -1;
    if ( starty > endy ) incerementJ = -1;

    for (int i = startx; i != endx; i += incerementI) {
        for (int j = starty; j != endy; j += incerementJ) {
            this->writePixel(pixel, i, j);
        }
    }

    return;
}

void Drawer::fillScreen(Uint32 pixel) {
    this->drawRect(pixel, 0, 0, this->bufferWidth, this->bufferHeight);
}

void Drawer::drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy) {

    int limit = radiusx * radiusy;
    double factorx = sqrt( radiusy / radiusx );
    double factory = 1 / factorx;

    for (int i = -radiusx; i < radiusx; i++) {
        for (int j = -radiusy; j < radiusy; j++) {

            if ( ((factorx * i) * (factorx * i)) + ((factory * j) * (factory * j)) < limit ) {
                this->writePixel(pixel, locationx + i, locationy + j);
            }
            
        }
    }
}

void Drawer::drawCircle(Uint32 pixel, int locationx, int locationy, int radius) {

    int limit = radius * radius;

    for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {

            if ( (i * i) + (j * j) < limit ) {
                this->writePixel(pixel, locationx + i, locationy + j);
            }
            
        }
    }
}

void Drawer::drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle
        First find where each point stands in relation to eachother, then from the lowest x go to the highest x
    */

    // When all 3 points have the same coordinates we just return and draw nothing
    if ( x1 == x2 && x2 == x3 && y1 == y2 && y2 == y3 ) return;

    // Cases where the 'triangle' should just be drawn as a line, meaning two verticies share the same coordinates
    if ( x1 == x2 && y1 == y2 ) {
        this->drawLine(pixel, x1, y1, x3, y3);
        return;
    }

    if ( x1 == x3 && y1 == y3 ) {
        this->drawLine(pixel, x1, y1, x2, y2);
        return;
    }

    if ( x2 == x3 && y2 == y3 ) {
        this->drawLine(pixel, x2, y2, x1, y1);
        return;
    }

    // Sort the coordinates by their x values from least to greatest (left to right)
    if (x2 < x1) {
        swap(&x1, &x2);
        swap(&y1, &y2);
    }

    if (x3 < x1) {
        swap(&x1, &x3);
        swap(&y1, &y3);
    }

    if (x3 < x2) {
        swap(&x2, &x3);
        swap(&y2, &y3);
    }

    // These are the y values the line will go to/from for each x
    // The doubles store the actual value, and the ints are rounded
    // The actual values may not actually be start and end as they say and might be backwards, thats why the min and max functions are used later
    int startY, endY;
    double actualStartY = y1;
    double actualEndY = y1;

    // Find slopes, 1e250 slope means that they have the same x value
    double slopeLeftMid;
    double slopeMidRight;
    double slopeLeftRight;

    // Slope between left-most point and the middle point
    if (x1 != x2) slopeLeftMid = ((double) (y2 - y1)) / (double) (x2 - x1);
    else slopeLeftMid = inf; // just a big number representing infinity

    // Slope between middle point and the right-most point
    if (x2 != x3) slopeMidRight = ((double) (y3 - y2)) / (double) (x3 - x2);
    else slopeMidRight = inf; // just a big number representing infinity

    // Slope between the left-most point and the right-most point
    if (x1 != x3) slopeLeftRight = ((double) (y3 - y1)) / (double) (x3 - x1);
    else slopeLeftRight = inf; // just a big number representing infinity

    // this checks if all the points have the same x coordinate and draws a single line accordingly
    // Since the points are sorted, if the lowest (left) and highest (right) have the same x, so does the middle
    if (slopeLeftRight == inf) {
        startY = min(min(y1, y2), y3);
        endY = max(max(y1, y2), y3);
        this->drawVerticalLine(pixel, startY, endY, x1);
        return;
    }

    // From left to right until the mid vertex is hit
    if (slopeLeftMid != inf) {
        for (int i = x1; i < x2; i++) {

            actualStartY += slopeLeftMid;
            actualEndY += slopeLeftRight;

            startY = min(actualStartY, actualEndY);
            endY = max(actualStartY, actualEndY);

            this->drawVerticalLine(pixel, startY, endY, i);

        }
    
    // When the two left points have the same x, the startY and endY need to be adjusted becuase the first loop was skipped
    } else {
        actualStartY = y2;
        actualEndY = y1;
    }
    
    // Carry on from the last loop
    if (slopeMidRight != inf) {
        for (int i = x2; i < x3; i++) {

            actualStartY += slopeMidRight;
            actualEndY += slopeLeftRight;

            startY = min(actualStartY, actualEndY);
            endY = max(actualStartY, actualEndY);

            this->drawVerticalLine(pixel, startY, endY, i);

        }
    }

    return;

}

void Drawer::drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, double depth1, double depth2, double depth3) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle
        First find where each point stands in relation to eachother, then from the lowest x go to the highest x
    */

    // When all 3 points have the same coordinates we just return and draw nothing
    if ( x1 == x2 && x2 == x3 && y1 == y2 && y2 == y3 ) return;

    // Cases where the 'triangle' should just be drawn as a line, meaning two verticies share the same coordinates
    if ( x1 == x2 && y1 == y2 ) {
        this->drawLine(pixel, x1, y1, x3, y3);
        return;
    }

    if ( x1 == x3 && y1 == y3 ) {
        this->drawLine(pixel, x1, y1, x2, y2);
        return;
    }

    if ( x2 == x3 && y2 == y3 ) {
        this->drawLine(pixel, x2, y2, x1, y1);
        return;
    }

    // Sort the coordinates by their x values from least to greatest (left to right)
    if (x2 < x1) {
        swap(&x1, &x2);
        swap(&y1, &y2);
    }

    if (x3 < x1) {
        swap(&x1, &x3);
        swap(&y1, &y3);
    }

    if (x3 < x2) {
        swap(&x2, &x3);
        swap(&y2, &y3);
    }

    // These are the y values the line will go to/from for each x
    // The doubles store the actual value, and the ints are rounded
    // The actual values may not actually be start and end as they say and might be backwards, thats why the min and max functions are used later
    int startY, endY;
    double actualStartY = y1;
    double actualEndY = y1;

    // Find slopes, 1e250 slope means that they have the same x value
    double slopeLeftMid;
    double slopeMidRight;
    double slopeLeftRight;

    // Slope between left-most point and the middle point
    if (x1 != x2) slopeLeftMid = ((double) (y2 - y1)) / (double) (x2 - x1);
    else slopeLeftMid = inf; // just a big number representing infinity

    // Slope between middle point and the right-most point
    if (x2 != x3) slopeMidRight = ((double) (y3 - y2)) / (double) (x3 - x2);
    else slopeMidRight = inf; // just a big number representing infinity

    // Slope between the left-most point and the right-most point
    if (x1 != x3) slopeLeftRight = ((double) (y3 - y1)) / (double) (x3 - x1);
    else slopeLeftRight = inf; // just a big number representing infinity

    // this checks if all the points have the same x coordinate and draws a single line accordingly
    // Since the points are sorted, if the lowest (left) and highest (right) have the same x, so does the middle
    if (slopeLeftRight == inf) {
        startY = min(min(y1, y2), y3);
        endY = max(max(y1, y2), y3);
        this->drawVerticalLine(pixel, startY, endY, x1);
        return;
    }

    // From left to right until the mid vertex is hit
    if (slopeLeftMid != inf) {
        for (int i = x1; i < x2; i++) {

            actualStartY += slopeLeftMid;
            actualEndY += slopeLeftRight;

            startY = min(actualStartY, actualEndY);
            endY = max(actualStartY, actualEndY);

            this->drawVerticalLine(pixel, startY, endY, i);

        }
    
    // When the two left points have the same x, the startY and endY need to be adjusted becuase the first loop was skipped
    } else {
        actualStartY = y2;
        actualEndY = y1;
    }
    
    // Carry on from the last loop
    if (slopeMidRight != inf) {
        for (int i = x2; i < x3; i++) {

            actualStartY += slopeMidRight;
            actualEndY += slopeLeftRight;

            startY = min(actualStartY, actualEndY);
            endY = max(actualStartY, actualEndY);

            this->drawVerticalLine(pixel, startY, endY, i);

        }
    }

    return;

}

void Drawer::drawTriangle(Uint32 pixel, Tri2* tri) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (tri == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) on a null pointer!", true);
        return;
    }

    if (tri->v1 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v1 as a null pointer", true);
        return;
    }

    if (tri->v2 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v2 as a null pointer", true);
        return;
    }

    if (tri->v3 == nullptr) {
        logWrite("Called Drawer->drawTriangle(Uint32, Tri2*) with tri->v3 as a null pointer", true);
        return;
    }
    
    int x1 = (int) round(tri->v1->x);
    int y1 = (int) round(tri->v1->y);
    int x2 = (int) round(tri->v2->x);
    int y2 = (int) round(tri->v2->y);
    int x3 = (int) round(tri->v3->x);
    int y3 = (int) round(tri->v3->y);

    this->drawTriangle(pixel, x1, y1, x2, y2, x3, y3);

    return;

}

void Drawer::drawpng(PNG* file, int x, int y) {

    if (x + file->width > bufferWidth) return;
    if (y + file->height > bufferHeight) return;
    
    if (this->buffer == nullptr) {
        return;
    }

    for (int i = x; i < (x + file->width); i++) {
        for (int j = y; j < (y + file->height); j++) {

            Color* pixel = file->getPixel(i - x, j - y);

            if (pixel->opacityValue != 0x00) {
                this->writePixel(pixel->rawValue, i, j);
            }

        }
    }
    
    return;
}



/* -------------------------- */
/* ---------- Font ---------- */
/* -------------------------- */

// Constructors
Font::Font() {
    this->drawer = nullptr;
}

Font::Font(Drawer* drawer) {
    this->drawer = drawer;
}

// Instance Functions
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
