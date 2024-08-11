#pragma once

#include "../math/math.h"

#include "Vec2Class.h"
#include "Vec3Class.h"
#include "MeshClass.h"

// For logging error cases
#include "../log/log.h"


class Camera {
    public:
        
        /*   Instance variables   */

        // Physics vectors
        Vec3* pos;
        Vec3* velocity;
        Vec3* acceleration;

        // Facing vectors. yaw -> about Y-axis, pitch -> about X-axis, roll -> about Z-axis
        double yaw, pitch, roll;

        // Vector which points in the same direction the camera is facing
        Vec3* facingDirection;

        // degrees of fov on the x and y axis
        Vec2* fov;

        // Movement speed in units per second
        double movementSpeed;
        double sprintFactor;

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
        void setPos(double x, double y, double z);
        void setPos(Vec3* position);

        // Velocity
        void setVelocity(double x, double y, double z);
        void setVelocity(Vec3* velocity);

        // Acceleration
        void setAcceleration(double x, double y, double z);
        void setAcceleration(Vec3* acceleration);

        // Facing direction
        void setFacingDirection(double x, double y, double z);
        void setFacingDirection(Vec3* facingDirection);

        // Fov
        void setFov(double x, double y);
        void setFov(Vec2* fov);

        // Lighting Vector
        void setLightingVec(double x, double y, double z);
        void setLightingVec(Vec3* lightingVec);


        // This rotates the camera based on the input angles in DEGREES
        // Also updates the facing direction vector
        void rotate(double yaw, double pitch, double roll);

        // Takes a Vec3 object, and projects it into a Vec2 object.
        // The Vec2 components will be overwritten with the output of this function.
        // The values will be given in terms of fov (0 -> 1 is one fov length) so they dont mean anything for drawing until converted using a Display object
        void project(Vec3* vec, Vec2* displayPos);

        // Runs the function above for all the verticies in a mesh
        void project(Mesh* mesh);

    private:

        // Just used to ensure angles between 0-360
        void rolloverAngles();
        
};
