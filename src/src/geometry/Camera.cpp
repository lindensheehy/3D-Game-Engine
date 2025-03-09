#include "geometry/Camera.h"


// Constructors
Camera::Camera() {

    this->pos = new Vec3();
    this->velocity = new Vec3();
    this->acceleration = new Vec3();

    this->facingDirection = new Vec3(0, 0, 1);
    this->fov = new Vec2();
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->movementSpeed = 3;
    this->sprintFactor = 2;

    this->lightingVec = new Vec3();

}

// Destructor
Camera::~Camera() {
    delete this->pos;
    delete this->velocity;
    delete this->acceleration;
    delete this->facingDirection;
    delete this->fov;
}

// Instance functions
void Camera::setPos(float x, float y, float z) {
    this->pos->x = x;
    this->pos->y = y;
    this->pos->z = z;
    return;
}

void Camera::setPos(Vec3* position) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (position == nullptr) {
        logWrite("Called Camera->setPos(Vec3*) on a null pointer!\n");
        return;
    }

    delete this->pos;
    this->pos = position->copy();
}

void Camera::setVelocity(float x, float y, float z) {
    this->velocity->x = x;
    this->velocity->y = y;
    this->velocity->z = z;
    return;
}

void Camera::setVelocity(Vec3* velocity) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (velocity == nullptr) {
        logWrite("Called Camera->setVelocity(Vec3*) on a null pointer!");
        return;
    }

    delete this->velocity;
    this->velocity = velocity->copy();
}

void Camera::setAcceleration(float x, float y, float z) {
    this->acceleration->x = x;
    this->acceleration->y = y;
    this->acceleration->z = z;
    return;
}

void Camera::setAcceleration(Vec3* acceleration) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (acceleration == nullptr) {
        logWrite("Called Camera->setAcceleration(Vec3*) on a null pointer!");
        return;
    }

    delete this->acceleration;
    this->acceleration = acceleration->copy();
}

void Camera::setFacingDirection(float x, float y, float z) {
    this->facingDirection->x = x;
    this->facingDirection->y = y;
    this->facingDirection->z = z;
    return;
}

void Camera::setFacingDirection(Vec3* facingDirection) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (facingDirection == nullptr) {
        logWrite("Called Camera->setFacingDirection(Vec3*) on a null pointer!");
        return;
    }

    delete this->facingDirection;
    this->facingDirection = facingDirection->copy();
    return;
}

void Camera::setFov(float x, float y) {
    this->fov->x = x;
    this->fov->y = y;
    return;
}

void Camera::setFov(Vec2* fov) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (fov == nullptr) {
        logWrite("Called Camera->setFov(Vec2*) on a null pointer!", true);
        return;
    }

    delete this->fov;
    this->fov = fov->copy();
    return;
}

void Camera::setLightingVec(float x, float y, float z) {
    this->lightingVec->x = x;
    this->lightingVec->y = y;
    this->lightingVec->z = z;
    return;
}

void Camera::setLightingVec(Vec3* lightingVec) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (lightingVec == nullptr) {
        logWrite("Called Camera->setLightingVec(Vec3*) on a null pointer!", true);
        return;
    }

    delete this->lightingVec;
    this->lightingVec = lightingVec->copy();
    return;
}

void Camera::setPreset(int preset) {

    switch (preset) {

        case 0:
            this->setPos(0, 0, -10);
            this->setFov(90, 54);
            this->setLightingVec(1, -5, 2); // downfacing off axis lighting
            this->movementSpeed = 50;
            break;

    }

}

void Camera::rotate(float yaw, float pitch, float roll) {

    // Update angles
    this->yaw += yaw;
    this->pitch += pitch;
    this->roll += roll;
    this->rolloverAngles();

    // Find new facing direction vector
    this->facingDirection->set(0, 0, 1);
    this->facingDirection->rotate(-this->yaw, -this->pitch, this->roll);

    return;

}

void Camera::project(Vec3* vec, Vec3* displayPos) const {

    /*
        Same as above, but this one places the distance between the point and the camera pos into the z component of displayPos
    */

    // Address error cases, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*) with 'vec' being a null pointer!", true);
        return;
    }

    if (displayPos == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*) with 'displayPos' being a null pointer!", true);
        return;
    }
    
    // Get points location relative to the cameras position and rotation
    displayPos->set(vec);
    displayPos->sub(this->pos);
    displayPos->rotate(this->yaw, 0, 0);
    displayPos->rotate(0, this->pitch, 0);

    displayPos->project();

    return;
    
}

void Camera::project(Vec3* vec, Vec3* displayPos, Vec3* offset) const {

    /*
        Same as above, but this one allows for the point to be treated as though its in a different location.
        'offset' acts as a relative position for the point from (0, 0, 0), so it is simply added to 'relative'
    */

    // Address error cases, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*, Vec3*) with 'vec' being a null pointer!", true);
        return;
    }

    if (displayPos == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*, Vec3*) with 'displayPos' being a null pointer!", true);
        return;
    }

    if (offset == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*, Vec3*) with 'offset' being a null pointer!", true);
        return;
    }
    
    // Get points location relative to the cameras position and rotation
    displayPos->set(vec);
    displayPos->add(offset);
    displayPos->sub(this->pos);
    displayPos->rotate(this->yaw, 0, 0);
    displayPos->rotate(0, this->pitch, 0);

    displayPos->project();

    return;

}

void Camera::project(Mesh* mesh) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called Camera->project(Mesh*) on a null pointer!", true);
        return;
    }
    
    // This uses the other project function to project each of the mesh verticies to the meshes projectedVerticies
    for (int i = 0; i < mesh->vertexCount; i++) {
        this->project(mesh->verticies[i], mesh->projectedVerticies[i]);
    }

}

void Camera::project(Mesh* mesh, Vec3* offset) const {

    // Address error case, but dont kill the process yet in case its not fatal
    if (mesh == nullptr) {
        logWrite("Called Camera->relativeProject(Mesh*, Vec3*) with 'mesh' being a null pointer!", true);
        return;
    }

    if (offset == nullptr) {
        logWrite("Called Camera->relativeProject(Mesh*, Vec3*) with 'offset' being a null pointer!", true);
        return;
    }
    
    // This uses the other project function to project each of the mesh verticies to the meshes projectedVerticies
    for (int i = 0; i < mesh->vertexCount; i++) {
        this->project(mesh->verticies[i], mesh->projectedVerticies[i], offset);
    }

}

bool Camera::canSee(Tri3* tri) const {

    // Find the distance to the triangle, relative to the camera position
    Vec3* distance;
    distance = tri->getCenter();
    distance->sub(this->pos);

    bool returnValue = tri->isFacing(distance);

    delete distance;

    return returnValue;

}

bool Camera::canSee(Tri3* tri, Vec3* offset) const {

    // Find the distance to the triangle, relative to the camera position, accounting for offset
    Vec3* distance;
    distance = tri->getCenter();
    distance->add(offset);
    distance->sub(this->pos);

    bool returnValue = tri->isFacing(distance);

    delete distance;

    return returnValue;

}

void Camera::rolloverAngles() {
    while (this->yaw > (float) 360) {
        this->yaw -= 360;
    }
    while (this->yaw < (float) 0) {
        this->yaw += 360;
    }
    while (this->pitch > (float) 360) {
        this->pitch -= 360;
    }
    while (this->pitch < (float) 0) {
        this->pitch += 360;
    }
    while (this->roll > (float) 360) {
        this->roll -= 360;
    }
    while (this->roll < (float) 0) {
        this->roll += 360;
    }
}
