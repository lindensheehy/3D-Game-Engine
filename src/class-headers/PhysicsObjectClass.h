#pragma once

#include "Vec2Class.h"
#include "Vec3Class.h"
#include "Tri2Class.h"
#include "Tri3Class.h"
#include "MeshClass.h"

class PhysicsObject {

    /*
        This class serves as an extension to the Mesh class.
        This uses a Mesh object to find collisions.
        Other instance variables here determine other qualities the object can have.
    */

    public:

        /*   Instance Variables   */

        Mesh* mesh;

        // Object qualities
        double mass;
        double frictionFactor;
        double bounceFactor;


        /*   Constructors   */
        PhysicsObject();
        PhysicsObject(Mesh* mesh);

        // Destructor
        ~PhysicsObject();


        /*   Instance Functions   */
        
        
};