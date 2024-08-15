#include "../include/Mesh.h"


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

    if (index >= this->size) {
        logWrite("Called Mesh::IndexMap->setGroup() for index ");
        logWrite(index);
        logWrite(" of size ");
        logWrite(this->size, true);
        return;
    }

    this->map[index].vertex1 = v1;
    this->map[index].vertex2 = v2;
    this->map[index].vertex3 = v3;
    this->map[index].normal = normal;
}

void Mesh::IndexMap::getGroup(int index, int* v1, int* v2, int* v3, int* normal) {

    if (index >= this->size) {
        logWrite("Called Mesh::IndexMap->getGroup() for index ");
        logWrite(index);
        logWrite(" of size ");
        logWrite(this->size, true);
        return;
    }

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
Mesh* Mesh::sphereMesh = nullptr;
Mesh* Mesh::tetrahedronMesh = nullptr;
Mesh* Mesh::capsuleMesh = nullptr;

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

    this->center = new Vec3();
    this->centerValid = false;
    
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
        if (this->verticies[i] == nullptr) newCopy->verticies[i] = nullptr;
        else newCopy->verticies[i] = this->verticies[i]->copy();

    for (int i = 0; i < this->normalCount; i++)
        if (this->normals[i] == nullptr) newCopy->normals[i] = nullptr;
        else newCopy->normals[i] = this->normals[i]->copy();

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

Vec3* Mesh::getCenter() {

    if (this->centerValid) return this->center;

    double x = 0;
    double y = 0;
    double z = 0;

    for (int i = 0; i < this->vertexCount; i++) {
        x += this->verticies[i]->x;
        y += this->verticies[i]->y;
        z += this->verticies[i]->z;
    }

    x /= this->vertexCount;
    y /= this->vertexCount;
    z /= this->vertexCount;

    this->center->set(x, y, z);
    this->centerValid = true;

    return this->center;

}

Mesh* Mesh::move(double dx, double dy, double dz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->add(dx, dy, dz);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::scale(double factor) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->scale(factor, factor, factor);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::scale(double fx, double fy, double fz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->scale(fx, fy, fz);
    }

    this->updateNormals();

    this->centerValid = false;

    return this;

}

Mesh* Mesh::rotate(Vec3* angle, Vec3* around /* default value = nullptr */) {

    this->rotate(angle->x, angle->y, angle->z, around);

    return this;

}

Mesh* Mesh::rotate(double yaw, double pitch, double roll, Vec3* around /* default value = nullptr */) {

    // around = nullptr is allowed, no need to error check

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->rotate(yaw, pitch, roll, around);
    }

    // Normals are not relative to anything, and as such should not be rotated around anything but (0, 0, 0)
    for (int i = 0; i < this->normalCount; i++) {
        this->normals[i]->rotate(yaw, pitch, roll);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::rotateSelf(Vec3* angle) {

    this->rotateSelf(angle->x, angle->y, angle->z);

    return this;

}

Mesh* Mesh::rotateSelf(double yaw, double pitch, double roll) {

    // This doesnt create any new object
    Vec3* center = this->getCenter();

    for (int i = 0; i < this->vertexCount; i++) {
        this->verticies[i]->rotate(yaw, pitch, roll, center);
    }

    // Normals are not relative to anything, and as such should not be rotated around anything but (0, 0, 0)
    for (int i = 0; i < this->normalCount; i++) {
        this->normals[i]->rotate(yaw, pitch, roll);
    }

    return this;

}

Mesh* Mesh::setColor(uint32 color) {
    this->color = color;
    return this;
}

void Mesh::updateNormals() {

    for (int i = 0; i < this->triCount; i++) {

        Vec3* newNormal;
        Tri3* tri = this->tris[i];

        // Get one of the two possible normals
        Vec3* vec1to2 = tri->v1->copy()->sub(tri->v2);
        Vec3* vec1to3 = tri->v1->copy()->sub(tri->v3);

        newNormal = vec1to2->crossProduct(vec1to3);
        newNormal->normalise();

        delete vec1to2, vec1to3;

        // Check if the found normal faces outwards
        Vec3* meshCenter = this->getCenter();                   // Not a new object
        Vec3* triCenter = tri->getCenter();                     // New object
        Vec3* normalOffset = newNormal->copy()->scale(0.05);    // New object

        triCenter->add(normalOffset);
        double dist1 = triCenter->distanceTo(meshCenter);
        triCenter->sub(normalOffset)->sub(normalOffset);
        double dist2 = triCenter->distanceTo(meshCenter);

        delete triCenter, normalOffset;

        // Flip if its facing towards the center
        if (dist1 < dist2) newNormal->scale(-1);

        // Place the found normal into its place in the list
        int _, index; // The underscore represents a value which isnt wanted/needed

        this->indexMap->getGroup(i, &_, &_, &_, &index);

        if (this->normals[index] == nullptr) {
            this->normals[index] = newNormal;
            continue;
        };

        this->normals[index]->set(newNormal);
        delete newNormal;

    }

}

void Mesh::mapTris() {

    if (this->triCount != this->indexMap->size) {
        logWrite("Called Mesh->mapTris() with ");
        logWrite(this->triCount);
        logWrite(" tris, but ");
        logWrite(this->indexMap->size);
        logWrite(" entries in the index map", true);
        return;
    }

    int vertex1Index, vertex2Index, vertex3Index, normalIndex;

    for (int i = 0; i < this->indexMap->size; i++) {

        // Get values from map
        this->indexMap->getGroup(i, &vertex1Index, &vertex2Index, &vertex3Index, &normalIndex);

        // Set pointers for 3d tris
        this->tris[i]->v1 = this->verticies[vertex1Index];
        this->tris[i]->v2 = this->verticies[vertex2Index];
        this->tris[i]->v3 = this->verticies[vertex3Index];
        this->tris[i]->normal = this->normals[normalIndex];

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

    /* ------------------- */
    /* ---  Cube Mesh  --- */
    /* ------------------- */

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

    /* --------------------- */
    /* ---  Sphere Mesh  --- */
    /* --------------------- */

    int triCount = 200;
    int vertexCount = 102;

    // Create lists
    vertexList = new Vec3*[vertexCount];
    normalList = new Vec3*[triCount];
    triList = new Tri3*[triCount];
    projectedVertexList = new Vec2*[vertexCount];
    projectedTriList = new Tri2*[triCount];
    
    // Load verticies

    // Bottom and top
    vertexList[100] = new Vec3(0, -0.5, 0);
    vertexList[101] = new Vec3(0, 0.5, 0);

    // Rotate a vector around at a certain length to make new vertices
    double theta = 360 / 20;
    Vec3* newVec = new Vec3();

    // Along the circumference (index 0-19 inclusive)
    newVec->set(0, 0, 0.5);

    for (int i = 0; i < 20; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }

    // 30 degrees below the circumference (index 20-39 inclusive)
    newVec->set(0, 0, 0.5);
    newVec->rotate(0, 30, 0);
    newVec->rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 20; i < 40; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }

    // 30 degrees above the circumference (index 40-59 inclusive)
    newVec->set(0, 0, 0.5);
    newVec->rotate(0, -30, 0);
    newVec->rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 40; i < 60; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }

    // 60 degrees below the circumference (index 60-79 inclusive)
    newVec->set(0, 0, 0.5);
    newVec->rotate(0, 60, 0);

    for (int i = 60; i < 80; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }

    // 60 degrees above the circumference (index 80-99 inclusive)
    newVec->set(0, 0, 0.5);
    newVec->rotate(0, -60, 0);

    for (int i = 80; i < 100; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy();

    }



    // Clear space for normal vectors
    for (int i = 0; i < triCount; i++) {
        normalList[i] = nullptr;
    }

    // Load index map
    indexMap = new IndexMap(triCount);
    //                triangle          v2          normal
    //                   ||      v1     ||     v3     ||
    //                   \/      \/     \/     \/     \/
    indexMap->setGroup(  0,     101,    80,    81,    0    );     // -------------
    indexMap->setGroup(  1,     101,    81,    82,    1    );     //
    indexMap->setGroup(  2,     101,    82,    83,    2    );     //
    indexMap->setGroup(  3,     101,    83,    84,    3    );     //
    indexMap->setGroup(  4,     101,    84,    85,    4    );     //
    indexMap->setGroup(  5,     101,    85,    86,    5    );     //     here
    indexMap->setGroup(  6,     101,    86,    87,    6    );     //     ----     
    indexMap->setGroup(  7,     101,    87,    88,    7    );     //     ----     
    indexMap->setGroup(  8,     101,    88,    89,    8    );     //     ----    
    indexMap->setGroup(  9,     101,    89,    90,    9    );     //     ----     
    indexMap->setGroup(  10,    101,    90,    91,    10   );     //     ----     
    indexMap->setGroup(  11,    101,    91,    92,    11   );     //     ----    
    indexMap->setGroup(  12,    101,    92,    93,    12   );     //     ----     
    indexMap->setGroup(  13,    101,    93,    94,    13   );     //     ----     
    indexMap->setGroup(  14,    101,    94,    95,    14   );     //     ----     
    indexMap->setGroup(  15,    101,    95,    96,    15   );     //
    indexMap->setGroup(  16,    101,    96,    97,    16   );     //
    indexMap->setGroup(  17,    101,    97,    98,    17   );     //
    indexMap->setGroup(  18,    101,    98,    99,    18   );     //
    indexMap->setGroup(  19,    101,    99,    80,    19   );     // -------------

    indexMap->setGroup(  20,     81,    40,    41,    20   );     // -------------
    indexMap->setGroup(  21,     82,    41,    42,    21   );     //
    indexMap->setGroup(  22,     83,    42,    43,    22   );     //
    indexMap->setGroup(  23,     84,    43,    44,    23   );     //
    indexMap->setGroup(  24,     85,    44,    45,    24   );     //
    indexMap->setGroup(  25,     86,    45,    46,    25   );     //     ----
    indexMap->setGroup(  26,     87,    46,    47,    26   );     //     here     
    indexMap->setGroup(  27,     88,    47,    48,    27   );     //     ----     
    indexMap->setGroup(  28,     89,    48,    49,    28   );     //     ----    
    indexMap->setGroup(  29,     90,    49,    50,    29   );     //     ----     
    indexMap->setGroup(  30,     91,    50,    51,    30   );     //     ----     
    indexMap->setGroup(  31,     92,    51,    52,    31   );     //     ----    
    indexMap->setGroup(  32,     93,    52,    53,    32   );     //     ----     
    indexMap->setGroup(  33,     94,    53,    54,    33   );     //     ----     
    indexMap->setGroup(  34,     95,    54,    55,    34   );     //     ----     
    indexMap->setGroup(  35,     96,    55,    56,    35   );     //
    indexMap->setGroup(  36,     97,    56,    57,    36   );     //
    indexMap->setGroup(  37,     98,    57,    58,    37   );     //
    indexMap->setGroup(  38,     99,    58,    59,    38   );     //
    indexMap->setGroup(  39,     80,    59,    40,    39   );     // -------------

    indexMap->setGroup(  40,     40,    80,    81,    40   );     // -------------
    indexMap->setGroup(  41,     41,    81,    82,    41   );     //
    indexMap->setGroup(  42,     42,    82,    83,    42   );     //
    indexMap->setGroup(  43,     43,    83,    84,    43   );     //
    indexMap->setGroup(  44,     44,    84,    85,    44   );     //
    indexMap->setGroup(  45,     45,    85,    86,    45   );     //     ----
    indexMap->setGroup(  46,     46,    86,    87,    46   );     //     ----     
    indexMap->setGroup(  47,     47,    87,    88,    47   );     //     here     
    indexMap->setGroup(  48,     48,    88,    89,    48   );     //     ----    
    indexMap->setGroup(  49,     49,    89,    90,    49   );     //     ----     
    indexMap->setGroup(  50,     50,    90,    91,    50   );     //     ----     
    indexMap->setGroup(  51,     51,    91,    92,    51   );     //     ----    
    indexMap->setGroup(  52,     52,    92,    93,    52   );     //     ----     
    indexMap->setGroup(  53,     53,    93,    94,    53   );     //     ----     
    indexMap->setGroup(  54,     54,    94,    95,    54   );     //     ----     
    indexMap->setGroup(  55,     55,    95,    96,    55   );     //
    indexMap->setGroup(  56,     56,    96,    97,    56   );     //
    indexMap->setGroup(  57,     57,    97,    98,    57   );     //
    indexMap->setGroup(  58,     58,    98,    99,    58   );     //
    indexMap->setGroup(  59,     59,    99,    80,    59   );     // -------------

    indexMap->setGroup(  60,      1,    40,    41,    60   );     // -------------
    indexMap->setGroup(  61,      2,    41,    42,    61   );     //
    indexMap->setGroup(  62,      3,    42,    43,    62   );     //
    indexMap->setGroup(  63,      4,    43,    44,    63   );     //
    indexMap->setGroup(  64,      5,    44,    45,    64   );     //
    indexMap->setGroup(  65,      6,    45,    46,    65   );     //     ----
    indexMap->setGroup(  66,      7,    46,    47,    66   );     //     ----     
    indexMap->setGroup(  67,      8,    47,    48,    67   );     //     ----     
    indexMap->setGroup(  68,      9,    48,    49,    68   );     //     here    
    indexMap->setGroup(  69,     10,    49,    50,    69   );     //     ----     
    indexMap->setGroup(  70,     11,    50,    51,    70   );     //     ----     
    indexMap->setGroup(  71,     12,    51,    52,    71   );     //     ----    
    indexMap->setGroup(  72,     13,    52,    53,    72   );     //     ----     
    indexMap->setGroup(  73,     14,    53,    54,    73   );     //     ----     
    indexMap->setGroup(  74,     15,    54,    55,    74   );     //     ----     
    indexMap->setGroup(  75,     16,    55,    56,    75   );     //
    indexMap->setGroup(  76,     17,    56,    57,    76   );     //
    indexMap->setGroup(  77,     18,    57,    58,    77   );     //
    indexMap->setGroup(  78,     19,    58,    59,    78   );     //
    indexMap->setGroup(  79,      0,    59,    40,    79   );     // -------------

    indexMap->setGroup(  80,     40,     0,     1,    80   );     // -------------
    indexMap->setGroup(  81,     41,     1,     2,    81   );     //
    indexMap->setGroup(  82,     42,     2,     3,    82   );     //
    indexMap->setGroup(  83,     43,     3,     4,    83   );     //
    indexMap->setGroup(  84,     44,     4,     5,    84   );     //
    indexMap->setGroup(  85,     45,     5,     6,    85   );     //     ----
    indexMap->setGroup(  86,     46,     6,     7,    86   );     //     ----     
    indexMap->setGroup(  87,     47,     7,     8,    87   );     //     ----     
    indexMap->setGroup(  88,     48,     8,     9,    88   );     //     ----    
    indexMap->setGroup(  89,     49,     9,    10,    89   );     //     here     
    indexMap->setGroup(  90,     50,    10,    11,    90   );     //     ----     
    indexMap->setGroup(  91,     51,    11,    12,    91   );     //     ----    
    indexMap->setGroup(  92,     52,    12,    13,    92   );     //     ----     
    indexMap->setGroup(  93,     53,    13,    14,    93   );     //     ----     
    indexMap->setGroup(  94,     54,    14,    15,    94   );     //     ----     
    indexMap->setGroup(  95,     55,    15,    16,    95   );     //
    indexMap->setGroup(  96,     56,    16,    17,    96   );     //
    indexMap->setGroup(  97,     57,    17,    18,    97   );     //
    indexMap->setGroup(  98,     58,    18,    19,    98   );     //
    indexMap->setGroup(  99,     59,    19,     0,    99   );     // -------------

    indexMap->setGroup(  100,    20,     0,     1,    100  );     // -------------
    indexMap->setGroup(  101,    21,     1,     2,    101  );     //
    indexMap->setGroup(  102,    22,     2,     3,    102  );     //
    indexMap->setGroup(  103,    23,     3,     4,    103  );     //
    indexMap->setGroup(  104,    24,     4,     5,    104  );     //
    indexMap->setGroup(  105,    25,     5,     6,    105  );     //     ----
    indexMap->setGroup(  106,    26,     6,     7,    106  );     //     ----     
    indexMap->setGroup(  107,    27,     7,     8,    107  );     //     ----     
    indexMap->setGroup(  108,    28,     8,     9,    108  );     //     ----    
    indexMap->setGroup(  109,    29,     9,    10,    109  );     //     ----     
    indexMap->setGroup(  110,    30,    10,    11,    110  );     //     here     
    indexMap->setGroup(  111,    31,    11,    12,    111  );     //     ----    
    indexMap->setGroup(  112,    32,    12,    13,    112  );     //     ----     
    indexMap->setGroup(  113,    33,    13,    14,    113  );     //     ----     
    indexMap->setGroup(  114,    34,    14,    15,    114  );     //     ----     
    indexMap->setGroup(  115,    35,    15,    16,    115  );     //
    indexMap->setGroup(  116,    36,    16,    17,    116  );     //
    indexMap->setGroup(  117,    37,    17,    18,    117  );     //
    indexMap->setGroup(  118,    38,    18,    19,    118  );     //
    indexMap->setGroup(  119,    39,    19,     0,    119  );     // -------------

    indexMap->setGroup(  120,     1,    20,    21,    120  );     // -------------
    indexMap->setGroup(  121,     2,    21,    22,    121  );     //
    indexMap->setGroup(  122,     3,    22,    23,    122  );     //
    indexMap->setGroup(  123,     4,    23,    24,    123  );     //
    indexMap->setGroup(  124,     5,    24,    25,    124  );     //
    indexMap->setGroup(  125,     6,    25,    26,    125  );     //     ----
    indexMap->setGroup(  126,     7,    26,    27,    126  );     //     ----     
    indexMap->setGroup(  127,     8,    27,    28,    127  );     //     ----     
    indexMap->setGroup(  128,     9,    28,    29,    128  );     //     ----    
    indexMap->setGroup(  129,    10,    29,    30,    129  );     //     ----     
    indexMap->setGroup(  130,    11,    30,    31,    130  );     //     ----     
    indexMap->setGroup(  131,    12,    31,    32,    131  );     //     here    
    indexMap->setGroup(  132,    13,    32,    33,    132  );     //     ----     
    indexMap->setGroup(  133,    14,    33,    34,    133  );     //     ----     
    indexMap->setGroup(  134,    15,    34,    35,    134  );     //     ----     
    indexMap->setGroup(  135,    16,    35,    36,    135  );     //
    indexMap->setGroup(  136,    17,    36,    37,    136  );     //
    indexMap->setGroup(  137,    18,    37,    38,    137  );     //
    indexMap->setGroup(  138,    19,    38,    39,    138  );     //
    indexMap->setGroup(  139,     0,    39,    20,    139  );     // -------------

    indexMap->setGroup(  140,    61,    20,    21,    140  );     // -------------
    indexMap->setGroup(  141,    62,    21,    22,    141  );     //
    indexMap->setGroup(  142,    63,    22,    23,    142  );     //
    indexMap->setGroup(  143,    64,    23,    24,    143  );     //
    indexMap->setGroup(  144,    65,    24,    25,    144  );     //
    indexMap->setGroup(  145,    66,    25,    26,    145  );     //     ----
    indexMap->setGroup(  146,    67,    26,    27,    146  );     //     ----     
    indexMap->setGroup(  147,    68,    27,    28,    147  );     //     ----     
    indexMap->setGroup(  148,    69,    28,    29,    148  );     //     ----    
    indexMap->setGroup(  149,    70,    29,    30,    149  );     //     ----     
    indexMap->setGroup(  150,    71,    30,    31,    150  );     //     ----     
    indexMap->setGroup(  151,    72,    31,    32,    151  );     //     ----    
    indexMap->setGroup(  152,    73,    32,    33,    152  );     //     here     
    indexMap->setGroup(  153,    74,    33,    34,    153  );     //     ----     
    indexMap->setGroup(  154,    75,    34,    35,    154  );     //     ----     
    indexMap->setGroup(  155,    76,    35,    36,    155  );     //
    indexMap->setGroup(  156,    77,    36,    37,    156  );     //
    indexMap->setGroup(  157,    78,    37,    38,    157  );     //
    indexMap->setGroup(  158,    79,    38,    39,    158  );     //
    indexMap->setGroup(  159,    60,    39,    20,    159  );     // -------------

    indexMap->setGroup(  160,    20,    60,    61,    160  );     // -------------
    indexMap->setGroup(  161,    21,    61,    62,    161  );     //
    indexMap->setGroup(  162,    22,    62,    63,    162  );     //
    indexMap->setGroup(  163,    23,    63,    64,    163  );     //
    indexMap->setGroup(  164,    24,    64,    65,    164  );     //
    indexMap->setGroup(  165,    25,    65,    66,    165  );     //     ----
    indexMap->setGroup(  166,    26,    66,    67,    166  );     //     ----     
    indexMap->setGroup(  167,    27,    67,    68,    167  );     //     ----     
    indexMap->setGroup(  168,    28,    68,    69,    168  );     //     ----    
    indexMap->setGroup(  169,    29,    69,    70,    169  );     //     ----     
    indexMap->setGroup(  170,    30,    70,    71,    170  );     //     ----     
    indexMap->setGroup(  171,    31,    71,    72,    171  );     //     ----    
    indexMap->setGroup(  172,    32,    72,    73,    172  );     //     ----     
    indexMap->setGroup(  173,    33,    73,    74,    173  );     //     here     
    indexMap->setGroup(  174,    34,    74,    75,    174  );     //     ----     
    indexMap->setGroup(  175,    35,    75,    76,    175  );     //
    indexMap->setGroup(  176,    36,    76,    77,    176  );     //
    indexMap->setGroup(  177,    37,    77,    78,    177  );     //
    indexMap->setGroup(  178,    38,    78,    79,    178  );     //
    indexMap->setGroup(  179,    39,    79,    60,    179  );     // -------------

    indexMap->setGroup(  180,   100,    60,    61,    180  );     // -------------
    indexMap->setGroup(  181,   100,    61,    62,    181  );     //
    indexMap->setGroup(  182,   100,    62,    63,    182  );     //
    indexMap->setGroup(  183,   100,    63,    64,    183  );     //
    indexMap->setGroup(  184,   100,    64,    65,    184  );     //
    indexMap->setGroup(  185,   100,    65,    66,    185  );     //     ----
    indexMap->setGroup(  186,   100,    66,    67,    186  );     //     ----     
    indexMap->setGroup(  187,   100,    67,    68,    187  );     //     ----     
    indexMap->setGroup(  188,   100,    68,    69,    188  );     //     ----    
    indexMap->setGroup(  189,   100,    69,    70,    189  );     //     ----     
    indexMap->setGroup(  190,   100,    70,    71,    190  );     //     ----     
    indexMap->setGroup(  191,   100,    71,    72,    191  );     //     ----    
    indexMap->setGroup(  192,   100,    72,    73,    192  );     //     ----     
    indexMap->setGroup(  193,   100,    73,    74,    193  );     //     ----     
    indexMap->setGroup(  194,   100,    74,    75,    194  );     //     here     
    indexMap->setGroup(  195,   100,    75,    76,    195  );     //
    indexMap->setGroup(  196,   100,    76,    77,    196  );     //
    indexMap->setGroup(  197,   100,    77,    78,    197  );     //
    indexMap->setGroup(  198,   100,    78,    79,    198  );     //
    indexMap->setGroup(  199,   100,    79,    60,    199  );     // -------------


    // Space for triangle objects (which point to the verticies vectors)
    for (int i = 0; i < triCount; i++)
        triList[i] = new Tri3(true);

    // allocate space for projection values
    for (int i = 0; i < vertexCount; i++)
        projectedVertexList[i] = new Vec2();
    for (int i = 0; i < triCount; i++)
        projectedTriList[i] = new Tri2(true);

    // Store the created mesh in the class variable
    Mesh::sphereMesh = new Mesh();

    Mesh::sphereMesh->indexMap = indexMap;
    Mesh::sphereMesh->verticies = vertexList;
    Mesh::sphereMesh->normals = normalList;

    Mesh::sphereMesh->vertexCount = vertexCount;
    Mesh::sphereMesh->normalCount = triCount;
    Mesh::sphereMesh->triCount = triCount;

    Mesh::sphereMesh->tris = triList;
    Mesh::sphereMesh->projectedVerticies = projectedVertexList;
    Mesh::sphereMesh->projectedTris = projectedTriList;

    // Populate tri lists with pointers
    Mesh::sphereMesh->mapTris();

    // Load normals
    Mesh::sphereMesh->updateNormals();



    /* ---------------------- */
    /* ---  Capsule Mesh  --- */
    /* ---------------------- */

    triCount = 240;
    vertexCount = 122;

    // Create lists
    vertexList = new Vec3*[vertexCount];
    normalList = new Vec3*[triCount];
    triList = new Tri3*[triCount];
    projectedVertexList = new Vec2*[vertexCount];
    projectedTriList = new Tri2*[triCount];
    
    // Load verticies

    // Bottom and top
    vertexList[120] = new Vec3(0, -0.5, 0);
    vertexList[121] = new Vec3(0, 0.5, 0);

    // Rotate a vector around at a certain length to make new vertices
    theta = 360 / 20;
    newVec = new Vec3();

    // Along the circumference (index 0-19 inclusive for the top, index 100-119 inclusive for the bottom)
    newVec->set(0, 0, 0.25);

    for (int i = 0; i < 20; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->add(0, 0.25, 0);
        vertexList[i + 100] = newVec->copy()->sub(0, 0.25, 0);

    }

    // 30 degrees below the circumference (index 20-39 inclusive)
    newVec->set(0, 0, 0.25);
    newVec->rotate(0, 30, 0);
    newVec->rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 20; i < 40; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->sub(0, 0.25, 0);

    }

    // 30 degrees above the circumference (index 40-59 inclusive)
    newVec->set(0, 0, 0.25);
    newVec->rotate(0, -30, 0);
    newVec->rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 40; i < 60; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->add(0, 0.25, 0);

    }

    // 60 degrees below the circumference (index 60-79 inclusive)
    newVec->set(0, 0, 0.25);
    newVec->rotate(0, 60, 0);

    for (int i = 60; i < 80; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->sub(0, 0.25, 0);

    }

    // 60 degrees above the circumference (index 80-99 inclusive)
    newVec->set(0, 0, 0.25);
    newVec->rotate(0, -60, 0);

    for (int i = 80; i < 100; i++) {

        // Rotate the vector by a changing amount
        newVec->rotate(theta, 0, 0);

        // Add it and update the angle for next iteration
        vertexList[i] = newVec->copy()->add(0, 0.25, 0);

    }

    // Clear space for normal vectors
    for (int i = 0; i < triCount; i++) {
        normalList[i] = nullptr;
    }

    // Load index map
    indexMap = new IndexMap(triCount);
    //                triangle          v2          normal
    //                   ||      v1     ||     v3     ||
    //                   \/      \/     \/     \/     \/
    indexMap->setGroup(  0,     121,    80,    81,    0    );     // -------------
    indexMap->setGroup(  1,     121,    81,    82,    1    );     //
    indexMap->setGroup(  2,     121,    82,    83,    2    );     //
    indexMap->setGroup(  3,     121,    83,    84,    3    );     //
    indexMap->setGroup(  4,     121,    84,    85,    4    );     //     here
    indexMap->setGroup(  5,     121,    85,    86,    5    );     //     ----
    indexMap->setGroup(  6,     121,    86,    87,    6    );     //     ----     
    indexMap->setGroup(  7,     121,    87,    88,    7    );     //     ----     
    indexMap->setGroup(  8,     121,    88,    89,    8    );     //     ----    
    indexMap->setGroup(  9,     121,    89,    90,    9    );     //     ----     
    indexMap->setGroup(  10,    121,    90,    91,    10   );     //     ----     
    indexMap->setGroup(  11,    121,    91,    92,    11   );     //     ----    
    indexMap->setGroup(  12,    121,    92,    93,    12   );     //     ----     
    indexMap->setGroup(  13,    121,    93,    94,    13   );     //     ----     
    indexMap->setGroup(  14,    121,    94,    95,    14   );     //     ----     
    indexMap->setGroup(  15,    121,    95,    96,    15   );     //     ----
    indexMap->setGroup(  16,    121,    96,    97,    16   );     //
    indexMap->setGroup(  17,    121,    97,    98,    17   );     //
    indexMap->setGroup(  18,    121,    98,    99,    18   );     //
    indexMap->setGroup(  19,    121,    99,    80,    19   );     // -------------

    indexMap->setGroup(  20,     81,    40,    41,    20   );     // -------------
    indexMap->setGroup(  21,     82,    41,    42,    21   );     //
    indexMap->setGroup(  22,     83,    42,    43,    22   );     //
    indexMap->setGroup(  23,     84,    43,    44,    23   );     //
    indexMap->setGroup(  24,     85,    44,    45,    24   );     //     ----
    indexMap->setGroup(  25,     86,    45,    46,    25   );     //     here
    indexMap->setGroup(  26,     87,    46,    47,    26   );     //     ----     
    indexMap->setGroup(  27,     88,    47,    48,    27   );     //     ----     
    indexMap->setGroup(  28,     89,    48,    49,    28   );     //     ----    
    indexMap->setGroup(  29,     90,    49,    50,    29   );     //     ----     
    indexMap->setGroup(  30,     91,    50,    51,    30   );     //     ----     
    indexMap->setGroup(  31,     92,    51,    52,    31   );     //     ----    
    indexMap->setGroup(  32,     93,    52,    53,    32   );     //     ----     
    indexMap->setGroup(  33,     94,    53,    54,    33   );     //     ----     
    indexMap->setGroup(  34,     95,    54,    55,    34   );     //     ----     
    indexMap->setGroup(  35,     96,    55,    56,    35   );     //     ----
    indexMap->setGroup(  36,     97,    56,    57,    36   );     //
    indexMap->setGroup(  37,     98,    57,    58,    37   );     //
    indexMap->setGroup(  38,     99,    58,    59,    38   );     //
    indexMap->setGroup(  39,     80,    59,    40,    39   );     // -------------

    indexMap->setGroup(  40,     40,    80,    81,    40   );     // -------------
    indexMap->setGroup(  41,     41,    81,    82,    41   );     //
    indexMap->setGroup(  42,     42,    82,    83,    42   );     //
    indexMap->setGroup(  43,     43,    83,    84,    43   );     //
    indexMap->setGroup(  44,     44,    84,    85,    44   );     //     ----
    indexMap->setGroup(  45,     45,    85,    86,    45   );     //     ----
    indexMap->setGroup(  46,     46,    86,    87,    46   );     //     here     
    indexMap->setGroup(  47,     47,    87,    88,    47   );     //     ----     
    indexMap->setGroup(  48,     48,    88,    89,    48   );     //     ----    
    indexMap->setGroup(  49,     49,    89,    90,    49   );     //     ----     
    indexMap->setGroup(  50,     50,    90,    91,    50   );     //     ----     
    indexMap->setGroup(  51,     51,    91,    92,    51   );     //     ----    
    indexMap->setGroup(  52,     52,    92,    93,    52   );     //     ----     
    indexMap->setGroup(  53,     53,    93,    94,    53   );     //     ----     
    indexMap->setGroup(  54,     54,    94,    95,    54   );     //     ----     
    indexMap->setGroup(  55,     55,    95,    96,    55   );     //     ----
    indexMap->setGroup(  56,     56,    96,    97,    56   );     //
    indexMap->setGroup(  57,     57,    97,    98,    57   );     //
    indexMap->setGroup(  58,     58,    98,    99,    58   );     //
    indexMap->setGroup(  59,     59,    99,    80,    59   );     // -------------

    indexMap->setGroup(  60,      1,    40,    41,    60   );     // -------------
    indexMap->setGroup(  61,      2,    41,    42,    61   );     //
    indexMap->setGroup(  62,      3,    42,    43,    62   );     //
    indexMap->setGroup(  63,      4,    43,    44,    63   );     //
    indexMap->setGroup(  64,      5,    44,    45,    64   );     //     ----
    indexMap->setGroup(  65,      6,    45,    46,    65   );     //     ----
    indexMap->setGroup(  66,      7,    46,    47,    66   );     //     ----     
    indexMap->setGroup(  67,      8,    47,    48,    67   );     //     here     
    indexMap->setGroup(  68,      9,    48,    49,    68   );     //     ----    
    indexMap->setGroup(  69,     10,    49,    50,    69   );     //     ----     
    indexMap->setGroup(  70,     11,    50,    51,    70   );     //     ----     
    indexMap->setGroup(  71,     12,    51,    52,    71   );     //     ----    
    indexMap->setGroup(  72,     13,    52,    53,    72   );     //     ----     
    indexMap->setGroup(  73,     14,    53,    54,    73   );     //     ----     
    indexMap->setGroup(  74,     15,    54,    55,    74   );     //     ----     
    indexMap->setGroup(  75,     16,    55,    56,    75   );     //     ----
    indexMap->setGroup(  76,     17,    56,    57,    76   );     //
    indexMap->setGroup(  77,     18,    57,    58,    77   );     //
    indexMap->setGroup(  78,     19,    58,    59,    78   );     //
    indexMap->setGroup(  79,      0,    59,    40,    79   );     // -------------

    indexMap->setGroup(  80,     40,     0,     1,    80   );     // -------------
    indexMap->setGroup(  81,     41,     1,     2,    81   );     //
    indexMap->setGroup(  82,     42,     2,     3,    82   );     //
    indexMap->setGroup(  83,     43,     3,     4,    83   );     //
    indexMap->setGroup(  84,     44,     4,     5,    84   );     //     ----
    indexMap->setGroup(  85,     45,     5,     6,    85   );     //     ----
    indexMap->setGroup(  86,     46,     6,     7,    86   );     //     ----     
    indexMap->setGroup(  87,     47,     7,     8,    87   );     //     ----     
    indexMap->setGroup(  88,     48,     8,     9,    88   );     //     here    
    indexMap->setGroup(  89,     49,     9,    10,    89   );     //     ----     
    indexMap->setGroup(  90,     50,    10,    11,    90   );     //     ----     
    indexMap->setGroup(  91,     51,    11,    12,    91   );     //     ----    
    indexMap->setGroup(  92,     52,    12,    13,    92   );     //     ----     
    indexMap->setGroup(  93,     53,    13,    14,    93   );     //     ----     
    indexMap->setGroup(  94,     54,    14,    15,    94   );     //     ----     
    indexMap->setGroup(  95,     55,    15,    16,    95   );     //     ----
    indexMap->setGroup(  96,     56,    16,    17,    96   );     //
    indexMap->setGroup(  97,     57,    17,    18,    97   );     //
    indexMap->setGroup(  98,     58,    18,    19,    98   );     //
    indexMap->setGroup(  99,     59,    19,     0,    99   );     // -------------

    indexMap->setGroup(  100,    101,    0,     1,    100  );     // -------------
    indexMap->setGroup(  101,    102,    1,     2,    101  );     //
    indexMap->setGroup(  102,    103,    2,     3,    102  );     //
    indexMap->setGroup(  103,    104,    3,     4,    103  );     //
    indexMap->setGroup(  104,    105,    4,     5,    104  );     //     ----
    indexMap->setGroup(  105,    106,    5,     6,    105  );     //     ----
    indexMap->setGroup(  106,    107,    6,     7,    106  );     //     ----     
    indexMap->setGroup(  107,    108,    7,     8,    107  );     //     ----     
    indexMap->setGroup(  108,    109,    8,     9,    108  );     //     ----    
    indexMap->setGroup(  109,    110,    9,    10,    109  );     //     here     
    indexMap->setGroup(  110,    111,   10,    11,    110  );     //     ----     
    indexMap->setGroup(  111,    112,   11,    12,    111  );     //     ----    
    indexMap->setGroup(  112,    113,   12,    13,    112  );     //     ----     
    indexMap->setGroup(  113,    114,   13,    14,    113  );     //     ----     
    indexMap->setGroup(  114,    115,   14,    15,    114  );     //     ----     
    indexMap->setGroup(  115,    116,   15,    16,    115  );     //     ----
    indexMap->setGroup(  116,    117,   16,    17,    116  );     //
    indexMap->setGroup(  117,    118,   17,    18,    117  );     //
    indexMap->setGroup(  118,    119,   18,    19,    118  );     //
    indexMap->setGroup(  119,    100,   19,     0,    119  );     // -------------

    indexMap->setGroup(  120,    0,    100,   101,    120  );     // -------------
    indexMap->setGroup(  121,    1,    101,   102,    121  );     //
    indexMap->setGroup(  122,    2,    102,   103,    122  );     //
    indexMap->setGroup(  123,    3,    103,   104,    123  );     //
    indexMap->setGroup(  124,    4,    104,   105,    124  );     //     ----
    indexMap->setGroup(  125,    5,    105,   106,    125  );     //     ----
    indexMap->setGroup(  126,    6,    106,   107,    126  );     //     ----     
    indexMap->setGroup(  127,    7,    107,   108,    127  );     //     ----     
    indexMap->setGroup(  128,    8,    108,   109,    128  );     //     ----    
    indexMap->setGroup(  129,    9,    109,   110,    129  );     //     ----     
    indexMap->setGroup(  130,    10,   110,   111,    130  );     //     here     
    indexMap->setGroup(  131,    11,   111,   112,    131  );     //     ----    
    indexMap->setGroup(  132,    12,   112,   113,    132  );     //     ----     
    indexMap->setGroup(  133,    13,   113,   114,    133  );     //     ----     
    indexMap->setGroup(  134,    14,   114,   115,    134  );     //     ----     
    indexMap->setGroup(  135,    15,   115,   116,    135  );     //     ----
    indexMap->setGroup(  136,    16,   116,   117,    136  );     //
    indexMap->setGroup(  137,    17,   117,   118,    137  );     //
    indexMap->setGroup(  138,    18,   118,   119,    138  );     //
    indexMap->setGroup(  139,    19,   119,   100,    139  );     // -------------

    indexMap->setGroup(  140,    20,   100,   101,    140  );     // -------------
    indexMap->setGroup(  141,    21,   101,   102,    141  );     //
    indexMap->setGroup(  142,    22,   102,   103,    142  );     //
    indexMap->setGroup(  143,    23,   103,   104,    143  );     //
    indexMap->setGroup(  144,    24,   104,   105,    144  );     //     ----
    indexMap->setGroup(  145,    25,   105,   106,    145  );     //     ----
    indexMap->setGroup(  146,    26,   106,   107,    146  );     //     ----     
    indexMap->setGroup(  147,    27,   107,   108,    147  );     //     ----     
    indexMap->setGroup(  148,    28,   108,   109,    148  );     //     ----    
    indexMap->setGroup(  149,    29,   109,   110,    149  );     //     ----     
    indexMap->setGroup(  150,    30,   110,   111,    150  );     //     ----     
    indexMap->setGroup(  151,    31,   111,   112,    151  );     //     here    
    indexMap->setGroup(  152,    32,   112,   113,    152  );     //     ----     
    indexMap->setGroup(  153,    33,   113,   114,    153  );     //     ----     
    indexMap->setGroup(  154,    34,   114,   115,    154  );     //     ----     
    indexMap->setGroup(  155,    35,   115,   116,    155  );     //     ----
    indexMap->setGroup(  156,    36,   116,   117,    156  );     //
    indexMap->setGroup(  157,    37,   117,   118,    157  );     //
    indexMap->setGroup(  158,    38,   118,   119,    158  );     //
    indexMap->setGroup(  159,    39,   119,   100,    159  );     // -------------

    indexMap->setGroup(  160,   101,    20,    21,    160  );     // -------------
    indexMap->setGroup(  161,   102,    21,    22,    161  );     //
    indexMap->setGroup(  162,   103,    22,    23,    162  );     //
    indexMap->setGroup(  163,   104,    23,    24,    163  );     //
    indexMap->setGroup(  164,   105,    24,    25,    164  );     //     ----
    indexMap->setGroup(  165,   106,    25,    26,    165  );     //     ----
    indexMap->setGroup(  166,   107,    26,    27,    166  );     //     ----     
    indexMap->setGroup(  167,   108,    27,    28,    167  );     //     ----     
    indexMap->setGroup(  168,   109,    28,    29,    168  );     //     ----    
    indexMap->setGroup(  169,   110,    29,    30,    169  );     //     ----     
    indexMap->setGroup(  170,   111,    30,    31,    170  );     //     ----     
    indexMap->setGroup(  171,   112,    31,    32,    171  );     //     ----    
    indexMap->setGroup(  172,   113,    32,    33,    172  );     //     here     
    indexMap->setGroup(  173,   114,    33,    34,    173  );     //     ----     
    indexMap->setGroup(  174,   115,    34,    35,    174  );     //     ----     
    indexMap->setGroup(  175,   116,    35,    36,    175  );     //     ----
    indexMap->setGroup(  176,   117,    36,    37,    176  );     //
    indexMap->setGroup(  177,   118,    37,    38,    177  );     //
    indexMap->setGroup(  178,   119,    38,    39,    178  );     //
    indexMap->setGroup(  179,   100,    39,    20,    179  );     // -------------

    indexMap->setGroup(  180,    61,    20,    21,    180  );     // -------------
    indexMap->setGroup(  181,    62,    21,    22,    181  );     //
    indexMap->setGroup(  182,    63,    22,    23,    182  );     //
    indexMap->setGroup(  183,    64,    23,    24,    183  );     //
    indexMap->setGroup(  184,    65,    24,    25,    184  );     //     ----
    indexMap->setGroup(  185,    66,    25,    26,    185  );     //     ----
    indexMap->setGroup(  186,    67,    26,    27,    186  );     //     ----     
    indexMap->setGroup(  187,    68,    27,    28,    187  );     //     ----     
    indexMap->setGroup(  188,    69,    28,    29,    188  );     //     ----    
    indexMap->setGroup(  189,    70,    29,    30,    189  );     //     ----     
    indexMap->setGroup(  190,    71,    30,    31,    190  );     //     ----     
    indexMap->setGroup(  191,    72,    31,    32,    191  );     //     ----    
    indexMap->setGroup(  192,    73,    32,    33,    192  );     //     ----     
    indexMap->setGroup(  193,    74,    33,    34,    193  );     //     here     
    indexMap->setGroup(  194,    75,    34,    35,    194  );     //     ----     
    indexMap->setGroup(  195,    76,    35,    36,    195  );     //     ----
    indexMap->setGroup(  196,    77,    36,    37,    196  );     //
    indexMap->setGroup(  197,    78,    37,    38,    197  );     //
    indexMap->setGroup(  198,    79,    38,    39,    198  );     //
    indexMap->setGroup(  199,    60,    39,    20,    199  );     // -------------

    indexMap->setGroup(  200,    20,    60,    61,    200  );     // -------------
    indexMap->setGroup(  201,    21,    61,    62,    201  );     //
    indexMap->setGroup(  202,    22,    62,    63,    202  );     //
    indexMap->setGroup(  203,    23,    63,    64,    203  );     //
    indexMap->setGroup(  204,    24,    64,    65,    204  );     //     ----
    indexMap->setGroup(  205,    25,    65,    66,    205  );     //     ----
    indexMap->setGroup(  206,    26,    66,    67,    206  );     //     ----     
    indexMap->setGroup(  207,    27,    67,    68,    207  );     //     ----     
    indexMap->setGroup(  208,    28,    68,    69,    208  );     //     ----    
    indexMap->setGroup(  209,    29,    69,    70,    209  );     //     ----     
    indexMap->setGroup(  210,    30,    70,    71,    210  );     //     ----     
    indexMap->setGroup(  211,    31,    71,    72,    211  );     //     ----    
    indexMap->setGroup(  212,    32,    72,    73,    212  );     //     ----     
    indexMap->setGroup(  213,    33,    73,    74,    213  );     //     ----     
    indexMap->setGroup(  214,    34,    74,    75,    214  );     //     here     
    indexMap->setGroup(  215,    35,    75,    76,    215  );     //     ----
    indexMap->setGroup(  216,    36,    76,    77,    216  );     //
    indexMap->setGroup(  217,    37,    77,    78,    217  );     //
    indexMap->setGroup(  218,    38,    78,    79,    218  );     //
    indexMap->setGroup(  219,    39,    79,    60,    219  );     // -------------

    indexMap->setGroup(  220,   120,    60,    61,    220  );     // -------------
    indexMap->setGroup(  221,   120,    61,    62,    221  );     //
    indexMap->setGroup(  222,   120,    62,    63,    222  );     //
    indexMap->setGroup(  223,   120,    63,    64,    223  );     //
    indexMap->setGroup(  224,   120,    64,    65,    224  );     //     ----
    indexMap->setGroup(  225,   120,    65,    66,    225  );     //     ----
    indexMap->setGroup(  226,   120,    66,    67,    226  );     //     ----     
    indexMap->setGroup(  227,   120,    67,    68,    227  );     //     ----     
    indexMap->setGroup(  228,   120,    68,    69,    228  );     //     ----    
    indexMap->setGroup(  229,   120,    69,    70,    229  );     //     ----     
    indexMap->setGroup(  230,   120,    70,    71,    230  );     //     ----     
    indexMap->setGroup(  231,   120,    71,    72,    231  );     //     ----    
    indexMap->setGroup(  232,   120,    72,    73,    232  );     //     ----     
    indexMap->setGroup(  233,   120,    73,    74,    233  );     //     ----     
    indexMap->setGroup(  234,   120,    74,    75,    234  );     //     ----     
    indexMap->setGroup(  235,   120,    75,    76,    235  );     //     here
    indexMap->setGroup(  236,   120,    76,    77,    236  );     //
    indexMap->setGroup(  237,   120,    77,    78,    237  );     //
    indexMap->setGroup(  238,   120,    78,    79,    238  );     //
    indexMap->setGroup(  239,   120,    79,    60,    239  );     // -------------


    // Space for triangle objects (which point to the verticies vectors)
    for (int i = 0; i < triCount; i++)
        triList[i] = new Tri3(true);

    // allocate space for projection values
    for (int i = 0; i < vertexCount; i++)
        projectedVertexList[i] = new Vec2();
    for (int i = 0; i < triCount; i++)
        projectedTriList[i] = new Tri2(true);

    // Store the created mesh in the class variable
    Mesh::capsuleMesh = new Mesh();

    Mesh::capsuleMesh->indexMap = indexMap;
    Mesh::capsuleMesh->verticies = vertexList;
    Mesh::capsuleMesh->normals = normalList;

    Mesh::capsuleMesh->vertexCount = vertexCount;
    Mesh::capsuleMesh->normalCount = triCount;
    Mesh::capsuleMesh->triCount = triCount;

    Mesh::capsuleMesh->tris = triList;
    Mesh::capsuleMesh->projectedVerticies = projectedVertexList;
    Mesh::capsuleMesh->projectedTris = projectedTriList;

    // Populate tri lists with pointers
    Mesh::capsuleMesh->mapTris();

    // Load normals
    Mesh::capsuleMesh->updateNormals();

}
