#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "geometry/Mesh.h"


class Camera {
    public:
        
        /*   Instance variables   */

        // Physics vectors
        Vec3* pos;
        Vec3* velocity;
        Vec3* acceleration;

        // Facing vectors. yaw -> about Y-axis, pitch -> about X-axis, roll -> about Z-axis
        float yaw, pitch, roll;

        // Vector which points in the same direction the camera is facing
        Vec3* facingDirection;

        // degrees of fov on the x and y axis
        Vec2* fov;

        // Movement speed in units per second
        float movementSpeed;
        float sprintFactor;

        // This is the vector representing the direction of the global light source for this camera
        Vec3* lightingVec;


        // Constructor
        Camera();

        // Destructor
        ~Camera();


        /*   Instance functions   */

        // Setters for all the instance variable vector objects.
        // The functions which take a Vec object as input DO NOT delete the object, it must be done manually.

        // Position 
        void setPos(float x, float y, float z);
        void setPos(Vec3* position);

        // Velocity
        void setVelocity(float x, float y, float z);
        void setVelocity(Vec3* velocity);

        // Acceleration
        void setAcceleration(float x, float y, float z);
        void setAcceleration(Vec3* acceleration);

        // Facing direction
        void setFacingDirection(float x, float y, float z);
        void setFacingDirection(Vec3* facingDirection);

        // Fov
        void setFov(float x, float y);
        void setFov(Vec2* fov);

        // Lighting Vector
        void setLightingVec(float x, float y, float z);
        void setLightingVec(Vec3* lightingVec);

        // Sets all the instance variables to one of the presets
        void setPreset(int preset);


        // This rotates the camera based on the input angles in DEGREES
        // Also updates the facing direction vector
        void rotate(float yaw, float pitch, float roll);

        // Takes a Vec3 object, and projects it into a Vec2 object.
        // The Vec2 components will be overwritten with the output of this function.
        // The values will be given in terms of fov (0 -> 1 is one fov length) so they dont mean anything for drawing until converted using a Display object
        // here the places distance between point and camera position into the z coordinate of displayPos
        void project(Vec3* vec, Vec3* displayPos) const;
        void project(Vec3* vec, Vec3* displayPos, Vec3* offset) const;

        // Runs the functions above for all the verticies in a mesh
        void project(Mesh* mesh) const;
        void project(Mesh* mesh, Vec3* offset) const;

        // Returns true if the camera can see the triangle, based on the location of the tri relative to the cam, and the normal vector of the tri
        bool canSee(Tri3* tri) const;
        bool canSee(Tri3* tri, Vec3* offset) const;

    private:

        // Just used to ensure angles between 0-360
        void rolloverAngles();
        
};
