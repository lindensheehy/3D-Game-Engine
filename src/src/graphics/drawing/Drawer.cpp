#include "graphics/drawing/Drawer.h"

using namespace Graphics::Drawing;


void Drawer::updateDimensions(int width, int height) {
    
    this->pixelDrawer.updateDimensions(width, height);
    return;

}

void Drawer::setBuffer(uint32* buffer) {

    this->pixelDrawer.buffer = buffer;
    return;

}

void Drawer::drawLine(uint32 color, int x1, int y1, int x2, int y2) {

    int distx = x2 - x1;
    int disty = y2 - y1;

    int totalDist = max(abs(distx), abs(disty));

    if (totalDist == 0) return;

    float x = (float) x1;
    float y = (float) y1;

    float dx = distx / (float) totalDist;
    float dy = disty / (float) totalDist;

    for (int i = 0; i <= totalDist; i++) {

        this->pixelDrawer.drawPixel(color, round(x), round(y));

        x += dx;
        y += dy;

    }

    return;

}

void Drawer::drawLine(uint32 color, int x1, int y1, int x2, int y2, float depth1, float depth2, float opacity) {

    int distx = x2 - x1;
    int disty = y2 - y1;
    float distDepth = depth2 - depth1;

    int totalDist = max(abs(distx), abs(disty));

    if (totalDist == 0) return;

    float x = (float) x1;
    float y = (float) y1;
    float d = depth1;

    float dx = distx / (float) totalDist;
    float dy = disty / (float) totalDist;
    float dd = distDepth / (float) totalDist;

    for (int i = 0; i < totalDist; i++) {

        this->pixelDrawer.drawPixel(color, round(x), round(y), d, opacity);

        x += dx;
        y += dy;
        d += dd;

    }

    return;

}

void Drawer::drawVerticalLine(uint32 color, int y1, int y2, int x) {

    // Skip if this line lies outside the screen horizontally
    if (!this->pixelDrawer.inBufferRange(x, 0)) return;

    // Clip y values to lie within the buffer
    this->pixelDrawer.clipCoordinates(&x, &y1);
    this->pixelDrawer.clipCoordinates(&x, &y2);

    if (y1 > y2) {
        swap(&y1, &y2);
    }

    for (int i = y1; i <= y2; i++) {
        this->pixelDrawer.drawPixel(color, x, i);
    }

    return;

}

void Drawer::drawVerticalLine(uint32 color, int y1, int y2, int x, float depth1, float depth2, float opacity) {

    // Skip if this line is out of range
    if ( !(this->pixelDrawer.inBufferRange(x, y1)) && !(this->pixelDrawer.inBufferRange(x, y2)) ) return;

    // Clip y values to lie within the buffer
    this->pixelDrawer.clipCoordinates(&x, &y1);
    this->pixelDrawer.clipCoordinates(&x, &y2);
    
    // Edge case
    if (y1 == y2) {

        float d = min(depth1, depth2);
        this->pixelDrawer.drawPixel(color, x, y1, d, opacity);

        return;

    }

    if (y1 > y2) {
        swap(&y1, &y2);
        swap(&depth1, &depth2);
    }

    float depthSlope = (depth2 - depth1) / (y2 - y1);
    float d = depth1;

    for (int i = y1; i <= y2; i++) {
        this->pixelDrawer.drawPixel(color, x, i, d, opacity);
        d += depthSlope;
    }

    return;

}

void Drawer::drawHorizontalLine(uint32 color, int x1, int x2, int y) {

    // Skip if this line lies outside the screen horizontally
    if (!this->pixelDrawer.inBufferRange(0, y)) return;

    // Clip y values to lie within the buffer
    this->pixelDrawer.clipCoordinates(&x1, &y);
    this->pixelDrawer.clipCoordinates(&x2, &y);

    if (x1 > x2) {
        swap(&x1, &x2);
    }

    for (int i = x1; i <= x2; i++) {
        this->pixelDrawer.drawPixel(color, i, y);
    }

    return;

}

void Drawer::drawHorizontalLine(uint32 color, int x1, int x2, int y, float depth1, float depth2, float opacity) {

    // Skip if coordinates are out of range
    if (!this->pixelDrawer.inBufferRange(x1, y) && !this->pixelDrawer.inBufferRange(x2, y)) return;

    // Clip y values to lie within the buffer
    this->pixelDrawer.clipCoordinates(&x1, &y);
    this->pixelDrawer.clipCoordinates(&x2, &y);

    // Edge case
    if (x1 == x2) {

        float d = min(depth1, depth2);
        this->pixelDrawer.drawPixel(color, x1, y, d, opacity);

        return;

    }

    if (x1 > x2) {
        swap(&x1, &x2);
        swap(&depth1, &depth2);
    }

    float depthSlope = (depth2 - depth1) / (x2 - x1);
    float d = depth1;

    for (int i = x1; i <= x2; i++) {
        this->pixelDrawer.drawPixel(color, i, y, d, opacity);
        d += depthSlope;
    }

    return;
    
}

void Drawer::drawRect(uint32 color, int x1, int y1, int x2, int y2) {

    this->drawVerticalLine(color, y1, y2, x1);
    this->drawVerticalLine(color, y1, y2, x2);
    this->drawHorizontalLine(color, x1, x2, y1);
    this->drawHorizontalLine(color, x1, x2, y2);

    return;

}

void Drawer::drawRectFilled(uint32 color, int x1, int y1, int x2, int y2) {

    if (x1 > x2) swap(&x1, &x2);
    if (y1 > y2) swap(&y1, &y2);

    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            this->pixelDrawer.drawPixel(color, i, j);
        }
    }

    return;

}

void Drawer::fillScreen(uint32 color) {

    this->drawRectFilled(color, 0, 0, this->pixelDrawer.bufferWidth, this->pixelDrawer.bufferHeight);

    return;

}

void Drawer::drawElipse(uint32 color, int x, int y, int radiusX, int radiusY) {

    int limit = radiusX * radiusY;
    float factorx = sqrt( (float) (radiusY / radiusX) );
    float factory = 1 / factorx;

    for (int i = -radiusX; i < radiusX; i++) {
        for (int j = -radiusY; j < radiusY; j++) {

            if ( ((factorx * i) * (factorx * i)) + ((factory * j) * (factory * j)) < limit ) {
                this->pixelDrawer.drawPixel(color, x + i, y + j);
            }
            
        }
    }

    return;

}

void Drawer::drawCircle(uint32 color, int x, int y, int radius) {

    int limit = radius * radius;

    for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {

            if ( (i * i) + (j * j) < limit ) {
                this->pixelDrawer.drawPixel(color, x + i, y + j);
            }
            
        }
    }
}

void Drawer::drawTriangle(uint32 color, int x1, int y1, int x2, int y2, int x3, int y3) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle (scalines)
        First find where each point stands in relation to eachother, then from the lowest x go to the highest x
    */

    // When all 3 points have the same coordinates we just return and draw nothing
    if ( x1 == x2 && x2 == x3 && y1 == y2 && y2 == y3 ) return;

    // Cases where the 'triangle' should just be drawn as a line, meaning two verticies share the same coordinates
    if ( x1 == x2 && y1 == y2 ) {
        this->drawLine(color, x1, y1, x3, y3);
        return;
    }

    if ( x1 == x3 && y1 == y3 ) {
        this->drawLine(color, x1, y1, x2, y2);
        return;
    }

    if ( x2 == x3 && y2 == y3 ) {
        this->drawLine(color, x2, y2, x1, y1);
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
        this->drawVerticalLine(color, startY, endY, x1);
        return;
    }

    // From left to right until the mid vertex is hit
    if (slopeLeftMid != inf) {
        for (int i = x1; i < x2; i++) {

            actualStartY += slopeLeftMid;
            actualEndY += slopeLeftRight;

            startY = round(actualStartY);
            endY = round(actualEndY);

            this->drawVerticalLine(color, startY, endY, i);

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

            this->drawVerticalLine(color, startY, endY, i);

        }
    }

    return;

}

void Drawer::drawTriangle(uint32 color, int x1, int y1, int x2, int y2, int x3, int y3, float depth1, float depth2, float depth3, float opacity) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle (scalines)
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

        this->drawLine(color, x1, y1, x3, y3, depth1, depth3, opacity);
        return;

    }

    // Either of these cases draw the same line
    if ( oneIsThree || twoIsThree) {
        this->drawLine(color, x1, y1, x2, y2, depth1, depth2, opacity);
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
            this->drawVerticalLine(color, y1, y2, x1, depth1, depth2, opacity);
        else
            this->drawVerticalLine(color, y2, y1, x1, depth2, depth1, opacity);

        if (y2 < y3)
            this->drawVerticalLine(color, y2, y3, x1, depth2, depth3, opacity);
        else
            this->drawVerticalLine(color, y3, y2, x1, depth3, depth2, opacity);

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

            this->drawVerticalLine(color, startYInt, endYInt, i, startDepth, endDepth, opacity);

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

            this->drawVerticalLine(color, startYInt, endYInt, i, startDepth, endDepth, opacity);

        }

    }

    return;

}

void Drawer::drawTriangle(uint32 color, Geometry::Tri2* tri) {

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
    
    int x1 = round(tri->v1->x);
    int y1 = round(tri->v1->y);
    int x2 = round(tri->v2->x);
    int y2 = round(tri->v2->y);
    int x3 = round(tri->v3->x);
    int y3 = round(tri->v3->y);

    this->drawTriangle(color, x1, y1, x2, y2, x3, y3);

    return;

}

void Drawer::drawTriangle(uint32 color, Geometry::Tri3* tri, float opacity) {

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
    
    int x1 = round(tri->v1->x);
    int y1 = round(tri->v1->y);

    int x2 = round(tri->v2->x);
    int y2 = round(tri->v2->y);
    
    int x3 = round(tri->v3->x);
    int y3 = round(tri->v3->y);

    float d1 = tri->v1->z;
    float d2 = tri->v2->z;
    float d3 = tri->v3->z;

    this->drawTriangle(color, x1, y1, x2, y2, x3, y3, d1, d2, d3, opacity);

    return;

}

void Drawer::drawFps(Gui::State* state, Rendering::Display* display) {

    if (state == nullptr) {
        logWrite("Called Drawer->drawFps(State) on a nullptr!", true);
        return;
    }

    int w = display->width + display->widthOffset;
    int h = display->heightOffset;

    this->drawRectFilled(Color::BLACK, w - 50, h, w, h + 13);
    this->fontDrawer.drawInt(Color::WHITE, state->time->fps, (w - 50) + 12, 3);

}

void Drawer::drawSky(Rendering::Camera* camera, Rendering::Display* display) {

    if (camera == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Find the height on the display to draw the skyline
    Geometry::Vec2* heightVec = new Geometry::Vec2(display->height, 0);
    heightVec->rotate(camera->facingAngle.x);
    float height = (display->height / 2) + heightVec->y;
    delete heightVec;

    // If the camera is facing down enough that no sky is visible
    if (height < 0) {
        this->fillScreen(Color::BLACK);
        return;
    }

    // Draw the rectangles
    constexpr uint32 skyColorLight = 0x00323296;  // o->FF, r->32, g->32, b->96
    constexpr uint32 skyColorDark = 0x00161648;   // o->FF, r->16, g->16, b->48

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

void Drawer::drawCrosshair(Rendering::Display* display) {

    int centerX = display->middleX();
    int centerY = display->middleY();
    
    // Middle dot
    this->pixelDrawer.drawPixel(Color::WHITE, centerX, centerY);

    // Vertical lines
    this->drawVerticalLine(Color::WHITE, centerY - 6, centerY - 12, centerX);
    this->drawVerticalLine(Color::WHITE, centerY + 6, centerY + 12, centerX);

    // Horizontal lines
    this->drawHorizontalLine(Color::WHITE, centerX - 6, centerX - 12, centerY);
    this->drawHorizontalLine(Color::WHITE, centerX + 6, centerX + 12, centerY);

}
