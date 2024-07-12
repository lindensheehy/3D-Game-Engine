#include <iostream>

#include "../src/log/log.h"

// Libs for functions to test
#include "../src/math/math.h"


// Test counters
int totalTests;
int passedTests;

// This template allows this class to be used for any function signature
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
        bool test(returnType expected, args... arguments, double percentTolerance = 0) {

            // Get actual value
            returnType actual = func(arguments...);
            double error = (abs((double) actual - (double) expected)) / (double) expected;
            bool passed = error <= percentTolerance;

            totalTests++;

            //LogQueue<const char*>* q = new LogQueue<const char*>("Test: ");

            logWrite("Test: ");
            logWrite(this->funcName);
            logWrite("(");

            bool firstFlag = true;

            // Log packed items
            (..., [&]
            {   
                
                // Print the ", " on every iteration after the first
                if (firstFlag)
                    firstFlag = false;
                else
                    logWrite(", ");

                logWrite(arguments);

            } ());

            logWrite(") == ");
            logWrite(expected);
            logWrite("   ->   ");

            if (passed) {
                logWrite("Passed!", true);
                passedTests++;
                return true;
            }

            else {
                logWrite("Failed!  (Output: ");
                logWrite(actual);
                logWrite(")", true);
                return false;
            }

        }

};

int main() {

    totalTests = 0;
    passedTests = 0;

    logInit("testlog.txt");
    logWrite("Loading Functions...", true);

    FunctionWrapper<int, double>* funcFloor = new FunctionWrapper<int, double>(floor, "math.floor");
    FunctionWrapper<double, double, double, double>* funcRange = new FunctionWrapper<double, double, double, double>(range, "math.range");

    logWrite("Functions Loaded!", true);

    funcFloor->test(4, 3.2);
    funcRange->test(0.4, 5, 3, 8, 0.001);


    logWrite("\n\n");
    logWrite(totalTests);
    logWrite(" tests run", true);
    logWrite(passedTests);
    logWrite(" tests passed", true);

    return 0;
}