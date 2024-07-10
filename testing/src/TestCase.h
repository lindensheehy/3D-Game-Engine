#pragma once

#include "FunctionWrapperClass.h"

#include "../../src/log/log.h"

// This template allows this class to be used for any function signature
template<typename returnType, typename... args>
class TestCase {
    /*
        This class is used to create test cases
        As an input it takes a function to test and a set of parameters and return values to test
    */

    public:

        // Instance Variables
        FunctionWrapper<returnType, args...>* func;

        // Constructor
        TestCase(FunctionWrapper<returnType, args...>* func) {
            this->func = func;
            this->argSet = argSet;
        }

        // Destructor
        ~TestCase() {
            
            if (this->func != nullptr)
                delete this->func;

            return;

        }

        /*   Instance Functions   */

        // Runs all argument sets on the function
        void run() {

        }

    private:

        /*   Instance Functions   */

        // Runs a single argument set. This is called from run()
        void runSet(int set) {

        }

};