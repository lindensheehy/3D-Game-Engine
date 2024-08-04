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
            
            // Hide any written logs from function call, like error messages
            logWrite("<span class=\"hidden\">\n");
            returnType actual = func(arguments...);
            logWrite("</span>\n");

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

                passed = ((error > 0) ? error : -error) <= percentTolerance;

            }

            totalTests++; 

            logWrite(
                "<br>\n"
                "<p>\n"
            );

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
            logNewLine();

            if (passed) {
                logWrite(
                    "<span class=\"test-pass\">\n"
                    "   Passed!\n"
                    "</span>\n"
                );  

                if (percentTolerance != 0) {
                    logWrite("<p class=\"note\">\n");
                    logWrite( "Error: ");
                    logWrite(error);
                    logWrite(" / ");
                    logWrite(percentTolerance);
                    logWrite(" %");
                    logWrite("</p>\n");
                }

                logWrite(
                    "</p>\n"
                );

                passedTests++;
                return true;
            }

            else {
                logWrite(
                    "<span class=\"test-fail\">\n"
                    "   Failed!\n"
                    "</span>\n"
                );
                logWrite("<p class=\"note\">\n");
                logWrite("Output: ");
                logWrite(actual);
                logWrite("</p>\n");
                logWrite(
                    "</p>\n"
                );
                return false;
            }

        }

};

int main() {

    totalTests = 0;
    passedTests = 0;

    /*
        This file uses an html file as output. so all the log statements are in the form of html elements
    */

    logInit("testreport.html");
    logWrite(
        "<!DOCTYPE html> \n"
        "<html lang=\"en\">\n\n"
        "<head>\n"
        "   <link rel=\"stylesheet\" href=\"testreport.css\">\n"
        "</head>\n\n"
        "<body>\n"
    );

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

    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h1>\n"
        "   Testing Output\n"
        "</h1>\n"
    );


    /*  ---------------------------------  */
    /*  ---------   Run Tests   ---------  */
    /*  ---------------------------------  */

    // floor
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   floor function from math.cpp\n"
        "</h2>\n"
    );

    //                   Return    Input
    funcFloor->test(       0,        0        );
    funcFloor->test(       0,      1e-300     );
    funcFloor->test(      -1,     -1e-300     );
    funcFloor->test(      -1,       -1        );
    funcFloor->test(      -2,      -1.01      );
    funcFloor->test(      1e6,      1e6       );
    funcFloor->test(     -1e6,     -1e6       );


    // round
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   round function from math.cpp\n"
        "</h2>\n"
    );

    //                   Return    Input
    funcRound->test(       0,        0        );
    funcRound->test(       0,     0.49999     );
    funcRound->test(       1,       0.5       );
    funcRound->test(      -1,      -1.5       );
    funcRound->test(      -2,    -1.50001     );
    funcRound->test(      1e6,      1e6       );
    funcRound->test(     -1e6,     -1e6       );


    // sqrt
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   sqrt function from math.cpp\n"
        "</h2>\n"
    );

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
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   sin function from math.cpp\n"
        "</h2>\n"
    );

    //                   Return    Input     Percent Error
    funcSin->test(         0,          0,           0.75          );
    funcSin->test(         1,         pi/2,         0.75          );
    funcSin->test(         -1,       -pi/2,         0.75          );
    funcSin->test(         0,          pi,          0.75          );
    funcSin->test(         0,         -pi,          0.75          );
    funcSin->test(      0.84147,       1,           0.75          );
    funcSin->test(         0,        pi * 99,       0.75          );

    // cos
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   cos function from math.cpp\n"
        "</h2>\n"
    );

    //                   Return    Input     Percent Error
    funcCos->test(         1,          0,           0.25          );
    funcCos->test(         0,         pi/2,         0.25          );
    funcCos->test(         0,        -pi/2,         0.25          );
    funcCos->test(        -1,          pi,          0.25          );
    funcCos->test(        -1,         -pi,          0.25          );
    funcCos->test(      0.5403,        1,           0.25          );
    funcCos->test(        -1,        pi * 99,       0.25          );

    // tan
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   tan function from math.cpp\n"
        "</h2>\n"
    );

    //                   Return    Input     Percent Error
    funcTan->test(         0,          0,           0.75          );
    funcTan->test(         1,         pi/4,         0.75          ); 
    funcTan->test(        inf,        pi/2,          0            );
    funcTan->test(        -1,        -pi/4,         0.75          ); 
    funcTan->test(       -inf,       -pi/2,          0            );
    funcTan->test(      1.5574,        1,           0.75          );
    funcTan->test(         0,        pi * 99,       0.75          );

    // arctan
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   arctan function from math.cpp\n"
        "</h2>\n"
    );

    //                     Return     Input      Percent Error
    funcArctan->test(         0,          0,           0.5          );
    funcArctan->test(       pi/4,         1,           0.5          );
    funcArctan->test(      -pi/4,        -1,           0.5          );
    funcArctan->test(         1,        1.557,         0.5          );
    funcArctan->test(        -1,       -1.557,         0.5          );
    funcArctan->test(       pi/2,        1e6,          0.5          );
    funcArctan->test(      -pi/2,       -1e6,          0.5          );

    // arcsin
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   arcsin function from math.cpp\n"
        "</h2>\n"
    );

    //                     Return     Input      Percent Error
    funcArcsin->test(         0,          0,           0.25          );
    funcArcsin->test(       pi/2,         1,           0.25          );
    funcArcsin->test(      -pi/2,        -1,           0.25          );
    funcArcsin->test(       pi/6,        0.5,          0.25          );
    funcArcsin->test(      -pi/6,       -0.5,          0.25          );
    funcArcsin->test(         0,        1.001,         0.25          );
    funcArcsin->test(         0,       -1.001,         0.25          );

    // arccos
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   arccos function from math.cpp\n"
        "</h2>\n"
    );

    //                     Return     Input      Percent Error
    funcArccos->test(         1,        0,           0.25          );
    funcArccos->test(         0,       pi/2,         0.25          );
    funcArccos->test(         0,      -pi/2,         0.25          );
    funcArccos->test(        -1,        pi,          0.25          );
    funcArccos->test(        -1,       -pi,          0.25          );
    funcArccos->test(      0.5403,      1,           0.25          );
    funcArccos->test(        -1,      pi * 99,       0.25          );

    // range
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   range function from math.cpp\n"
        "</h2>\n"
    );
    
    funcRange->test(0.4, 5, 3, 8, 0.001);

    //inRange
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   inRange function from math.cpp\n"
        "</h2>\n"
    );

    //getAngle
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   getAngle function from math.cpp\n"
        "</h2>\n"
    );



    // Log Results
    logWrite("\n\n");
    logWrite(totalTests);
    logWrite(" tests run", true);
    logWrite(passedTests);
    logWrite(" tests passed", true);

    logWrite(
        "</body>\n"
    );

    return 0;
}