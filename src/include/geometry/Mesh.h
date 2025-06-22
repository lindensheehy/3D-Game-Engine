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
        This is the class used to define and transform meshes
        Some default meshes are populted after initMeshes() is called

        This mesh design does not store the triangles directly. Instead, it uses IndexMap
        IndexMap stores the index of each vertex and the normal for each triangle index
        Check out the IndexMap interface defined inside this class for more information

        All the vector data for the mesh is stored in a single contiguous buffer
        This means repeated access is fast within the vector data, even across 'seperate' arrays

        When using the default meshes, they should be copied (via Mesh::copy()) before they are modified
    */

    public:

        // Default meshes, populated from initMeshes()
        // These will be removed when I implement mesh importing from files (postponed until V2)
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
                These indexes refer to the position of the vectors in their respective array.
            */

            public:

                // List item for the map array
                struct Set {
                    int vertex1;
                    int vertex2;
                    int vertex3;
                    int normal;
                };


                /*   Instance Variables   */
                
                Set* map;
                int size;


                // Constructor (see IndexMap::init())
                IndexMap() : map(nullptr), size(0) {}

                // Destructor
                ~IndexMap();


                /*   Instance Functions   */

                // This does the actual construction, since IndexMap is stack allocated in Mesh
                void init(int size);

                // This is the equivalent to a deep copy, just sets all the instance variables of this to that of 'other'
                void setState(const IndexMap* other);

                // Sets the values of the Set item at a given index
                void setGroup(int index, int v1, int v2, int v3, int normal);

                // Gets the values of the Set item at a given index. These values will be placed into the pointers given.
                void getGroup(int index, int* v1, int* v2, int* v3, int* normal) const;

        };

    public:

        /*   Instance Variables   */

        const int vertexCount, normalCount, triCount;

        Vec3* vertices;
        Vec3* normals;

        IndexMap indexMap;

        // The color which the mesh should appear as.
        // This will be changed in the near future, each triangle should have their own color/texture (postponed until V2)
        uint32 color;


        // Constructor
        Mesh(int vertexCount, int normalCount, int triCount);

        // Destructor
        ~Mesh();


        /*   Instance Funtions   */

        // Deep copy
        Mesh* copy() const;

        // Returns the center of the mesh (average of all verticies)
        // This returns a pointer to a private instance variable. It should be copied before being modified
        Vec3* getCenter(); 

        // Moves the mesh by the specified distance. Just calls Vec3::add() for each vertex.
        Mesh* move(Vec3* dist);
        Mesh* move(float dx, float dy, float dz);

        // Scales the mesh by a given factor on each axis. Just calls Vec3::scale() for each vertex.
        Mesh* scale(float factor);
        Mesh* scale(float fx, float fy, float fz);

        // Rotates all the Vec3 objects by the specified angles. Just calls Vec3::rotate() for each vertex.
        Mesh* rotate(Vec3* angle, Vec3* around);
        Mesh* rotate(float yaw, float pitch, float roll, Vec3* around = nullptr);

        // Sets the color of the mesh
        Mesh* setColor(uint32 color);

        // This sets all the normals to the assumed values using cross products
        // These will always face outwards from the center of the mesh
        void updateNormals();


        /*   Class functions   */

        // Initializes all the standard meshes. Such as cubeMesh for example.
        // Temporary, while I implement mesh file importing (postponed until V2)
        static void initMeshes();

    private:

        /*
            I also allocate the memory for rendering vertex data here
            This allows for better cache locality during rendering, plus it just keeps things organized in memory
            The Renderer class is friended for this reason, as no other piece of this app needs to know about this memory
        */

        friend class Graphics::Rendering::Renderer;

        Vec2* screenVertices;       // Screen space data
        Vec3* cameraVertices;       // Camera space data
        Vec3* transformedNormals;   // Rotated versions of the normals (with respect to object and camera rotation)


        // This is the main pointer to the memory block owned by this mesh
        // This memory holds all of "vertices", "normals", "screenVertices", "cameraVertices", and "transformedNormals"
        void* mem;
        int memSize;

        // The center of the mesh. Cached here because its expensive to compute
        Vec3 center;
        bool centerValid;

};

}
