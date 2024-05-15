#ifndef MeshClass
#define MeshClass

#include <iostream>

#include "Vec2Class.h"
#include "Vec3Class.h"
#include "Tri2Class.h"
#include "Tri3Class.h"

#include "../log.cpp"

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
                IndexMap(int size) {
                    this->map = new int[size * 4];
                    this->size = size;
                }

                // Destructor
                ~IndexMap() {
                    delete this->map;
                }

                // Instance variables
                IndexMap* copy() {

                    IndexMap* newCopy = new IndexMap(this->size);

                    for (int i = 0; i < (this->size * 4); i++) {
                        newCopy->map[i] = this->map[i];
                    }

                    return newCopy;

                }

                void setGroup(int index, int v1, int v2, int v3, int normal) {
                    int actualIndex = index * 4;
                    this->map[actualIndex + VERTEX1] = v1;
                    this->map[actualIndex + VERTEX2] = v2;
                    this->map[actualIndex + VERTEX3] = v3;
                    this->map[actualIndex + NORMAL] = normal;
                }

                void setValue(int index, int subIndex, int value) {
                    this->map[ (index * 4) + subIndex ] = value;
                }

                void getGroup(int index, int* v1, int* v2, int* v3, int* normal) {
                    int actualIndex = index * 4;
                    (*v1) = this->map[actualIndex + VERTEX1];
                    (*v2) = this->map[actualIndex + VERTEX2];
                    (*v3) = this->map[actualIndex + VERTEX3];
                    (*normal) = this->map[actualIndex + NORMAL];
                }

                int getValue(int index, int subIndex) {
                    return this->map[ (index * 4) + subIndex ];
                }

        };

        // Meshes, populated from initMeshes()
        static Mesh* cubeMesh;
        static Mesh* tetrahedronMesh;

        // Instance variables
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
        Mesh() {
            this->verticies = NULL;
            this->normals = NULL;
            this->tris = NULL;
            this->vertexCount = 0;
            this->normalCount = 0;
            this->triCount = 0;
            this->color = Color::WHITE;

            this->indexMap = NULL;

            this->projectedVerticies = NULL;
            this->projectedTris = NULL;
        }

        // Destructor
        ~Mesh() {

            delete this->indexMap;

            // Delete all objects in the lists
            for (int i = 0; i < this->vertexCount; i++) { 
                if (this->verticies[i] != NULL) delete this->verticies[i]; 
                if (this->projectedVerticies[i] != NULL) delete this->projectedVerticies[i]; 
            }
            for (int i = 0; i < this->triCount; i++) {
                if (this->tris[i] != NULL) delete this->tris[i];
                if (this->projectedTris[i] != NULL) delete this->projectedTris[i];
            }
            for (int i = 0; i < this->normalCount; i++) {
                if (this->normals[i] != NULL) delete this->normals[i];
            }

            // Delete lists
            delete[] this->verticies;
            delete[] this->normals;
            delete[] this->tris;
            delete[] this->projectedVerticies;
            delete[] this->projectedTris;

            return;

        }

        // Instance Funtions
        Mesh* copy() {
            /*
                Makes a copy of a mesh where all the values are at new locations
                DOES NOT copy over projection data, must project again after copy
            */

            Mesh* newCopy = new Mesh();
            newCopy->vertexCount = this->vertexCount;
            newCopy->normalCount = this->normalCount;
            newCopy->triCount = this->triCount;

            // allocate space for lists
            newCopy->verticies = new Vec3*[this->vertexCount];
            newCopy->normals = new Vec3*[this->normalCount];
            newCopy->tris = new Tri3*[this->triCount];
            newCopy->projectedVerticies = new Vec2*[this->vertexCount];
            newCopy->projectedTris = new Tri2*[this->triCount];

            // Fill lists
            for (int i = 0; i < this->vertexCount; i++)
                newCopy->verticies[i] = this->verticies[i]->copy();

            for (int i = 0; i < this->normalCount; i++)
                newCopy->normals[i] = this->normals[i]->copy();

            for (int i = 0; i < this->triCount; i++) {
                newCopy->tris[i] = new Tri3(true);
                newCopy->projectedTris[i] = new Tri2(true);
            }

            for (int i = 0; i < this->vertexCount; i++) 
                newCopy->projectedVerticies[i] = new Vec2();

            // Copy index map
            newCopy->indexMap = this->indexMap->copy();

            newCopy->mapTris();

            return newCopy;
        }

        Mesh* move(double dx, double dy, double dz) {

            for (int i = 0; i < this->vertexCount; i++) {
                this->verticies[i]->add(dx, dy, dz);
            }

            return this;

        }

        Mesh* scale(double fx, double fy, double fz) {

            for (int i = 0; i < this->vertexCount; i++) {
                this->verticies[i]->scale(fx, fy, fz);
            }

            return this;

        }

        Mesh* rotate(double yaw, double pitch, double roll, Vec3* around = NULL) {

            for (int i = 0; i < this->vertexCount; i++) {
                this->verticies[i]->rotate(yaw, pitch, roll, around);
            }

            return this;

        }

        Mesh* setColor(Uint32 color) {
            this->color = color;
            return this;
        }

        void mapTris() {

            int vertex1Index, vertex2Index, vertex3Index, normalIndex;

            for (int i = 0; i < this->indexMap->size; i++) {

                // Get values from map
                this->indexMap->getGroup(i, &vertex1Index, &vertex2Index, &vertex3Index, &normalIndex);

                // Set pointers for 3d tris
                this->tris[i]->v1 = this->verticies[vertex1Index];
                this->tris[i]->v2 = this->verticies[vertex2Index];
                this->tris[i]->v3 = this->verticies[vertex3Index];
                this->tris[i]->normal = this->verticies[normalIndex];

                // Set pointers for 2d tris
                this->projectedTris[i]->v1 = this->projectedVerticies[vertex1Index];
                this->projectedTris[i]->v2 = this->projectedVerticies[vertex2Index];
                this->projectedTris[i]->v3 = this->projectedVerticies[vertex3Index];

            }

        }

        // Class function
        static void initMeshes() {

            Vec3** vertexList;
            Vec3** normalList;
            Tri3** triList;
            Vec2** projectedVertexList;
            Tri2** projectedTriList;
            IndexMap* indexMap;

            /* ---  Cube Mesh  --- */

            // Create lists
            vertexList = new Vec3*[8];
            normalList = new Vec3*[6];
            triList = new Tri3*[12];
            projectedVertexList = new Vec2*[8];
            projectedTriList = new Tri2*[12];
            
            // Load verticies
            vertexList[0] = new Vec3(-0.5, -0.5, -0.5);
            vertexList[1] = new Vec3(-0.5, -0.5, 0.5);
            vertexList[2] = new Vec3(0.5, -0.5, -0.5);
            vertexList[3] = new Vec3(0.5, -0.5, 0.5);
            vertexList[4] = new Vec3(-0.5, 0.5, -0.5);
            vertexList[5] = new Vec3(-0.5, 0.5, 0.5);
            vertexList[6] = new Vec3(0.5, 0.5, -0.5);
            vertexList[7] = new Vec3(0.5, 0.5, 0.5);

            // Load Normals
            normalList[0] = new Vec3(0, -1, 0);
            normalList[1] = new Vec3(0, 1, 0);
            normalList[2] = new Vec3(-1, 0, 0);
            normalList[3] = new Vec3(1, 0, 0);
            normalList[4] = new Vec3(0, 0, -1);
            normalList[5] = new Vec3(0, 0, 1);

            // Load index map
            indexMap = new IndexMap(12);
            //              triangle     v2      normal
            //                 ||   v1   ||   v3   ||
            //                 \/   \/   \/   \/   \/
            indexMap->setGroup(0,   0,   3,   1,   0); // facing -y
            indexMap->setGroup(1,   0,   3,   2,   0); // facing -y
            indexMap->setGroup(2,   4,   7,   5,   1); // facing +y
            indexMap->setGroup(3,   4,   7,   6,   1); // facing +y
            indexMap->setGroup(4,   0,   5,   4,   2); // facing -x
            indexMap->setGroup(5,   0,   5,   1,   2); // facing -x
            indexMap->setGroup(6,   2,   7,   3,   3); // facing +x
            indexMap->setGroup(7,   2,   7,   6,   3); // facing +x
            indexMap->setGroup(8,   0,   6,   2,   4); // facing -z
            indexMap->setGroup(9,   0,   6,   4,   4); // facing -z
            indexMap->setGroup(10,  1,   7,   3,   5); // facing +z
            indexMap->setGroup(11,  1,   7,   5,   5); // facing +z

            // Space for triangle objects (which point to the verticies vectors)
            for (int i = 0; i < 12; i++)
                triList[i] = new Tri3(true);

            // allocate space for projection values
            for (int i = 0; i < 8; i++) 
                projectedVertexList[i] = new Vec2();
            for (int i = 0; i < 12; i++)
                projectedTriList[i] = new Tri2(true);

            // Store the created mesh in the class variable
            Mesh::cubeMesh = new Mesh();

            Mesh::cubeMesh->indexMap = indexMap;
            Mesh::cubeMesh->verticies = vertexList;
            Mesh::cubeMesh->normals = normalList;

            Mesh::cubeMesh->vertexCount = 8;
            Mesh::cubeMesh->normalCount = 6;
            Mesh::cubeMesh->triCount = 12;

            Mesh::cubeMesh->tris = triList;
            Mesh::cubeMesh->projectedVerticies = projectedVertexList;
            Mesh::cubeMesh->projectedTris = projectedTriList;

            // Populate tri lists with pointers
            Mesh::cubeMesh->mapTris();

        }

};

Mesh* Mesh::cubeMesh = NULL;
Mesh* Mesh::tetrahedronMesh = NULL;

#endif