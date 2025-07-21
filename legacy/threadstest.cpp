/*
    This file holds a sketch I wrote up for planning how multithreading might look in this project.

    Since the current project is single-threaded, this clearly never went anywhere, but here it is.
*/

#include <thread>

#include "src/include/State.h"

bool breakAll = false;

// state holds information about the input events on that frame
State* currentState;
State* bufferState;

bool usingState = false;
bool rendering = false;
bool doneGraphics = false;
bool doneRendering = false;

void handleInput() {

    while (!breakAll) {

        // wait if the state is in use
        while (usingState) {}
        usingState = true;

        // handle input events

        usingState = false;

    }

}

void doGraphics() {

    while (!breakAll) {

        // just resets the pixel buffer and does not depend on other data
        drawBackground();

        while (rendering) {}

        // draw everything

        doneGraphics = true;

        // wait for main to flag
        while (doneGraphics) {}

    }

}

void doRendering() {

    while (!breakAll) {

        rendering = true;

        // do rendering

        rendering = false;

        doneRendering = true;

        // wait for main to flag
        while (doneRendering) {}

    }

}

int main() {

    // setup

    thread(handleInput);
    thread(doGraphics);
    thread(doRendering);

    while (!breakAll) {

        while (usingState) {}
        usingState = true;

        // capture input events from sdl

        usingState = false;

        // wait for threads to finish
        while (!doneGraphics || !doneRendering) {}
        doneGraphics = false;
        doneRendering = false;

    }

}
