:: Directories
set include=-I../src/include
set srcdir=../src/src/
set objdir=../src/obj/

:: Build test.exe
g++ -Ofast %include% ^
    speed-tests.cpp ^
    %objdir%*.o ^
    -o results/speed-tests.exe ^
    -mwindows

:: Run the tests
cd results
speed-tests.exe


:: Uncomment this for debugging
pause