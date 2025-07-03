set include=-I../../src/include
set objdir=../../src/obj/

:: Build UnitTests.exe
g++ -Ofast %include% ^
    code.cpp ^
    %objdir%*.o ^
    -o results/UnitTests.exe ^
    -mwindows

:: Run the tests
cd results
UnitTests.exe

:: Open the html file
start "" testreport.html

:: Just here for debugging when errors are thrown
pause