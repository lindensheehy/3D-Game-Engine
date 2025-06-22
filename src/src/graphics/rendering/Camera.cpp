#include "graphics/rendering/Camera.h"

using namespace Graphics::Rendering;


Camera::Camera() : 
pos(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0), 
facingAngle(0, 0, 0), facingVec(0, 0, 1), fov(0, 0) {

    this->movementSpeed = 3;
    this->sprintFactor = 2;

    this->lightingVec.set(0, 0, 0);

    return;

}

void Camera::setPreset(int preset) {

    switch (preset) {

        case 0:
            this->pos.set(0, 0, -10);
            this->fov.set(90, 54);
            this->lightingVec.set(1, -5, 2); // downfacing off axis lighting
            this->movementSpeed = 50;
            break;

        default:
            break;

    }

    return;

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

void Camera::loadProjectionMatrix(Geometry::Matrix4* out) const {

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

void Camera::rolloverAngles() {

    rolloverAngle( &(this->facingAngle.x) );
    rolloverAngle( &(this->facingAngle.y) );
    rolloverAngle( &(this->facingAngle.z) );

    return;

}
