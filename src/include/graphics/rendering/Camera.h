#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "geometry/Matrix.h"
#include "geometry/Mesh.h"


namespace Graphics {
namespace Rendering {

class Camera {

    public:
        
        /*   Instance variables   */

        // Physics vectors
        Geometry::Vec3 pos;
        Geometry::Vec3 velocity;
        Geometry::Vec3 acceleration;

        // Tells which way the camera is facing
        // Angle gives the yaw, pitch and roll (in degrees). Vec is a normalized spatial vector
        Geometry::Vec3 facingAngle;
        Geometry::Vec3 facingVec;

        // Degrees of fov on the x and y axis
        Geometry::Vec2 fov;

        
        /*
            These values are used for projection

            'nearPlane' and 'farPlane' define the min and max depth vertices will be rendered at
            Any vertices outside this range will not be considered for rendering

            The frustum is symetric, so the 'Top' and 'Left' values are equivalent to 'Bottom' and 'Right' respectively
            The values in these are in relation to the width and height of the frustum at the near plane
            As they are scaled with depth, these effectively make up the width and height of the frustum at any depth
        */

        float nearPlane;
        float farPlane;
        float frustumTop;
        float frustumRight;

        // Movement speed in units per second
        float movementSpeed;
        float sprintFactor;

        // This is the vector representing the direction of the global light source for this camera
        // This will be removed at some point, when I implement better lighting
        Geometry::Vec3 lightingVec;


        // Constructor
        Camera();

        // Destructor
        ~Camera();


        /*   Instance functions   */

        // Sets all the instance variables to one of the presets
        void setPreset(int preset);

        // This rotates the camera based on the input angles in DEGREES
        // Also updates the facing direction vector
        void rotate(float yaw, float pitch, float roll);

        // Draws the mesh to the screen, based on this camera
        void drawMesh(const Geometry::Mesh* mesh, const Geometry::Vec3* positionOffset) const;

        // Loads the projection matrix for this camera into 'out'
        void loadProjectionMatrix(Geometry::Matrix4* out);

        // Takes a Vec3 object, and projects it into a Vec2 object.
        // The Vec2 components will be overwritten with the output of this function.
        // The values will be given in terms of fov (0 -> 1 is one fov length) so they dont mean anything for drawing until converted using a Display object
        // here the places distance between point and camera position into the z coordinate of displayPos
        void project(const Geometry::Vec3* vec, Geometry::Vec3* out, const Geometry::Vec3* offset = nullptr) const;

        // Runs the functions above for all the verticies in a mesh
        void project(Geometry::Mesh* mesh) const;
        void project(Geometry::Mesh* mesh, Geometry::Vec3* offset) const;

        // Returns true if the camera can see the triangle, based on the location of the tri relative to the cam, and the normal vector of the tri
        bool canSee(const Geometry::Tri3* tri) const;
        bool canSee(const Geometry::Tri3* tri, const Geometry::Vec3* offset) const;

    private:

        // Just used to ensure angles are between 0-360
        void rolloverAngles();
        
};

}
}
