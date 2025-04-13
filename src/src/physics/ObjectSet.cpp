#include "physics/ObjectSet.h"

using namespace Physics;


/* -------------- */
/* --- Object --- */
/* -------------- */

Object::Object() {

    this->mesh = nullptr;
    
    this->pos.set(0, 0, 0);
    this->rotation.set(0, 0, 0);
    this->scale.set(1, 1, 1);
    this->velocity.set(0, 0, 0);
    this->gravity.set(0, 0, 0);

    this->opacity = 1;

    this->mass = 100;
    this->gravityFactor = 1;
    this->frictionFactor = 1;
    this->bounceFactor = 1;

    this->lastRotation.set(this->rotation);
    this->lastScale.set(this->scale);

    return;

}

Object::Object(Geometry::Mesh* mesh) {

    this->mesh = mesh;

    this->pos.set(0, 0, 0);
    this->rotation.set(0, 0, 0);
    this->scale.set(1, 1, 1);
    this->velocity.set(0, 0, 0);
    this->gravity.set(0, 0, 0);

    this->opacity = 1;

    this->mass = 100;
    this->gravityFactor = 1;
    this->frictionFactor = 1;
    this->bounceFactor = 1;

    this->lastRotation.set(this->rotation);
    this->lastScale.set(this->scale);

    return;

}

Object* Object::copy() {

    Object* ret = new Object();

    ret->mesh = this->mesh;

    ret->pos.set(this->pos);
    ret->rotation.set(this->rotation);
    ret->scale.set(this->scale);
    ret->velocity.set(this->velocity);
    ret->gravity.set(this->gravity);

    ret->opacity = this->opacity;

    ret->mass = this->mass;
    ret->gravityFactor = this->gravityFactor;
    ret->frictionFactor = this->frictionFactor;
    ret->bounceFactor = this->bounceFactor;

    return ret;

}

Geometry::Vec3* Object::getCenter() {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->getCenter() while Object->mesh was nullptr!", true);
        return nullptr;
    }

    return this->mesh->getCenter();

}

Object* Object::move(Geometry::Vec3* dist) {

    // Log the error cases
    if (dist == nullptr) {
        logWrite("Called Object->move(Geometry::Vec3*) with 'dist' being a null pointer!", true);
        return nullptr;
    }

    this->pos.add(dist);
    return this;

}

Object* Object::move(float dx, float dy, float dz) {

    this->pos.add(dx, dy, dz);
    return this;
    
}

Object* Object::scaleBy(float factor) {

    this->scale.scale(factor);
    return this;

}

Object* Object::scaleBy(float fx, float fy, float fz) {

    this->scale.scale(fx, fy ,fz);
    return this;

}

Object* Object::rotate(Geometry::Vec3* angle) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotate(Geometry::Vec3*, Geometry::Vec3*) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->rotation.add(angle);
    return this;

}

Object* Object::rotate(float yaw, float pitch, float roll) {

    // Log the error case
    if (this->mesh == nullptr) {
        logWrite("Called Object->rotate(float, float, float, Geometry::Vec3*) while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->rotation.add(yaw, pitch, roll);
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

void Object::doPhysics(float dt) {

    float dtSeconds = dt / 1000;

    Geometry::Vec3 delta;

    delta.set(this->velocity).scale(dtSeconds);
    this->pos.add(delta);

    delta.set(this->gravity).scale(dtSeconds).scale(this->gravityFactor);
    this->velocity.add(delta);

    return;

}

void Object::doFloorCollision(float y) {

    return;

}

bool Object::collides(Object* other) {

    return false;

}



/* ----------------- */
/* --- ObjectSet --- */
/* ----------------- */

ObjectSet::ObjectSet() {

    this->list = new LinkedList<Object*>();

}

ObjectSet::~ObjectSet() {
    
    delete this->list;

}

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

void ObjectSet::moveAll(Geometry::Vec3* dist) {

    // Log the error case
    if (dist == nullptr) {
        logWrite("Called ObjectSet->moveAll(Geometry::Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->move(dist);

}

void ObjectSet::moveAll(float dx, float dy, float dz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) 
        this->iterGetObj()->move(dx, dy, dz);

}

void ObjectSet::setPosAll(Geometry::Vec3* pos) {

    // Log the error case
    if (pos == nullptr) {
        logWrite("Called ObjectSet->setPosAll(Geometry::Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->pos.set(pos);

}

void ObjectSet::setPosAll(float x, float y, float z) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->pos.set(x, y, z); 

}

void ObjectSet::addVelocityAll(Geometry::Vec3* v) {

    // Log the error case
    if (v == nullptr) {
        logWrite("Called ObjectSet->addVelocityAll(Geometry::Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity.add(v);

}

void ObjectSet::addVelocityAll(float vx, float vy, float vz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity.add(vx, vy, vz); 

}

void ObjectSet::setVelocityAll(Geometry::Vec3* v) {

    // Log the error case
    if (v == nullptr) {
        logWrite("Called ObjectSet->setVelocityAll(Geometry::Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity.set(v);

}

void ObjectSet::setVelocityAll(float vx, float vy, float vz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->velocity.set(vx, vy, vz);

}

void ObjectSet::setGravityAll(Geometry::Vec3* gravity) {

    // Log the error case
    if (gravity == nullptr) {
        logWrite("Called ObjectSet->setAllGravity(Geometry::Vec3*) on a null pointer!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())  
        this->iterGetObj()->gravity.set(gravity);

}

void ObjectSet::setGravityAll(float gx, float gy, float gz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->gravity.set(gx, gy, gz);

}

void ObjectSet::setGravityAll(float gy) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->gravity.set(0, gy, 0);

}

void ObjectSet::setOpacityAll(float opacity) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->opacity = opacity;

}

void ObjectSet::doAllPhysics(float dt) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext())
        this->iterGetObj()->doPhysics(dt);

}

void ObjectSet::drawAll(Graphics::Rendering::Renderer* renderer, Graphics::Rendering::Camera* camera) {

    // Log the error cases
    if (renderer == nullptr) {
        logWrite("Called ObjectSet->drawAll(Graphics::Rendering::Renderer*, Graphics::Rendering::Camera*) with arg1 as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet->drawAll(Graphics::Rendering::Renderer*, Graphics::Rendering::Camera*) with arg2 as a null pointer!", true);
        return;
    }

    Object* current;

    for (this->list->iterStart(0); this->list->iterHasNext(); this->list->iterNext()) {
        
        current = this->list->iterGetObj();

        renderer->drawObject(current, camera);

    }

    return;

}

void ObjectSet::drawAllWithNormals(Graphics::Rendering::Renderer* renderer, Graphics::Rendering::Camera* camera) {

    // Address error cases, but dont kill the process yet in case its not fatal
    if (renderer == nullptr) {
        logWrite("Called ObjectSet->drawAllWithNormals(Graphics::Rendering::Renderer*, Graphics::Rendering::Camera*) with arg1 as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet->drawAllWithNormals(Graphics::Rendering::Renderer*, Graphics::Rendering::Camera*) with arg2 as a null pointer!", true);
        return;
    }

    // No implementation yet

    return;

}
