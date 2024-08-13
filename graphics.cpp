#pragma once

#include "src/class-headers/DrawerClass.h"
#include "src/class-headers/FrameStateClass.h"
#include "src/class-headers/Vec2Class.h"
#include "src/class-headers/Vec3Class.h"
#include "src/class-headers/MeshClass.h"
#include "src/class-headers/CameraClass.h"
#include "src/class-headers/DisplayClass.h"
#include "src/class-headers/FontClass.h"

#include "src/log/log.h"

bool drawNormals;

class MeshSet {

    /*
        Contains a set of meshes in the form of a doubly linked list
        This can be added and removed from, and this way a group of meshes can be rendered and drawn together
    */

    public:



};

void drawMesh(Mesh* mesh, Drawer* drawer, Camera* camera, Display* display) {

    // Because of how this function is called from drawGraphics, none of these should ever be null but it doesnt really hurt to check

    // Address error cases, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'frameState' as a null pointer!", true);
        return;
    }

    if (drawer == nullptr) {
        logWrite("Called drawGraphics(Drawer*, FrameState*, Camera*, Display*) with 'drawer' as a null pointer!", true);
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

    // Draw Tris
    for (int i = 0; i < mesh->triCount; i++) {
        
        // Skip if tri cant be seen face on by cam
        if (!camera->canSee(mesh->tris[i])) continue;

        // Find a shade based on the lighting vec
        double lightAngle = mesh->tris[i]->normal->getAngle(camera->lightingVec);
        double lightFactor = lightAngle / 180;

        Uint32 shade = mesh->color;
        shade = Color::setBrightness(shade, lightFactor);

        // Draw the tri    
        drawer->drawTriangle(shade, mesh->projectedTris[i]);

    }

    Vec2* vecStart = new Vec2(); 
    Vec2* vecEnd = new Vec2();

    // Draw Normals
    if (drawNormals) {
        for (int i = 0; i < mesh->triCount; i++) {

            // Skip if tri cant be seen face on by cam
            if (!camera->canSee(mesh->tris[i])) continue;

            Vec3* triCenter;
            Vec3* normalOffset;
            Vec3* triNormal;

            // Get projected coords for normal start and end
            triCenter = mesh->tris[i]->getCenter();
            normalOffset = mesh->tris[i]->normal->copy()->normalise(1);
            triNormal = triCenter->copy()->add(normalOffset);

            camera->project(triCenter, vecStart);
            camera->project(triNormal, vecEnd);
            display->toDisplayPos(vecStart);
            display->toDisplayPos(vecEnd);

            drawer->drawLine(Color::RED, vecStart, vecEnd);

            delete triCenter;
            delete normalOffset;
            delete triNormal;

        }
    }

    delete vecStart; delete vecEnd;

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
Mesh** meshes;

Font* font;

void initGraphics() {

    drawNormals = false;

    font = new Font();
    font->init();

    meshes = new Mesh*[28];

    Uint32 colorKeys[] = {
        Color::WHITE,
        Color::BLUE,
        Color::RED,
        Color::GREEN,
        Color::GREY,
        Color::BLACK
    };

    double offsetx = -50;
    double offsety = -50;

    for (int i = 0; i < 25; i++) {

        int size = (i % 4) + 16; 
        meshes[i] = Mesh::sphereMesh->copy()->scale(size, size, size);
        meshes[i]->move(offsetx, offsety, 100);
        meshes[i]->setColor(colorKeys[i % 6]);

        offsetx += 25;

        // When its above 50, im using 60 in case of float errors
        if (offsetx > 60) {
            offsetx = -50;
            offsety += 25;
        }

    }

    meshes[25] = Mesh::cubeMesh->copy()->scale(15, 15, 15)->move(0, 0, 50);
    meshes[25]->setColor(Color::WHITE);

    meshes[26] = Mesh::cubeMesh->copy()->scale(5, 5, 5)->move(0, 20, 50);
    meshes[26]->setColor(Color::GREY);

    meshes[27] = Mesh::cubeMesh->copy()->scale(10, 5, 15)->move(30, 10, 40)->rotateSelf(10, 0, 0);
    meshes[27]->setColor(Color::BLUE);

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

    if (frameState->wasRightJustPressed()) {
        drawNormals = !drawNormals;
    }

    // Rotate things based on keypresses
    if (frameState->keyIsDown(SDLK_j)) {
        for (int i = 0; i < 28; i++) {
            meshes[i]->rotateSelf(1, 0, 0);
        }
    }

    if (frameState->keyIsDown(SDLK_k)) {
        for (int i = 0; i < 28; i++) {
            meshes[i]->rotateSelf(0, 1, 0);
        }
    }

    if (frameState->keyIsDown(SDLK_l)) {
        for (int i = 0; i < 28; i++) {
            meshes[i]->rotateSelf(0, 0, 1);
        }
    }

    drawSky(drawer, camera, display);

    for (int i = 0; i < 28; i++) {
        camera->project(meshes[i]);
        display->toDisplayPos(meshes[i]);
        drawMesh(meshes[i], drawer, camera, display);
    }
    

    // Draw the fps
    drawer->drawRect(Color::BLACK, 0, 0, 30, 13);
    font->drawer = drawer;
    font->drawInt(frameState->time->fps, 6, 3, Color::WHITE);

    return;

}
