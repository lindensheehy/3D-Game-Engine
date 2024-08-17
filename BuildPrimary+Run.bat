:: Build libraries which are frequently changed at this point in development

:: Paths
set srcdir=src/src/
set objdir=src/obj/
set SDLinclude=-I SDL2/include -L SDL2/lib -l SDL2 -l SDL2main



:: Mesh
g++ -c %srcdir%Mesh.cpp ^
    -o %objdir%Mesh.o ^
    %SDLinclude%

:: Drawer
g++ -c %srcdir%Drawer.cpp ^
    -o %objdir%Drawer.o ^
    %SDLinclude%

:: ObjectSet
g++ -c %srcdir%ObjectSet.cpp ^
    -o %objdir%ObjectSet.o ^
    %SDLinclude%


:: Build main.exe

:: Compile main.exe
g++ main.cpp ^
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
    -o main.exe ^
    %SDLinclude%

main.exe

:: pause for debugging purposes
pause
