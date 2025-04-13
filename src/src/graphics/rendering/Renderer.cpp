#include "graphics/rendering/Renderer.h"

using namespace Graphics::Rendering;


Renderer::Renderer(Drawing::PixelDrawer* pixelDrawer, Display* display) {

    this->pixelDrawer = pixelDrawer;
    this->display = display;

}

void Renderer::drawObject(Physics::Object* object, Camera* camera) {

    if (object == nullptr) {
        logWrite("Called Renderer::drawObject(Object*, Camera*) with arg1 as nullptr", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called Renderer::drawObject(Object*, Camera*) with arg2 as nullptr", true);
        return;
    }
    
    using namespace Geometry;   // for Matrix4 and Vec3
    
    /*
        These are the operations I handle here, in order of when they should happen:
        - Object scaling
        - Object rotation (around the origin)
            - Y (pitch)
            - X (yaw)
            - Z (roll)
        - Translation (object.pos - camera.pos)
        - Camera rotation (after translation because its relative to the camera position)
            - Y (pitch)
            - X (yaw)
            - (roll is ignored for the camera)

        Matrices can be joined by multiplying them. The resulting matrix contains the properties of both initial matrices
        However, when matrices are multiplied, the operations happen backwards
        So given:       m3 = m1 * m2;
        This makes:     vec *= m3;
        Equivalent to:  vec *= m2;  vec *= m1;

        The order above is the order they should execute, so the following is the order of joining
        - Camera rotation
            - X
            - Y
        - Translation
        - Object rotation
            - Z
            - X
            - Y
        - Object scaling
    */

    // First I build two matrices:
    // - transform      => general transformation matrix for the mesh vertices
    // - objectRotation => used to transform normals. Also a subpart of transform

    Matrix4 transform;
    Matrix4 rotation;
    {   
        // For holding intermediate matrices
        Matrix4 temp;


        Matrix4 objectRotation;
        Matrix4::rotationZ( object->rotation.z, &(objectRotation) );

        Matrix4::rotationX( object->rotation.x, &(temp) );
        objectRotation.mul(temp);

        Matrix4::rotationY( object->rotation.y, &(temp) );
        objectRotation.mul(temp);


        Matrix4 cameraRotation;
        Matrix4::rotationX( camera->facingAngle.x, &(cameraRotation) );

        Matrix4::rotationY( camera->facingAngle.y, &(temp) );
        cameraRotation.mul(temp);


        // Build the transform matrix
        transform.set(cameraRotation);

        Vec3 positionOffset;
        positionOffset.set(object->pos).sub(camera->pos);
        Matrix4::translation( positionOffset, &(temp) );
        transform.mul(temp);

        transform.mul(objectRotation);

        Matrix4::scaling( object->scale, &(temp) );
        transform.mul(temp);

        // Build the rotation matrix
        rotation.set(cameraRotation);
        rotation.mul(objectRotation);
    }

    // Apply the transformations to all vertices and normals. This is effectively the projection pipeline
    {
        Geometry::Vec3 temp;
        Geometry::Mesh* mesh = object->mesh;

        // Transform the vertices
        for (int i = 0; i < mesh->vertexCount; i++) {

            temp.set(mesh->vertices[i]);
            transform.mul( &(temp) );

            // Cache the camera space vector
            mesh->cameraVertices[i].set(temp);

            temp.project();
            this->display->toDisplayPos( &(temp) );

            // Cache the screen space vector
            mesh->screenVertices[i].set(temp.x, temp.y);

        }

        // Transform the normals
        for (int i = 0; i < mesh->normalCount; i++) {

            temp.set(mesh->normals[i]);
            rotation.mul( &(temp) );

            // Cache the result
            mesh->transformedNormals[i].set(temp);

        }
    }

    // Tell PixelTracker which Object is being drawn (if needed)
    if (this->pixelDrawer->pixelTracker.watchingPixelWrites) {
        this->pixelDrawer->pixelTracker.currentObject = object;
    }

    // Now draw the mesh with this matrix
    this->drawerOpacity = object->opacity;
    this->drawMesh(object->mesh, camera);

    // Reset PixelTracker (again, if needed)
    if (this->pixelDrawer->pixelTracker.watchingPixelWrites) {
        this->pixelDrawer->pixelTracker.currentObject = nullptr;
    }

    return;

}

void Renderer::drawMesh(Geometry::Mesh* mesh, Camera* camera) {

    float lightAngle, lightFactor;
    uint32 shade;

    int indexNormal, indexA, indexB, indexC;
    Geometry::Vec2 a2; Geometry::Vec3 a3;
    Geometry::Vec2 b2; Geometry::Vec3 b3;
    Geometry::Vec2 c2; Geometry::Vec3 c3;

    for (int i = 0; i < mesh->triCount; i++) {

        // Get the indexes
        mesh->indexMap.getGroup(i, &(indexA), &(indexB), &(indexC), &(indexNormal));

        // Store the camera space vertices locally
        a3.set( mesh->cameraVertices[indexA] );
        b3.set( mesh->cameraVertices[indexB] );
        c3.set( mesh->cameraVertices[indexC] );
        
        // Get triangle center
        Geometry::Vec3 triCenter;
        triCenter.set(a3).add(b3).add(c3).inverseScale(3);

        // Backface culling
        Geometry::Vec3 triCenterNormalized;
        triCenterNormalized.set(triCenter).normalize();
        float angle = triCenterNormalized.getAngle(mesh->transformedNormals[indexNormal]);
        if (angle < 90.0f ) continue;

        // Find a shade based on the lighting vec
        lightAngle = mesh->transformedNormals[indexNormal].getAngle( &(camera->lightingVec) );
        lightFactor = lightAngle / 180;

        shade = mesh->color;
        shade = Color::setBrightness(shade, lightFactor);

        // Store the screen space vertices before calling drawTri with these values
        a2.set( mesh->screenVertices[indexA] );
        b2.set( mesh->screenVertices[indexB] );
        c2.set( mesh->screenVertices[indexC] );

        // Draw the triangle
        this->drawTri(shade, a2, a3, b2, b3, c2, c3);

    }

    return;

}

void Renderer::drawTri(
    uint32 color,
    Geometry::Vec2& a, Geometry::Vec3& a3,
    Geometry::Vec2& b, Geometry::Vec3& b3,
    Geometry::Vec2& c, Geometry::Vec3& c3
) {

    /*
        This function uses a bounding box approach to fill the triangle
        It defines starting points, with some padding (see 'constexpr int padding')
        Then it uses the edge functions for each edge of the triangle to determine if the pixel lies within
        It also allows a little bit of leniency (see 'constexpr float leniency'), which helps fill gaps between triangles
    */

    // First find the bounding box of the triangle
    constexpr int padding = 1;
    int x1 = round( min(a.x, min(b.x, c.x)) ) - padding;
    int y1 = round( min(a.y, min(b.y, c.y)) ) - padding;
    int x2 = round( max(a.x, max(b.x, c.x)) ) + padding;
    int y2 = round( max(a.y, max(b.y, c.y)) ) + padding;

    // Break early if the triangle is unreasonably large (this means it lies outside the cameras FOV)
    // This will be replaced later with proper frustum culling, but it does the job for the time being
    if ( (x2 - x1 > 4096) || (y2 - y1 > 4096) ) return; 

    // Lambda helper functions

    // Returns true if the pixel (x, y) lies within the triangle (a, b, c)
    auto insideTri = [a, b, c](
        int x, int y
    ) -> bool {

        // Get the edge function value for each line (a, b), (b, c), (c, a)
        float ab = ((b.x - a.x) * (y - a.y)) - ((b.y - a.y) * (x - a.x));
        float bc = ((c.x - b.x) * (y - b.y)) - ((c.y - b.y) * (x - b.x));
        float ca = ((a.x - c.x) * (y - c.y)) - ((a.y - c.y) * (x - c.x));

        // Pixels this far away the from the triangle will be counted
        constexpr float leniency = 0.8f;

        // Return true if they all share a sign. All positive or all negative
        return (
            (ab >= -leniency && bc >= -leniency && ca >= -leniency) ||
            (ab <= leniency && bc <= leniency && ca <= leniency) 
        );

    };


    // Some general stuff for finding barycentric coordinates in the loop
    float inverseAreaTotal = 1.0f / abs(
        (a.x * (b.y - c.y)) +
        (b.x * (c.y - a.y)) +
        (c.x * (a.y - b.y))
    );

    Geometry::Vec3 temp, depthVec;
    float areaA, areaB, areaC;
    float lA, lB, lC;

    // Loop over the previously defined bounds
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {

            // Skip iteration if the pixel is outside the triangle
            if ( !insideTri(i, j) ) continue;

            areaA = abs(
                (i * (b.y - c.y)) +
                (b.x * (c.y - j)) +
                (c.x * (j - b.y))
            );
        
            areaB = abs(
                (a.x * (j - c.y)) +
                (i * (c.y - a.y)) +
                (c.x * (a.y - j))
            );
        
            areaC = abs(
                (a.x * (b.y - j)) +
                (b.x * (j - a.y)) +
                (i * (a.y - b.y))
            );
        
            lA = areaA * inverseAreaTotal;
            lB = areaB * inverseAreaTotal;
            lC = areaC * inverseAreaTotal;
            
            temp.set(a3).scale(lA);
            depthVec.set(temp);

            temp.set(b3).scale(lB);
            depthVec.add(temp);

            temp.set(c3).scale(lC);
            depthVec.add(temp);

            // Magnitude, but without the sqrt call
            float depth = (depthVec.x * depthVec.x) + (depthVec.y * depthVec.y) + (depthVec.z * depthVec.z);

            this->pixelDrawer->drawPixel(color, i, j, depth, this->drawerOpacity);

        }
    }

    return;

}
