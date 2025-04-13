#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"
#include "geometry/Tri.h"


// Forward declaration
namespace Graphics {
namespace Rendering {

class Renderer;

}
}


namespace Geometry {

class Mesh {

    /*
        This is the class used to define and transform meshes, some default meshes are populted after a call to initMeshes()
        The reason there is a verticies list and a tri list is to simplify transformations and to use less memory
        The verticies list stores the actual points, and the tris list only point to values in the verticies list
        Same goes for the normals
        The projected verticies use Vec3 objects to store depth. the x,y values are the screen coordinates and the z is the depth
    */

    public:

        // Meshes, populated from initMeshes()
        // These will be removed when I implement mesh importing from files
        static Mesh* tempMesh;
        static Mesh* cubeMesh;
        static Mesh* sphereMesh;
        static Mesh* tetrahedronMesh;
        static Mesh* capsuleMesh;

    private:

        class IndexMap {

            /*
                This contains an array named 'map' of the input size, where each item contains a Set struct.
                Each Set item contains the index to various vecs for the triangles in a mesh.
                These indexes refer to the position of the vectors in thier respective array.
            */

            public:

                // List items for the map variable
                struct Set {
                    int vertex1;
                    int vertex2;
                    int vertex3;
                    int normal;
                };

                // Instance variables
                Set* map;
                int size;

                // Constructor
                IndexMap();

                // Destructor
                ~IndexMap();

                /*   Instance Functions   */

                // This does the actual construction, since IndexMap is stack allocated in Mesh
                void init(int size);

                // This is the equivalent to a deep copy, just sets all the instance variables of this to that of other
                void setState(const IndexMap* other);

                // Sets the values of the Set item at a given index
                void setGroup(int index, int v1, int v2, int v3, int normal);

                // Gets the values of the Set item at a given index. These values will be placed into the pointers given to the function.
                void getGroup(int index, int* v1, int* v2, int* v3, int* normal) const;

        };

    public:

        /*   Instance Variables   */

        /*
            For all "vertices", "normals", and "tris":
            The list items are stored directly at the list location, not pointers
            This is done for performance, but also so they can be easily imported from files

            All three lists are also stored contiguously in memory, in one allocation
            So they are in the same place, for cache locality, and the pointers are just offset to allow this

            Also note the Tri3 objects in "tris" just point to Vec3 objects from the other 2 lists (no duplication)
        */

        const int vertexCount, normalCount, triCount;

        Vec3* vertices;
        Vec3* normals;
        Tri3* tris;

        // Maps vecs from verticies and normals to tris
        IndexMap indexMap;

        // The color which the mesh should appear as.
        // This will be changed in the near future, each triangle should have their own color/texture
        uint32 color;


        // Constructor
        Mesh(int vertexCount, int normalCount, int triCount);

        // Destructor
        ~Mesh();


        /*   Instance Funtions   */

        // Deep copy
        Mesh* copy() const;

        // Returns the center of the mesh (average of all verticies). This returns a reference to an instance variable.
        Vec3* getCenter(); 

        // Moves all the Vec3 objects within 'verticies' by the specified distance.
        Mesh* move(Vec3* dist);
        Mesh* move(float dx, float dy, float dz);

        // Scales the mesh by a given factor on each axis. Simply applies these factors to each component of every Vec3 object.
        Mesh* scale(float factor);
        Mesh* scale(float fx, float fy, float fz);

        // Rotates all the Vec3 objects by the specified angles. just calls Vec3->rotate() for each vertex.
        Mesh* rotate(Vec3* angle, Vec3* around);
        Mesh* rotate(float yaw, float pitch, float roll, Vec3* around = nullptr);

        // Sets the color of the mesh
        Mesh* setColor(uint32 color);

        void updateNormals();

        // This uses the IndexMap to map the Tri3 vectors so that they point to Vec3 objects from the verticies and normals lists.
        // Also does the same thing for the projected versions of both.
        // Should be called when creating a custom mesh. This is done by default for the standard meshes.
        void mapTris();


        /*   Class functions   */

        // Initializes all the standard meshes. Such as cubeMesh for example.
        // Temporary, while i implement mesh file importing
        static void initMeshes();

    private:

        /*
            I also store the memory for the screen coordinates of each vertex
            This allows for better cache locality during rendering, plus it just keeps things organized in memory
            The Renderer class is friended for this reason, as no other piece of this app cares about this memory
        */

        friend class Graphics::Rendering::Renderer;

        Vec2* screenVertices;       // Screen space data
        Vec3* cameraVertices;       // Camera space data
        Vec3* transformedNormals;   // Rotated versions of the normals (with respect to object and camera rotation)


        // This is the main pointer to the memory block owned by this mesh
        // This memory holds all of "vertices", "normals", and "tris"
        void* mem;
        int memSize;

        // The center of the mesh. Will be updated when the flag is false.
        Vec3 center;
        bool centerValid;

};

}
