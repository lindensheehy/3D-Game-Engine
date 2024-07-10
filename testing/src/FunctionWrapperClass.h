#pragma once

/*
    This class is seperate for cleanliness, but it could just be in the same file, its not used anywhere else
*/

// This template allows this class to be used for any function signature
template<typename returnType, typename... args>
class FunctionWrapper {
    /*
        This class is used to define functions based on their return value and parameters
        The reason for this is so the TestCase class can just use an instance of this which is defined once somewhere rather than calling the function seperately a bunch of times
    */

    public:

        // Hold the function pointer
        returnType (*func)(args...);

        // Constructor
        FunctionWrapper(returnType (*func)(args...)) {
            this->func = func;
        }

        // Calls the function with a set of arguments
        returnType call(args... arguments) {
            return func(arguments...);
        }

        // This calls the function with some args and tests it against the expected value
        // tolerance is the percent difference the actual is allowed to be off from the expected by
        void test(returnType expected, args... arguments, double tolerance = 0) {

            // Get actual value
            returnType actual = func(arguments...);
        }

};
