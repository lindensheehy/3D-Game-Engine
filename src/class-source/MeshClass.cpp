#include "../class-headers/MeshClass.h"

#include "../class-headers/Vec2Class.h"
#include "../class-headers/Vec3Class.h"
#include "../class-headers/Tri2Class.h"
#include "../class-headers/Tri3Class.h"
#include "../class-headers/ColorClass.h"

// For logging error cases
#include "../log/log.h"

/*  ------------------------------------  */
/*  -----------   IndexMap   -----------  */
/*  ------------------------------------  */

// Constructor
Mesh::IndexMap::IndexMap(int size) {
    this->map = new Set[size];
    this->size = size;
}

// Destructor
Mesh::IndexMap::~IndexMap() {
    delete this->map;
}

// Instance variables
Mesh::IndexMap* Mesh::IndexMap::copy() {

    IndexMap* newCopy = new IndexMap(this->size);

    for (int i = 0; i < (this->size); i++) {
        newCopy->map[i].vertex1 = this->map[i].vertex1;
        newCopy->map[i].vertex2 = this->map[i].vertex2;
        newCopy->map[i].vertex3 = this->map[i].vertex3;
        newCopy->map[i].normal = this->map[i].normal;
    }

    return newCopy;

}

void Mesh::IndexMap::setGroup(int index, int v1, int v2, int v3, int normal) {
    this->map[index].vertex1 = v1;
    this->map[index].vertex2 = v2;
    this->map[index].vertex3 = v3;
    this->map[index].normal = normal;
}

void Mesh::IndexMap::getGroup(int index, int* v1, int* v2, int* v3, int* normal) {
    (*v1) = this->map[index].vertex1;
    (*v2) = this->map[index].vertex2;
    (*v3) = this->map[index].vertex3;
    (*normal) = this->map[index].normal;
}

/*  ------------------------------------  */
/*  -------------   Mesh   -------------  */
/*  ------------------------------------  */

// Static variables for simple meshes
Mesh* Mesh::cubeMesh = nullptr;
Mesh* Mesh::tetrahedronMesh = nullptr;

// Constructor
Mesh::Mesh() {

    this->verticies = nullptr;
    this->normals = nullptr;
    this->tris = nullptr;
    this->vertexCount = 0;
    this->normalCount = 0;
    this->triCount = 0;
    this->color = Color::WHITE;

    this->indexMap = nullptr;

    this->projectedVerticies = nullptr;
    this->projectedTris = nullptr;
    
}

// Destructor
Mesh::~Mesh() {

    if (this->indexMap != nullptr) delete this->indexMap;

    // Delete all objects in the lists
    for (int i = 0; i < this->vertexCount; i++) { 
        if (this->verticies[i] != nullptr) delete this->verticies[i]; 
        if (this->projectedVerticies[i] != nullptr) delete this->projectedVerticies[i]; 
    }
    for (int i = 0; i < this->triCount; i++) {
        if (this->tris[i] != nullptr) delete this->tris[i];
        if (this->projectedTris[i] != nullptr) delete this->projectedTris[i];
    }
    for (int i = 0; i < this->normalCount; i++) {
        if (this->normals[i] != nullptr) delete this->normals[i];
    }

    // Delete lists
    if (this->verticies != nullptr) delete[] this->verticies;
    if (this->normals != nullptr) delete[] this->normals;
    if (this->tris != nullptr) delete[] this->tris;
    if (this->projectedVerticies != nullptr) delete[] this->projectedVerticies;
    if (this->projectedTris != nullptr) delete[] this->projectedTris;

    return;

}

// Instance Funtions
Mesh* Mesh::copy() {
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

Mesh* Mesh::move(double dx, double dy, double dz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->add(dx, dy, dz);
    }

    return this;

}

Mesh* Mesh::scale(double fx, double fy, double fz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->scale(fx, fy, fz);
    }

    return this;

}

Mesh* Mesh::rotate(double yaw, double pitch, double roll, Vec3* around /* default value = nullptr */) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (around == nullptr) {
        logWrite("Called Mesh->rotate(double, double, double, Vec3*) on a null pointer!", true);
        return nullptr;
    }

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->rotate(yaw, pitch, roll, around);
    }

    return this;

}

Mesh* Mesh::setColor(uint32 color) {
    this->color = color;
    return this;
}

void Mesh::mapTris() {

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
void Mesh::initMeshes() {

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
