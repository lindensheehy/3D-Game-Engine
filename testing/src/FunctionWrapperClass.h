/*
    This class is seperate from TestCase for cleanliness, but it could just be in the same file its not used anywhere else
*/

// This template allows this class to be used for any function signature
template<typename returnType, typename... args>
class FunctionWrapper {
    /*
        This class is used to define functions based on their return value and parameters
        The reason for this is so the TestCase class can just use an instance of this rather than having tons functions
        Functions are defined here becuase I was having issues defining them in the .cpp file
    */

    public:

        // Hold the function pointer
        returnType (*func)(args...)

        // Constructor
        FunctionWrapper(returnType (*func)(args...)) {
            this->func = func;
        }

        // Calls the function with a set of arguments
        returnType call(args... arguments) {
            return func(arguments...);
        }

};
