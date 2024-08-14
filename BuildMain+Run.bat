:: This only builds the main.exe, anything changed in the header files will not take effect when building this way

set objdir=src/obj/
set SDLinclude=-I SDL2/include -L SDL2/lib -l SDL2 -l SDL2main

:: Compile main.exe
g++ main.cpp ^
    %objdir%math.o ^
    %objdir%log.o ^
    %objdir%Vec2Class.o ^
    %objdir%Vec3Class.o ^
    %objdir%Tri2Class.o ^
    %objdir%Tri3Class.o ^
    %objdir%CameraClass.o ^
    %objdir%MeshClass.o ^
    %objdir%ColorClass.o ^
    %objdir%PNGClass.o ^
    %objdir%DisplayClass.o ^
    %objdir%GuiClass.o ^
    %objdir%DrawerClass.o ^
    %objdir%FrameStateClass.o ^
    %objdir%FontClass.o ^
    %objdir%PhysicsObjectClass.o ^
    %objdir%MeshSetClass.o ^
    %objdir%lodepng.o ^
    -o main.exe ^
    %SDLinclude%

main.exe

:: pause for debugging purposes
pause