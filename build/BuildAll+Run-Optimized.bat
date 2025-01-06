:: Build libraries

:: Paths
set srcdir=../src/src/
set objdir=../src/obj/
set SDLinclude=-I ../SDL2/include -L ../SDL2/lib -l SDL2 -l SDL2main



:: Not mine

:: lodepng
g++ -Ofast -c ../src/lodepng/lodepng.cpp ^
    -o %objdir%lodepng.o



:: Mine

:: Utility
g++ -Ofast -c %srcdir%Utility.cpp ^
    -o %objdir%Utility.o

:: Math
g++ -Ofast -c %srcdir%Math.cpp ^
    -o %objdir%Math.o

:: Log
g++ -Ofast -c %srcdir%Log.cpp ^
    -o %objdir%Log.o

:: Vec
g++ -Ofast -c %srcdir%Vec.cpp ^
    -o %objdir%Vec.o

:: Tri
g++ -Ofast -c %srcdir%Tri.cpp ^
    -o %objdir%Tri.o

:: Mesh
g++ -Ofast -c %srcdir%Mesh.cpp ^
    -o %objdir%Mesh.o


:: The rest of the libraries require SDL2 includes

:: Camera
g++ -Ofast -c %srcdir%Camera.cpp ^
    -o %objdir%Camera.o ^
    %SDLinclude%

:: Gui
g++ -Ofast -c %srcdir%Gui.cpp ^
    -o %objdir%Gui.o ^
    %SDLinclude%

:: Drawer
g++ -Ofast -c %srcdir%Drawer.cpp ^
    -o %objdir%Drawer.o ^
    %SDLinclude%

:: State
g++ -Ofast -c %srcdir%State.cpp ^
    -o %objdir%State.o ^
    %SDLinclude%

:: ObjectSet
g++ -Ofast -c %srcdir%ObjectSet.cpp ^
    -o %objdir%ObjectSet.o ^
    %SDLinclude%


:: UI
g++ -Ofast -c %srcdir%UI.cpp ^
    -o %objdir%UI.o ^
    %SDLinclude%


:: Build main.exe

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
    -mwindows ^
    %SDLinclude%

main.exe

:: pause for debugging purposes
pause
