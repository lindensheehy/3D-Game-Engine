#pragma once

#include "util/Utility.h"

#include "util/LinkedList.h"
#include "geometry/Mesh.h"
#include "graphics/rendering/Camera.h"
#include "graphics/rendering/Renderer.h"
#include "graphics/drawing/Drawer.h"


namespace Physics {

class Object {
    
    /*
        This class represents a game object. It contains a Mesh pointer and some vectors/values
        Meshes are shared by Objects, because the transformations happen Object side

        The Meshes in this program are largely static. So this class contains the primary transformation vectors
        To adjust how the object appears (position, scale, etc.), change the vectors in this class, no where else
    */

    public:

        /*   Instance Variables   */

        Geometry::Mesh* mesh;

        Geometry::Vec3 pos;
        Geometry::Vec3 rotation;
        Geometry::Vec3 scale;
        Geometry::Vec3 velocity;
        Geometry::Vec3 gravity;

        float opacity;

        float gravityFactor;
        
        // Unused (postponed until V2)
        float mass;
        float frictionFactor;
        float bounceFactor;


        // Constructors
        Object();
        Object(Geometry::Mesh* mesh);


        /*   Instance Functions   */

        // Deep copy (mostly). Returns a new Object instance. The copy will use the same Mesh pointer
        Object* copy() const;

        // Moves the object in space by the specified distance.
        Object* move(const Geometry::Vec3* dist);
        Object* move(float dx, float dy, float dz);

        // Scales the object by a given factor on each axis
        Object* scaleBy(float factor);
        Object* scaleBy(float fx, float fy, float fz);

        // Rotates the object by the specified angles (in place rotation)
        Object* rotate(const Geometry::Vec3* angle);
        Object* rotate(float yaw, float pitch, float roll);

        Object* setColor(uint32 color);

        // Updates all the physics variables of this object based on a delta time
        void doPhysics(float dt);

        // Unfinished (postponed until V2)
        bool collides(const Object* other) const;

};



class ObjectSet {

    /*
        Contains a set of Objects in a LinkedList (util/LinkedList.h)
        This allows a group of objects to be rendered, drawn, and even transformed together
    */

    public:

        // Constructor
        ObjectSet();

        // Destructor
        ~ObjectSet();


        /*   Instance Functions   */
        
        void pushBack(Object* obj);
        void pushBack(Object* obj, int id);
        void pushFront(Object* obj);
        void pushFront(Object* obj, int id);


        /*
            Inline functions. These operations are simply forwarded to the internal LinkedList
            This could be avoiding by extending LinkedList, but composition > inheritance ;)

            See LinkedList for more detail about implementation and behaviour
        */

        inline int getLength() const { return this->list->length; }

        inline Object* popBack() { return this->list->popBack(); }

        inline Object* popFront() { return this->list->popFront(); }

        inline Object* popById(int id) { return this->list->popById(id); }

        inline Object* getById(int id) { return this->list->getById(id); }

        inline void iterStart(int index) { this->list->iterStart(index); }

        inline Object* iterGetObj() const { return this->list->iterGetObj(); }

        inline int iterGetId() const { return this->list->iterGetId(); }

        inline void iterNext() { this->list->iterNext(); }

        inline void iterLast() { this->list->iterLast(); }

        inline bool iterIsDone() const { return this->list->iterIsDone(); }


        /*   Functions affecting all objects in the set   */

        // Adds to the position of all the objects
        void moveAll(const Geometry::Vec3* dist);
        void moveAll(float dx, float dy, float dz);

        // Sets the position of all the objects
        void setPosAll(const Geometry::Vec3* pos);
        void setPosAll(float x, float y, float z);

        // Adds velocity to all the objects
        void addVelocityAll(const Geometry::Vec3* v);
        void addVelocityAll(float vx, float vy, float vz);

        // Sets the velocity of all the objects
        void setVelocityAll(const Geometry::Vec3* v);
        void setVelocityAll(float vx, float vy, float vz);

        // Sets the gravitational acceleration for all objects in the set
        void setGravityAll(const Geometry::Vec3* gravity);
        void setGravityAll(float gx, float gy, float gz);
        void setGravityAll(float gy);

        // Sets the opacity of all the objects (between 0 and 1)
        void setOpacityAll(float opacity);

        // Calls Object->doPhysics for all in the set
        void doAllPhysics(float dt);

        // Projects, sorts, and draws all the objects in the set, in order from furthest away to closest, optional opacity value from 0-1
        void drawAll(Graphics::Rendering::Renderer* renderer, const Graphics::Rendering::Camera* camera);

        // Does the same as drawAll(), but also draws red normal vectors on all the tris
        void drawAllWithNormals(Graphics::Rendering::Renderer* renderer, const Graphics::Rendering::Camera* camera);

        // Logs all of the nodes in the order they stand in the list
        inline void log() const { this->list->log(); }

    private:
        
        /*   Instance Variables   */

        // This shouldnt be directly accessed
        LinkedList<Object*>* list;

};

}
