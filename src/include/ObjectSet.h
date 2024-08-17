#pragma once

#include "LinkedList.h"
#include "Mesh.h"
#include "Camera.h"
#include "Drawer.h"

#include "Log.h"


class Object {
    
    /*
        This class contains a mesh alongside some variables for handling physics interactions
    */

    public:

        /*   Instance Variables   */

        Mesh* mesh;

        Vec3* pos;
        Vec3* velocity;
        Vec3* acceleration;

        double mass;
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
        Object* move(double dx, double dy, double dz);

        // Scales the object by a given factor on each axis
        Object* scale(double factor);
        Object* scale(double fx, double fy, double fz);

        // Rotates the object by the specified angles. rotates around (0, 0, 0) if no around vector is given
        Object* rotate(Vec3* angle, Vec3* around);
        Object* rotate(double yaw, double pitch, double roll, Vec3* around = nullptr);

        // Rotates the object around its center
        Object* rotateSelf(Vec3* angle);
        Object* rotateSelf(double yaw, double pitch, double roll);

        // Sets the color of the object
        Object* setColor(Uint32 color);

        bool collides(Object* other);

        void doGravity();


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

        Object* popBack();
        Object* popFront();

        // Pops the node with this id. If the id doesnt exist in the list, this returns nullptr
        Object* popById(int id);

        // Returns a reference to the object with a given id. DOES NOT change the internal list.
        Object* getById(int id);

        // Sets the instance variable iterCurrent to an index, from where the other iterator functions can be called
        void iterStart(int index);

        // Returns the object of iterCurrent. Returns nullptr if the iterator is at null
        Object* iterGetObj();

        // Returns the id of iterCurrent. Returns -1 if the iterator is at null
        int iterGetId();

        // Moves the iterator forward 1
        void iterNext();

        // Moves the iterator back 1
        void iterLast();

        // Returns true if iterCurrent equals nullptr
        bool iterIsDone();

        // Projects all the objects into window coordinates
        void projectAll(Camera* camera, Display* display);

        // Projects, sorts, and draws all the objects in the set, in order from furthest away to closest
        void drawAll(Drawer* drawer, Camera* camera, Display* display);

        // Does the same as drawAll(), but also draws red normal vectors on all the tris
        void drawAllWithNormals(Drawer* drawer, Camera* camera, Display* display);

        // Logs all of the nodes in the order they stand in the list
        void log();

    private:
        
        /*   Instance Variables   */

        // List shouldnt be directly accessed
        LinkedList<Object*>* list;

};
