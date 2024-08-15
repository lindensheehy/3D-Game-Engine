#pragma once

#include "Mesh.h"
#include "Camera.h"
#include "Drawer.h"

#include "Log.h"

// Related classes
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

        class Node {

            /*
                Item for the doubly linked list
                Includes an object type, and a string tag
            */

            public:

                /*   Instance Variables   */

                Node* next;
                Node* last;

                Object* obj;
                int id;

                // Optional ones for physics
                double mass;
                double frictionFactor;
                double bounceFactor;


                /*   Constructors   */
                Node();
                Node(Object* obj);
                Node(int id);
                Node(Object* obj, int id);


                /*   Instance Functions   */

                // Returns true if this node is the first node in the list.
                bool isFirst();

                // Returns true if this node is the last node in the list.
                bool isLast();
                
                // Logs the node in the format:  last id <- this id -> next id
                void log();

        };

        /*   Instance Variables   */

        int length;


        // Constructor
        ObjectSet();

        // Destructor
        ~ObjectSet();


        /*   Instance Functions   */
        
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

        // Sorts the nodes based on distance between the object center and the camera pos. Sorting is done from greatest to largest
        void sortByDistance(Camera* camera);

        // Projects, sorts, and draws all the objects in the set, in order from furthest away to closest
        void drawAll(Drawer* drawer, Camera* camera, Display* display);

        // Does the same as drawAll(), but also draws red normal vectors on all the tris
        void drawAllWithNormals(Drawer* drawer, Camera* camera, Display* display);

        // Logs all of the nodes in the order they stand in the list
        void log();

    private:
        
        /*   Instance Variables   */

        // Node objects shouldnt be used outside of the class
        Node* first;
        Node* last;
        Node* iterCurrent;

        // No reason to make this public
        int nextFreeId;

        /*   Instance Functions   */

        // Swaps the two nodes in the list. This changes the affected nodes, as well as those around them.
        void swap(Node* node1, Node* node2);

};
