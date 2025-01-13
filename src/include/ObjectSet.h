#pragma once

#include "Utility.h"

#include "LinkedList.h"
#include "Mesh.h"
#include "Camera.h"
#include "Drawer.h"


class Object {
    
    /*
        This class contains a mesh alongside some variables for handling physics interactions
        Most of the instance functions here just directly call the same function from Mesh class
    */

    public:

        /*   Instance Variables   */

        Mesh* mesh;

        Vec3* pos;
        Vec3* rotation;
        Vec3* scale;
        Vec3* velocity;
        Vec3* gravity;

        double opacity;

        double mass;
        double gravityFactor;
        double frictionFactor;
        double bounceFactor;


        // Constructor
        Object();
        Object(Mesh* mesh);

        // Destructor
        ~Object();


        /*   Instance Functions   */

        // Creates a copy of the instance, and returns a pointer to it.
        Object* copy();

        // Returns the center of the mesh (average of all verticies). This returns a reference to an instance variable.
        Vec3* getCenter();

        // Moves the object in space by the specified distance.
        Object* move(Vec3* dist);
        Object* move(double dx, double dy, double dz);

        // Scales the object by a given factor on each axis
        Object* scaleBy(double factor);
        Object* scaleBy(double fx, double fy, double fz);

        // Rotates the object by the specified angles. rotates around (0, 0, 0) if no around vector is given
        Object* rotate(Vec3* angle, Vec3* around);
        Object* rotate(double yaw, double pitch, double roll, Vec3* around /* default value = nullptr */);

        // Rotates the object around its center
        Object* rotateSelf(Vec3* angle);
        Object* rotateSelf(double yaw, double pitch, double roll);

        // Sets the color of the object
        Object* setColor(uint32 color);

        // Updates all the physics variables of this object based on a delta time
        void doPhysics(double dt);

        // Simple collision check. the object will act as though there is an infinite mass plane at a y level
        void doFloorCollision(double y);

        // Updates the mesh if any vectors have been changed
        void update();

        bool collides(Object* other);

    private:

        // Stores the last version of each vector so update() knows what to do. 
        // pos does not need this becuase its handled object side as opposed to mesh side
        Vec3* lastRotation;
        Vec3* lastScale;


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
        void moveAll(Vec3* dist);
        void moveAll(double dx, double dy, double dz);

        // Sets the position of all the objects
        void setPosAll(Vec3* pos);
        void setPosAll(double x, double y, double z);

        // Adds velocity to all the objects
        void addVelocityAll(Vec3* v);
        void addVelocityAll(double vx, double vy, double vz);

        // Sets the velocity of all the objects
        void setVelocityAll(Vec3* v);
        void setVelocityAll(double vx, double vy, double vz);

        // Sets the gravitational acceleration for all objects in the set
        void setGravityAll(Vec3* gravity);  // This copies the values from thi Vec3 into instance variables, this one needs to be handled accordingly
        void setGravityAll(double gx, double gy, double gz);  // Sets all the instance variables to these values
        void setGravityAll(double gy);  // Sets the gravity to just down or up

        // Sets the opacity of all the objects
        void setOpacityAll(double opacity);

        // Calls Object->doPhysics for all in the set
        void doAllPhysics(double dt);

        // Updates any objects where vectors have been changed
        void updateAll();

        // Projects all the objects into window coordinates
        void projectAll(Camera* camera, Display* display);

        // Projects, sorts, and draws all the objects in the set, in order from furthest away to closest, optional opacity value from 0-1
        void drawAll(Drawer* drawer, Camera* camera, Display* display);
        void drawAll(Drawer* drawer, Camera* camera, Display* display, double opacity);

        // Does the same as drawAll(), but also draws red normal vectors on all the tris
        void drawAllWithNormals(Drawer* drawer, Camera* camera, Display* display);
        void drawAllWithNormals(Drawer* drawer, Camera* camera, Display* display, double opacity);

        // Logs all of the nodes in the order they stand in the list
        inline void log() { this->list->log(); }

    private:
        
        /*   Instance Variables   */

        // List shouldnt be directly accessed
        LinkedList<Object*>* list;

};
