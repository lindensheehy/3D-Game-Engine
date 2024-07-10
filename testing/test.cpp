#include <iostream>

#include "../src/log/log.h"

// Libs for functions to test
#include "../src/math/math.h"

template<typename returnType, typename... args>
class FunctionWrapper {
    /*
        This class is used to define functions based on their return value and parameters
        The reason for this is so there is a general testing function hich is defined once somewhere rather than having it seperately a bunch of times
    */

    public:

        // Hold the function pointer
        returnType (*func)(args...);
        const char* funcName;

        // Constructor
        FunctionWrapper(returnType (*func)(args...), const char* funcName) {
            this->func = func;
            this->funcName = funcName;
        }

        // Calls the function with a set of arguments
        returnType call(args... arguments) {
            return func(arguments...);
        }

        // This calls the function with some args and tests it against the expected value
        // percentTolerance is the percent difference the actual is allowed to be off from the expected by
        void test(returnType expected, args... arguments, double percentTolerance = 0) {

            // Get actual value
            returnType actual = func(arguments...);

            logWrite(arguments...);


        }

};

int main() {

    logInit("testlog.txt");
    logWrite("Starting Tests...", true);

    FunctionWrapper<int, double>* funcFloor = new FunctionWrapper<int, double>(floor, "math.floor");
    FunctionWrapper<double, double, double, double>* funcRange = new FunctionWrapper<double, double, double, double>(range, "math.range");

    funcFloor->test(3, 3.2);
    funcRange->test(0.4, 5, 3, 8, 0.001);

    return 0;
}