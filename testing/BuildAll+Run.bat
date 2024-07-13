set srcdir=../src/class-source/
set objdir=../src/obj/
set SDLinclude=-I ../SDL2/include -L ../SDL2/lib -l SDL2 -l SDL2main

:: math
g++ -c ../src/math/math.cpp ^
    -o %objdir%math.o

:: build test exe
g++ test.cpp ^
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
    -o test.exe ^
    %SDLinclude%

test.exe

pause