:: Build libraries

:: Paths
set include=-I../src/include
set srcdir=../src/src/
set objdir=../src/obj/


:: Build dependancies

:: util
@REM g++ -Ofast %include%        -c %srcdir%util/Utility.cpp         -o %objdir%Utility.o
@REM g++ -Ofast %include%        -c %srcdir%util/Math.cpp            -o %objdir%Math.o
@REM g++ -Ofast %include%        -c %srcdir%util/Log.cpp             -o %objdir%Log.o

:: geometry
@REM g++ -Ofast %include%        -c %srcdir%geometry/Vec.cpp         -o %objdir%Vec.o
@REM g++ -Ofast %include%        -c %srcdir%geometry/Tri.cpp         -o %objdir%Tri.o
@REM g++ -Ofast %include%        -c %srcdir%geometry/Mesh.cpp        -o %objdir%Mesh.o
@REM g++ -Ofast %include%        -c %srcdir%geometry/Camera.cpp      -o %objdir%Camera.o

:: gui
@REM g++ -Ofast %include%        -c %srcdir%gui/Gui.cpp              -o %objdir%Gui.o
@REM g++ -Ofast %include%        -c %srcdir%gui/Drawer.cpp           -o %objdir%Drawer.o
@REM g++ -Ofast %include%        -c %srcdir%gui/State.cpp            -o %objdir%State.o

:: physics
@REM g++ -Ofast %include%        -c %srcdir%physics/ObjectSet.cpp    -o %objdir%ObjectSet.o
@REM g++ -Ofast %include%        -c %srcdir%physics/Bounding.cpp     -o %objdir%Bounding.o

:: ui
g++ -Ofast %include%        -c %srcdir%ui/UI.cpp                -o %objdir%UI.o


:: Build main
g++ -Ofast %include% ^
    ../main.cpp ^
    %objdir%*.o ^
    -o GameEngine.exe ^
    -mwindows

GameEngine.exe

:: pause for debugging purposes
pause
