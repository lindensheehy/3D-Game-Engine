#pragma once

#include "Vec2Class.h"
#include "Vec3Class.h"
#include "Tri2Class.h"
#include "Tri3Class.h"

#include "../log/log.h"

class Mesh {

    /*
        This is the class used to define and transform meshes, some default meshes are populted after a call to initMeshes()
        Contains transformation functions
        The reason there is a verticies list and a tri list is to simplify transformations and to use less memory
        The verticies list stores the actual points, and the tris list only point to values in the verticies list
        Same goes for the normals
    */

    public:

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
                IndexMap(int size);

                // Destructor
                ~IndexMap();

                /*   Instance Functions   */

                // Creates a copy of the instance, and returns a pointer to it.
                IndexMap* copy();

                // Sets the values of the Set item at a given index
                void setGroup(int index, int v1, int v2, int v3, int normal);
                //void setValue(int index, int subIndex, int value);

                // Gets the values of the Set item at a given index. These values will be placed into the pointers given to the function.
                void getGroup(int index, int* v1, int* v2, int* v3, int* normal);
                //int getValue(int index, int subIndex);

        };

        // Meshes, populated from initMeshes()
        static Mesh* cubeMesh;
        static Mesh* tetrahedronMesh;

        /*   Instance Variables   */

        // List containing pointers to the verticies in the mesh.
        Vec3** verticies;

        // List containing pointers to the normals for the triangles in the mesh
        Vec3** normals;

        // List containing the triangles making up the mesh. All vecs within these triangles are the same ones from 'verticies' list.
        Tri3** tris;

        // Variables which count how many items are in each of the above lists. used for list iteration.
        int vertexCount, normalCount, triCount;

        // The color which the mesh should appear as.
        Uint32 color;

        // Maps vecs from verticies and normals to tris
        IndexMap* indexMap;

        // Contains the position on the window which thier respective points from the Vec3 list should appear
        Vec2** projectedVerticies;

        // Same as 'tris' list. all the vecs witihin these triangles are the same ones from 'projectedVerticies' list.
        Tri2** projectedTris;


        // Constructor
        Mesh();

        // Destructor
        ~Mesh();


        /*   Instance Funtions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Mesh* copy();

        // Moves all the Vec3 objects within 'verticies' by the specified distance.
        Mesh* move(double dx, double dy, double dz);

        // Scales the mesh by a given factor on each axis. Simply applies these factors to each component of every Vec3 object.
        Mesh* scale(double fx, double fy, double fz);

        // Rotates all the Vec3 objects by the specified angles. just calls Vec3->rotate() for each Vec3.
        Mesh* rotate(double yaw, double pitch, double roll, Vec3* around = nullptr);

        // Sets the color of the mesh
        Mesh* setColor(Uint32 color);

        // This uses the IndexMap to map the Tri3 vectors so that they point to Vec3 objects from the verticies and normals lists.
        // Also does the same thing for the projected versions of both.
        // Should be called when creating a custom mesh. This is done by default for the standard meshes.
        void mapTris();


        /*   Class functions   */

        // Initializes all the standard meshes. such as cubeMesh for example.
        static void initMeshes();

};

// Declare the standard meshes.
Mesh* Mesh::cubeMesh = nullptr;
Mesh* Mesh::tetrahedronMesh = nullptr;
