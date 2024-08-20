#pragma once

#include "src/include/Vec.h"
#include "src/include/State.h"
#include "src/include/ObjectSet.h"

void doPhysics(ObjectSet* objectSet, State* state) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (objectSet == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'objectSet' as a null pointer!", true);
        return;
    }

    if (state == nullptr) {
        logWrite("Called drawGraphics(ObjectSet*, Drawer*, State*, Camera*, Display*) with 'state' as a null pointer!", true);
        return;
    }

    objectSet->doAllPhysics(state->time->dt);

    return;

}
