#pragma once

#include "util/Utility.h"
#include "util/LinkedList.h"

#include "xml/Core.h"


namespace Xml {

struct Parameter {
    const char* name;
    ParameterType type;
    // position is stored as id in the linked list
};


class ParameterInfo {

    /*
        This is a wrapper for two internal arrays as follows
        This is used to determine if a parameter exists, and what type it is

        This simplifies the process a TON, but just use matchParameter so check it

        The constructor is private because it is not intended to be used directly
        ParameterInfoBuilder should do this for you because it will dynamically build the data set
    */

    // This gives ParameterInfoBuilder access to the private members
    friend class ParameterInfoBuilder;

    public:

        // Destructor
        ~ParameterInfo();


        /*   Instance Functions   */

        ParameterType matchParameter(const char* name, int* positionOut);

    private:

        // Constructor
        ParameterInfo(LinkedList<Parameter*>* params);

        /*   Instance Variables   */

        // Stores each name in one long string
        char* names;

        // Stores the start index of each sub string in names
        int* namesIndexes;

        // Stores the length of each sub string in names
        // This is sort of redundant becuase of namesIndexes, but its just better ease of use
        int* namesLengths;

        // Stores each type
        ParameterType* types;

        // Length of each array, they should only ever be the same length, so one variable is fine
        int length;

};


class ParameterInfoBuilder {

    /*
        This class serves to help in constructing ParameterInfo objects
        This makes use of linked lists for dynamic insertion
        Once the build() function is called, it will return a valid ParameterInfo object holding the same data
    */

    // Also let ParameterInfo see into this builder
    friend class ParameterInfo;

    public:

        // Constructor
        ParameterInfoBuilder();

        // Destructor
        ~ParameterInfoBuilder();

        
        /*   Instance Functions   */

        // Builds the ParameterInfo object. Also resets the builder
        ParameterInfo* build();

        // Resets the object being built to empty
        void reset();

        // Adds the parameter to the list. Takes a string and a type
        // The strings in this class are read only, so this will use the same pointer
        void addParameter(const char* name, ParameterType type, int position);
        void addParameter(char* name, ParameterType type, int position);

    private:

        /*   Instance Variables   */

        // Holds the parameters
        LinkedList<Parameter*>* params;

};

}
