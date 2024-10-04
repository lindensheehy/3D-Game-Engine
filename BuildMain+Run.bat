:: This only builds the main.exe, anything changed in the header files will not take effect when building this way

set objdir=src/obj/
set SDLinclude=-I SDL2/include -L SDL2/lib -l SDL2 -l SDL2main

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
    %objdir%Window.o ^
    %objdir%UI.o ^
    %objdir%lodepng.o ^
    -o main.exe ^
    %SDLinclude%

main.exe

:: pause for debugging purposes
pause

:: vscode-fold-0