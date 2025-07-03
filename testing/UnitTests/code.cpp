#include "include.h"

#include "util/Log.h"

// Libs for functions to test
#include "util/Math.h"
#include "util/Utility.h"

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

    // Functions from "src/include/Math.h"
    FunctionWrapper<float, float, float>* funcSqrt = /* ---------------- */ new FunctionWrapper<float, float, float>(sqrt, "sqrt");
    FunctionWrapper<float, float>* funcSin = /* ------------------------ */ new FunctionWrapper<float, float>(sin, "sin");
    FunctionWrapper<float, float>* funcCos = /* ------------------------ */ new FunctionWrapper<float, float>(cos, "cos");
    FunctionWrapper<float, float>* funcTan = /* ------------------------ */ new FunctionWrapper<float, float>(tan, "tan");
    FunctionWrapper<float, float>* funcArctan = /* --------------------- */ new FunctionWrapper<float, float>(arctan, "arctan");
    FunctionWrapper<float, float>* funcArcsin = /* --------------------- */ new FunctionWrapper<float, float>(arcsin, "arcsin");
    FunctionWrapper<float, float>* funcArccos = /* --------------------- */ new FunctionWrapper<float, float>(arccos, "arccos");
    FunctionWrapper<float, float, float, float>* funcNormalize = /* ---- */ new FunctionWrapper<float, float, float, float>(normalize, "range");
    FunctionWrapper<float, float, float, float>* funcInRange = /* ------ */ new FunctionWrapper<float, float, float, float>(inRange, "inRange");
    FunctionWrapper<float, float, float, float, float>* funcGetAngle = /**/ new FunctionWrapper<float, float, float, float, float>(getAngle, "getAngle");

    // Functions from "src/include/Utility.h"
    FunctionWrapper<int, float>* funcFloor = /* ------------------------ */ new FunctionWrapper<int, float>(floor, "floor");
    FunctionWrapper<int, float>* funcRound = /* ------------------------ */ new FunctionWrapper<int, float>(round, "round");

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

    //                   Return    Input    Tolerance     Percent Error
    funcSqrt->test(        0,        0,       0.001,          0.001       );
    funcSqrt->test(        1,        1,       0.001,          0.001       );
    funcSqrt->test(       -1,       -1,       0.001,          0.001       );
    funcSqrt->test(       -1,     -1000,      0.001,          0.001       );
    funcSqrt->test(       10,       100,      0.001,          0.001       );
    funcSqrt->test(        2,        4,       0.001,          0.001       );
    funcSqrt->test(     1.4142,      2,       0.001,          0.001       );
    funcSqrt->test(     1.0488,     1.1,      0.001,          0.001       );

    // sin
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   sin function from math.cpp\n"
        "</h2>\n"
    );

    //                   Return      Input     Percent Error
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

    //                   Return      Input     Percent Error
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

    //                   Return      Input     Percent Error
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

    //                     Return       Input      Percent Error
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

    //                     Return       Input      Percent Error
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

    //                     Return       Input      Percent Error
    funcArccos->test(       pi/2,         0,           0.25          );
    funcArccos->test(         0,          1,           0.25          );
    funcArccos->test(        pi,         -1,           0.25          );
    funcArccos->test(       pi/3,        0.5,          0.25          );
    funcArccos->test(      2*pi/3,      -0.5,          0.25          );
    funcArccos->test(         0,        1.001,         0.25          );
    funcArccos->test(         0,       -1.001,         0.25          );

    // range
    logWrite(
        "<div class=\"seperation\"></div>\n"
        "<h2>\n"
        "   range function from math.cpp\n"
        "</h2>\n"
    );
    
    funcNormalize->test(0.4, 5, 3, 8, 0.001);

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
