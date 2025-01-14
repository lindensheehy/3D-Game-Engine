:: Build libraries

:: Paths
set srcdir=../src/src/
set objdir=../src/obj/



:: Not mine

@REM :: lodepng
@REM g++ -Ofast -c ../src/lodepng/lodepng.cpp ^
@REM     -o %objdir%lodepng.o



:: Mine

@REM :: Utility
@REM g++ -Ofast -c %srcdir%Utility.cpp ^
@REM     -o %objdir%Utility.o

@REM :: Math
@REM g++ -Ofast -c %srcdir%Math.cpp ^
@REM     -o %objdir%Math.o

:: Log
g++ -Ofast -c %srcdir%Log.cpp ^
    -o %objdir%Log.o

@REM :: Vec
@REM g++ -Ofast -c %srcdir%Vec.cpp ^
@REM     -o %objdir%Vec.o

@REM :: Tri
@REM g++ -Ofast -c %srcdir%Tri.cpp ^
@REM     -o %objdir%Tri.o

@REM :: Mesh
@REM g++ -Ofast -c %srcdir%Mesh.cpp ^
@REM     -o %objdir%Mesh.o

@REM :: Camera
@REM g++ -Ofast -c %srcdir%Camera.cpp ^
@REM     -o %objdir%Camera.o

:: Gui
g++ -Ofast -c %srcdir%Gui.cpp ^
    -o %objdir%Gui.o

@REM :: Drawer
@REM g++ -Ofast -c %srcdir%Drawer.cpp ^
@REM     -o %objdir%Drawer.o

@REM :: State
@REM g++ -Ofast -c %srcdir%State.cpp ^
@REM     -o %objdir%State.o

@REM :: ObjectSet
@REM g++ -Ofast -c %srcdir%ObjectSet.cpp ^
@REM     -o %objdir%ObjectSet.o

@REM :: UI
@REM g++ -Ofast -c %srcdir%UI.cpp ^
@REM     -o %objdir%UI.o


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
    -mwindows

main.exe

:: pause for debugging purposes
pause
