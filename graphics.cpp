#pragma once

#include <iostream>

#include "src/class-headers/DrawerClass.h"
#include "src/class-headers/FrameStateClass.h"
#include "src/class-headers/Vec2Class.h"
#include "src/class-headers/Vec3Class.h"
#include "src/class-headers/MeshClass.h"
#include "src/class-headers/CameraClass.h"
#include "src/class-headers/DisplayClass.h"

#include "src/log/log.h"

void drawMesh(Mesh* mesh, Camera* camera, Drawer* drawer, Display* display) {

    // Draw Tris
    for (int i = 0; i < mesh->triCount; i++) {
        if (!mesh->tris[i]->isFacing(camera->facingDirection)) continue;
        drawer->drawTriangle(Color::WHITE, mesh->projectedTris[i]);
    }

    Vec2* vecStart = new Vec2(); 
    Vec2* vecEnd = new Vec2();

    // Draw Normals
    // for (int i = 0; i < mesh->triCount; i++) {

    //     // Pass if tri isnt facing cam
    //     if (!mesh->tris[i]->isFacing(camera->facingDirection)) continue;

    //     // Get projected coords for normal start and end
    //     Vec3* triCenter = mesh->tris[i]->getCenter();
    //     Vec3* normalOffset = mesh->tris[i]->normal->copy()->normalise();
    //     Vec3* triNormal = triCenter->add(normalOffset);

    //     logWrite("here", true);

    //     camera->project(triCenter, vecStart);
    //     camera->project(triNormal, vecEnd);
    //     display->toDisplayPos(vecStart);
    //     display->toDisplayPos(vecEnd);

    //     logWrite(vecStart->x);
    //     logWrite(", ");
    //     logWrite(vecStart->y, true);
    //     logWrite(vecEnd->x);
    //     logWrite(", ");
    //     logWrite(vecEnd->y, true);
    //     logNewLine();

    //     drawer->drawLine(Color::RED, vecStart, vecEnd);

    //     delete triCenter; delete normalOffset; delete triNormal;

    // }

    delete vecStart; delete vecEnd;

}

void drawSky(Drawer* drawer, Camera* camera, Display* display) {

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
Vec3* points[8];
Mesh* cube1;
Mesh* cube2;

void initGraphics() {

    // Init points to draw
    for (int i = 0; i < 8; i++) {

        // These values will count in binary
        int x = i % 2;
        int y = (int) (i % 4) >= 2;
        int z = (int) i >= 4;

        points[i] = new Vec3(5 * x, 5 * y, 5 * z);

    }

    // Init cube mesh then move it away and make it bigger
    cube1 = Mesh::cubeMesh->copy()->scale(15, 15, 15)->move(0, 0, 10);
    //cube2 = Mesh::cubeMesh->copy()->scale(5, 5, 5)->move(0, 10, 0)->rotate(0, 10, 0);

}

void drawGraphics(Drawer* drawer, FrameState* frameState, Camera* camera, Display* display) {

    drawSky(drawer, camera, display);

    camera->project(cube1);
    camera->project(cube2);
    display->toDisplayPos(cube1);
    display->toDisplayPos(cube2);

    drawMesh(cube1, camera, drawer, display);
    drawMesh(cube2, camera, drawer, display);

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
