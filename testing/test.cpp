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

            double error;
            bool passed;

            if (percentTolerance == 0) {
                passed = actual == expected;
            }

            else {

                if (expected != 0) 
                    error = 100 * (((double) actual - (double) expected) / (double) expected);
                else
                    error = 100 * ((double) actual - (double) expected);

                passed = (error > 0) ? error <= percentTolerance : -error <= percentTolerance;

            }

            totalTests++; 

            logWrite("Test: ");
            logWrite(this->funcName);
            logWrite("(");

            bool firstFlag = true;

            // Lambda function to log packed items
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
                logWrite("Passed!");

                if (percentTolerance != 0) {
                    logWrite( "  ( Error: ");
                    logWrite(error);
                    logWrite("% / ");
                    logWrite(percentTolerance);
                    logWrite("% )");
                }

                logNewLine();

                passedTests++;
                return true;
            }

            else {
                logWrite("Failed!  ( Output: ");
                logWrite(actual);
                logWrite(" )", true);
                return false;
            }

        }

};

int main() {

    totalTests = 0;
    passedTests = 0;

    logInit("testlog.txt");
    logWrite("Loading Functions...", true);

    /*  --------------------------------------  */
    /*  -----   Load Functions To Test   -----  */
    /*  --------------------------------------  */

    // Functions from "src/math/math.h"
    FunctionWrapper<int, double>* funcFloor = /* ----------------------- */ new FunctionWrapper<int, double>(floor, "floor");
    FunctionWrapper<int, double>* funcRound = /* ----------------------- */ new FunctionWrapper<int, double>(round, "round");
    FunctionWrapper<double, double, double>* funcSqrt = /* ------------- */ new FunctionWrapper<double, double, double>(sqrt, "sqrt");
    FunctionWrapper<double, double>* funcSin = /* ---------------------- */ new FunctionWrapper<double, double>(sin, "sin");
    FunctionWrapper<double, double>* funcCos = /* ---------------------- */ new FunctionWrapper<double, double>(cos, "cos");
    FunctionWrapper<double, double>* funcTan = /* ---------------------- */ new FunctionWrapper<double, double>(tan, "tan");
    FunctionWrapper<double, double>* funcArctan = /* ------------------- */ new FunctionWrapper<double, double>(arctan, "arctan");
    FunctionWrapper<double, double>* funcArcsin = /* ------------------- */ new FunctionWrapper<double, double>(arcsin, "arcsin");
    FunctionWrapper<double, double>* funcArccos = /* ------------------- */ new FunctionWrapper<double, double>(arccos, "arccos");
    FunctionWrapper<double, double, double, double>* funcRange = /* ---- */ new FunctionWrapper<double, double, double, double>(range, "range");
    FunctionWrapper<double, double, double, double>* funcInRange = /* -- */ new FunctionWrapper<double, double, double, double>(inRange, "inRange");
    FunctionWrapper<double, double, double, double, double>* funcGetAngle = new FunctionWrapper<double, double, double, double, double>(getAngle, "getAngle");

    logWrite("Functions Loaded!", true);


    /*  ---------------------------------  */
    /*  ---------   Run Tests   ---------  */
    /*  ---------------------------------  */

    // floor
    logWrite("\nfloor function from math.cpp\n");
    //                   Return    Input
    funcFloor->test(       0,        0        );
    funcFloor->test(       0,      1e-300     );
    funcFloor->test(      -1,     -1e-300     );
    funcFloor->test(      -1,       -1        );
    funcFloor->test(      -2,      -1.01      );
    funcFloor->test(      1e6,      1e6       );
    funcFloor->test(     -1e6,     -1e6       );


    // round
    logWrite("\nround function from math.cpp\n");
    //                   Return    Input
    funcRound->test(       0,        0        );
    funcRound->test(       0,     0.49999     );
    funcRound->test(       1,       0.5       );
    funcRound->test(      -1,      -1.5       );
    funcRound->test(      -2,    -1.50001     );
    funcRound->test(      1e6,      1e6       );
    funcRound->test(     -1e6,     -1e6       );


    // sqrt
    logWrite("\nsqrt function from math.cpp\n");
    //                   Return    Input    Tolerance
    funcSqrt->test(        0,        0,       0.001       );
    funcSqrt->test(        1,        1,       0.001       );
    funcSqrt->test(       -1,       -1,       0.001       );
    funcSqrt->test(       -1,     -1000,      0.001       );
    funcSqrt->test(       10,       100,      0.001       );
    funcSqrt->test(        2,        4,       0.001       );
    funcSqrt->test(        0,        2,       0.001       );
    funcSqrt->test(        0,       1.1,      0.001       );

    // sin
    logWrite("\nsin function from math.cpp\n");
    //                   Return    Input     Percent Error
    funcSin->test(         0,        0,           0.75          );
    funcSin->test(         1,       pi/2,         0.75          );
    funcSin->test(         -1,     -pi/2,         0.75          );
    funcSin->test(         0,        pi,          0.75          );
    funcSin->test(         0,       -pi,          0.75          );
    funcSin->test(      0.84147,     1,           0.75          );
    funcSin->test(         0,      pi * 99,       0.75          );

    // cos
    logWrite("\ncos function from math.cpp\n");
    funcCos->test(         1,        0,           0.25          );
    funcCos->test(         0,       pi/2,         0.25          );
    funcCos->test(         0,      -pi/2,         0.25          );
    funcCos->test(        -1,        pi,          0.25          );
    funcCos->test(        -1,       -pi,          0.25          );
    funcCos->test(      0.5403,      1,           0.25          );
    funcCos->test(        -1,      pi * 99,       0.25          );

    // tan
    logWrite("\ntan function from math.cpp\n");

    // arctan
    logWrite("\narctan function from math.cpp\n");

    // arcsin
    logWrite("\narcsin function from math.cpp\n");

    // arccos
    logWrite("\narccos function from math.cpp\n");

    // range
    logWrite("\nrange function from math.cpp\n");
    funcRange->test(0.4, 5, 3, 8, 0.001);

    //inRange
    logWrite("\ninRange function from math.cpp\n");

    //getAngle
    logWrite("\ngetAngle function from math.cpp\n");



    // Log Results
    logWrite("\n\n");
    logWrite(totalTests);
    logWrite(" tests run", true);
    logWrite(passedTests);
    logWrite(" tests passed", true);

    return 0;
}