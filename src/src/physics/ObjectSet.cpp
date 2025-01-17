#include "physics/ObjectSet.h"


/* -------------- */
/* --- Object --- */
/* -------------- */

// Constructors
Object::Object() {

    this->mesh = nullptr;
    
    this->pos = new Vec3(0, 0, 0);
    this->rotation = new Vec3(0, 0, 0);
    this->scale = new Vec3(1, 1, 1);
    this->velocity = new Vec3(0, 0, 0);
    this->gravity = new Vec3(0, 0, 0);

    this->opacity = 1;

    this->mass = 100;
    this->gravityFactor = 1;
    this->frictionFactor = 1;
    this->bounceFactor = 1;

    this->lastRotation = this->rotation->copy();
    this->lastScale = this->scale->copy();

    return;

}

Object::Object(Mesh* mesh) {

    this->mesh = mesh;

    this->pos = new Vec3();
    this->velocity = new Vec3();
    this->gravity = new Vec3();

    this->opacity = 1;

    this->mass = 100;
    this->gravityFactor = 1;
    this->frictionFactor = 1;
    this->bounceFactor = 1;

    return;

}

// Destructor
Object::~Object() {

    if (this->mesh != nullptr) delete this->mesh;

    if (this->pos != nullptr) delete this->pos;
    if (this->velocity != nullptr) delete this->velocity;
    if (this->gravity != nullptr) delete this->gravity;

}

// Instance functions
Object* Object::copy() {

    Object* ret = new Object();

    ret->mesh = this->mesh;

    ret->pos = this->pos;
    ret->velocity = this->velocity;
    ret->gravity = this->gravity;

    ret->mass = this->mass;
    ret->gravityFactor = this->gravityFactor;
    ret->frictionFactor = this->frictionFactor;
    ret->bounceFactor = this->bounceFactor;

    return ret;

}

Vec3* Object::getCenter() {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->getCenter() while Object->mesh was nullptr!", true);
        return nullptr;
    }

    return this->mesh->getCenter();

}

Object* Object::move(Vec3* dist) {

    // Log the error cases
    if (dist == nullptr) {
        logWrite("Called Object->move(Vec3*) with 'dist' being a null pointer!", true);
        return nullptr;
    }

    this->pos->add(dist);
    return this;

}

Object* Object::move(double dx, double dy, double dz) {

    this->pos->add(dx, dy, dz);
    return this;
    
}

Object* Object::scaleBy(double factor) {

    this->scale->scale(factor);
    return this;

}

Object* Object::scaleBy(double fx, double fy, double fz) {

    this->scale->scale(fx, fy ,fz);
    return this;

}

Object* Object::rotate(Vec3* angle, Vec3* around) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotate(Vec3*, Vec3*) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->rotate(angle, around);
    return this;

}

Object* Object::rotate(double yaw, double pitch, double roll, Vec3* around = nullptr) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotate(double, double, double, Vec3*) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->rotate(yaw, pitch, roll, around);
    return this;

}

Object* Object::rotateSelf(Vec3* angle) {

    // Log the error case
    if (angle == nullptr) {
        logWrite("Called Object->rotateSelf(Vec3*) on a nullptr!", true);
        return nullptr;
    }

    this->rotation->add(angle);
    return this;

}

Object* Object::rotateSelf(double yaw, double pitch, double roll) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotateSelf(double, double, double) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->rotation->add(yaw, pitch, roll);
    return this;

}

Object* Object::setColor(uint32 color) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->setColor(uint32) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->mesh->setColor(color);
    return this;

}

void Object::doPhysics(double dt) {

    double dtSeconds = dt / 1000;

    Vec3* delta = new Vec3();

    delta->set(this->velocity)->scale(dtSeconds);
    this->pos->add(delta);

    delta->set(this->gravity)->scale(dtSeconds)->scale(this->gravityFactor);
    this->velocity->add(delta);

    delete delta;

}

void Object::doFloorCollision(double y) {

    return;

}

void Object::update() {
    
    // Update rotation if nessecary
    if ( !(this->rotation->is(this->lastRotation)) ) {

        double dx = this->rotation->x - this->lastRotation->x;
        double dy = this->rotation->y - this->lastRotation->y;
        double dz = this->rotation->z - this->lastRotation->z;

        this->mesh->rotateSelf(dx, dy, dz);

        this->lastRotation->set(this->rotation);

    }

    // Update scale if nessecary
    if ( !(this->scale->is(this->lastScale)) ) {

        double fx = this->scale->x / this->lastScale->x;
        double fy = this->scale->y / this->lastScale->y;
        double fz = this->scale->z / this->lastScale->z;

        this->mesh->scale(fx, fy, fz);

        this->lastScale->set(this->scale);

    }
    
}

bool Object::collides(Object* other) {

    return false;

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

    // Log the error case
    if (obj == nullptr) {
        logWrite("Called ObjectSet->pushBack(Object*) on a null pointer!", true);
        return;
    }
    
    this->list->pushBack(obj);
    return;

}

void ObjectSet::pushBack(Object* obj, int id) {

    // Log the error case
    if (obj == nullptr) {
        logWrite("Called ObjectSet->pushBack(Object*, int) on a null pointer!", true);
        return;
    }
    
    this->list->pushBack(obj, id);
    return;

}

void ObjectSet::pushFront(Object* obj) {

    // Log the error case
    if (obj == nullptr) {
        logWrite("Called ObjectSet->pushFront(Object*) on a null pointer!", true);
        return;
    }

    this->list->pushFront(obj);
    return;

}

void ObjectSet::pushFront(Object* obj, int id) {

    // Log the error case
    if (obj == nullptr) {
        logWrite("Called ObjectSet->pushFront(Object*, int) on a null pointer!", true);
        return;
    }

    this->list->pushFront(obj, id);
    return;
    
}

void ObjectSet::moveAll(Vec3* dist) {

    // Log the error case
    if (dist == nullptr) {
        logWrite("Called ObjectSet->moveAll(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->move(dist);

}

void ObjectSet::moveAll(double dx, double dy, double dz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) 
        this->iterGetObj()->move(dx, dy, dz);

}

void ObjectSet::setPosAll(Vec3* pos) {

    // Log the error case
    if (pos == nullptr) {
        logWrite("Called ObjectSet->setPosAll(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->pos->set(pos);

}

void ObjectSet::setPosAll(double x, double y, double z) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->pos->set(x, y, z); 

}

void ObjectSet::addVelocityAll(Vec3* v) {

    // Log the error case
    if (v == nullptr) {
        logWrite("Called ObjectSet->addVelocityAll(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity->add(v);

}

void ObjectSet::addVelocityAll(double vx, double vy, double vz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity->add(vx, vy, vz); 

}

void ObjectSet::setVelocityAll(Vec3* v) {

    // Log the error case
    if (v == nullptr) {
        logWrite("Called ObjectSet->setVelocityAll(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity->set(v);

}

void ObjectSet::setVelocityAll(double vx, double vy, double vz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity->set(vx, vy, vz);

}

void ObjectSet::setGravityAll(Vec3* gravity) {

    // Log the error case
    if (gravity == nullptr) {
        logWrite("Called ObjectSet->setAllGravity(Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())  
        this->iterGetObj()->gravity->set(gravity);

}

void ObjectSet::setGravityAll(double gx, double gy, double gz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->gravity->set(gx, gy, gz);

}

void ObjectSet::setGravityAll(double gy) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->gravity->set(0, gy, 0);

}

void ObjectSet::setOpacityAll(double opacity) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->opacity = opacity;

}

void ObjectSet::doAllPhysics(double dt) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->doPhysics(dt);

}

void ObjectSet::updateAll() {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->update();

}

void ObjectSet::projectAll(Camera* camera, Display* display) {

    // Log the error cases
    if (camera == nullptr) {
        logWrite("Called ObjectSet->projectAll(Camera*, Display*) with 'camera' being a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called ObjectSet->projectAll(Camera*, Display*) with 'display' being on a null pointer!", true);
        return;
    }

    this->updateAll();

    Object* currentObj;

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentObj = this->iterGetObj();

        camera->project(currentObj->mesh, currentObj->pos);
        display->toDisplayPos(currentObj->mesh);

    }

}

void ObjectSet::drawAll(Drawer* drawer, Camera* camera, Display* display) {

    // Log the error cases
    if (drawer == nullptr) {
        logWrite("Called ObjectSet->drawAll(Drawer*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet->drawAll(Drawer*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called ObjectSet->drawAll(Drawer*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Set up
    this->projectAll(camera, display);
    Object* currentObj;

    // First loop for opaque objects
    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentObj = this->iterGetObj();

        if (currentObj->opacity != 1) continue;

        for (int i = 0; i < currentObj->mesh->triCount; i++) {

            // Skip if all the vertices are behind the camera. This is flagged by marking the depth as inf
            if (
                currentObj->mesh->projectedTris[i]->v1->z == inf ||
                currentObj->mesh->projectedTris[i]->v2->z == inf ||
                currentObj->mesh->projectedTris[i]->v3->z == inf
            ) continue;
        
            // Skip if tri cant be seen by cam on the outfacing side
            if (!camera->canSee(currentObj->mesh->tris[i], currentObj->pos)) continue;

            // Find a shade based on the lighting vec
            double lightAngle = currentObj->mesh->tris[i]->normal->getAngle(camera->lightingVec);
            double lightFactor = lightAngle / 180;

            uint32 shade = currentObj->mesh->color;
            shade = Color::setBrightness(shade, lightFactor);

            // Draw the tri    
            drawer->drawTriangle(shade, currentObj->mesh->projectedTris[i]);

        }

    }

    // Second loop for transparent objects
    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentObj = this->iterGetObj();

        if (currentObj->opacity == 1) continue;

        for (int i = 0; i < currentObj->mesh->triCount; i++) {

            // Skip if all the vertices are behind the camera. This is flagged by marking the depth as inf
            if (
                currentObj->mesh->projectedTris[i]->v1->z == inf ||
                currentObj->mesh->projectedTris[i]->v2->z == inf ||
                currentObj->mesh->projectedTris[i]->v3->z == inf
            ) continue;
        
            // Skip if tri cant be seen by cam on the outfacing side
            if (!camera->canSee(currentObj->mesh->tris[i], currentObj->pos)) continue;

            // Find a shade based on the lighting vec
            double lightAngle = currentObj->mesh->tris[i]->normal->getAngle(camera->lightingVec);
            double lightFactor = lightAngle / 180;

            uint32 shade = currentObj->mesh->color;
            shade = Color::setBrightness(shade, lightFactor);

            // Draw the tri    
            drawer->drawTriangle(shade, currentObj->mesh->projectedTris[i], currentObj->opacity);

        }

    }

}

void ObjectSet::drawAll(Drawer* drawer, Camera* camera, Display* display, double opacity) {

    

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
    Object* currentObj;
    Vec3* vecStart = new Vec3(); 
    Vec3* vecEnd = new Vec3();

    // Loop for opaque objects
    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentObj = this->iterGetObj();

        if (currentObj->opacity != 1) continue;

        for (int i = 0; i < currentObj->mesh->triCount; i++) {

            // Skip if all the vertices are behind the camera
            if (
                currentObj->mesh->projectedTris[i]->v1->z == inf ||
                currentObj->mesh->projectedTris[i]->v2->z == inf ||
                currentObj->mesh->projectedTris[i]->v3->z == inf
            ) continue;

            // Skip if tri can't be seen by the camera
            if (!camera->canSee(currentObj->mesh->tris[i], currentObj->pos)) continue;

            // Find a shade based on the lighting vector
            double lightAngle = currentObj->mesh->tris[i]->normal->getAngle(camera->lightingVec);
            double lightFactor = lightAngle / 180;

            uint32 shade = currentObj->mesh->color;
            shade = Color::setBrightness(shade, lightFactor);

            // Draw the triangle
            drawer->drawTriangle(shade, currentObj->mesh->projectedTris[i]);

        }

        // Draw normals for opaque objects
        for (int i = 0; i < currentObj->mesh->triCount; i++) {

            if (!camera->canSee(currentObj->mesh->tris[i], currentObj->pos)) continue;

            Vec3* triCenter = currentObj->mesh->tris[i]->getCenter()->add(currentObj->pos);
            Vec3* normalOffset = currentObj->mesh->tris[i]->normal->copy()->normalise(1);
            Vec3* triNormal = triCenter->copy()->add(normalOffset);

            camera->project(triCenter, vecStart);
            camera->project(triNormal, vecEnd);
            display->toDisplayPos(vecStart);
            display->toDisplayPos(vecEnd);

            drawer->drawLine(Color::RED, vecStart->x, vecStart->y, vecEnd->x, vecEnd->y, vecStart->z, vecEnd->z);

            delete triCenter;
            delete normalOffset;
            delete triNormal;

        }

    }

    // Loop for transparent objects
    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

        currentObj = this->iterGetObj();

        if (currentObj->opacity == 1) continue;

        for (int i = 0; i < currentObj->mesh->triCount; i++) {

            // Skip if all the vertices are behind the camera
            if (
                currentObj->mesh->projectedTris[i]->v1->z == inf ||
                currentObj->mesh->projectedTris[i]->v2->z == inf ||
                currentObj->mesh->projectedTris[i]->v3->z == inf
            ) continue;

            // Skip if tri can't be seen by the camera
            if (!camera->canSee(currentObj->mesh->tris[i], currentObj->pos)) continue;

            // Find a shade based on the lighting vector
            double lightAngle = currentObj->mesh->tris[i]->normal->getAngle(camera->lightingVec);
            double lightFactor = lightAngle / 180;

            uint32 shade = currentObj->mesh->color;
            shade = Color::setBrightness(shade, lightFactor);

            // Draw the triangle with transparency
            drawer->drawTriangle(shade, currentObj->mesh->projectedTris[i], currentObj->opacity);

        }

        // Draw normals for transparent objects
        for (int i = 0; i < currentObj->mesh->triCount; i++) {

            if (!camera->canSee(currentObj->mesh->tris[i], currentObj->pos)) continue;

            Vec3* triCenter = currentObj->mesh->tris[i]->getCenter()->add(currentObj->pos);
            Vec3* normalOffset = currentObj->mesh->tris[i]->normal->copy()->normalise(1);
            Vec3* triNormal = triCenter->copy()->add(normalOffset);

            camera->project(triCenter, vecStart);
            camera->project(triNormal, vecEnd);
            display->toDisplayPos(vecStart);
            display->toDisplayPos(vecEnd);

            drawer->drawLine(Color::RED, vecStart->x, vecStart->y, vecEnd->x, vecEnd->y, vecStart->z, vecEnd->z);

            delete triCenter;
            delete normalOffset;
            delete triNormal;

        }

    }

    delete vecStart; delete vecEnd;

}

void ObjectSet::drawAllWithNormals(Drawer* drawer, Camera* camera, Display* display, double opacity) {

    

}
