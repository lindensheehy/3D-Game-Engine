#pragma once

#include "src/include/Drawer.h"
#include "src/include/State.h"
#include "src/include/Vec.h"
#include "src/include/Mesh.h"
#include "src/include/Camera.h"
#include "src/include/ObjectSet.h"    

#include "src/include/Log.h"

void drawObjectSet(ObjectSet* objectSet, Drawer* drawer, State* state, Camera* camera, Display* display) {

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
    
    // Draw all the objects
    if (drawNormals) 
        objectSet->drawAllWithNormals(drawer, camera, display);
    else 
        objectSet->drawAll(drawer, camera, display);

    return;

}
