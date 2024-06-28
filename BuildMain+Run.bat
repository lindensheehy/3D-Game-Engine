:: This only builds the main.exe, anything changed in the header files will not take effect when building this way

set objdir=src/obj/

:: Change the value of SDLdir based on where SDL is installed
set SDLdir=C:/dev/SDL2/64-bit-mingw32/
set SDLinclude=-I %SDLdir%include -L %SDLdir%lib -l SDL2 -l SDL2main

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
    %objdir%lodepng.o ^
    -o main.exe ^
    %SDLinclude%

main.exe