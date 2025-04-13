
set include=-I../../src/include
set objdir=../../src/obj/

:: Build UnitTests.exe
g++ -Ofast %include% ^
    core.cpp ^
    %objdir%*.o ^
    -o results/UnitTests.exe ^
    -mwindows

:: Run the tests
cd results
UnitTests.exe

:: Open the html file
start "" testreport.html

:: Uncomment this for debugging
pause