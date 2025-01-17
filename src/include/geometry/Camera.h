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

        // Sets all the instance variables to one of the presets
        void setPreset(int preset);


        // This rotates the camera based on the input angles in DEGREES
        // Also updates the facing direction vector
        void rotate(double yaw, double pitch, double roll);

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



class Display {

    /*
        This class IS NOT the same as GuiClass.
        The gui class is used for making an actual window and drawing to it.
        This class simply defines an area within an existing window where things should be drawn.
        Think of it like a way to do split screen. you can define areas of any size and position which can act as the whole window.

        width and height are straightforward. the offsets are the distance from the top left for each.
        every length is in pixels.
    */

    public:

        // Instance variables
        int width, height;
        int widthOffset, heightOffset;


        /*   Constructors   */

        // No offset values. Sets both to 0.
        Display(int width, int height);

        // Given offset values
        Display(int width, int height, int widthOffset, int heightOffset);


        /*   Instance functions   */

        // Returns the center of the display area on the given axis relative to the whole gui window
        int middleX();
        int middleY();

        // The second step of projection. 
        // This takes the fov factor from the output of a projection call, and turns it into a pixel position on the gui window.
        // The return values of this are placed into the components of the input vector. meaning the old values are overwritten
        void toDisplayPos(Vec2* vec);

        // Same as above but supports depth in the z value. the z value is upscaled by 2^8 times in this
        void toDisplayPos(Vec3* vec);

        // Does the above step for each vertex in a mesh
        void toDisplayPos(Mesh* mesh);

};
