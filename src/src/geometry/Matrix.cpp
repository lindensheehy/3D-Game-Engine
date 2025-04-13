#include "geometry/Matrix.h"

using namespace Geometry;


void Matrix4::log() {

    logWrite("Matrix4: [ ");

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            logWrite(this->m[i][j]);
            logWrite(" ");

        }

        logWrite("]\n         [ ");

    }

    return;

}

void Matrix4::set(const Matrix4& other) {

    memcpy(this->m, other.m, sizeof(this->m));

    return;

}

void Matrix4::set(const Matrix4* other) {
    
    memcpy(this->m, other->m, sizeof(this->m));

    return;

}

void Matrix4::mul(const Matrix4& other) {
    
    // Cache other.m as o
    float o[4][4];
    memcpy(o, other.m, sizeof(o));

    // Cache this->m as t
    float t[4][4];
    memcpy(t, this->m, sizeof(t));

    // Inlined matrix multiplication, rows of t (this) by columns of o (other)
    this->m[0][0] = (t[0][0] * o[0][0]) + (t[0][1] * o[1][0]) + (t[0][2] * o[2][0]) + (t[0][3] * o[3][0]);
    this->m[0][1] = (t[0][0] * o[0][1]) + (t[0][1] * o[1][1]) + (t[0][2] * o[2][1]) + (t[0][3] * o[3][1]);
    this->m[0][2] = (t[0][0] * o[0][2]) + (t[0][1] * o[1][2]) + (t[0][2] * o[2][2]) + (t[0][3] * o[3][2]);
    this->m[0][3] = (t[0][0] * o[0][3]) + (t[0][1] * o[1][3]) + (t[0][2] * o[2][3]) + (t[0][3] * o[3][3]);

    this->m[1][0] = (t[1][0] * o[0][0]) + (t[1][1] * o[1][0]) + (t[1][2] * o[2][0]) + (t[1][3] * o[3][0]);
    this->m[1][1] = (t[1][0] * o[0][1]) + (t[1][1] * o[1][1]) + (t[1][2] * o[2][1]) + (t[1][3] * o[3][1]);
    this->m[1][2] = (t[1][0] * o[0][2]) + (t[1][1] * o[1][2]) + (t[1][2] * o[2][2]) + (t[1][3] * o[3][2]);
    this->m[1][3] = (t[1][0] * o[0][3]) + (t[1][1] * o[1][3]) + (t[1][2] * o[2][3]) + (t[1][3] * o[3][3]);

    this->m[2][0] = (t[2][0] * o[0][0]) + (t[2][1] * o[1][0]) + (t[2][2] * o[2][0]) + (t[2][3] * o[3][0]);
    this->m[2][1] = (t[2][0] * o[0][1]) + (t[2][1] * o[1][1]) + (t[2][2] * o[2][1]) + (t[2][3] * o[3][1]);
    this->m[2][2] = (t[2][0] * o[0][2]) + (t[2][1] * o[1][2]) + (t[2][2] * o[2][2]) + (t[2][3] * o[3][2]);
    this->m[2][3] = (t[2][0] * o[0][3]) + (t[2][1] * o[1][3]) + (t[2][2] * o[2][3]) + (t[2][3] * o[3][3]);

    this->m[3][0] = (t[3][0] * o[0][0]) + (t[3][1] * o[1][0]) + (t[3][2] * o[2][0]) + (t[3][3] * o[3][0]);
    this->m[3][1] = (t[3][0] * o[0][1]) + (t[3][1] * o[1][1]) + (t[3][2] * o[2][1]) + (t[3][3] * o[3][1]);
    this->m[3][2] = (t[3][0] * o[0][2]) + (t[3][1] * o[1][2]) + (t[3][2] * o[2][2]) + (t[3][3] * o[3][2]);
    this->m[3][3] = (t[3][0] * o[0][3]) + (t[3][1] * o[1][3]) + (t[3][2] * o[2][3]) + (t[3][3] * o[3][3]);

    return;

}

void Matrix4::mul(const Matrix4* other) {

    if (other == nullptr) {
        logWrite("Matrix->mul(Matrix*) was called on a nullptr!", true);
        return;
    }

    this->mul( *(other) );

}

void Matrix4::mul(Vec3* vec) const {

    if (vec == nullptr) {
        logWrite("Matrix->mul(Vec3*) was called on a nullptr!", true);
        return;
    }

    float x = vec->x;
    float y = vec->y;
    float z = vec->z;

    /*
        Since this is a Vec3, the w component is assumed to be 1
    */

    vec->x = (
        (this->m[0][0] * x) +
        (this->m[0][1] * y) +
        (this->m[0][2] * z) +
        (this->m[0][3])
    );
    
    vec->y = (
        (this->m[1][0] * x) +
        (this->m[1][1] * y) +
        (this->m[1][2] * z) +
        (this->m[1][3])
    );

    vec->z = (
        (this->m[2][0] * x) +
        (this->m[2][1] * y) +
        (this->m[2][2] * z) +
        (this->m[2][3])
    );

    return;

}

void Matrix4::identity(Matrix4* out) {

    if (out == nullptr) {
        logWrite("Called Matrix::identity(Matrix*) on a nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    return;

}

void Matrix4::translation(float x, float y, float z, Matrix4* out) {

    if (out == nullptr) {
        logWrite("Called Matrix::translation(float, float, float, Matrix*) on a nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    out->m[0][3] = x;
    out->m[1][3] = y;
    out->m[2][3] = z;

    return;


}

void Matrix4::translation(const Vec3& vec, Matrix4* out) {
    
    if (out == nullptr) {
        logWrite("Called Matrix::translation(Vec3&, Matrix*) on a nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    out->m[0][3] = vec.x;
    out->m[1][3] = vec.y;
    out->m[2][3] = vec.z;

    return;

}

void Matrix4::translation(const Vec3* vec, Matrix4* out) {
    
    if (vec == nullptr) {
        logWrite("Called Matrix::translation(Vec3*, Matrix*) with arg1 as nullptr!", true);
        return;
    }

    if (out == nullptr) {
        logWrite("Called Matrix::translation(Vec3*, Matrix*) with arg2 as nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    out->m[0][3] = vec->x;
    out->m[1][3] = vec->y;
    out->m[2][3] = vec->z;

    return;

}

void Matrix4::scaling(float x, float y, float z, Matrix4* out) {

    if (out == nullptr) {
        logWrite("Called Matrix::scaling(float, float, float, Matrix*) on a nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    out->m[0][0] = x;
    out->m[1][1] = y;
    out->m[2][2] = z;

    return;

}

void Matrix4::scaling(const Vec3& vec, Matrix4* out) {
    
    if (out == nullptr) {
        logWrite("Called Matrix::scaling(Vec3&, Matrix*) on a nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    out->m[0][0] = vec.x;
    out->m[1][1] = vec.y;
    out->m[2][2] = vec.z;

    return;

}

void Matrix4::scaling(const Vec3* vec, Matrix4* out) {
    
    if (vec == nullptr) {
        logWrite("Called Matrix::scaling(Vec3*, Matrix*) with arg1 as nullptr!", true);
        return;
    }

    if (out == nullptr) {
        logWrite("Called Matrix::scaling(Vec3*, Matrix*) with arg2 as nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    out->m[0][0] = vec->x;
    out->m[1][1] = vec->y;
    out->m[2][2] = vec->z;

    return;

}

void Matrix4::rotationX(float angle, Matrix4* out) {

    if (out == nullptr) {
        logWrite("Called Matrix::rotationX(float, Matrix*) on a nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    float radians = toRadians(angle);

    out->m[1][1] = cos(radians);
    out->m[1][2] = -sin(radians);
    out->m[2][1] = sin(radians);
    out->m[2][2] = cos(radians);

    return;

}

void Matrix4::rotationY(float angle, Matrix4* out) {
    
    if (out == nullptr) {
        logWrite("Called Matrix::rotationY(float, Matrix*) on a nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    float radians = toRadians(angle);

    out->m[0][0] = cos(radians);
    out->m[2][0] = -sin(radians);
    out->m[0][2] = sin(radians);
    out->m[2][2] = cos(radians);

    return;

}

void Matrix4::rotationZ(float angle, Matrix4* out) {
    
    if (out == nullptr) {
        logWrite("Called Matrix::rotationZ(float, Matrix*) on a nullptr!", true);
        return;
    }

    Matrix4::identityNoCheck(out);

    float radians = toRadians(angle);

    out->m[0][0] = cos(radians);
    out->m[0][1] = -sin(radians);
    out->m[1][0] = sin(radians);
    out->m[1][1] = cos(radians);

    return;

}

void Matrix4::projection(float focalLengthX, float focalLengthY, Matrix4* out) {

    

}
