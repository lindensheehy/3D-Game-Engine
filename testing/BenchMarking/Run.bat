set include=-I../../src/include
set objdir=../../src/obj/

:: Build BenchMarking.exe
g++ -Ofast %include% ^
    code.cpp ^
    -o results/BenchMarking.exe

:: Run the bench marking
cd results
BenchMarking.exe


:: Just here for debugging when errors are thrown
pause