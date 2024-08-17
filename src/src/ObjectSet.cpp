#include "../include/ObjectSet.h"


/* -------------- */
/* --- Object --- */
/* -------------- */

// Constructors
Object::Object() {
    this->mesh = nullptr;
}

Object::Object(Mesh* mesh) {
    this->mesh = mesh;
}



/* ----------------- */
/* --- ObjectSet --- */
/* ----------------- */

// Constructor
ObjectSet::ObjectSet() {

    this->list = new LinkedList<Object*>();

}

// Destructor
ObjectSet::~ObjectSet() {
    
    delete this->list;

}

// Instance Functions
int ObjectSet::getLength() {

    return this->list->length;

}

void ObjectSet::pushBack(Object* obj) {
    
    this->list->pushBack(obj);
    return;

}

void ObjectSet::pushBack(Object* obj, int id) {
    
    this->list->pushBack(obj, id);
    return;

}

void ObjectSet::pushFront(Object* obj) {

    this->list->pushFront(obj);
    return;

}

void ObjectSet::pushFront(Object* obj, int id) {

    this->list->pushFront(obj, id);
    return;
    
}

Object* ObjectSet::popBack() {

    return this->list->popBack();

}

Object* ObjectSet::popFront() {

    return this->list->popFront();
    
}

Object* ObjectSet::popById(int id) {

    return this->list->popById(id);

}

Object* ObjectSet::getById(int id) {

    return this->list->getById(id);

}

void ObjectSet::iterStart(int index) {

    this->list->iterStart(index);

}

Object* ObjectSet::iterGetObj() {

    return this->list->iterGetObj();

}

int ObjectSet::iterGetId() {

    return this->list->iterGetId();

}

void ObjectSet::iterNext() {

    this->list->iterNext();

}

void ObjectSet::iterLast() {

    this->list->iterLast();

}

bool ObjectSet::iterIsDone() {

    return this->list->iterIsDone();

}

void ObjectSet::projectAll(Camera* camera, Display* display) {

    Mesh* currentMesh;

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentMesh = this->iterGetObj()->mesh;

        camera->project(currentMesh);
        display->toDisplayPos(currentMesh);

    }

}

void ObjectSet::drawAll(Drawer* drawer, Camera* camera, Display* display) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (drawer == nullptr) {
        logWrite("Called ObjectSet->drawAll(Drawer*, Camera*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet->drawAll(Drawer*, Camera*) with 'camera' as a null pointer!", true);
        return;
    }

    // Set up
    this->projectAll(camera, display);
    Mesh* currentMesh;

    // Main loop
    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentMesh = this->iterGetObj()->mesh;

        for (int i = 0; i < currentMesh->triCount; i++) {
        
            // Skip if tri cant be seen by cam on the outfacing side
            if (!camera->canSee(currentMesh->tris[i])) continue;

            // Find a shade based on the lighting vec
            double lightAngle = currentMesh->tris[i]->normal->getAngle(camera->lightingVec);
            double lightFactor = lightAngle / 180;

            Uint32 shade = currentMesh->color;
            shade = Color::setBrightness(shade, lightFactor);

            // Draw the tri    
            drawer->drawTriangle(shade, currentMesh->projectedTris[i]);

        }

    }

}

void ObjectSet::drawAllWithNormals(Drawer* drawer, Camera* camera, Display* display) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (drawer == nullptr) {
        logWrite("Called ObjectSet->drawAllWithNormals(Drawer*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet->drawAllWithNormals(Drawer*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called ObjectSet->drawAllWithNormals(Drawer*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Set up
    this->projectAll(camera, display);
    Mesh* currentMesh;
    Vec2* vecStart = new Vec2(); 
    Vec2* vecEnd = new Vec2();

    // Main loop
    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentMesh = this->iterGetObj()->mesh;

        for (int i = 0; i < currentMesh->triCount; i++) {
        
            // Skip if tri cant be seen by cam on the outfacing side
            if (!camera->canSee(currentMesh->tris[i])) continue;

            // Find a shade based on the lighting vec
            double lightAngle = currentMesh->tris[i]->normal->getAngle(camera->lightingVec);
            double lightFactor = lightAngle / 180;

            Uint32 shade = currentMesh->color;
            shade = Color::setBrightness(shade, lightFactor);

            // Draw the tri    
            drawer->drawTriangle(shade, currentMesh->projectedTris[i]);

        }

        // Draw normals
        for (int i = 0; i < currentMesh->triCount; i++) {

            // Skip if tri cant be seen face on by cam
            if (!camera->canSee(currentMesh->tris[i])) continue;

            Vec3* triCenter;
            Vec3* normalOffset;
            Vec3* triNormal;

            // Get projected coords for normal start and end
            triCenter = currentMesh->tris[i]->getCenter();
            normalOffset = currentMesh->tris[i]->normal->copy()->normalise(1);
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

void ObjectSet::log() {

    this->list->log();
    return;

}
