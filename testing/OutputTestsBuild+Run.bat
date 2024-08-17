:: Directories
set objdir=../src/obj/
set SDLinclude=-I ../SDL2/include -L ../SDL2/lib -l SDL2 -l SDL2main

:: Build test.exe
g++ output-tests.cpp ^
    %objdir%Math.o ^
    %objdir%Log.o ^
    %objdir%Vec.o ^
    %objdir%Tri.o ^
    %objdir%Camera.o ^
    %objdir%Mesh.o ^
    %objdir%Gui.o ^
    %objdir%Drawer.o ^
    %objdir%FrameState.o ^
    %objdir%ObjectSet.o ^
    %objdir%lodepng.o ^
    -o results/output-tests.exe ^
    %SDLinclude%

:: Run the tests
cd results
output-tests.exe

:: Open the html file
start "" testreport.html

:: Uncomment this for debugging
pause