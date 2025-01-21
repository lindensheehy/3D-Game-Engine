:: This only builds the main.exe, anything changed in the header files will not take effect when building this way

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
