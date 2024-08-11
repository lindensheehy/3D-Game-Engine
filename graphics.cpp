#pragma once

#include "src/class-headers/DrawerClass.h"
#include "src/class-headers/FrameStateClass.h"
#include "src/class-headers/Vec2Class.h"
#include "src/class-headers/Vec3Class.h"
#include "src/class-headers/MeshClass.h"
#include "src/class-headers/CameraClass.h"
#include "src/class-headers/DisplayClass.h"

#include "src/log/log.h"

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

        logWrite("Checking -> ", false);
        
        // Draw the triangle only if its facing the camera
        if (mesh->tris[i]->isFacing(camera->facingDirection)) {
            logWrite("Facing!", true);
            drawer->drawTriangle(Color::WHITE, mesh->projectedTris[i]);
        }

        else {
            logWrite("Not Facing!", true);
        }

    }

    Vec2* vecStart = new Vec2(); 
    Vec2* vecEnd = new Vec2();

    Vec3* triCenter;
    Vec3* normalOffset;
    Vec3* triNormal;

    // Draw Normals
    for (int i = 0; i < mesh->triCount; i++) {

        // Pass if tri isnt facing cam
        if (!mesh->tris[i]->isFacing(camera->facingDirection)) continue;

        // Get projected coords for normal start and end
        triCenter = mesh->tris[i]->getCenter();
        normalOffset = mesh->tris[i]->normal->copy()->normalise(10);
        triNormal = triCenter->add(normalOffset);

        logWrite("here", true);

        camera->project(triCenter, vecStart);
        camera->project(triNormal, vecEnd);
        display->toDisplayPos(vecStart);
        display->toDisplayPos(vecEnd);

        vecStart->log();
        vecEnd->log();

        drawer->drawLine(Color::RED, vecStart, vecEnd);

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
Mesh* cube1;
Mesh* cube2;

void initGraphics() {

    // Init cube mesh then move it away and make it bigger
    cube1 = Mesh::cubeMesh->copy()->scale(15, 15, 15)->move(0, 0, 50);

    //cube2 = Mesh::cubeMesh->copy()->scale(5, 5, 5)->move(0, 10, 0)->rotate(0, 10, 0);

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

    drawSky(drawer, camera, display);

    for (int i = 0; i < cube1->vertexCount; i++) {
        cube1->verticies[i]->log();
    }

    camera->project(cube1);

    for (int i = 0; i < cube1->vertexCount; i++) {
        cube1->projectedVerticies[i]->log();
    }

    display->toDisplayPos(cube1);

    for (int i = 0; i < cube1->vertexCount; i++) {
        cube1->projectedVerticies[i]->log();
    }
    
    drawMesh(cube1, drawer, camera, display);

    // camera->project(cube2);
    // display->toDisplayPos(cube2);
    // drawMesh(cube2, drawer, camera, display);

    // Vec3* camFacingVec = camera->facingDirection->copy()->scale(50);
    // Vec3* camFacingVecStart = new Vec3(0, 0, 0);
    // Vec2* projectedCamFacingVec = new Vec2();
    // Vec2* projectedCamFacingVecStart = new Vec2();
    // camera->project(camFacingVec, projectedCamFacingVec);
    // camera->project(camFacingVecStart, projectedCamFacingVecStart);
    // display->toDisplayPos(projectedCamFacingVec);
    // display->toDisplayPos(projectedCamFacingVecStart);

    // drawer->drawLine(Color::RED, projectedCamFacingVecStart, projectedCamFacingVec);

    // delete camFacingVec, camFacingVecStart;
    // delete projectedCamFacingVec, projectedCamFacingVecStart;

    return;

}
