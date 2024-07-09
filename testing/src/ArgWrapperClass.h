/*
    This class is seperate from TestCase for cleanliness, but it could just be in the same file its not used anywhere else
*/

// For logging error cases
#include "../../src/log/log.h"

// This template allows this class to be used for any set of arguments types
template<typename... types>
class ArgWrapper {
    /*
        This wraps a list of argument sets which would then be passed to a TestCase instance to test upon
    */

    public:

        // Instance Variables
        args* items;
        int setCount;
        int setLength;
        int listLength;

        // Constructor
        ArgumentWrapper(int size, types... args) {

            this->setCount = size;
            this->setLength = sizeof...(types);
            this->listLength = this->setCount * this->setLength;

            this->items = new types[this->listLength]{args...};

            return;

        }

        // Destructor
        ~ArgWrapper() {
            
            if (this->items != nullptr) {

                for (int i = 0; i < this->size; i++) {

                    if (this->items[i] != nullptr)
                        delete this->items[i];

                }

            }

            return;

        }

        /*   Instance Functions   */

        // Returns a pointer to the value becuase the type is dynamic
        void* get(int set, int index) {

            if (set >= this->setCount || index >= this->setLength) {

                logWrite("Called ArgWrapper->get(int, int) on an out of bounds index!", true);
                logWrite("get(");
                logWrite(set);
                logWrite(", ");
                logWrite(index);
                logWrite(") on length (");
                logWrite(this->setCount);
                logWrite(", ");
                logWrite(this->setLength);
                logWrite(")", true);

                return nullptr;

            }

            return &this->items[(set * this->setLength) + index];

        }
};
