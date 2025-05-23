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
        This class contains a mesh alongside some variables for handling physics interactions
        Most of the instance functions here just directly call the same function from Mesh class
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

        float mass;
        float gravityFactor;
        float frictionFactor;
        float bounceFactor;


        // Constructor
        Object();
        Object(Geometry::Mesh* mesh);


        /*   Instance Functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Object* copy();

        // Returns the center of the mesh (average of all verticies). This returns a reference to an instance variable.
        Geometry::Vec3* getCenter();

        // Moves the object in space by the specified distance.
        Object* move(Geometry::Vec3* dist);
        Object* move(float dx, float dy, float dz);

        // Scales the object by a given factor on each axis
        Object* scaleBy(float factor);
        Object* scaleBy(float fx, float fy, float fz);

        // Rotates the object by the specified angles. rotates around (0, 0, 0) if no around vector is given
        Object* rotate(Geometry::Vec3* angle);
        Object* rotate(float yaw, float pitch, float roll);

        // Sets the color of the object
        Object* setColor(uint32 color);

        // Updates all the physics variables of this object based on a delta time
        void doPhysics(float dt);

        // Simple collision check. the object will act as though there is an infinite mass plane at a y level
        void doFloorCollision(float y);

        bool collides(Object* other);

    private:

        // Stores the last version of each vector so update() knows what to do. 
        // pos does not need this becuase its handled object side as opposed to mesh side
        Geometry::Vec3 lastRotation;
        Geometry::Vec3 lastScale;


};



class ObjectSet {

    /*
        Contains a set of Objects in the form of a doubly linked list
        This can be added and removed from, and this way a group of objects can be rendered and drawn together
        This set is used for items unaffected by physics
    */

    public:

        // Constructor
        ObjectSet();

        // Destructor
        ~ObjectSet();


        /*   Instance Functions   */

        // Returns the length of the internal linked list
        int getLength();
        
        void pushBack(Object* obj);
        void pushBack(Object* obj, int id);
        void pushFront(Object* obj);
        void pushFront(Object* obj, int id);


        inline Object* popBack() { return this->list->popBack(); }
        inline Object* popFront() { return this->list->popFront(); }

        // Pops the node with this id. If the id doesnt exist in the list, this returns nullptr
        inline Object* popById(int id) { return this->list->popById(id); }

        // Returns a reference to the object with a given id. DOES NOT change the internal list.
        inline Object* getById(int id) { return this->list->getById(id); }

        // Sets the instance variable iterCurrent to an index, from where the other iterator functions can be called
        inline void iterStart(int index) { this->list->iterStart(index); }

        // Returns the object of iterCurrent. Returns nullptr if the iterator is at null
        inline Object* iterGetObj() { return this->list->iterGetObj(); }

        // Returns the id of iterCurrent. Returns -1 if the iterator is at null
        inline int iterGetId() { return this->list->iterGetId(); }

        // Moves the iterator forward 1
        inline void iterNext() { this->list->iterNext(); }

        // Moves the iterator back 1
        inline void iterLast() { this->list->iterLast(); }

        // Returns true if iterCurrent equals nullptr
        inline bool iterIsDone() { return this->list->iterIsDone(); }


        /*   Functions to affect all objects in the set   */

        // Changes the position of all the objects
        void moveAll(Geometry::Vec3* dist);
        void moveAll(float dx, float dy, float dz);

        // Sets the position of all the objects
        void setPosAll(Geometry::Vec3* pos);
        void setPosAll(float x, float y, float z);

        // Adds velocity to all the objects
        void addVelocityAll(Geometry::Vec3* v);
        void addVelocityAll(float vx, float vy, float vz);

        // Sets the velocity of all the objects
        void setVelocityAll(Geometry::Vec3* v);
        void setVelocityAll(float vx, float vy, float vz);

        // Sets the gravitational acceleration for all objects in the set
        void setGravityAll(Geometry::Vec3* gravity);  // This copies the values from thi Vec3 into instance variables, this one needs to be handled accordingly
        void setGravityAll(float gx, float gy, float gz);  // Sets all the instance variables to these values
        void setGravityAll(float gy);  // Sets the gravity to just down or up

        // Sets the opacity of all the objects
        void setOpacityAll(float opacity);

        // Calls Object->doPhysics for all in the set
        void doAllPhysics(float dt);

        // Projects all the objects into window coordinates
        void projectAll(Graphics::Rendering::Camera* camera, Graphics::Rendering::Display* display);

        // Projects, sorts, and draws all the objects in the set, in order from furthest away to closest, optional opacity value from 0-1
        void drawAll(Graphics::Rendering::Renderer* renderer, Graphics::Rendering::Camera* camera);

        // Does the same as drawAll(), but also draws red normal vectors on all the tris
        void drawAllWithNormals(Graphics::Rendering::Renderer* renderer, Graphics::Rendering::Camera* camera);

        // Logs all of the nodes in the order they stand in the list
        inline void log() { this->list->log(); }

    private:
        
        /*   Instance Variables   */

        // List shouldnt be directly accessed
        LinkedList<Object*>* list;

};

}
