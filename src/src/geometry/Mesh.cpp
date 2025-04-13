#include "geometry/Mesh.h"

using namespace Geometry;


// Static declarations
Mesh* Mesh::tempMesh = nullptr;
Mesh* Mesh::cubeMesh = nullptr;
Mesh* Mesh::sphereMesh = nullptr;
Mesh* Mesh::tetrahedronMesh = nullptr;
Mesh* Mesh::capsuleMesh = nullptr;

/*  ------------------------------------  */
/*  -----------   IndexMap   -----------  */
/*  ------------------------------------  */

Mesh::IndexMap::IndexMap() {
    this->map = nullptr;
    this->size = 0;
}

Mesh::IndexMap::~IndexMap() {
    delete this->map;
}

void Mesh::IndexMap::init(int size) {

    this->size = size;

    delete[] map;
    this->map = new Set[size];

    return;

}

void Mesh::IndexMap::setState(const IndexMap* other) {

    for (int i = 0; i < (this->size); i++) {
        this->map[i].vertex1 = other->map[i].vertex1;
        this->map[i].vertex2 = other->map[i].vertex2;
        this->map[i].vertex3 = other->map[i].vertex3;
        this->map[i].normal = other->map[i].normal;
    }

    return;

}

void Mesh::IndexMap::setGroup(int index, int v1, int v2, int v3, int normal) {

    if (index >= this->size) {
        logWrite("Called Mesh::IndexMap->setGroup() for index ");
        logWrite(index);
        logWrite(" with size ");
        logWrite(this->size, true);
        return;
    }

    this->map[index].vertex1 = v1;
    this->map[index].vertex2 = v2;
    this->map[index].vertex3 = v3;
    this->map[index].normal = normal;
}

void Mesh::IndexMap::getGroup(int index, int* v1, int* v2, int* v3, int* normal) const {

    if (index >= this->size) {
        logWrite("Called Mesh::IndexMap->getGroup() for index ");
        logWrite(index);
        logWrite(" with size ");
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

Mesh::Mesh(int vertexCount, int normalCount, int triCount) : 
vertexCount(vertexCount), normalCount(normalCount), triCount(triCount) {

    this->indexMap.init(triCount);

    int verticesSize = (vertexCount * sizeof(Vec3));
    int normalsSize = (normalCount * sizeof(Vec3));
    int trisSize = (triCount * sizeof(Tri3)); 

    int screenVerticesSize = (vertexCount * sizeof(Vec2));

    this->memSize = (
        (2 * verticesSize) +    // These two need second buffers for projection data
        (2 * normalsSize) +     // Vertices for 'cameraVertices' and normals for 'transformedNormals'
        trisSize + 
        screenVerticesSize
    );

    // Allocate the memory block
    this->mem = operator new(this->memSize);

    // Cast to char* because the compiler complains about void* arithmatic
    // char* is still byte alligned, so the numbers im adding represent byte offset values
    char* p = reinterpret_cast<char*>(this->mem);
    char* pStart = p;
    
    // Order is intentional here. Tris first because they are used less often than the rest
    // Then the 3d vertex data, then screen space data, then normal data

    this->tris = reinterpret_cast<Tri3*>(p);
    p += trisSize;

    this->vertices = reinterpret_cast<Vec3*>(p);
    p += verticesSize;

    this->cameraVertices = reinterpret_cast<Vec3*>(p);
    p += verticesSize;

    this->screenVertices = reinterpret_cast<Vec2*>(p);
    p += screenVerticesSize;

    this->normals = reinterpret_cast<Vec3*>(p);
    p += normalsSize;

    this->transformedNormals = reinterpret_cast<Vec3*>(p);
    p += normalsSize;

    char* pEnd = p;

    // Log error if needed. Sensitive memory operations are happening here, so i want to make sure im safe
    if ((pEnd - pStart) != this->memSize) {
        logWrite("Problem occurred during Mesh instantiation!", true);
        logWrite(" -> Allocated buffer of size ");
        logWrite(this->memSize);
        logWrite(" but wrote ");
        logWrite(pEnd - pStart);
        logWrite(" bytes", true);
    }

    this->color = 0xFFFFFFFF;

    this->centerValid = false;

}

Mesh::~Mesh() {

    /*
        Since there is only one master allocation for this class, thats all that needs to be freed
        Also it was made using "operator new", so it must be freed using "operator delete"
    */

    operator delete(this->mem);

    return;

}

Mesh* Mesh::copy() const {

    Mesh* copy = new Mesh(this->vertexCount, this->normalCount, this->triCount);

    // Copy over the memory block
    memcpy(copy->mem, this->mem, this->memSize);

    // Copy index map
    copy->indexMap.setState( &(this->indexMap) );

    copy->mapTris();

    return copy;
    
}

Vec3* Mesh::getCenter() {

    /*
        The rest of this app expects pointers for arg passing so the return type is Vec3*
    */

    if (this->centerValid) return &(this->center);

    float x = 0;
    float y = 0;
    float z = 0;

    for (int i = 0; i < this->vertexCount; i++) {
        x += this->vertices[i].x;
        y += this->vertices[i].y;
        z += this->vertices[i].z;
    }

    x /= this->vertexCount;
    y /= this->vertexCount;
    z /= this->vertexCount;

    this->center.set(x, y, z);
    this->centerValid = true;

    return &(this->center);

}

Mesh* Mesh::move(Vec3* dist) {

    // Log the error case
    if (dist == nullptr) {
        logWrite("Called Mesh->move(Vec3*) on a null pointer!", true);
        return nullptr;
    }

    return this->move(dist->x, dist->y, dist->z);

}

Mesh* Mesh::move(float dx, float dy, float dz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->vertices[i].add(dx, dy, dz);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::scale(float factor) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->vertices[i].scale(factor, factor, factor);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::scale(float fx, float fy, float fz) {

    for (int i = 0; i < this->vertexCount; i++) {
        this->vertices[i].scale(fx, fy, fz);
    }

    this->updateNormals();

    this->centerValid = false;

    return this;

}

Mesh* Mesh::rotate(Vec3* angle, Vec3* around /* default value = nullptr */) {

    // Log the error case
    if (angle == nullptr) {
        logWrite("Called Mesh->rotate(Vec3*, Vec3*) with 'angle' being a null pointer!", true);
        return nullptr;
    }

    this->rotate(angle->x, angle->y, angle->z, around);

    return this;

}

Mesh* Mesh::rotate(float yaw, float pitch, float roll, Vec3* around /* default value = nullptr */) {

    /*
        When 'around' is nullptr (the default value), the rotation happens around the center
    */

    if (around == nullptr) {
        for (int i = 0; i < this->vertexCount; i++) {
            this->vertices[i].rotate(yaw, pitch, roll, this->getCenter());
        }
    }

    else {
        for (int i = 0; i < this->vertexCount; i++) {
            this->vertices[i].rotate(yaw, pitch, roll, around);
        }
    }

    // Normals are not relative to anything, and as such should not be rotated around anything but (0, 0, 0)
    for (int i = 0; i < this->normalCount; i++) {
        this->normals[i].rotate(yaw, pitch, roll);
    }

    this->centerValid = false;

    return this;

}

Mesh* Mesh::setColor(uint32 color) {
    this->color = color;
    return this;
}

void Mesh::updateNormals() {

    /*   Variables used for this loop   */

    // Current triangle
    Tri3 tri;

    // These are the operands for the cross product
    Vec3 vec1to2, vec1to3;

    // Stores the result of the cross product. Cross product returns a new Vec3, so this needs to be a pointer
    Vec3 newNormal;

    // Used to determine normal direction with respect to the plane of the triangle
    float dist1, dist2;
    Vec3* meshCenter = this->getCenter();;
    Vec3 triCenter;
    Vec3 normalOffset;

    // Used to find the index in the normals list for the given triangles normal
    // The underscore is a placeholder becuase i dont need the first 3 out parameters
    int _, normalIndex;


    for (int i = 0; i < this->triCount; i++) {

        tri = this->tris[i];

        // Get one of the two possible normals
        vec1to2.set(tri.v1).sub(tri.v2);
        vec1to3.set(tri.v1).sub(tri.v3);

        vec1to2.crossProduct( &(vec1to3), &(newNormal) );
        newNormal.normalize();

        // Check if the found normal faces outwards
        tri.getCenter( &(triCenter) );
        normalOffset.set( &(newNormal) ).scale(0.05);

        triCenter.add( &(normalOffset) );
        float dist1 = triCenter.distanceTo(meshCenter);
        triCenter.sub( &(normalOffset) ).sub( &(normalOffset) );
        float dist2 = triCenter.distanceTo(meshCenter);

        // Flip if its facing towards the center
        if (dist1 < dist2) newNormal.scale(-1);

        this->indexMap.getGroup(i, &_, &_, &_, &normalIndex);
        this->normals[normalIndex].set( &(newNormal) );

    }

    return;

}

void Mesh::mapTris() {

    if (this->triCount != this->indexMap.size) {
        logWrite("Called Mesh->mapTris() with ");
        logWrite(this->triCount);
        logWrite(" tris, but ");
        logWrite(this->indexMap.size);
        logWrite(" entries in the index map", true);
        return;
    }

    int vertex1Index, vertex2Index, vertex3Index, normalIndex;

    for (int i = 0; i < this->indexMap.size; i++) {

        // Get values from map
        this->indexMap.getGroup(i, &vertex1Index, &vertex2Index, &vertex3Index, &normalIndex);

        // Set pointers for 3d tris
        this->tris[i].v1 = &(this->vertices[vertex1Index]);
        this->tris[i].v2 = &(this->vertices[vertex2Index]);
        this->tris[i].v3 = &(this->vertices[vertex3Index]);
        this->tris[i].normal = &(this->normals[normalIndex]);

    }

}

void Mesh::initMeshes() {

    // Some pointers to make assignments easier to read
    Vec3* vertexList;
    Vec3* normalList;
    Tri3* triList;

    // General variables used across different mesh instantiations
    int vertexCount;
    int normalCount;
    int triCount;

 
    /* ------------------- */
    /* ---  Temp Mesh  --- */
    /* ------------------- */

    vertexCount = 3;
    normalCount = 1;
    triCount = 1;

    Mesh::tempMesh = new Mesh(vertexCount, normalCount, triCount);

    // Load vertices
    vertexList = Mesh::tempMesh->vertices;
    vertexList[0].set(-0.5, -0.5, 0);
    vertexList[1].set(0.5, -0.5, 0);
    vertexList[2].set(0, 1, 0);

    // Load normal
    normalList = Mesh::tempMesh->normals;
    normalList[0].set(0, 0, -1);

    Mesh::tempMesh->indexMap.setGroup(0, 0, 1, 2, 0);

    Mesh::tempMesh->mapTris();


    /* ------------------- */
    /* ---  Cube Mesh  --- */
    /* ------------------- */

    vertexCount = 8;
    normalCount = 6;
    triCount = 12;

    Mesh::cubeMesh = new Mesh(vertexCount, normalCount, triCount);
    
    // Load verticies
    vertexList = Mesh::cubeMesh->vertices;
    vertexList[0].set(-0.5, -0.5, -0.5);
    vertexList[1].set(-0.5, -0.5, 0.5);
    vertexList[2].set(0.5, -0.5, -0.5);
    vertexList[3].set(0.5, -0.5, 0.5);
    vertexList[4].set(-0.5, 0.5, -0.5);
    vertexList[5].set(-0.5, 0.5, 0.5);
    vertexList[6].set(0.5, 0.5, -0.5);
    vertexList[7].set(0.5, 0.5, 0.5);

    // Load Normals
    normalList = Mesh::cubeMesh->normals;
    normalList[0].set(0, -1, 0);
    normalList[1].set(0, 1, 0);
    normalList[2].set(-1, 0, 0);
    normalList[3].set(1, 0, 0);
    normalList[4].set(0, 0, -1);
    normalList[5].set(0, 0, 1);

    // Load index map
    //                             triangle     v2      normal
    //                                ||   v1   ||   v3   ||
    //                                \/   \/   \/   \/   \/
    Mesh::cubeMesh->indexMap.setGroup(0,   0,   3,   1,   0); // facing -y
    Mesh::cubeMesh->indexMap.setGroup(1,   0,   3,   2,   0); // facing -y
    Mesh::cubeMesh->indexMap.setGroup(2,   4,   7,   5,   1); // facing +y
    Mesh::cubeMesh->indexMap.setGroup(3,   4,   7,   6,   1); // facing +y
    Mesh::cubeMesh->indexMap.setGroup(4,   0,   5,   4,   2); // facing -x
    Mesh::cubeMesh->indexMap.setGroup(5,   0,   5,   1,   2); // facing -x
    Mesh::cubeMesh->indexMap.setGroup(6,   2,   7,   3,   3); // facing +x
    Mesh::cubeMesh->indexMap.setGroup(7,   2,   7,   6,   3); // facing +x
    Mesh::cubeMesh->indexMap.setGroup(8,   0,   6,   2,   4); // facing -z
    Mesh::cubeMesh->indexMap.setGroup(9,   0,   6,   4,   4); // facing -z
    Mesh::cubeMesh->indexMap.setGroup(10,  1,   7,   3,   5); // facing +z
    Mesh::cubeMesh->indexMap.setGroup(11,  1,   7,   5,   5); // facing +z

    // Populate tri lists with pointers
    Mesh::cubeMesh->mapTris();

    /* --------------------- */
    /* ---  Sphere Mesh  --- */
    /* --------------------- */

    vertexCount = 102;
    triCount = 200;
    normalCount = 200;

    Mesh::sphereMesh = new Mesh(vertexCount, normalCount, triCount);
    vertexList = Mesh::sphereMesh->vertices;
    
    // Load verticies

    // Bottom and top
    vertexList[100].set(0, -0.5, 0);
    vertexList[101].set(0, 0.5, 0);

    // Rotate a vector around at a certain length to make new vertices
    float theta = 360 / 20;
    Vec3 v;

    // Along the circumference (index 0-19 inclusive)
    v.set(0, 0, 0.5);

    for (int i = 0; i < 20; i++) {
        v.rotate(theta, 0, 0);
        vertexList[i].set(v);
    }

    // 30 degrees below the circumference (index 20-39 inclusive)
    v.set(0, 0, 0.5);
    v.rotate(0, 30, 0);
    v.rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 20; i < 40; i++) {
        v.rotate(theta, 0, 0);
        vertexList[i].set(v);
    }

    // 30 degrees above the circumference (index 40-59 inclusive)
    v.set(0, 0, 0.5);
    v.rotate(0, -30, 0);
    v.rotate(theta / 2, 0, 0); // Offset by half

    for (int i = 40; i < 60; i++) {
        v.rotate(theta, 0, 0);
        vertexList[i].set(v);
    }

    // 60 degrees below the circumference (index 60-79 inclusive)
    v.set(0, 0, 0.5);
    v.rotate(0, 60, 0);

    for (int i = 60; i < 80; i++) {
        v.rotate(theta, 0, 0);
        vertexList[i].set(v);
    }

    // 60 degrees above the circumference (index 80-99 inclusive)
    v.set(0, 0, 0.5);
    v.rotate(0, -60, 0);

    for (int i = 80; i < 100; i++) {
        v.rotate(theta, 0, 0);
        vertexList[i].set(v);
    }

    // Normals are handled automatically later

    // Load index map
    //                                 triangle          v2          normal
    //                                    ||      v1     ||     v3     ||
    //                                    \/      \/     \/     \/     \/
    Mesh::sphereMesh->indexMap.setGroup(  0,     101,    80,    81,    0    );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  1,     101,    81,    82,    1    );     //
    Mesh::sphereMesh->indexMap.setGroup(  2,     101,    82,    83,    2    );     //
    Mesh::sphereMesh->indexMap.setGroup(  3,     101,    83,    84,    3    );     //
    Mesh::sphereMesh->indexMap.setGroup(  4,     101,    84,    85,    4    );     //
    Mesh::sphereMesh->indexMap.setGroup(  5,     101,    85,    86,    5    );     //     here
    Mesh::sphereMesh->indexMap.setGroup(  6,     101,    86,    87,    6    );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  7,     101,    87,    88,    7    );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  8,     101,    88,    89,    8    );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  9,     101,    89,    90,    9    );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  10,    101,    90,    91,    10   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  11,    101,    91,    92,    11   );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  12,    101,    92,    93,    12   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  13,    101,    93,    94,    13   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  14,    101,    94,    95,    14   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  15,    101,    95,    96,    15   );     //
    Mesh::sphereMesh->indexMap.setGroup(  16,    101,    96,    97,    16   );     //
    Mesh::sphereMesh->indexMap.setGroup(  17,    101,    97,    98,    17   );     //
    Mesh::sphereMesh->indexMap.setGroup(  18,    101,    98,    99,    18   );     //
    Mesh::sphereMesh->indexMap.setGroup(  19,    101,    99,    80,    19   );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  20,     81,    40,    41,    20   );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  21,     82,    41,    42,    21   );     //
    Mesh::sphereMesh->indexMap.setGroup(  22,     83,    42,    43,    22   );     //
    Mesh::sphereMesh->indexMap.setGroup(  23,     84,    43,    44,    23   );     //
    Mesh::sphereMesh->indexMap.setGroup(  24,     85,    44,    45,    24   );     //
    Mesh::sphereMesh->indexMap.setGroup(  25,     86,    45,    46,    25   );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  26,     87,    46,    47,    26   );     //     here     
    Mesh::sphereMesh->indexMap.setGroup(  27,     88,    47,    48,    27   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  28,     89,    48,    49,    28   );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  29,     90,    49,    50,    29   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  30,     91,    50,    51,    30   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  31,     92,    51,    52,    31   );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  32,     93,    52,    53,    32   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  33,     94,    53,    54,    33   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  34,     95,    54,    55,    34   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  35,     96,    55,    56,    35   );     //
    Mesh::sphereMesh->indexMap.setGroup(  36,     97,    56,    57,    36   );     //
    Mesh::sphereMesh->indexMap.setGroup(  37,     98,    57,    58,    37   );     //
    Mesh::sphereMesh->indexMap.setGroup(  38,     99,    58,    59,    38   );     //
    Mesh::sphereMesh->indexMap.setGroup(  39,     80,    59,    40,    39   );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  40,     40,    80,    81,    40   );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  41,     41,    81,    82,    41   );     //
    Mesh::sphereMesh->indexMap.setGroup(  42,     42,    82,    83,    42   );     //
    Mesh::sphereMesh->indexMap.setGroup(  43,     43,    83,    84,    43   );     //
    Mesh::sphereMesh->indexMap.setGroup(  44,     44,    84,    85,    44   );     //
    Mesh::sphereMesh->indexMap.setGroup(  45,     45,    85,    86,    45   );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  46,     46,    86,    87,    46   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  47,     47,    87,    88,    47   );     //     here     
    Mesh::sphereMesh->indexMap.setGroup(  48,     48,    88,    89,    48   );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  49,     49,    89,    90,    49   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  50,     50,    90,    91,    50   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  51,     51,    91,    92,    51   );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  52,     52,    92,    93,    52   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  53,     53,    93,    94,    53   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  54,     54,    94,    95,    54   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  55,     55,    95,    96,    55   );     //
    Mesh::sphereMesh->indexMap.setGroup(  56,     56,    96,    97,    56   );     //
    Mesh::sphereMesh->indexMap.setGroup(  57,     57,    97,    98,    57   );     //
    Mesh::sphereMesh->indexMap.setGroup(  58,     58,    98,    99,    58   );     //
    Mesh::sphereMesh->indexMap.setGroup(  59,     59,    99,    80,    59   );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  60,      1,    40,    41,    60   );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  61,      2,    41,    42,    61   );     //
    Mesh::sphereMesh->indexMap.setGroup(  62,      3,    42,    43,    62   );     //
    Mesh::sphereMesh->indexMap.setGroup(  63,      4,    43,    44,    63   );     //
    Mesh::sphereMesh->indexMap.setGroup(  64,      5,    44,    45,    64   );     //
    Mesh::sphereMesh->indexMap.setGroup(  65,      6,    45,    46,    65   );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  66,      7,    46,    47,    66   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  67,      8,    47,    48,    67   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  68,      9,    48,    49,    68   );     //     here    
    Mesh::sphereMesh->indexMap.setGroup(  69,     10,    49,    50,    69   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  70,     11,    50,    51,    70   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  71,     12,    51,    52,    71   );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  72,     13,    52,    53,    72   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  73,     14,    53,    54,    73   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  74,     15,    54,    55,    74   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  75,     16,    55,    56,    75   );     //
    Mesh::sphereMesh->indexMap.setGroup(  76,     17,    56,    57,    76   );     //
    Mesh::sphereMesh->indexMap.setGroup(  77,     18,    57,    58,    77   );     //
    Mesh::sphereMesh->indexMap.setGroup(  78,     19,    58,    59,    78   );     //
    Mesh::sphereMesh->indexMap.setGroup(  79,      0,    59,    40,    79   );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  80,     40,     0,     1,    80   );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  81,     41,     1,     2,    81   );     //
    Mesh::sphereMesh->indexMap.setGroup(  82,     42,     2,     3,    82   );     //
    Mesh::sphereMesh->indexMap.setGroup(  83,     43,     3,     4,    83   );     //
    Mesh::sphereMesh->indexMap.setGroup(  84,     44,     4,     5,    84   );     //
    Mesh::sphereMesh->indexMap.setGroup(  85,     45,     5,     6,    85   );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  86,     46,     6,     7,    86   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  87,     47,     7,     8,    87   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  88,     48,     8,     9,    88   );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  89,     49,     9,    10,    89   );     //     here     
    Mesh::sphereMesh->indexMap.setGroup(  90,     50,    10,    11,    90   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  91,     51,    11,    12,    91   );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  92,     52,    12,    13,    92   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  93,     53,    13,    14,    93   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  94,     54,    14,    15,    94   );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  95,     55,    15,    16,    95   );     //
    Mesh::sphereMesh->indexMap.setGroup(  96,     56,    16,    17,    96   );     //
    Mesh::sphereMesh->indexMap.setGroup(  97,     57,    17,    18,    97   );     //
    Mesh::sphereMesh->indexMap.setGroup(  98,     58,    18,    19,    98   );     //
    Mesh::sphereMesh->indexMap.setGroup(  99,     59,    19,     0,    99   );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  100,    20,     0,     1,    100  );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  101,    21,     1,     2,    101  );     //
    Mesh::sphereMesh->indexMap.setGroup(  102,    22,     2,     3,    102  );     //
    Mesh::sphereMesh->indexMap.setGroup(  103,    23,     3,     4,    103  );     //
    Mesh::sphereMesh->indexMap.setGroup(  104,    24,     4,     5,    104  );     //
    Mesh::sphereMesh->indexMap.setGroup(  105,    25,     5,     6,    105  );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  106,    26,     6,     7,    106  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  107,    27,     7,     8,    107  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  108,    28,     8,     9,    108  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  109,    29,     9,    10,    109  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  110,    30,    10,    11,    110  );     //     here     
    Mesh::sphereMesh->indexMap.setGroup(  111,    31,    11,    12,    111  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  112,    32,    12,    13,    112  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  113,    33,    13,    14,    113  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  114,    34,    14,    15,    114  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  115,    35,    15,    16,    115  );     //
    Mesh::sphereMesh->indexMap.setGroup(  116,    36,    16,    17,    116  );     //
    Mesh::sphereMesh->indexMap.setGroup(  117,    37,    17,    18,    117  );     //
    Mesh::sphereMesh->indexMap.setGroup(  118,    38,    18,    19,    118  );     //
    Mesh::sphereMesh->indexMap.setGroup(  119,    39,    19,     0,    119  );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  120,     1,    20,    21,    120  );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  121,     2,    21,    22,    121  );     //
    Mesh::sphereMesh->indexMap.setGroup(  122,     3,    22,    23,    122  );     //
    Mesh::sphereMesh->indexMap.setGroup(  123,     4,    23,    24,    123  );     //
    Mesh::sphereMesh->indexMap.setGroup(  124,     5,    24,    25,    124  );     //
    Mesh::sphereMesh->indexMap.setGroup(  125,     6,    25,    26,    125  );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  126,     7,    26,    27,    126  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  127,     8,    27,    28,    127  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  128,     9,    28,    29,    128  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  129,    10,    29,    30,    129  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  130,    11,    30,    31,    130  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  131,    12,    31,    32,    131  );     //     here    
    Mesh::sphereMesh->indexMap.setGroup(  132,    13,    32,    33,    132  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  133,    14,    33,    34,    133  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  134,    15,    34,    35,    134  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  135,    16,    35,    36,    135  );     //
    Mesh::sphereMesh->indexMap.setGroup(  136,    17,    36,    37,    136  );     //
    Mesh::sphereMesh->indexMap.setGroup(  137,    18,    37,    38,    137  );     //
    Mesh::sphereMesh->indexMap.setGroup(  138,    19,    38,    39,    138  );     //
    Mesh::sphereMesh->indexMap.setGroup(  139,     0,    39,    20,    139  );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  140,    61,    20,    21,    140  );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  141,    62,    21,    22,    141  );     //
    Mesh::sphereMesh->indexMap.setGroup(  142,    63,    22,    23,    142  );     //
    Mesh::sphereMesh->indexMap.setGroup(  143,    64,    23,    24,    143  );     //
    Mesh::sphereMesh->indexMap.setGroup(  144,    65,    24,    25,    144  );     //
    Mesh::sphereMesh->indexMap.setGroup(  145,    66,    25,    26,    145  );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  146,    67,    26,    27,    146  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  147,    68,    27,    28,    147  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  148,    69,    28,    29,    148  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  149,    70,    29,    30,    149  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  150,    71,    30,    31,    150  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  151,    72,    31,    32,    151  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  152,    73,    32,    33,    152  );     //     here     
    Mesh::sphereMesh->indexMap.setGroup(  153,    74,    33,    34,    153  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  154,    75,    34,    35,    154  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  155,    76,    35,    36,    155  );     //
    Mesh::sphereMesh->indexMap.setGroup(  156,    77,    36,    37,    156  );     //
    Mesh::sphereMesh->indexMap.setGroup(  157,    78,    37,    38,    157  );     //
    Mesh::sphereMesh->indexMap.setGroup(  158,    79,    38,    39,    158  );     //
    Mesh::sphereMesh->indexMap.setGroup(  159,    60,    39,    20,    159  );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  160,    20,    60,    61,    160  );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  161,    21,    61,    62,    161  );     //
    Mesh::sphereMesh->indexMap.setGroup(  162,    22,    62,    63,    162  );     //
    Mesh::sphereMesh->indexMap.setGroup(  163,    23,    63,    64,    163  );     //
    Mesh::sphereMesh->indexMap.setGroup(  164,    24,    64,    65,    164  );     //
    Mesh::sphereMesh->indexMap.setGroup(  165,    25,    65,    66,    165  );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  166,    26,    66,    67,    166  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  167,    27,    67,    68,    167  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  168,    28,    68,    69,    168  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  169,    29,    69,    70,    169  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  170,    30,    70,    71,    170  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  171,    31,    71,    72,    171  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  172,    32,    72,    73,    172  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  173,    33,    73,    74,    173  );     //     here     
    Mesh::sphereMesh->indexMap.setGroup(  174,    34,    74,    75,    174  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  175,    35,    75,    76,    175  );     //
    Mesh::sphereMesh->indexMap.setGroup(  176,    36,    76,    77,    176  );     //
    Mesh::sphereMesh->indexMap.setGroup(  177,    37,    77,    78,    177  );     //
    Mesh::sphereMesh->indexMap.setGroup(  178,    38,    78,    79,    178  );     //
    Mesh::sphereMesh->indexMap.setGroup(  179,    39,    79,    60,    179  );     // -------------

    Mesh::sphereMesh->indexMap.setGroup(  180,   100,    60,    61,    180  );     // -------------
    Mesh::sphereMesh->indexMap.setGroup(  181,   100,    61,    62,    181  );     //
    Mesh::sphereMesh->indexMap.setGroup(  182,   100,    62,    63,    182  );     //
    Mesh::sphereMesh->indexMap.setGroup(  183,   100,    63,    64,    183  );     //
    Mesh::sphereMesh->indexMap.setGroup(  184,   100,    64,    65,    184  );     //
    Mesh::sphereMesh->indexMap.setGroup(  185,   100,    65,    66,    185  );     //     ----
    Mesh::sphereMesh->indexMap.setGroup(  186,   100,    66,    67,    186  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  187,   100,    67,    68,    187  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  188,   100,    68,    69,    188  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  189,   100,    69,    70,    189  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  190,   100,    70,    71,    190  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  191,   100,    71,    72,    191  );     //     ----    
    Mesh::sphereMesh->indexMap.setGroup(  192,   100,    72,    73,    192  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  193,   100,    73,    74,    193  );     //     ----     
    Mesh::sphereMesh->indexMap.setGroup(  194,   100,    74,    75,    194  );     //     here     
    Mesh::sphereMesh->indexMap.setGroup(  195,   100,    75,    76,    195  );     //
    Mesh::sphereMesh->indexMap.setGroup(  196,   100,    76,    77,    196  );     //
    Mesh::sphereMesh->indexMap.setGroup(  197,   100,    77,    78,    197  );     //
    Mesh::sphereMesh->indexMap.setGroup(  198,   100,    78,    79,    198  );     //
    Mesh::sphereMesh->indexMap.setGroup(  199,   100,    79,    60,    199  );     // -------------

    // Populate tri lists with pointers
    Mesh::sphereMesh->mapTris();

    // Load normals automatically
    Mesh::sphereMesh->updateNormals();

    // Not gonna bother handling these this way yet, this whole function will be deprecated soon anyway
    Mesh::capsuleMesh = nullptr;
    Mesh::tetrahedronMesh = nullptr;

    return;

}
