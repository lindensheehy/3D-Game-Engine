#ifndef MeshClass
#define MeshClass

#include "Vec2Class.h"
#include "Vec3Class.h"
#include "Tri2Class.h"
#include "Tri3Class.h"

#include "../log/log.cpp"

class Mesh {
    /*
        This is the class used to define and transform meshes, some default meshes are populted after a call to initMeshes()
        Contains transformation functions
        The reason there is a verticies list and a tri list is to simplify transformations and to use less memory
        The verticies stores the actual points, and the tris list only point to values in the verticies list
        Same goes for the normals
    */

    public:

        // Class used to store index maps
        class IndexMap {
            /*
                This contains an array of size 4n where n is the input size
                Each set of 4 elements contains the index to various vecs for the triangles in a mesh
            */

            public:

                // Readable Indexes
                static const int VERTEX1 = 0;
                static const int VERTEX2 = 1;
                static const int VERTEX3 = 2;
                static const int NORMAL = 3;

                // Instance variables
                int* map;
                int size;

                // Constructor
                IndexMap(int size);

                // Destructor
                ~IndexMap();

                // Instance variables
                IndexMap* copy();
                void setGroup(int index, int v1, int v2, int v3, int normal);
                void setValue(int index, int subIndex, int value);
                void getGroup(int index, int* v1, int* v2, int* v3, int* normal);
                int getValue(int index, int subIndex);

        };

        // Meshes, populated from initMeshes()
        static Mesh* cubeMesh;
        static Mesh* tetrahedronMesh;

        /*   Instance Variables   */

        Vec3** verticies;
        Vec3** normals;
        Tri3** tris;
        int vertexCount;
        int normalCount;
        int triCount;
        Uint32 color;

        // Maps vecs from verticies and normals to tris
        IndexMap* indexMap;

        // For projection
        Vec2** projectedVerticies;
        Tri2** projectedTris;

        // Constructor
        Mesh();

        // Destructor
        ~Mesh();

        // Instance Funtions
        Mesh* copy();
        Mesh* move(double dx, double dy, double dz);
        Mesh* scale(double fx, double fy, double fz);
        Mesh* rotate(double yaw, double pitch, double roll, Vec3* around = nullptr);
        Mesh* setColor(Uint32 color);
        void mapTris();

        // Class functions
        static void initMeshes();

};

Mesh* Mesh::cubeMesh = nullptr;
Mesh* Mesh::tetrahedronMesh = nullptr;

#endif