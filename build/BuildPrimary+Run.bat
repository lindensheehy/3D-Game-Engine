:: Build libraries

:: Paths
set srcdir=../src/src/
set objdir=../src/obj/
set SDLinclude=-I ../SDL2/include -L ../SDL2/lib -l SDL2 -l SDL2main



:: Not mine

:: lodepng
@REM g++ -c ../src/lodepng/lodepng.cpp ^
@REM     -o %objdir%lodepng.o



:: Mine

:: Utility
@REM g++ -c %srcdir%Utility.cpp ^
@REM     -o %objdir%Utility.o

:: Math
@REM g++ -c %srcdir%Math.cpp ^
@REM     -o %objdir%Math.o

:: Log
@REM g++ -c %srcdir%Log.cpp ^
@REM     -o %objdir%Log.o

:: Vec
@REM g++ -c %srcdir%Vec.cpp ^
@REM     -o %objdir%Vec.o

:: Tri
@REM g++ -c %srcdir%Tri.cpp ^
@REM     -o %objdir%Tri.o

:: Mesh
@REM g++ -c %srcdir%Mesh.cpp ^
@REM     -o %objdir%Mesh.o


:: The rest of the libraries require SDL2 includes

:: Camera
@REM g++ -c %srcdir%Camera.cpp ^
@REM     -o %objdir%Camera.o ^
@REM     %SDLinclude%

:: Gui
@REM g++ -c %srcdir%Gui.cpp ^
@REM     -o %objdir%Gui.o ^
@REM     %SDLinclude%

:: Drawer
@REM g++ -c %srcdir%Drawer.cpp ^
@REM     -o %objdir%Drawer.o ^
@REM     %SDLinclude%

:: State
@REM g++ -c %srcdir%State.cpp ^
@REM     -o %objdir%State.o ^
@REM     %SDLinclude%

:: ObjectSet
g++ -c %srcdir%ObjectSet.cpp ^
    -o %objdir%ObjectSet.o ^
    %SDLinclude%


:: UI
g++ -c %srcdir%UI.cpp ^
    -o %objdir%UI.o ^
    %SDLinclude%


:: Build main.exe

:: Compile main.exe
g++ ../main.cpp ^
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
