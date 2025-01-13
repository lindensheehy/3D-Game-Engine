#pragma once

#include "Utility.h"

template<typename type>
class LinkedList {

    /*
        Doubly linked list implementation.
        Any type is allowed, and nodes also store an integer id alongside their item
        There is an included iterator, to avoid using ids to iterate
    */

    public:

        class Node {

            /*
                Item for the doubly linked list
                Includes an item, and a int tag
            */

            public:

                /*   Instance Variables   */

                Node* next;
                Node* last;

                type item;
                int id;


                /*   Constructors   */
                Node() {
                    this->next = nullptr;
                    this->last = nullptr;
                    this->item = nullptr;
                    this->id = 0;
                }

                Node(type item) {
                    this->next = nullptr;
                    this->last = nullptr;
                    this->item = item;
                    this->id = 0;
                }

                Node(int id) {
                    this->next = nullptr;
                    this->last = nullptr;
                    this->item = nullptr;
                    this->id = id;
                }

                Node(type item, int id) {
                    this->next = nullptr;
                    this->last = nullptr;
                    this->item = item;
                    this->id = id;
                }


                /*   Instance Functions   */

                // Returns true if this node is the first node in the list.
                bool isFirst() {
                    return (this->last == nullptr);
                }

                // Returns true if this node is the last node in the list.
                bool isLast() {
                    return (this->next == nullptr);
                }
                
                // Logs the node in the format:  last id <- this id -> next id
                void log() {

                    if (this->last == nullptr)
                        logWrite("null");
                    else
                        logWrite(this->last->id);

                    logWrite(" <- ");
                    logWrite(this->id);
                    logWrite(" -> ");

                    if (this->next == nullptr)
                        logWrite("null", true);
                    else
                        logWrite(this->next->id, true);

                    return;

                }

        };

        /*   Instance Variables   */

        int length;


        // Constructor
        LinkedList() {
            this->first = nullptr;
            this->last = nullptr;

            this->length = 0;
            this->nextFreeId = 0;
        }

        // Destructor
        ~LinkedList() {

            if (this->length == 0) return;

            Node* currentRef = this->first;
            Node* nextRef = this->first->next;

            while (true) {

                delete currentRef;
                
                // Break case
                if (nextRef == nullptr) break;

                currentRef = nextRef;
                nextRef = currentRef->next;

            }

        }


        /*   Instance Functions   */
        
        void pushBack(type item) {

            this->pushBack(item, this->nextFreeId);
            this->nextFreeId++;
            return;

        }

        void pushBack(type item, int id) {

            Node* newNode = new Node(item, id);

            this->length++;

            // Empty list
            if (this->first == nullptr && this->last == nullptr) {
                this->first = newNode;
                this->last = newNode;
                return;
            }

            // Length 1 list
            if (this->first == this->last) {
                this->last = newNode;
                this->first->next = newNode;
                newNode->last = this->first;
                return;
            }

            // Length >2 list
            this->last->next = newNode;
            newNode->last = this->last;
            this->last = newNode;

            return;

        }

        void pushFront(type item) {

            this->pushFront(item, this->nextFreeId);
            this->nextFreeId++;
            return;

        }

        void pushFront(type item, int id) {

            Node* newNode = new Node(item, id);

            this->length++;

            // Empty list
            if (this->first == nullptr && this->last == nullptr) {
                this->first = newNode;
                this->last = newNode;
                return;
            }

            // Length 1 list
            if (this->first == this->last) {
                this->first = newNode;
                this->last->last = newNode;
                newNode->next = this->last;
                return;
            }

            // Length >2 list
            this->first->last = newNode;
            newNode->next = this->first;
            this->first = newNode;

            return;

        }

        type popBack() {

            Node* ret;
            type item;

            // Empty list
            if (this->first == nullptr && this->last == nullptr) {
                return nullptr;
            }

            this->length--;

            // Length 1 list
            if (this->first == this->last) {

                ret = this->last;
                this->last = nullptr;
                this->first = nullptr;

                item = ret->item;
                delete ret;

                return item;

            }

            // Length >2 list
            ret = this->last;
            this->last = ret->last;
            this->last->next = nullptr;

            item = ret->item;
            delete ret;

            return item;

        }

        type popFront() {

            Node* ret;
            type item;

            // Empty list
            if (this->first == nullptr && this->last == nullptr) {
                return nullptr;
            }

            this->length--;

            // Length 1 list
            if (this->first == this->last) {

                ret = this->first;
                this->last = nullptr;
                this->first = nullptr;

                item = ret->item;
                delete ret;

                return item;

            }

            // Length >2 list
            ret = this->first;
            this->first = ret->next;
            this->first->last = nullptr;

            item = ret->item;
            delete ret;

            return item;

        }

        // Pops the given item from the list. If there is two, it will pop the first. If there are none, it will return nullptr
        type pop(type item) {

            if (this->length == 0) return nullptr;

            if (this->length == 1) {

                if (this->first->item != item) return nullptr;

                type ret = this->first->item;

                delete this->first;
                this->length--;

                this->first = nullptr;
                this->last = nullptr;

                return ret;

            }

            type current;

            for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

                current = this->iterGetObj();

                if (current == item) {
                    
                    // Update the node before current if necessary
                    if (this->iterCurrent->last != nullptr) 
                        this->iterCurrent->last->next = this->iterCurrent->next;

                    // Otherwise, current is the first node, so update this->first accordingly
                    else
                        this->first = this->iterCurrent->next;

                    // Update the node after current if necessary
                    if (this->iterCurrent->next != nullptr) 
                        this->iterCurrent->next->last = this->iterCurrent->last;

                    // Otherwise, current is the last node, so update this->last accordingly
                    else
                        this->last = this->iterCurrent->last;

                    delete this->iterCurrent;
                    this->length--;

                    return current;

                }

            }

            // If none found return null
            return nullptr;

        }

        // Pops the node with this id. If the id doesnt exist in the list, this returns nullptr
        type popById(int id) {

            if (this->length == 0) return nullptr;

            if (this->length == 1) {

                if (this->first->id != id) return nullptr;

                type ret = this->first->item;

                delete this->first;
                this->length--;

                this->first = nullptr;
                this->last = nullptr;

                return ret;

            }

            for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {

                if (this->iterGetId() == id) {
                    
                    // Update the node before current if necessary
                    if (this->iterCurrent->last != nullptr) 
                        this->iterCurrent->last->next = this->iterCurrent->next;

                    // Otherwise, current is the first node, so update this->first accordingly
                    else
                        this->first = this->iterCurrent->next;

                    // Update the node after current if necessary
                    if (this->iterCurrent->next != nullptr) 
                        this->iterCurrent->next->last = this->iterCurrent->last;

                    // Otherwise, current is the last node, so update this->last accordingly
                    else
                        this->last = this->iterCurrent->last;

                    type ret = this->iterGetObj();

                    delete this->iterCurrent;
                    this->length--;

                    return ret;

                }

            }

            return nullptr;

        }

        // Returns a reference to the object with a given id. DOES NOT change the internal list.
        type getById(int id) {

            if (this->length == 0) return nullptr;

            if (this->length == 1) {

                if (this->first->id != id) return nullptr;

                return this->first->item;

            }

            int current;

            for (this->iterStart(0); !this->iterIsDone(); this->iterNext()) {
                current = this->iterGetId();
                if (current == id) return this->iterGetObj();
            }

            // If none found return null
            return nullptr;

        }

        // Sets the instance variable iterCurrent to an index, from where the other iterator functions can be called
        void iterStart(int index) {

            this->iterCurrent = this->first;

            if (index == 0) return;

            for (int i = 0; i < index; i++) {

                if (iterCurrent == nullptr) {
                    logWrite("Tried to start at iter at too high of an index! (LinkedList->iterStart(int))");
                    return;
                }

                this->iterCurrent = this->iterCurrent->next;

            }

        }

        // Returns the object of iterCurrent. Returns nullptr if the iterator is at null
        type iterGetObj() {

            if (this->iterCurrent == nullptr) return nullptr;

            return this->iterCurrent->item;

        }

        // Returns the id of iterCurrent. Returns -1 if the iterator is at null
        int iterGetId() {

            if (this->iterCurrent == nullptr) return -1;

            return this->iterCurrent->id;

        }

        // Moves the iterator forward 1
        void iterNext() {

            if (this->iterCurrent == nullptr) return;

            this->iterCurrent = this->iterCurrent->next;
            return;

        }

        // Moves the iterator back 1
        void iterLast() {

            if (this->iterCurrent == nullptr) return;

            this->iterCurrent = this->iterCurrent->last;
            return;

        }

        // Returns true if iterCurrent equals nullptr
        bool iterIsDone() {

            return (this->iterCurrent == nullptr);

        }

        // Logs all of the nodes in the order they stand in the list
        void log() {

            logWrite("LinkedList( length = ");
            logWrite(this->length, true);

            Node* current = this->first;

            while (true) {

                if (current == nullptr) break;

                logWrite("  ");
                current->log();

                current = current->next;

            }

            logWrite(")", true);

            return;

        }

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
        void swap(Node* node1, Node* node2) {

            // Different handling for when the two nodes are adjacent
            if (node1->next == node2) {
                
                // Update adjacent node pointers
                if (node1->last != nullptr) node1->last->next = node2;
                else this->first = node2;
                if (node2->next != nullptr) node2->next->last = node1;
                else this->last = node1;

                // Update affected node pointers
                node1->next = node2->next;
                node2->next = node1;

                node2->last = node1->last;
                node1->last = node2;

                return;

            }

            if (node2->next == node2) {
                
                // Update adjacent node pointers
                if (node2->last != nullptr) node2->last->next = node1;
                else this->first = node1;
                if (node1->next != nullptr) node1->next->last = node2;
                else this->last = node2;

                // Update affected node pointers
                node2->next = node1->next;
                node1->next = node2;

                node1->last = node2->last;
                node2->last = node1;

                return;

            }

            // Get adjacent nodes
            Node* node1Last = node1->last;
            Node* node1Next = node1->next;

            Node* node2Last = node2->last;
            Node* node2Next = node2->next;

            // Update adjacent node pointers
            if (node1Last != nullptr) node1Last->next = node2;
            if (node1Next != nullptr) node1Next->last = node2;

            if (node2Last != nullptr) node2Last->next = node1;
            if (node2Next != nullptr) node2Next->last = node1;

            // Update affected node pointers
            node1->next = node2Next;
            node1->last = node2Last;

            node2->last = node1Last;
            node2->next = node1Next;

            return;

        }

};
