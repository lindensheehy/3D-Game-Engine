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
        This is used to determine if a parameter exists, and what type it is
        It does this by wrapping two internal arrays as follows:
        - 'names' This holds the name of each parameter, in one long string
                  This long string is not delimited, using 'namesIndexes' and 'namesLengths' to determine boundaries
        - 'types' This just a regular array of type ParameterType
                  These values coorespond to actual types (see xml/Core.h for more detail)

        This simplifies the process a TON, by just using matchParameter to check types

        The constructor is private because it is not intended to be used directly
        ParameterInfoBuilder should handle construction for you (see below)
    */

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
        // This is sort of redundant becuase of namesIndexes, but its just for ease of use
        int* namesLengths;

        // Stores each type
        ParameterType* types;

        // Length of each array. They should only ever be the same length, so one variable is fine
        int length;

};


class ParameterInfoBuilder {

    /*
        This class serves to construct ParameterInfo objects
        This makes use of linked lists for quick insertion
        Once the build() function is called, it will return a valid ParameterInfo object holding the same data
    */

    public:

        // Constructor
        ParameterInfoBuilder();

        // Destructor
        ~ParameterInfoBuilder();

        
        /*   Instance Functions   */

        // Builds the ParameterInfo object. Also resets the builder
        // Returns a new heap allocated ParameterInfo object
        ParameterInfo* build();

        // Deletes any existing data that was being built
        void reset();

        // Adds the parameter to the list
        // The strings in this class are read only, so this will use the same pointer
        void addParameter(const char* name, ParameterType type, int position);
        void addParameter(char* name, ParameterType type, int position);

    private:

        /*   Instance Variables   */

        // Holds the parameters
        LinkedList<Parameter*>* params;

};

}
