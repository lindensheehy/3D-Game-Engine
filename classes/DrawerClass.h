#ifndef DrawerClass
#define DrawerClass

#include <SDL2/SDL.h>

#include "PNGClass.h"
#include "Vec2Class.h"
#include "Tri2Class.h"
#include "../math.cpp"
#include "../log.cpp"

class Drawer {
    public:
        
        // Instance variables
        Uint32* buffer;
        unsigned int bufferHeight;
        unsigned int bufferWidth;
        unsigned int bufferSize;

        // Constructor
        Drawer(Uint32* buffer, unsigned int bufferWidthInput, unsigned int bufferHeightInput) {
            this->buffer = buffer;
            this->bufferWidth = bufferWidthInput;
            this->bufferHeight = bufferHeightInput;
            this->bufferSize = bufferHeightInput * bufferWidthInput;
        }

        // Instance functions
        void writePixel(Uint32 pixel, int x, int y) {

            if (this->buffer == NULL) {
                return;
            }

            // Dont draw if it outside the buffer
            if (x >= this->bufferWidth) return;
            if (y >= this->bufferHeight) return;

            int index = (y * this->bufferWidth) + x;
            if (index > this->bufferSize) return;

            buffer[index] = pixel;

            return;
        }

        void drawLine(Uint32 pixel, int x1, int y1, int x2, int y2) {

            if (this->buffer == NULL) {
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

        void drawLine(Uint32 pixel, Vec2* from, Vec2* to) {

            this->drawLine(pixel, from->x, from->y, to->x, to->y);
            return;

        }

        void drawVerticalLine(Uint32 pixel, int startY, int endY, int x) {
            for (int i = startY; i <= endY; i++) {
                this->writePixel(pixel, x, i);
            }
        }

        void drawHorizontalLine(Uint32 pixel, int startX, int endX, int y) {
            for (int i = startX; i <= endX; i++) {
                this->writePixel(pixel, i, y);
            }
        }

        void drawRect(Uint32 pixel, int startx, int starty, int endx, int endy) {

            if (this->buffer == NULL) {
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

        void fillScreen(Uint32 pixel) {
            this->drawRect(pixel, 0, 0, this->bufferWidth, this->bufferHeight);
        }

        void drawElipse(Uint32 pixel, int locationx, int locationy, int radiusx, int radiusy) {

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

        void drawCircle(Uint32 pixel, int locationx, int locationy, int radius) {

            int limit = radius * radius;

            for (int i = -radius; i < radius; i++) {
                for (int j = -radius; j < radius; j++) {

                    if ( (i * i) + (j * j) < limit ) {
                        this->writePixel(pixel, locationx + i, locationy + j);
                    }
                    
                }
            }
        }

        void drawTriangle(Uint32 pixel, int x1, int y1, int x2, int y2, int x3, int y3) {

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

            // Sort the coordinates by thier x values from least to greatest (left to right)
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
            else slopeLeftMid = 1e250; // just a big number representing infinity

            // Slope between middle point and the right-most point
            if (x2 != x3) slopeMidRight = ((double) (y3 - y2)) / (double) (x3 - x2);
            else slopeMidRight = 1e250; // just a big number representing infinity

            // Slope between the left-most point and the right-most point
            if (x1 != x3) slopeLeftRight = ((double) (y3 - y1)) / (double) (x3 - x1);
            else slopeLeftRight = 1e250; // just a big number representing infinity

            // this checks if all the points have the same x coordinate and draws a single line accordingly
            // Since the points are sorted, if the lowest (left) and highest (right) have the same x, so does the middle
            if (slopeLeftRight == 1e250) {
                startY = min(min(y1, y2), y3);
                endY = max(max(y1, y2), y3);
                this->drawVerticalLine(pixel, startY, endY, x1);
                return;
            }
    
            // From left to right until the mid vertex is hit
            if (slopeLeftMid != 1e250) {
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
            if (slopeMidRight != 1e250) {
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

        void drawTriangle(Uint32 pixel, Tri2* tri) {
            
            int x1 = (int) round(tri->v1->x);
            int y1 = (int) round(tri->v1->y);
            int x2 = (int) round(tri->v2->x);
            int y2 = (int) round(tri->v2->y);
            int x3 = (int) round(tri->v3->x);
            int y3 = (int) round(tri->v3->y);

            this->drawTriangle(pixel, x1, y1, x2, y2, x3, y3);

            return;

        }

        void drawpng(PNG* file, int x, int y) {

            if (x + file->width > bufferWidth) return;
            if (y + file->height > bufferHeight) return;
            
            if (this->buffer == NULL) {
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

    private:

};

#endif