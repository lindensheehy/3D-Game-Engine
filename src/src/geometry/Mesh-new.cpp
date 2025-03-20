#include "geometry/Mesh-new.h"


// Static declarations
Mesh* Mesh::cubeMesh = nullptr;
Mesh* Mesh::sphereMesh = nullptr;
Mesh* Mesh::tetrahedronMesh = nullptr;
Mesh* Mesh::capsuleMesh = nullptr;

/*  ------------------------------------  */
/*  -----------   IndexMap   -----------  */
/*  ------------------------------------  */

// Constructor
Mesh::IndexMap::IndexMap() {
    this->map = nullptr;
    this->size = 0;
}

// Destructor
Mesh::IndexMap::~IndexMap() {
    delete this->map;
}

// Instance functions
void Mesh::IndexMap::init(int size) {
    this->size = size;
    this->map = new Set[size];
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
        logWrite(" of size ");
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

// Constructor
Mesh::Mesh(int vertexCount, int normalCount, int triCount) : 
vertexCount(vertexCount), normalCount(normalCount), triCount(triCount) {

    int verticesSize = (vertexCount * sizeof(Vec3));
    int normalsSize = (normalCount * sizeof(Vec3));
    int trisSize = (triCount * sizeof(Tri3)); 

    this->memSize = verticesSize + normalsSize + trisSize;

    // Allocate the memory block
    this->mem = operator new(this->memSize);

    // Assign the list pointers to sections of the mem block
    this->vertices = reinterpret_cast<Vec3*>(this->mem);
    this->normals = reinterpret_cast<Vec3*>(this->mem + verticesSize);
    this->tris = reinterpret_cast<Tri3*>(this->mem + verticesSize + normalsSize);

    this->color = 0xFFFFFFFF;

    this->centerValid = false;

}

// Destructor
Mesh::~Mesh() {

    /*
        Since there is only one master allocation for this class, thats all that needs to be freed
        Also it was made using "operator new", so it must be freed using "operator delete"
    */

    operator delete(this->mem);

    return;

}

// Instance Funtions
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
    Vec3* newNormal;

    // Used to determine normal direction with respect to the plane of the triangle
    float dist1, dist2;
    Vec3* meshCenter;
    Vec3* triCenter;
    Vec3 normalOffset;

    // Used to find the index in the normals list for the given triangles normal
    // The underscore is a placeholder becuase i dont need the first 3 out parameters
    int _, normalIndex;


    for (int i = 0; i < this->triCount; i++) {

        tri = this->tris[i];

        // Get one of the two possible normals
        vec1to2.set(tri.v1)->sub(tri.v2);
        vec1to3.set(tri.v1)->sub(tri.v3);

        newNormal = vec1to2.crossProduct( &(vec1to3) );
        newNormal->normalise();

        // Check if the found normal faces outwards
        meshCenter = this->getCenter();                   // Not a new object
        triCenter = tri.getCenter();                      // New object
        normalOffset.set(newNormal)->scale(0.05);

        triCenter->add( &(normalOffset) );
        float dist1 = triCenter->distanceTo(meshCenter);
        triCenter->sub( &(normalOffset) )->sub( &(normalOffset) );
        float dist2 = triCenter->distanceTo(meshCenter);

        // Flip if its facing towards the center
        if (dist1 < dist2) newNormal->scale(-1);

        this->indexMap.getGroup(i, &_, &_, &_, &normalIndex);
        this->normals[normalIndex].set(newNormal);

        // Clean up
        delete triCenter;
        delete newNormal;

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
