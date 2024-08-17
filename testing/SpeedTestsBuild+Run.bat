:: Directories
set objdir=../src/obj/
set SDLinclude=-I ../SDL2/include -L ../SDL2/lib -l SDL2 -l SDL2main

:: Build test.exe
g++ speed-tests.cpp ^
    %objdir%Math.o ^
    %objdir%Log.o ^
    %objdir%Vec.o ^
    %objdir%Tri.o ^
    %objdir%Camera.o ^
    %objdir%Mesh.o ^
    %objdir%Gui.o ^
    %objdir%Drawer.o ^
    %objdir%State.o ^
    %objdir%ObjectSet.o ^
    %objdir%lodepng.o ^
    -o results/speed-tests.exe ^
    %SDLinclude%

:: Run the tests
cd results
speed-tests.exe


:: Uncomment this for debugging
pause