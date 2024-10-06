:: Build libraries which are frequently changed at this point in development

:: Paths
set srcdir=../src/src/
set objdir=../src/obj/
set SDLinclude=-I ../SDL2/include -L ../SDL2/lib -l SDL2 -l SDL2main



:: Drawer
g++ -c %srcdir%Drawer.cpp ^
    -o %objdir%Drawer.o ^
    %SDLinclude%

:: UI
g++ -c %srcdir%UI.cpp ^
    -o %objdir%UI.o ^
    %SDLinclude%


:: Build main.exe

:: Compile main.exe
g++ ../main.cpp ^
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
    %objdir%UI.o ^
    %objdir%lodepng.o ^
    -o main.exe ^
    -mwindows ^
    %SDLinclude%

main.exe

:: pause for debugging purposes
pause
