#ifndef CameraClass
#define CameraClass

#include "Vec2Class.h"
#include "Vec3Class.h"
#include "MeshClass.h"

class Camera {
    public:
        
        // Instance variables
        Vec3* pos;
        Vec3* velocity;
        Vec3* acceleration;

        double yaw;
        double pitch;
        double roll;
        Vec3* facingDirection;  // Vector which points in the same direction the camera is facing
        Vec2* fov;              // degrees of fov on the x and y axis
        double movementSpeed;   // Movement speed in units per second

        Vec3* lightingVec;      // This is the vector representing the direction of the global light source for this camera

        // Constructor
        Camera();

        // Destructor
        ~Camera();

        // Instance functions
        void setPos(double x, double y, double z);
        void setPos(Vec3* position);
        void setVelocity(double x, double y, double z);
        void setVelocity(Vec3* velocity);
        void setAcceleration(double x, double y, double z);
        void setAcceleration(Vec3* acceleration);
        void setFacingDirection(double x, double y, double z);
        void setFacingDirection(Vec3* facingDirection);
        void setFov(double x, double y);
        void setFov(Vec2* fov);
        void setLightingVec(double x, double y, double z);
        void setLightingVec(Vec3* lightingVec);
        void rotate(double yaw, double pitch, double roll);
        void project(Vec3* vec, Vec2* displayPos);
        void project(Mesh* mesh);

    private:

        void rolloverAngles();
        
};

#endif