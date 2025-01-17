:: Build libraries

:: Paths
set include=-I../src/include
set srcdir=../src/src/
set objdir=../src/obj/



:: Not mine

:: lodepng
@REM g++ -Ofast %include% -c %srcdir%lodepng/lodepng.cpp ^
@REM     -o %objdir%lodepng.o



:: Mine

:: Utility
@REM g++ -Ofast %include% -c %srcdir%util/Utility.cpp ^
@REM     -o %objdir%Utility.o

:: Math
@REM g++ -Ofast %include% -c %srcdir%util/Math.cpp ^
@REM     -o %objdir%Math.o

:: Log
@REM g++ -Ofast %include% -c %srcdir%util/Log.cpp ^
@REM     -o %objdir%Log.o

:: Vec
@REM g++ -Ofast %include% -c %srcdir%geometry/Vec.cpp ^
@REM     -o %objdir%Vec.o

:: Tri
@REM g++ -Ofast %include% -c %srcdir%geometry/Tri.cpp ^
@REM     -o %objdir%Tri.o

:: Mesh
@REM g++ -Ofast %include% -c %srcdir%geometry/Mesh.cpp ^
@REM     -o %objdir%Mesh.o

:: Camera
@REM g++ -Ofast %include% -c %srcdir%geometry/Camera.cpp ^
@REM     -o %objdir%Camera.o

:: Gui
@REM g++ -Ofast %include% -c %srcdir%gui/Gui.cpp ^
@REM     -o %objdir%Gui.o

:: Drawer
@REM g++ -Ofast %include% -c %srcdir%gui/Drawer.cpp ^
@REM     -o %objdir%Drawer.o

:: State
@REM g++ -Ofast %include% -c %srcdir%gui/State.cpp ^
@REM     -o %objdir%State.o

:: ObjectSet
@REM g++ -Ofast %include% -c %srcdir%physics/ObjectSet.cpp ^
@REM     -o %objdir%ObjectSet.o

:: Bounding
@REM g++ -Ofast %include% -c %srcdir%physics/Bounding.cpp ^
@REM     -o %objdir%Bounding.o

:: UI
g++ -Ofast %include% -c %srcdir%ui/UI.cpp ^
    -o %objdir%UI.o


:: Build main.exe

:: Compile main.exe
g++ -Ofast %include%  ../main.cpp ^
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
    %objdir%Bounding.o ^
    -o main.exe ^
    -mwindows

main.exe

:: pause for debugging purposes
pause
