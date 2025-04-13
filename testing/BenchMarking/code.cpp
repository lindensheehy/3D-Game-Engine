#include "include.h"

#include "util/Utility.h"
#include "../src/util/Utility.cpp"
#include "util/Log.h"
#include "../src/util/Log.cpp"
#include "util/Math.h"
#include "../src/util/Math.cpp"

// I use a TimeState object to do the time stuff, rather than reimplementing it all
#include "graphics/gui/State.h"
#include "../src/graphics/gui/State.cpp"


Graphics::Gui::State::TimeState* time;

int main(int argc, char* argv[]) {

    // Set up
    logInit("output.txt");
    logClear();
    logWrite("Starting...\n\n");

    time = new Graphics::Gui::State::TimeState();

    double startTime = time->getTimeMillis();
    double iterationTime;
    double nextLog = (floor(startTime / 1000) + 1) * 1000;

    // From "include.h"
    init();

    for (long long i = 0; i < iterations; i++) {

        // From "include.h"
        run();

        // Print data on first iteration
        if (i == 0) {

            logWrite("Found lambda values (");
            logWrite(lA);
            logWrite(", ");
            logWrite(lB);
            logWrite(", ");
            logWrite(lC);
            logWrite(")", true);

        }

        iterationTime = time->getTimeMillis();
        if (iterationTime >= nextLog) {
            logWrite("On iteration ");
            logWrite(i);
            logWrite(" ( ");
            logWrite( (i / (double) iterations) * 100 );
            logWrite("% )", true);
            nextLog = iterationTime + 1000;
        }

    }

    // From "include.h"
    cleanup();

    double endTime = time->getTimeMillis();

    double elapsedTime = endTime - startTime;
    logWrite("\n\nCompleted Execution in ");
    logWrite(elapsedTime);
    logWrite(" ms", true);

    return 0;

}
