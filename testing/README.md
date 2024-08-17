The 'output-tests.cpp' file in this folder serves to test the accuracy of various functions in parts of this program.
I have been running into some unexpected crashes, so this is my attempt to clear up those issues.

# Functions tested for output are
- Math -> floor
- Math -> round
- Math -> sqrt
- Math -> sin
- Math -> cos
- Math -> tan
- Math -> arctan
- Math -> arcsin
- Math -> arccos

The 'speed-tests.cpp' file serves to test the speed of functions so I can change things and then go here to see the change in time.
Since none of the tasks I do in this program are particularly long, these tests are done by calling some function many times (around thousands of calls) with many differnt inputs, so that the time taken better represents the average length of any given call.

# Functions tested for speed are
- Drawer -> 