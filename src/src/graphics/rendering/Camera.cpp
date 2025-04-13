#include "graphics/rendering/Camera.h"

using namespace Graphics::Rendering;


Camera::Camera() : 
pos(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0), 
facingAngle(0, 0, 0), facingVec(0, 0, 1), fov(0, 0) {

    this->movementSpeed = 3;
    this->sprintFactor = 2;

    this->lightingVec.set(0, 0, 0);

}

Camera::~Camera() {

}

void Camera::setPreset(int preset) {

    switch (preset) {

        case 0:
            this->pos.set(0, 0, -10);
            this->fov.set(90, 54);
            this->lightingVec.set(1, -5, 2); // downfacing off axis lighting
            this->movementSpeed = 50;
            break;

    }

}

void Camera::rotate(float yaw, float pitch, float roll) {

    // Update angles
    this->facingAngle.add(yaw, pitch, roll);
    this->rolloverAngles();

    // Find new facing direction vector
    this->facingVec.set(0, 0, 1);
    this->facingVec.rotate(0, -this->facingAngle.x, 0);
    this->facingVec.rotate(this->facingAngle.y, 0, 0);

    return;

}

void Camera::drawMesh(const Geometry::Mesh* mesh, const Geometry::Vec3* positionOffset) const {



}

void Camera::loadProjectionMatrix(Geometry::Matrix4* out) {

    // This also handles the nullptr check
    Geometry::Matrix4::identity(out);

    // X and Y scaling
    out->m[0][0] = this->nearPlane / this->frustumRight;
    out->m[1][1] = this->nearPlane / this->frustumTop;
    
    // Depth
    out->m[3][3] = (-1.0f) * (this->farPlane + this->nearPlane) / (this->farPlane - this->nearPlane);
    out->m[3][4] = (-2.0f * this->farPlane * this->nearPlane) / (this->farPlane - this->nearPlane);

    // Set W component to the negative of the original depth (Z)
    out->m[4][3] = -1.0f;

    return;

}

void Camera::project(const Geometry::Vec3* vec, Geometry::Vec3* out, const Geometry::Vec3* offset /* default value = nullptr */) const {

    /*
        This projects 'vec' into 'displayPos' based on this camera
        The optional 'offset' parameter allows passing a position to
    */

    // Address error cases, but dont kill the process yet in case its not fatal
    if (vec == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*, Vec3*) with arg1 as a nullptr!", true);
        return;
    }

    if (out == nullptr) {
        logWrite("Called Camera->project(Vec3*, Vec3*, Vec3*) with arg2 as a nullptr!", true);
        return;
    }
    
    // Get points location relative to the cameras position and rotation
    out->set(vec);
    out->add(offset);
    out->sub( &(this->pos) );
    out->rotate(this->facingAngle.x, this->facingAngle.y, 0);

    // // In case the new one is broken
    // displayPos->rotate(this->yaw, 0, 0);
    // displayPos->rotate(0, this->pitch, 0);

    out->project();

    return;

}

bool Camera::canSee(const Geometry::Tri3* tri) const {

    // Find the distance to the triangle, relative to the camera position
    Geometry::Vec3 distance;
    tri->getCenter( &(distance) );
    distance.sub( &(this->pos) );

    return tri->isFacing( &(distance) );

}

bool Camera::canSee(const Geometry::Tri3* tri, const Geometry::Vec3* offset) const {

    // Find the distance to the triangle, relative to the camera position, accounting for offset
    Geometry::Vec3 distance;
    tri->getCenter( &(distance) );
    distance.add(offset);
    distance.sub( &(this->pos) );

    return tri->isFacing( &(distance) );

}

void Camera::rolloverAngles() {

    rolloverAngle( &(this->facingAngle.x) );
    rolloverAngle( &(this->facingAngle.y) );
    rolloverAngle( &(this->facingAngle.z) );

    return;

}
