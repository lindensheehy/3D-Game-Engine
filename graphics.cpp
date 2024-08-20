#pragma once

#include "src/include/Drawer.h"
#include "src/include/State.h"
#include "src/include/Vec.h"
#include "src/include/Mesh.h"
#include "src/include/Camera.h"
#include "src/include/ObjectSet.h"    

#include "src/include/Log.h"

Font* font;
bool drawNormals;

void initGraphics() {

    drawNormals = false;

    font = new Font();
    font->init();

}

void drawSky(Drawer* drawer, Camera* camera, Display* display) {

    // Because of how this function is called from drawGraphics, none of these should ever be null but it doesnt really hurt to check

    // Address error cases, but dont kill the process yet in case its not fatal
    if (drawer == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

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
    double height = (display->height / 2) + heightVec->y;
    delete heightVec;

    // If the camera is facing down enough that no sky is visible
    if (height < 0) {
        drawer->fillScreen(Color::BLACK);
        return;
    }

    // Draw the rectangles
    uint32_t skyColorLight = 0xFF323296; // o->FF, r->32, g->32, b->96
    uint32_t skyColorDark = 0xFF161648; // o->FF, r->16, g->16, b->48

    drawer->drawRect(
        skyColorLight, 
        display->widthOffset, 
        display->heightOffset, 
        display->widthOffset + display->width, 
        display->heightOffset + (height - (double) 25)
    );
    drawer->drawRect(
        skyColorDark, 
        display->widthOffset, 
        display->heightOffset + (height - (double) 25), 
        display->widthOffset + display->width, 
        display->heightOffset + height
    );
    drawer->drawRect(
        Color::BLACK, 
        display->widthOffset, 
        display->heightOffset + height, 
        display->widthOffset + display->width, 
        display->heightOffset + display->height
    );

    return;

}

void drawGraphics(ObjectSet* objectSet, Drawer* drawer, State* state, Camera* camera, Display* display) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (objectSet == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'objectSet' as a null pointer!", true);
        return;
    }

    if (drawer == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (state == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'state' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Toggle normal vector drawing on key n
    if (state->keyJustDown(SDLK_n))
        drawNormals = !drawNormals;

    drawSky(drawer, camera, display);
    
    // Draw all the objects
    if (drawNormals) 
        objectSet->drawAllWithNormals(drawer, camera, display);
    else 
        objectSet->drawAll(drawer, camera, display);

    // Draw the fps
    drawer->drawRect(Color::BLACK, 0, 0, 30, 13);
    font->drawer = drawer;
    font->drawInt(state->time->fps, 6, 3, Color::WHITE);

    return;

}
