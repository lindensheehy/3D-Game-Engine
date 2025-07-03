:: This only builds main.cpp, anything changed in the dependancy files will not take effect when building this way

:: Paths
set include=-I../src/include
set objdir=../src/obj/

:: Compile main.exe
g++ -Ofast %include% ^
    ../main.cpp ^
    %objdir%*.o ^
    -o GameEngine.exe ^
    -mwindows

GameEngine.exe

:: pause for debugging purposes
pause
