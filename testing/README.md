The 'output-tests.cpp' file in this folder serves to test the accuracy of various functions in parts of this program.
I have been running into some unexpected crashes, so this is my attempt to clear up those issues.

# Output Tests

Functions Tested
- Math -> floor
- Math -> round
- Math -> sqrt
- Math -> sin
- Math -> cos
- Math -> tan
- Math -> arctan
- Math -> arcsin
- Math -> arccos

These functions are called several times each with different inputs, then the outputs are compared to expected outputs I have calculated manually. The output of these tests write to a html file which will automatically open after running OutputTestsBuild+Run.bat. This file gives the lists of function calls with thier inputs, outputs and if they passed or failed, this also shows the margin of error.

# Speed Tests

The speed tests are done by running 500 frames of the program 25 times. After each set of 500 frames, the time taken is printed to the console, and after all 25 sets run, the average is printed.