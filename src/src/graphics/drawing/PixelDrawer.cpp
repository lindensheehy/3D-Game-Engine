#include "graphics/drawing/PixelDrawer.h"

using namespace Graphics::Drawing;


PixelDrawer::PixelDrawer(int width, int height) {

    this->buffer = nullptr;
    this->bufferWidth = width;
    this->bufferHeight = height;
    this->bufferSize = height * height;

    // Depth buffer
    this->depthBuffer = new float[this->maxBufferSize];
    this->resetDepthBuffer();

    return;

}

PixelDrawer::~PixelDrawer() {

    delete this->depthBuffer;

    return;

}

void PixelDrawer::updateDimensions(int width, int height) {

    /*
        This function assumes the values have already been bound checked
        This function is not called directly, and is called by Drawer::updateDimensions() instead
    */

    this->bufferWidth = width;
    this->bufferHeight = height;
    this->bufferSize = width * height;

    return;

}

void PixelDrawer::resetDepthBuffer() {

    /*
        This only resets the first (this->bufferWidth * this->bufferHeight) pixels
        Those are the only ones used on any given draw frame, so no need to reset the rest
    */

    for (int i = 0; i < this->bufferSize; i++) {
        this->depthBuffer[i] = inf;
    }

    return;

}

int PixelDrawer::bufferIndex(int x, int y) const {

    if (!this->inBufferRange(x, y)) return -1;

    return (y * this->bufferWidth) + x;

}

bool PixelDrawer::inBufferRange(int x, int y) const {

    return (
        x >= 0 &&
        x < this->bufferWidth &&
        y >= 0 &&
        y < this->bufferHeight
    );

}

void PixelDrawer::clipCoordinates(int* x, int* y) const {

    if (x == nullptr) return;
    if (y == nullptr) return;

    if ( (*x) < 0 ) (*x) = 0;
    if ( (*y) < 0 ) (*y) = 0;

    if ( (*x) >= this->bufferWidth ) (*x) = this->bufferWidth - 1;
    if ( (*y) >= this->bufferHeight ) (*y) = this->bufferHeight - 1;

    return;

}

void PixelDrawer::drawPixel(uint32 pixel, int x, int y) {

    // Validate requested write
    int index = this->bufferIndex(x, y);
    if (index == -1) return;

    // Check with PixelTracker
    if (this->pixelTracker.watchingPixelWrites) {
        if (this->pixelTracker.watchedPixel.is(x, y)) {
            this->pixelTracker.foundWrite();
        }
    }

    this->buffer[index] = pixel;

    return;

}

void PixelDrawer::drawPixel(uint32 pixel, int x, int y, float depth, float opacity /* = 1.0 */) {

    // Validate requested write
    int index = this->bufferIndex(x, y);
    if (index == -1) return;

    if (depth > this->depthBuffer[index]) return;

    // Check with PixelTracker
    if (this->pixelTracker.watchingPixelWrites) [[unlikely]] {
        if (this->pixelTracker.watchedPixel.is(x, y)) [[unlikely]] {
            this->pixelTracker.foundWrite();
        }
    }

    if (opacity < 1.0) {

        // Find effective color based on pixel color, opacity, and color behind
        uint32 originalPixel = this->buffer[index];
        uint32 result = Color::merge(pixel, opacity, originalPixel, 1 - opacity);

        this->buffer[index] = result;

        return;

    }

    this->buffer[index] = pixel;
    this->depthBuffer[index] = depth;

    return;

}
