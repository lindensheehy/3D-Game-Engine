#pragma once

#include "util/Utility.h"
#include "util/LinkedList.h"

#include "xml/Core.h"


class ParameterInfo {

    /*
        This is a wrapper for two internal arrays as follows
        This is used to determine if a parameter exists, and what type it is

        This simplifies the process a TON, but just use matchParameter so check it

        The constructor is not intended to be used directly
        ParameterInfoBuilder should do this for you because it will dynamically build the data set
    */

    public:

        // Constructor
        ParameterInfo(char* names, ParameterType* types, int length);

        // Destructor
        ~ParameterInfo();


        /*   Instance Functions   */

        ParameterType matchParameter(const char* name);

    private:

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

    public:

        // Constructor
        ParameterInfoBuilder();

        // Destructor
        ~ParameterInfoBuilder();

        
        /*   Instance Functions   */

        // Builds the ParameterInfo object
        ParameterInfo* build();

        // Resets the object being built to empty
        void reset();

        // Adds the parameter to the list. Takes a string and a type
        // The strings in this class are read only, so this will use the same pointer
        void addParameter(const char* name, ParameterType type);
        void addParameter(char* name, ParameterType type);

    private:

        /*   Instance Variables   */

        // Holds the parameter names
        LinkedList<const char*>* names;

        // Holds the parameter types
        LinkedList<ParameterType>* types;


};
