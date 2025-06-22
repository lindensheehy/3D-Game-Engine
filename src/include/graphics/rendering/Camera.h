#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "geometry/Matrix.h"
#include "geometry/Mesh.h"


namespace Graphics {
namespace Rendering {

class Camera {

    /*
        This class represents a Camera in 3d space, for rendering purposes

        Contains a handful of vectors for physics/geometry, alongside some rendering focused data
        Projection is handled here, because it is inherently tied to the camera state

        Some of the stuff in this class is just a skeleton of future plans
        These sections are labeled as such, and will likely be implementedor removed in V2
    */

    public:
        
        /*   Instance Variables   */

        Geometry::Vec3 pos;
        Geometry::Vec3 velocity;
        Geometry::Vec3 acceleration;

        // Contains the camera rotation data (ie. which way the camera is facing)
        // 'facingAngle' gives the yaw, pitch and roll (in degrees). 'facingVec' is a normalized spatial vector
        Geometry::Vec3 facingAngle;
        Geometry::Vec3 facingVec;

        // Degrees of fov on the x and y axis
        Geometry::Vec2 fov;

        
        /*
            --- NOT USED (postponed until V2) ---

            These values are used for projection

            'nearPlane' and 'farPlane' define the min and max depth vertices will be rendered at
            Any vertices outside this range will not be considered for rendering

            The frustum is symetric, so the 'Top' and 'Left' values are equivalent to 'Bottom' and 'Right' respectively
            These values are in relation to the width and height of the frustum at the near plane
            As they are scaled with depth, these effectively make up the width/height ratio of the frustum at any depth
        */

        float nearPlane;
        float farPlane;
        float frustumTop;
        float frustumRight;

        // Movement speed in units per second
        float movementSpeed;
        float sprintFactor;

        // This is the vector representing the direction of the global light source for this camera
        // This will be removed at some point, when I implement better lighting (postponed until V2)
        Geometry::Vec3 lightingVec;


        // Constructor
        Camera();


        /*   Instance functions   */

        // Sets all the instance variables to one of the presets
        void setPreset(int preset);

        // This rotates the camera based on the input angles in DEGREES
        // Also updates the facing direction vector
        void rotate(float yaw, float pitch, float roll);

        // Loads the projection matrix for this camera into 'out' (NOT USED)
        void loadProjectionMatrix(Geometry::Matrix4* out) const;

    private:

        // Just used to ensure all internal angle values are between 0-360
        void rolloverAngles();
        
};

}
}
