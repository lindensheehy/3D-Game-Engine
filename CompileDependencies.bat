:: Im sure theres a way to do this automatically, but this was just easier.

set srcdir=src/class-source/
set objdir=src/obj/

:: Change the value of SDLdir based on where SDL is installed
set SDLdir=C:/dev/SDL2/64-bit-mingw32/
set SDLinclude=-I %SDLdir%include -L %SDLdir%lib -l SDL2 -l SDL2main



:: Not mine

:: lodepng
g++ -c src/lodepng/lodepng.cpp ^
    -o %objdir%lodepng.o



:: Mine

:: Math
g++ -c src/math/math.cpp ^
    -o %objdir%math.o

:: Log
g++ -c src/log/log.cpp ^
    -o %objdir%log.o

:: Vec2
g++ -c %srcdir%Vec2Class.cpp ^
    -o %objdir%Vec2Class.o

:: Vec3
g++ -c %srcdir%Vec3Class.cpp ^
    -o %objdir%Vec3Class.o

:: Tri2
g++ -c %srcdir%Tri2Class.cpp ^
    -o %objdir%Tri2Class.o

:: Tri3
g++ -c %srcdir%Tri3Class.cpp ^
    -o %objdir%Tri3Class.o


:: The rest of the libraries require SDL2 includes

:: Camera
g++ -c %srcdir%CameraClass.cpp ^
    -o %objdir%CameraClass.o ^
    %SDLinclude%

:: Mesh
g++ -c %srcdir%MeshClass.cpp ^
    -o %objdir%MeshClass.o ^
    %SDLinclude%

:: Color
g++ -c %srcdir%ColorClass.cpp ^
    -o %objdir%ColorClass.o ^
    %SDLinclude%

:: PNG
g++ -c %srcdir%PNGClass.cpp ^
    -o %objdir%PNGClass.o ^
    %SDLinclude%

:: Display
g++ -c %srcdir%DisplayClass.cpp ^
    -o %objdir%DisplayClass.o ^
    %SDLinclude%

:: Gui
g++ -c %srcdir%GuiClass.cpp ^
    -o %objdir%GuiClass.o ^
    %SDLinclude%

:: Drawer
g++ -c %srcdir%DrawerClass.cpp ^
    -o %objdir%DrawerClass.o ^
    %SDLinclude%

:: FrameState
g++ -c %srcdir%FrameStateClass.cpp ^
    -o %objdir%FrameStateClass.o ^
    %SDLinclude%

pause