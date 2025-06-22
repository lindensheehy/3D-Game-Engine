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

    this->gravityFactor = 1;
    this->mass = 100;
    this->frictionFactor = 1;
    this->bounceFactor = 1;

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

    this->gravityFactor = 1;
    this->mass = 100;
    this->frictionFactor = 1;
    this->bounceFactor = 1;

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

    ret->gravityFactor = this->gravityFactor;
    ret->mass = this->mass;
    ret->frictionFactor = this->frictionFactor;
    ret->bounceFactor = this->bounceFactor;

    return ret;

}

Object* Object::move(Geometry::Vec3* dist) {

    if (dist == nullptr) {
        logWrite("Called Object->move(Geometry::Vec3*) on a nullptr!", true);
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

    if (this->mesh == nullptr) {
        logWrite("Called Object->rotate() while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->rotation.add(angle);
    return this;

}

Object* Object::rotate(float yaw, float pitch, float roll) {

    if (this->mesh == nullptr) {
        logWrite("Called Object->rotate() while Object->mesh was nullptr!", true);
        return nullptr;
    }

    this->rotation.add(yaw, pitch, roll);
    return this;

}

Object* Object::setColor(uint32 color) {

    if (this->mesh == nullptr) {
        logWrite("Called Object->setColor() while Object->mesh was nullptr!", true);
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

bool Object::collides(Object* other) {
    return false;
}



/* ----------------- */
/* --- ObjectSet --- */
/* ----------------- */

ObjectSet::ObjectSet() {

    this->list = new LinkedList<Object*>();

    return;

}

ObjectSet::~ObjectSet() {
    
    Object* current;

    for (this->list->iterStart(0); this->list->iterHasNext(); this->list->iterNext()) {

        current = this->list->iterGetObj();
        delete current;

    }

    delete this->list;

    return;

}

void ObjectSet::pushBack(Object* obj) {

    if (obj == nullptr) {
        logWrite("Called ObjectSet::pushBack(Object*) on a nullptr!", true);
        return;
    }
    
    this->list->pushBack(obj);
    return;

}

void ObjectSet::pushBack(Object* obj, int id) {

    if (obj == nullptr) {
        logWrite("Called ObjectSet::pushBack(Object*, int) on a nullptr!", true);
        return;
    }
    
    this->list->pushBack(obj, id);
    return;

}

void ObjectSet::pushFront(Object* obj) {

    if (obj == nullptr) {
        logWrite("Called ObjectSet::pushFront(Object*) on a nullptr!", true);
        return;
    }

    this->list->pushFront(obj);
    return;

}

void ObjectSet::pushFront(Object* obj, int id) {

    if (obj == nullptr) {
        logWrite("Called ObjectSet::pushFront(Object*, int) on a nullptr!", true);
        return;
    }

    this->list->pushFront(obj, id);
    return;
    
}

void ObjectSet::moveAll(Geometry::Vec3* dist) {

    if (dist == nullptr) {
        logWrite("Called ObjectSet::moveAll(Geometry::Vec3*) on a nullptr!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->move(dist);
    }

    return;

}

void ObjectSet::moveAll(float dx, float dy, float dz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->move(dx, dy, dz);
    }

    return;

}

void ObjectSet::setPosAll(Geometry::Vec3* pos) {

    if (pos == nullptr) {
        logWrite("Called ObjectSet::setPosAll(Geometry::Vec3*) on a nullptr!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->pos.set(pos);
    }

    return;

}

void ObjectSet::setPosAll(float x, float y, float z) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->pos.set(x, y, z); 
    }

    return;

}

void ObjectSet::addVelocityAll(Geometry::Vec3* v) {

    if (v == nullptr) {
        logWrite("Called ObjectSet::addVelocityAll(Geometry::Vec3*) on a nullptr!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->velocity.add(v);
    }

    return;

}

void ObjectSet::addVelocityAll(float vx, float vy, float vz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->velocity.add(vx, vy, vz); 
    }

    return;

}

void ObjectSet::setVelocityAll(Geometry::Vec3* v) {

    if (v == nullptr) {
        logWrite("Called ObjectSet::setVelocityAll(Geometry::Vec3*) on a nullptr!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->velocity.set(v);
    }

    return;

}

void ObjectSet::setVelocityAll(float vx, float vy, float vz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->velocity.set(vx, vy, vz);
    }

    return;

}

void ObjectSet::setGravityAll(Geometry::Vec3* gravity) {

    if (gravity == nullptr) {
        logWrite("Called ObjectSet::setAllGravity(Geometry::Vec3*) on a nullptr!", true);
        return;
    }

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->gravity.set(gravity);
    }

    return;

}

void ObjectSet::setGravityAll(float gx, float gy, float gz) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->gravity.set(gx, gy, gz);
    }

    return;

}

void ObjectSet::setGravityAll(float gy) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->gravity.set(0, gy, 0);
    }

    return;

}

void ObjectSet::setOpacityAll(float opacity) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->opacity = opacity;
    }

    return;

}

void ObjectSet::doAllPhysics(float dt) {

    for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
        this->iterGetObj()->doPhysics(dt);
    }

    return;

}

void ObjectSet::drawAll(Graphics::Rendering::Renderer* renderer, Graphics::Rendering::Camera* camera) {

    if (renderer == nullptr) {
        logWrite("Called ObjectSet::drawAll(Graphics::Rendering::Renderer*, Graphics::Rendering::Camera*) with arg1 as a nullptr!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet::drawAll(Graphics::Rendering::Renderer*, Graphics::Rendering::Camera*) with arg2 as a nullptr!", true);
        return;
    }

    /*
        Two passes are done here, because any objects with < 1.0 opacity must be drawn last
        Otherwise, they will render incorrectly. This is because non opaque objects dont contribute to the depth buffer
    */

    Object* current;

    // == 1.0 opacity pass through
    for (this->list->iterStart(0); this->list->iterHasNext(); this->list->iterNext()) {
        
        current = this->list->iterGetObj();

        if (current->opacity != 1.0) continue;

        renderer->drawObject(current, camera);

    }

    // < 1.0 opacity pass through
    for (this->list->iterStart(0); this->list->iterHasNext(); this->list->iterNext()) {
         
        current = this->list->iterGetObj();

        if (current->opacity == 1.0) continue;

        renderer->drawObject(current, camera);

    }

    return;

}

void ObjectSet::drawAllWithNormals(Graphics::Rendering::Renderer* renderer, Graphics::Rendering::Camera* camera) {

    if (renderer == nullptr) {
        logWrite("Called ObjectSet::drawAllWithNormals(Graphics::Rendering::Renderer*, Graphics::Rendering::Camera*) with arg1 as a nullptr!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called ObjectSet::drawAllWithNormals(Graphics::Rendering::Renderer*, Graphics::Rendering::Camera*) with arg2 as a nullptr!", true);
        return;
    }

    // No implementation yet (postponed until V2, this is a debug feature anyway)

    return;

}
