#pragma once

#include "src/include/Drawer.h"
#include "src/include/FrameState.h"
#include "src/include/Vec.h"
#include "src/include/Mesh.h"
#include "src/include/Camera.h"
#include "src/include/ObjectSet.h"    

#include "src/include/Log.h"

bool drawNormals;

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
    if (height < 0) return;

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

    return;

}

// Static variables for objects to draw, reimplement later
StaticSet* staticSet;
PhysicsSet* physicsSet;
Font* font;

void initGraphics() {

    drawNormals = false;

    font = new Font();
    font->init();

    staticSet = new StaticSet();
    StaticObject* newStaticObject;

    newStaticObject = new StaticObject();
    newStaticObject->mesh = Mesh::cubeMesh->copy()->scale(15, 15, 15)->move(0, 0, 50)->setColor(Color::WHITE);
    staticSet->pushBack(newStaticObject, 1);

    newStaticObject = new StaticObject();
    newStaticObject->mesh = Mesh::cubeMesh->copy()->scale(5, 5, 5)->move(0, 20, 50)->setColor(Color::GREY);
    staticSet->pushBack(newStaticObject, 2);

    newStaticObject = new StaticObject();
    newStaticObject->mesh = Mesh::cubeMesh->copy()->scale(10, 5, 15)->move(30, 10, 40)->rotateSelf(10, 0, 0)->setColor(Color::BLUE);
    staticSet->pushBack(newStaticObject, 3);

    newStaticObject = new StaticObject();
    newStaticObject->mesh = Mesh::capsuleMesh->copy()->scale(15, 15, 15)->move(0, -20, 50)->setColor(Color::GREEN);
    staticSet->pushBack(newStaticObject, 4);

}

void drawGraphics(Drawer* drawer, FrameState* frameState, Camera* camera, Display* display) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (drawer == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (frameState == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'frameState' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Toggle normal vector drawing
    if (frameState->keyJustDown(SDLK_n))
        drawNormals = !drawNormals;

    drawSky(drawer, camera, display);
    
    if (drawNormals) staticSet->drawAllWithNormals(drawer, camera, display);
    else staticSet->drawAll(drawer, camera, display);

    // Draw the fps
    drawer->drawRect(Color::BLACK, 0, 0, 30, 13);
    font->drawer = drawer;
    font->drawInt(frameState->time->fps, 6, 3, Color::WHITE);

    return;

}
