#pragma once

#include "util/Utility.h"

#include "graphics/rendering/Display.h"
#include "graphics/drawing/Drawer.h"

#include "geometry/Vec.h"
#include "geometry/Tri.h"
#include "geometry/Matrix.h"
#include "physics/ObjectSet.h"


namespace Graphics {
namespace Rendering {

class Renderer {

    /*
        This class is responsible for doing all the 3D rendering in this program
        This is basically just a 3D version of Graphics::Drawing::Drawer (in that its a high level drawing interface)
    */

    public:

        /*   Instance Variables   */

        Display* display;
        Drawing::PixelDrawer* pixelDrawer;


        // Constructor
        Renderer(Drawing::PixelDrawer* pixelDrawer, Display* display);


        /*   Instance Functions   */

        // Draws an Object instance to the screen
        void drawObject(Physics::Object* object, Camera* camera);

    private:

        // Draws a mesh to the screen (assumes the private Mesh buffers are populated by drawObject)
        void drawMesh(Geometry::Mesh* mesh, Camera* camera);

        // Draws a triangle onto the screen where 'a', 'b', and 'c' are the triangle vertices
        // Uses the Vec2s as screen space and the Vec3s as camera space (for depth purposes)
        void drawTri(
            uint32 color,
            Geometry::Vec2& a, Geometry::Vec3& a3,
            Geometry::Vec2& b, Geometry::Vec3& b3,
            Geometry::Vec2& c, Geometry::Vec3& c3
        );

        // This is the opacity value this Renderer will draw at
        // This is updated from drawObject, and only exists to avoid passing an opacity value between functions
        float drawerOpacity;

};

}
}
