#include "../class-headers/CameraClass.h"

#include "../class-headers/Vec2Class.h"
#include "../class-headers/Vec3Class.h"
#include "../class-headers/MeshClass.h"


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
void Camera::setPos(double x, double y, double z) {
    this->pos->x = x;
    this->pos->y = y;
    this->pos->z = z;
    return;
}

void Camera::setPos(Vec3* position) {

    if (position == nullptr) {
        logWrite("Called Camera->setPos(Vec3*) on a null pointer!", true);
        return;
    }

    delete this->pos;
    this->pos = position->copy();
}

void Camera::setVelocity(double x, double y, double z) {
    this->velocity->x = x;
    this->velocity->y = y;
    this->velocity->z = z;
    return;
}

void Camera::setVelocity(Vec3* velocity) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (velocity == nullptr) {
        logWrite("Called Camera->setVelocity(Vec3*) on a null pointer!", true);
        return;
    }

    delete this->velocity;
    this->velocity = velocity->copy();
}

void Camera::setAcceleration(double x, double y, double z) {
    this->acceleration->x = x;
    this->acceleration->y = y;
    this->acceleration->z = z;
    return;
}

void Camera::setAcceleration(Vec3* acceleration) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (acceleration == nullptr) {
        logWrite("Called Camera->setAcceleration(Vec3*) on a null pointer!", true);
        return;
    }

    delete this->acceleration;
    this->acceleration = acceleration->copy();
}

void Camera::setFacingDirection(double x, double y, double z) {
    this->facingDirection->x = x;
    this->facingDirection->y = y;
    this->facingDirection->z = z;
    return;
}

void Camera::setFacingDirection(Vec3* facingDirection) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (facingDirection == nullptr) {
        logWrite("Called Camera->setFacingDirection(Vec3*) on a null pointer!", true);
        return;
    }

    delete this->facingDirection;
    this->facingDirection = facingDirection->copy();
    return;
}

void Camera::setFov(double x, double y) {
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

void Camera::setLightingVec(double x, double y, double z) {
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

void Camera::rotate(double yaw, double pitch, double roll) {

    // Update angles
    this->yaw += yaw;
    this->pitch += pitch;
    this->roll += roll;
    this->rolloverAngles();

    // Find new facing direction vector
    this->facingDirection->set(0, 0, 1);
    this->facingDirection->rotate(-this->yaw, -this->pitch, this->roll);
}

void Camera::project(Vec3* vec, Vec2* displayPos) {
    /*
        This returns a value between 0 and 1 which determines how far along each axis the given point should be drawn
        Can return values outside the 0-1 range, in this case the point lies off screen, but the location might still be needed
        These values are returned through the displayPos argument
    */

    // Address error cases, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec2*) with 'vec' being a null pointer!", true);
        return;
    }

    if (displayPos == nullptr) {
        logWrite("Called Camera->setAcceleration(Vec3*) with 'displayPos' being a null pointer!", true);
        return;
    }
    
    // Get points location relative to the cameras position and rotation
    Vec3* relative = vec->copy();
    relative->sub(this->pos);
    relative->rotate(this->yaw, 0, 0);
    relative->rotate(0, this->pitch, 0);

    // If the point is behind the camera
    if (relative->z < 0) {
        delete relative;
        displayPos->x = -1;
        displayPos->y = -1;
        return;
    }

    // Find the distance along the x,z axis, and the dy from the camera to the vec, this is used to find pitch
    Vec2* tempVar = new Vec2(relative->x, relative->z);
    double dist = tempVar->magnitude();
    double dy = relative->y - this->pos->y;
    delete tempVar;

    // Get the angle the point makes from the camera position on
    double angleYaw = getAngle(relative->x, relative->z);       // Angle from the +z axis
    double anglePitch = (double) 90 - getAngle(dist, dy);       // Angle from the +y axis, 90 - becuase its not against the axis used for getAngle

    // Gets the screen position given the angles found and the camera rotation angles
    /* ---  YAW  --- */

    double camYawFrom = -((double) this->fov->x / 2);
    double camYawTo = ((double) this->fov->x / 2);
    if (angleYaw > 180) {
        angleYaw -= 360;
    }

    double locationX = inRange(angleYaw, (double) -180, (double) 180);

    /* ---  PITCH  --- */
    double camPitchFrom = -(this->fov->y / 2);
    double camPitchTo = (this->fov->y / 2);
    if (anglePitch > 180) {
        anglePitch -= 360;
    }

    double locationY = inRange(anglePitch, (double) -180, (double) 180);

    // Value adjusting

    /*
        This code converts the range value between -180 and 180 into a value within the fov where values outside of 0-1 mean its outside the fov
        This is an extremely simplified version of the formula so it looks like nonsense but this is the math:
        First find the decimal value between -180 and 180 which represents the start of the fov
        value = (360 - k) / (2 * 360)
        Then use this value so find the new decimal for the posision
        pos = (360 * (oldpos - value)) / fov
        so this all simplifies to the math below, with a lot of type casting because I dont trust cpp auto typing
    */

    locationX = (((double) 180 * ((double) 2 * locationX - (double) 1)) / this->fov->x) + ((double) 0.5);
    locationY = (((double) 180 * ((double) 2 * locationY - (double) 1)) / this->fov->y) + ((double) 0.5);

    displayPos->x = locationX;
    displayPos->y = locationY;

    delete relative;

    return;
}

void Camera::project(Mesh* mesh) {

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

void Camera::rolloverAngles() {
    while (this->yaw > (double) 360) {
        this->yaw -= 360;
    }
    while (this->yaw < (double) 0) {
        this->yaw += 360;
    }
    while (this->pitch > (double) 360) {
        this->pitch -= 360;
    }
    while (this->pitch < (double) 0) {
        this->pitch += 360;
    }
    while (this->roll > (double) 360) {
        this->roll -= 360;
    }
    while (this->roll < (double) 0) {
        this->roll += 360;
    }
}