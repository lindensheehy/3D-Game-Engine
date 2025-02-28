#include "gui/Drawer.h"


/* --------------------------- */
/* ---------- Color ---------- */
/* --------------------------- */

// Contructors
Color::Color(uint32 color) {

    this->rawValue = color;

    // This gets the sub values at each 8 bit interval of the 32 bit input
    this->opacityValue = (uint8) (color >> 24);
    this->redValue = (uint8) (color >> 16);
    this->greenValue = (uint8) (color >> 8);
    this->blueValue = (uint8) (color);
}

Color::Color(uint8 o, uint8 r, uint8 g, uint8 b) {

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
uint32 Color::setBrightness(uint32 color, float newBrightness) {

    // Unpack color code
    uint8 opacityValue = (uint8) (color >> 24);
    uint8 redValue = (uint8) (color >> 16);
    uint8 greenValue = (uint8) (color >> 8);
    uint8 blueValue = (uint8) (color);

    // Update values
    redValue *= newBrightness;
    greenValue *= newBrightness;
    blueValue *= newBrightness;

    // Repack color code
    uint32 newColor = 0x00000000;
    newColor |= opacityValue;
    newColor <<= 8;
    newColor |= redValue;
    newColor <<= 8;
    newColor |= greenValue;
    newColor <<= 8;
    newColor |= blueValue;

    return newColor;

}

uint32 Color::merge(uint32 color1, float opacity1, uint32 color2, float opacity2) {

    // Unpack color codes
    uint8 redValue1 = (uint8) (color1 >> 16);
    uint8 greenValue1 = (uint8) (color1 >> 8);
    uint8 blueValue1 = (uint8) (color1);

    uint8 redValue2 = (uint8) (color2 >> 16);
    uint8 greenValue2 = (uint8) (color2 >> 8);
    uint8 blueValue2 = (uint8) (color2);

    // Downscale values accordingly, ignoring opacityValue
    redValue1 *= opacity1;
    greenValue1 *= opacity1;
    blueValue1 *= opacity1;

    redValue2 *= opacity2;
    greenValue2 *= opacity2;
    blueValue2 *= opacity2;

    // Get resulting color codes, using the first set to store this to avoid unnecessary variables
    redValue1 += redValue2;
    greenValue1 += greenValue2;
    blueValue1 += blueValue2;

    // Pack resulting color code
    uint32 newColor = 0x0000FF00; // This FF will become the opacity value after the bit shifts
    newColor |= redValue1;
    newColor <<= 8;
    newColor |= greenValue1;
    newColor <<= 8;
    newColor |= blueValue1;

    return newColor;

}


/* ------------------------- */
/* ---------- PNG ---------- */
/* ------------------------- */

// Constructor from filename
PNG::PNG(const char* filename) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (fileName == nullptr) {
        logWrite("Called PNG->PNG(const char*) on a null pointer!", true);
        return;
    }

    // Not implemented yet

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
    this->rawData = new uint8[size * 4];
    this->pixels = new Color*[size];

    for (int i = 0; i < size; i += 1) {

        int x = ((i % this->width) + startx);
        int y = (int) (i / this->width) + (starty);

        uint8 r = input->getChannel( x, y, RED);
        uint8 g = input->getChannel( x, y, GREEN);
        uint8 b = input->getChannel( x, y, BLUE);
        uint8 o = input->getChannel( x, y, OPACITY);

        if (r == -1 || g == -1 || b == -1 || o == -1) {
            logWrite("color channel failed to get", true);

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

uint8 PNG::getChannel(int x, int y, char channel) {

    if (x >= this->width || y >= this->height) return -1;

    if (channel > 3 || channel < 0) return -1;

    return this->rawData[ (((this->width * y) + x) * 4) + channel];

}

bool PNG::setChannel(int x, int y, char channel, uint8 value) {
    
    if (x >= this->width || y >= this->height) return false;

    if (channel > 3 || channel < 0) return false;

    this->rawData[ (((this->width * y) + x) * 4) + channel] = value;

    return true;

}



/* ---------------------------- */
/* ---------- Drawer ---------- */
/* ---------------------------- */

// Constructors
Drawer::Drawer(Display* display) {

    this->buffer = nullptr;
    this->bufferWidth = display->width;
    this->bufferHeight = display->height;
    this->bufferSize = display->width * display->height;

    // Depth buffer
    this->fullDepthBuffer = new float[this->maxBufferIndex];
    for (int i = 0; i < this->maxBufferIndex; i++)
        this->fullDepthBuffer[i] = inf;

    this->depthBuffer = this->fullDepthBuffer;

    this->chars = nullptr;

}

Drawer::Drawer(uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput) {

    this->buffer = buffer;
    this->bufferWidth = bufferWidthInput;
    this->bufferHeight = bufferHeightInput;
    this->bufferSize = bufferHeightInput * bufferWidthInput;

    // Depth buffer
    this->fullDepthBuffer = new float[this->maxBufferIndex];
    for (int i = 0; i < this->maxBufferIndex; i++)
        this->depthBuffer[i] = inf;

    this->depthBuffer = this->fullDepthBuffer;

    this->chars = nullptr;

}

// Destructor
Drawer::~Drawer() {

    delete[] this->fullDepthBuffer;

    for (int i = 0; i < 38; i++) {
        if (this->chars[i] != nullptr) delete[] this->chars[i];
    }

    delete[] this->chars;

}

// Instance functions
void Drawer::updateDimensions(int width, int height) {

    if (width > PIXEL_BUFFER_WIDTH) {
        logWrite("Drawer::updateBounds() tried to set the width beyond the max range!", true);
        logWrite(" -> Tried to set ");
        logWrite(width);
        logWrite(" while the max allowed is ");
        logWrite(PIXEL_BUFFER_WIDTH, true);
        return;
    }

    if (height > PIXEL_BUFFER_HEIGHT) {
        logWrite("Drawer::updateBounds() tried to set the height beyond the max range!", true);
        logWrite(" -> Tried to set ");
        logWrite(height);
        logWrite(" while the max allowed is ");
        logWrite(PIXEL_BUFFER_HEIGHT, true);
        return;
    }

    this->bufferWidth = width;
    this->bufferHeight = height;
    this->bufferSize = width * height;

    return;

}

void Drawer::resetDepthBuffer() {

    int index;

    for (int x = 0; x < this->bufferWidth; x++) {
        for (int y = 0; y < this->bufferHeight; y++) {
            
            index = this->bufferIndex(x, y);

            this->depthBuffer[index] = inf;

        }
    }

    return;

}

int Drawer::bufferIndex(int x, int y) const {

    if (!this->inBufferRange(x, y)) return -1;

    return (y * PIXEL_BUFFER_WIDTH) + x;

}

bool Drawer::inBufferRange(int x, int y) const {

    return (
        x >= 0 &&
        x < this->bufferWidth &&
        y >= 0 &&
        y < this->bufferHeight
    );

}

void Drawer::clipCoordinates(int* x, int* y) const {

    if (x == nullptr) return;
    if (y == nullptr) return;

    if ( (*x) < 0 ) (*x) = 0;
    if ( (*y) < 0 ) (*y) = 0;

    if ( (*x) >= this->bufferWidth ) (*x) = this->bufferWidth - 1;
    if ( (*y) >= this->bufferHeight ) (*y) = this->bufferHeight - 1;

    return;

}

void Drawer::writePixel(uint32 pixel, int x, int y) {

    if (this->buffer == nullptr) {
        return;
    }

    // Get index, and skip if its outside the buffer size
    int index = this->bufferIndex(x, y);
    if (index == -1) return;

    this->buffer[index] = pixel;

    return;
    
}

void Drawer::writePixel(uint32 pixel, int x, int y, float depth) {

    if (this->buffer == nullptr) {
        return;
    }

    int index = this->bufferIndex(x, y);
    if (index == -1) return;

    if (depth > this->depthBuffer[index]) return;

    this->buffer[index] = pixel;
    this->depthBuffer[index] = depth;

    return;

}

void Drawer::writePixel(uint32 pixel, int x, int y, float depth, float opacity) {

    if (this->buffer == nullptr) {
        return;
    }

    int index = this->bufferIndex(x, y);
    if (index == -1) return;

    if (depth > this->depthBuffer[index]) return;

    // Find effective color based on pixel color, opacity, and color behind
    uint32 originalPixel = this->buffer[index];
    uint32 result = Color::merge(pixel, opacity, originalPixel, 1 - opacity);

    this->buffer[index] = result;

    return;

}

void Drawer::drawLine(uint32 pixel, int x1, int y1, int x2, int y2) {

    if (this->buffer == nullptr) {
        return;
    }
    
    int distx = x2 - x1;
    int disty = y2 - y1;

    int totalDist = max(abs(distx), abs(disty));

    for (int i = 0; i < totalDist; i++) {
        int x = floor( (x1) + (distx * ( (float) i / totalDist)) );
        int y = floor( (y1) + (disty * ( (float) i / totalDist)) );
        this->writePixel(pixel, x, y);
    }

    return;

}

void Drawer::drawLine(uint32 pixel, int x1, int y1, int x2, int y2, float depth1, float depth2) {

    if (this->buffer == nullptr) {
        return;
    }
    
    int distx = x2 - x1;
    int disty = y2 - y1;
    float distDepth = depth2 - depth1;

    int totalDist = max(abs(distx), abs(disty));

    for (int i = 0; i < totalDist; i++) {
        int x = floor( (x1) + (distx * ( (float) i / totalDist)) );
        int y = floor( (y1) + (disty * ( (float) i / totalDist)) );
        float d = (depth1) + (distDepth * ( (float) i / totalDist ));
        this->writePixel(pixel, x, y, d);
    }

    return;

}

void Drawer::drawLine(uint32 pixel, int x1, int y1, int x2, int y2, float depth1, float depth2, float opacity) {

    if (this->buffer == nullptr) {
        return;
    }
    
    int distx = x2 - x1;
    int disty = y2 - y1;
    float distDepth = depth2 - depth1;

    int totalDist = max(abs(distx), abs(disty));

    for (int i = 0; i < totalDist; i++) {
        int x = floor( (x1) + (distx * ( (float) i / totalDist)) );
        int y = floor( (y1) + (disty * ( (float) i / totalDist)) );
        float d = (depth1) + (distDepth * ( (float) i / totalDist ));
        this->writePixel(pixel, x, y, d, opacity);
    }

    return;

}

void Drawer::drawLine(uint32 pixel, Vec2* from, Vec2* to) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (from == nullptr) {
        logWrite("Called Drawer->drawLine(uint32, Vec2*, Vec2*) with 'from' as a null pointer!", true);
        return;
    }

    if (to == nullptr) {
        logWrite("Called Drawer->drawLine(uint32, Vec2*, Vec2*) with 'to' as a null pointer!", true);
        return;
    }

    this->drawLine(pixel, from->x, from->y, to->x, to->y);
    return;

}

void Drawer::drawLine(uint32 pixel, Vec2* from, Vec2* to, float depth1, float depth2) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (from == nullptr) {
        logWrite("Called Drawer->drawLine(uint32, Vec2*, Vec2*) with 'from' as a null pointer!", true);
        return;
    }

    if (to == nullptr) {
        logWrite("Called Drawer->drawLine(uint32, Vec2*, Vec2*) with 'to' as a null pointer!", true);
        return;
    }

    this->drawLine(pixel, from->x, from->y, to->x, to->y, depth1, depth2);
    return;

}

void Drawer::drawLine(uint32 pixel, Vec2* from, Vec2* to, float depth1, float depth2, float opacity) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (from == nullptr) {
        logWrite("Called Drawer->drawLine(uint32, Vec2*, Vec2*) with 'from' as a null pointer!", true);
        return;
    }

    if (to == nullptr) {
        logWrite("Called Drawer->drawLine(uint32, Vec2*, Vec2*) with 'to' as a null pointer!", true);
        return;
    }

    this->drawLine(pixel, from->x, from->y, to->x, to->y, depth1, depth2, opacity);
    return;

}

void Drawer::drawVerticalLine(uint32 pixel, int y1, int y2, int x) {

    // Skip if this line lies outside the screen horizontally
    if (!this->inBufferRange(x, 0)) return;

    // Clip y values to lie within the buffer
    this->clipCoordinates(&x, &y1);
    this->clipCoordinates(&x, &y2);

    if (y1 > y2) {
        swap(&y1, &y2);
    }

    for (int i = y1; i <= y2; i++) {
        this->writePixel(pixel, x, i);
    }

}

void Drawer::drawVerticalLine(uint32 pixel, int y1, int y2, int x, float depth1, float depth2) {

    // Skip if this line lies outside the screen horizontally
    if (!this->inBufferRange(x, 0)) return;

    // Clip y values to lie within the buffer
    this->clipCoordinates(&x, &y1);
    this->clipCoordinates(&x, &y2);

    if (y1 == y2) {
        float d = min(depth1, depth2);
        this->writePixel(pixel, x, y1, d);
        return;
    }

    float depthSlope;
    float d;

    if (y1 < y2) {

        depthSlope = (depth2 - depth1) / (y2 - y1);
        d = depth1;

        for (int i = y1; i <= y2; i++) {
            this->writePixel(pixel, x, i, d);
            d += depthSlope;
        }


    }

    else {

        depthSlope = (depth1 - depth2) / (y1 - y2);
        d = depth2;

        for (int i = y2; i <= y1; i++) {
            this->writePixel(pixel, x, i, d);
            d += depthSlope;
        }


    }

}

void Drawer::drawVerticalLine(uint32 pixel, int y1, int y2, int x, float depth1, float depth2, float opacity) {

    // Skip if this line lies outside the screen horizontally
    if (!this->inBufferRange(x, 0)) return;

    // Clip y values to lie within the buffer
    this->clipCoordinates(&x, &y1);
    this->clipCoordinates(&x, &y2);

    if (y1 == y2) {
        float d = min(depth1, depth2);
        this->writePixel(pixel, x, y1, d, opacity);
        return;
    }

    float depthSlope;
    float d;

    if (y1 < y2) {

        depthSlope = (depth2 - depth1) / (y2 - y1);
        d = depth1;

        for (int i = y1; i <= y2; i++) {
            this->writePixel(pixel, x, i, d, opacity);
            d += depthSlope;
        }


    }

    else {

        depthSlope = (depth1 - depth2) / (y1 - y2);
        d = depth2;

        for (int i = y2; i <= y1; i++) {
            this->writePixel(pixel, x, i, d, opacity);
            d += depthSlope;
        }


    }

}

void Drawer::drawHorizontalLine(uint32 pixel, int x1, int x2, int y) {

    if (x1 > x2) {
        swap(&x1, &x2);
    }

    for (int i = x1; i <= x2; i++) {
        this->writePixel(pixel, i, y);
    }

}

void Drawer::drawHorizontalLine(uint32 pixel, int x1, int x2, int y, float depth1, float depth2) {

    // Skip if coordinates are out of range
    if (!this->inBufferRange(x1, y) && !this->inBufferRange(x2, y)) return;

    if (x1 == x2) {
        float d = min(depth1, depth2);
        this->writePixel(pixel, x1, y, d);
        return;
    }

    float depthSlope;
    float d;

    if (x1 < x2) {

        depthSlope = (depth2 - depth1) / (x2 - x1);
        d = depth1;

        for (int i = x1; i <= x2; i++) {
            this->writePixel(pixel, i, y, d);
            d += depthSlope;
        }


    }

    else {

        depthSlope = (depth1 - depth2) / (x1 - x2);
        d = depth2;

        for (int i = x2; i <= x1; i++) {
            this->writePixel(pixel, i, y, d);
            d += depthSlope;
        }


    }

}

void Drawer::drawHorizontalLine(uint32 pixel, int x1, int x2, int y, float depth1, float depth2, float opacity) {

    // Skip if coordinates are out of range
    if (!this->inBufferRange(x1, y) && !this->inBufferRange(x2, y)) return;

    if (x1 == x2) {
        float d = min(depth1, depth2);
        this->writePixel(pixel, x1, y, d, opacity);
        return;
    }

    float depthSlope;
    float d;

    if (x1 < x2) {

        depthSlope = (depth2 - depth1) / (x2 - x1);
        d = depth1;

        for (int i = x1; i <= x2; i++) {
            this->writePixel(pixel, i, y, d, opacity);
            d += depthSlope;
        }


    }

    else {

        depthSlope = (depth1 - depth2) / (x1 - x2);
        d = depth2;

        for (int i = x2; i <= x1; i++) {
            this->writePixel(pixel, i, y, d, opacity);
            d += depthSlope;
        }


    }
    
}

void Drawer::drawRect(uint32 pixel, int x1, int y1, int x2, int y2) {

    if (this->buffer == nullptr) {
        return;
    }

    this->drawVerticalLine(pixel, y1, y2, x1);
    this->drawVerticalLine(pixel, y1, y2, x2);
    this->drawHorizontalLine(pixel, x1, x2, y1);
    this->drawHorizontalLine(pixel, x1, x2, y2);

    return;

}

void Drawer::drawRect(uint32 pixel, Vec2* pos1, Vec2* pos2) {

    this->drawRect(pixel, pos1->x, pos1->y, pos2->x, pos2->y);

    return;
    
}

void Drawer::drawRectFilled(uint32 pixel, int x1, int y1, int x2, int y2) {

    if (this->buffer == nullptr) {
        return;
    }

    int incerementI = 1;
    int incerementJ = 1;

    if ( x1 > x2 ) incerementI = -1;
    if ( y1 > y2 ) incerementJ = -1;

    for (int i = x1; i != x2; i += incerementI) {
        for (int j = y1; j != y2; j += incerementJ) {
            this->writePixel(pixel, i, j);
        }
    }

    return;

}

void Drawer::drawRectFilled(uint32 pixel, Vec2* pos1, Vec2* pos2) {

    this->drawRectFilled(pixel, pos1->x, pos1->y, pos2->x, pos2->y);

    return;
    
}

void Drawer::fillScreen(uint32 pixel) {
    this->drawRectFilled(pixel, 0, 0, this->bufferWidth, this->bufferHeight);
}

void Drawer::drawElipse(uint32 pixel, int locationx, int locationy, int radiusx, int radiusy) {

    int limit = radiusx * radiusy;
    float factorx = sqrt( (float) (radiusy / radiusx) );
    float factory = 1 / factorx;

    for (int i = -radiusx; i < radiusx; i++) {
        for (int j = -radiusy; j < radiusy; j++) {

            if ( ((factorx * i) * (factorx * i)) + ((factory * j) * (factory * j)) < limit ) {
                this->writePixel(pixel, locationx + i, locationy + j);
            }
            
        }
    }
}

void Drawer::drawElipse(uint32 pixel, int locationx, int locationy, int radiusx, int radiusy, float depth) {

    int limit = radiusx * radiusy;
    float factorx = sqrt( (float) (radiusy / radiusx) );
    float factory = 1 / factorx;

    for (int i = -radiusx; i < radiusx; i++) {
        for (int j = -radiusy; j < radiusy; j++) {

            if ( ((factorx * i) * (factorx * i)) + ((factory * j) * (factory * j)) < limit ) {
                this->writePixel(pixel, locationx + i, locationy + j, depth);
            }
            
        }
    }
}

void Drawer::drawCircle(uint32 pixel, int x, int y, int radius) {

    int limit = radius * radius;

    for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {

            if ( (i * i) + (j * j) < limit ) {
                this->writePixel(pixel, x + i, y + j);
            }
            
        }
    }
}

void Drawer::drawCircle(uint32 pixel, Vec2* pos, int radius) {

    this->drawCircle(pixel, pos->x, pos->y, radius);

}

void Drawer::drawCircle(uint32 pixel, int x, int y, int radius, float depth) {

    int limit = radius * radius;

    for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {

            if ( (i * i) + (j * j) < limit ) {
                this->writePixel(pixel, x + i, y + j, depth);
            }
            
        }
    }
}

void Drawer::drawCircle(uint32 pixel, Vec2* pos, int radius, float depth) {

    this->drawCircle(pixel, pos->x, pos->y, radius, depth);

}

void Drawer::drawTriangle(uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3) {

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
    // The floats store the actual value, and the ints are rounded
    // The actual values may not actually be start and end as they say and might be backwards, thats why the min and max functions are used later
    int startY, endY;
    float actualStartY = y1;
    float actualEndY = y1;

    // Find slopes, 1e250 slope means that they have the same x value
    float slopeLeftMid;
    float slopeMidRight;
    float slopeLeftRight;

    // Slope between left-most point and the middle point
    if (x1 != x2) slopeLeftMid = ((float) (y2 - y1)) / (float) (x2 - x1);
    else slopeLeftMid = inf; // just a big number representing infinity

    // Slope between middle point and the right-most point
    if (x2 != x3) slopeMidRight = ((float) (y3 - y2)) / (float) (x3 - x2);
    else slopeMidRight = inf; // just a big number representing infinity

    // Slope between the left-most point and the right-most point
    if (x1 != x3) slopeLeftRight = ((float) (y3 - y1)) / (float) (x3 - x1);
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

            startY = round(actualStartY);
            endY = round(actualEndY);

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

            startY = round(actualStartY);
            endY = round(actualEndY);

            this->drawVerticalLine(pixel, startY, endY, i);

        }
    }

    return;

}

void Drawer::drawTriangle(uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, float depth1, float depth2, float depth3) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle
        First find where each point stands in relation to eachother, then from the lowest x go to the highest x
    */
  

    bool oneIsTwo = (x1 == x2) && (y1 == y2);
    bool twoIsThree = (x2 == x3) && (y2 == y3);
    bool oneIsThree = (x1 == x3) && (y1 == y3);

    // Cases where the 'triangle' has more than one point with the same coordinates, so these are checked here for quick handling
    if ( oneIsTwo ) {

        // If two also equals three, all three coordinates are the same, so just return.
        // I should draw a single pixel in this case, but its not really worth it as it will barely be noticable
        if (twoIsThree) return;

        this->drawLine(pixel, x1, y1, x3, y3, depth1, depth3);
        return;

    }

    // Either of these cases draw the same line
    if ( oneIsThree || twoIsThree) {
        this->drawLine(pixel, x1, y1, x2, y2, depth1, depth2);
        return;
    }


    // Sort the coordinates by their x values from least to greatest (left to right)
    if (x2 < x1) {
        swap(&x1, &x2);
        swap(&y1, &y2);
        swap(&depth1, &depth2);
    }

    if (x3 < x1) {
        swap(&x1, &x3);
        swap(&y1, &y3);
        swap(&depth1, &depth3);
    }

    if (x3 < x2) {
        swap(&x2, &x3);
        swap(&y2, &y3);
        swap(&depth2, &depth3);
    }

    // These are the y values the line will go to/from for each x
    // The floats store the actual value, and the ints are rounded
    // The actual values may not actually be start and end as they say and might be backwards
    float startY = (float) y1;
    float endY = (float) y1;
    int startYInt, endYInt;

    float slope12;
    float slope23;
    float slope13;

    float startDepth = depth1;
    float endDepth = depth1;

    float slopeDepth12;
    float slopeDepth23;
    float slopeDepth13;

    bool invalidSlope12 = false;
    bool invalidSlope23 = false;
    bool invalidSlope13 = false;


    // Slope between left-most point and the middle point
    if (x1 != x2) {
        slope12 = (float) (y2 - y1) / (x2 - x1);
        slopeDepth12 = (depth2 - depth1) / (x2 - x1);
    }

    else invalidSlope12 = true;

    // Slope between middle point and the right-most point
    if (x2 != x3) {
        slope23 = (float) (y3 - y2) / (x3 - x2);
        slopeDepth23 = (depth3 - depth2) / (x3 - x2);
    }

    else invalidSlope23 = true;

    // Slope between the left-most point and the right-most point
    if (x1 != x3) {
        slope13 = (float) (y3 - y1) / (x3 - x1);
        slopeDepth13 = (depth3 - depth1) / (x3 - x1);
    }

    else invalidSlope13 = true;


    // this checks if all the points have the same x coordinate and draws a single line accordingly (in two parts)
    // If the slope between 1 and 2, and the slope between 2 and 3 are both inf, theres no need to check the slope between 1 and 3.
    if (invalidSlope13) {

        if (y1 < y2)
            this->drawVerticalLine(pixel, y1, y2, x1, depth1, depth2);
        else
            this->drawVerticalLine(pixel, y2, y1, x1, depth2, depth1);

        if (y2 < y3)
            this->drawVerticalLine(pixel, y2, y3, x1, depth2, depth3);
        else
            this->drawVerticalLine(pixel, y3, y2, x1, depth3, depth2);

        return;

    }

    // From left to right until the mid vertex is hit
    if (!invalidSlope12) {

        for (int i = x1; i < x2; i++) {

            startY += slope12;
            endY += slope13;

            startYInt = (int) startY;
            endYInt = (int) endY;

            startDepth += slopeDepth12;
            endDepth += slopeDepth13;

            this->drawVerticalLine(pixel, startYInt, endYInt, i, startDepth, endDepth);

        }

    }
    
    // When the two left points have the same x, the startY and endY need to be adjusted becuase the first loop was skipped
    else {

        startY = (float) y2;
        endY = (float) y1;

        startDepth = depth2;
        endDepth = depth1;

    }
    
    // Carry on from the last loop
    if (!invalidSlope23) {

        for (int i = x2; i < x3; i++) {

            startY += slope23;
            endY += slope13;

            startYInt = (int) startY;
            endYInt = (int) endY;

            startDepth += slopeDepth23;
            endDepth += slopeDepth13;

            this->drawVerticalLine(pixel, startYInt, endYInt, i, startDepth, endDepth);

        }

    }

    return;

}

void Drawer::drawTriangle(uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3, float depth1, float depth2, float depth3, float opacity) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle
        First find where each point stands in relation to eachother, then from the lowest x go to the highest x
    */
  

    bool oneIsTwo = (x1 == x2) && (y1 == y2);
    bool twoIsThree = (x2 == x3) && (y2 == y3);
    bool oneIsThree = (x1 == x3) && (y1 == y3);

    // Cases where the 'triangle' has more than one point with the same coordinates, so these are checked here for quick handling
    if ( oneIsTwo ) {

        // If two also equals three, all three coordinates are the same, so just return.
        // I should draw a single pixel in this case, but its not really worth it as it will barely be noticable
        if (twoIsThree) return;

        this->drawLine(pixel, x1, y1, x3, y3, depth1, depth3, opacity);
        return;

    }

    // Either of these cases draw the same line
    if ( oneIsThree || twoIsThree) {
        this->drawLine(pixel, x1, y1, x2, y2, depth1, depth2, opacity);
        return;
    }


    // Sort the coordinates by their x values from least to greatest (left to right)
    if (x2 < x1) {
        swap(&x1, &x2);
        swap(&y1, &y2);
        swap(&depth1, &depth2);
    }

    if (x3 < x1) {
        swap(&x1, &x3);
        swap(&y1, &y3);
        swap(&depth1, &depth3);
    }

    if (x3 < x2) {
        swap(&x2, &x3);
        swap(&y2, &y3);
        swap(&depth2, &depth3);
    }

    // These are the y values the line will go to/from for each x
    // The floats store the actual value, and the ints are rounded
    // The actual values may not actually be low and high as the names imply, and might be backwards, but logically it works the same
    float startY = (float) y1;
    float endY = (float) y1;
    int startYInt, endYInt;

    float slope12;
    float slope23;
    float slope13;

    float startDepth = depth1;
    float endDepth = depth1;

    float slopeDepth12;
    float slopeDepth23;
    float slopeDepth13;

    bool invalidSlope12 = false;
    bool invalidSlope23 = false;
    bool invalidSlope13 = false;


    // Slope between left-most point and the middle point
    if (x1 != x2) {
        slope12 = (float) (y2 - y1) / (x2 - x1);
        slopeDepth12 = (depth2 - depth1) / (x2 - x1);
    }

    else invalidSlope12 = true;

    // Slope between middle point and the right-most point
    if (x2 != x3) {
        slope23 = (float) (y3 - y2) / (x3 - x2);
        slopeDepth23 = (depth3 - depth2) / (x3 - x2);
    }

    else invalidSlope23 = true;

    // Slope between the left-most point and the right-most point
    if (x1 != x3) {
        slope13 = (float) (y3 - y1) / (x3 - x1);
        slopeDepth13 = (depth3 - depth1) / (x3 - x1);
    }

    else invalidSlope13 = true;


    // this checks if all the points have the same x coordinate and draws a single line accordingly (in two parts)
    // If the slope between 1 and 2, and the slope between 2 and 3 are both inf, theres no need to check the slope between 1 and 3.
    if (invalidSlope13) {

        if (y1 < y2)
            this->drawVerticalLine(pixel, y1, y2, x1, depth1, depth2, opacity);
        else
            this->drawVerticalLine(pixel, y2, y1, x1, depth2, depth1, opacity);

        if (y2 < y3)
            this->drawVerticalLine(pixel, y2, y3, x1, depth2, depth3, opacity);
        else
            this->drawVerticalLine(pixel, y3, y2, x1, depth3, depth2, opacity);

        return;

    }

    // From left to right until the mid vertex is hit
    if (!invalidSlope12) {

        for (int i = x1; i < x2; i++) {

            startY += slope12;
            endY += slope13;

            startYInt = (int) startY;
            endYInt = (int) endY;

            startDepth += slopeDepth12;
            endDepth += slopeDepth13;

            this->drawVerticalLine(pixel, startYInt, endYInt, i, startDepth, endDepth, opacity);

        }

    }
    
    // When the two left points have the same x, the startY and endY need to be adjusted becuase the first loop was skipped
    else {

        startY = (float) y2;
        endY = (float) y1;

        startDepth = depth2;
        endDepth = depth1;

    }
    
    // Carry on from the last loop
    if (!invalidSlope23) {

        for (int i = x2; i < x3; i++) {

            startY += slope23;
            endY += slope13;

            startYInt = (int) startY;
            endYInt = (int) endY;

            startDepth += slopeDepth23;
            endDepth += slopeDepth13;

            this->drawVerticalLine(pixel, startYInt, endYInt, i, startDepth, endDepth, opacity);

        }

    }

    return;

}

void Drawer::drawTriangle(uint32 pixel, Tri2* tri) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (tri == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) on a null pointer!", true);
        return;
    }

    if (tri->v1 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v1 as a null pointer", true);
        return;
    }

    if (tri->v2 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v2 as a null pointer", true);
        return;
    }

    if (tri->v3 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v3 as a null pointer", true);
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

void Drawer::drawTriangle(uint32 pixel, Tri3* tri) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (tri == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) on a null pointer!", true);
        return;
    }

    if (tri->v1 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v1 as a null pointer", true);
        return;
    }

    if (tri->v2 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v2 as a null pointer", true);
        return;
    }

    if (tri->v3 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v3 as a null pointer", true);
        return;
    }
    
    int x1 = (int) round(tri->v1->x);
    int y1 = (int) round(tri->v1->y);
    int x2 = (int) round(tri->v2->x);
    int y2 = (int) round(tri->v2->y);
    int x3 = (int) round(tri->v3->x);
    int y3 = (int) round(tri->v3->y);

    float d1 = tri->v1->z;
    float d2 = tri->v2->z;
    float d3 = tri->v3->z;

    this->drawTriangle(pixel, x1, y1, x2, y2, x3, y3, d1, d2, d3);

    return;

}

void Drawer::drawTriangle(uint32 pixel, Tri3* tri, float opacity) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (tri == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) on a null pointer!", true);
        return;
    }

    if (tri->v1 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v1 as a null pointer", true);
        return;
    }

    if (tri->v2 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v2 as a null pointer", true);
        return;
    }

    if (tri->v3 == nullptr) {
        logWrite("Called Drawer->drawTriangle(uint32, Tri2*) with tri->v3 as a null pointer", true);
        return;
    }
    
    int x1 = (int) round(tri->v1->x);
    int y1 = (int) round(tri->v1->y);

    int x2 = (int) round(tri->v2->x);
    int y2 = (int) round(tri->v2->y);
    
    int x3 = (int) round(tri->v3->x);
    int y3 = (int) round(tri->v3->y);

    float d1 = tri->v1->z;
    float d2 = tri->v2->z;
    float d3 = tri->v3->z;

    this->drawTriangle(pixel, x1, y1, x2, y2, x3, y3, d1, d2, d3, opacity);

    return;

}

void Drawer::drawpng(PNG* texture, int x, int y) {

    if (x + texture->width > bufferWidth) return;
    if (y + texture->height > bufferHeight) return;
    
    if (this->buffer == nullptr) {
        return;
    }

    for (int i = x; i < (x + texture->width); i++) {
        for (int j = y; j < (y + texture->height); j++) {

            Color* pixel = texture->getPixel(i - x, j - y);

            if (pixel->opacityValue != 0x00) {
                this->writePixel(pixel->rawValue, i, j);
            }

        }
    }
    
    return;
}

void Drawer::drawpng(PNG* texture, Vec2* pos) {

    this->drawpng(texture, pos->x, pos->y);

}

void Drawer::drawpng(PNG* texture, int x, int y, float depth) {

    if (x + texture->width > bufferWidth) return;
    if (y + texture->height > bufferHeight) return;
    
    if (this->buffer == nullptr) {
        return;
    }

    for (int i = x; i < (x + texture->width); i++) {
        for (int j = y; j < (y + texture->height); j++) {

            Color* pixel = texture->getPixel(i - x, j - y);

            if (pixel->opacityValue != 0x00) {
                this->writePixel(pixel->rawValue, i, j, depth);
            }

        }
    }
    
    return;
}

void Drawer::drawpng(PNG* texture, Vec2* pos, float depth) {

    this->drawpng(texture, pos->x, pos->y, depth);

}

void Drawer::initFont() {

    this->chars = new bool*[this->rawCharsCount];

    for (int i = 0; i < this->rawCharsCount; i++) {
        this->chars[i] = new bool[49];
    }

    int index1 = 0;
    int index2 = 0;

    for (int i = 0; i < this->rawCharsSize; i++) {

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

void Drawer::drawChar(uint32 pixel, char ch, int x, int y) {

    if (this->chars == nullptr) {
        logWrite("Called Drawer->drawChar() without calling Drawer->initFont()!", true);
        return;
    }

    bool* pixels = this->getCharRef(ch);

    this->drawPixels(pixel, pixels, x, y);
    
    return;

}

void Drawer::drawString(uint32 pixel, const char* string, int x, int y) {

    if (this->chars == nullptr) {
        logWrite("Called Drawer->drawString() without calling Drawer->initFont()!", true);
        return;
    }

    int dx = 0;

    for (int i = 0; string[i] != '\0'; i++) {

        this->drawChar(pixel, string[i], x + dx, y);
        dx += 6;

    }

    return;
    
}

void Drawer::drawString(uint32 pixel, const char* string, Vec2* pos) {

    this->drawString(pixel, string, pos->x, pos->y);
    return;

}

void Drawer::drawInt(uint32 pixel, int num, int x, int y) {

    if (this->chars == nullptr) {
        logWrite("Called Drawer->drawInt() without calling Drawer->initFont()!", true);
        return;
    }

    float a = (float) num;
    int b; // for casting 'a' into
    int counter = 0;

    int dx = 0;

    while (a >= 1) {
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

        this->drawPixels(pixel, pixels, x + dx, y);
        dx += 6;

    }

}

void Drawer::drawFps(State* state, Display* display) {

    if (state == nullptr) {
        logWrite("Called Drawer->drawFps(State) on a nullptr!", true);
        return;
    }

    if (this->chars == nullptr) {
        logWrite("Called Drawer->drawFps() without calling Drawer->initFont()!", true);
        return;
    }

    int w = display->width + display->widthOffset;
    int h = display->heightOffset;

    this->drawRectFilled(Color::BLACK, w - 50, h, w, h + 13);
    this->drawInt(Color::WHITE, state->time->fps, (w - 50) + 12, 3);

}

void Drawer::drawPixels(uint32 pixel, bool* pixels, int x, int y) {

    if (pixels == nullptr) return;
    
    int dx = 0;
    int dy = 0;

    for (int i = 0; i < 49; i++) {

        if (pixels[i])
            this->writePixel(pixel, x + dx, y + dy);

        dx++;
        if (dx > 6) {
            dx = 0;
            dy++;
        }

    }

}

bool* Drawer::getCharRef(char ch) const {

    /*
        Because the chars 'a' - 'z' are in order for their cooresponding integer value, I can use this to simplify the indexing
        Same goes for 'A' - 'Z' and '0' - '9'
        As I do not have lower/upper variants for the letters, lowercase chars and uppercase chars turn to the same pixels
    */

    // Chars 'a' - 'z' turn to 0 - 25
    if ( ch >= 'a' && ch <= 'z' ) {
        return this->chars[ch - 'a'];
    }

    // Chars 'A' - 'Z' turn to 0 - 25
    if ( ch >= 'A' && ch <= 'Z' ) {
        return this->chars[ch - 'A'];
    }

    // Chars '0' - '9' turn to 26 - 35
    if ( ch >= '0' && ch <= '9' ) {
        return this->chars[ (ch - '0') + 26 ];
    }

    // Other chars
    switch (ch) {

        // Space
        case ' ':
            return this->chars[36];
        
        // Minus / Negative Sign
        case '-':
            return this->chars[37];

        // Period / Decimal
        case '.':
            return this->chars[38];

    }

    // Return null char if nothing else applies
    return this->chars[39];

}

bool* Drawer::getCharRef(int num) const {

    // Return ref to null char if the int is negative or not single digit
    if ( num < 0 || num > 9 ) {
        return this->chars[39];
    }

    // Since the numbers are ordered properly in my list, I use this to simplify the indexing
    return this->chars[26 + num];

}

void Drawer::drawSky(Camera* camera, Display* display) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (camera == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Find the height on the display to draw the skyline
    Vec2* heightVec = new Vec2(display->height, 0);
    heightVec->rotate(camera->pitch);
    float height = (display->height / 2) + heightVec->y;
    delete heightVec;

    // If the camera is facing down enough that no sky is visible
    if (height < 0) {
        this->fillScreen(Color::BLACK);
        return;
    }

    // Draw the rectangles
    uint32 skyColorLight = 0xFF323296;  // o->FF, r->32, g->32, b->96
    uint32 skyColorDark = 0xFF161648;   // o->FF, r->16, g->16, b->48

    this->drawRectFilled(
        skyColorLight, 
        display->widthOffset, 
        display->heightOffset, 
        display->widthOffset + display->width, 
        display->heightOffset + (height - (float) 25)
    );
    this->drawRectFilled(
        skyColorDark, 
        display->widthOffset, 
        display->heightOffset + (height - (float) 25), 
        display->widthOffset + display->width, 
        display->heightOffset + height
    );
    this->drawRectFilled(
        Color::BLACK, 
        display->widthOffset, 
        display->heightOffset + height, 
        display->widthOffset + display->width, 
        display->heightOffset + display->height
    );

    return;

}

void Drawer::drawCrosshair(Display* display) {

    int centerX = display->middleX();
    int centerY = display->middleY();
    
    // Middle dot
    this->writePixel(Color::WHITE, centerX, centerY);

    // Vertical lines
    this->drawVerticalLine(Color::WHITE, centerY - 6, centerY - 12, centerX);
    this->drawVerticalLine(Color::WHITE, centerY + 6, centerY + 12, centerX);

    // Horizontal lines
    this->drawHorizontalLine(Color::WHITE, centerX - 6, centerX - 12, centerY);
    this->drawHorizontalLine(Color::WHITE, centerX + 6, centerX + 12, centerY);

}
