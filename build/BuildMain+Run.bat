:: This only builds the main.exe, anything changed in the header files will not take effect when building this way

set objdir=../src/obj/

:: Compile main.exe
g++ -Ofast ../main.cpp ^
    %objdir%Utility.o ^
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
    -mwindows

main.exe

:: pause for debugging purposes
pause
