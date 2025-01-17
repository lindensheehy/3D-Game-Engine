:: Build libraries

:: Paths
set include=-I../src/include
set srcdir=../src/src/
set objdir=../src/obj/



:: Not mine

:: lodepng
g++ -Ofast %include% -c %srcdir%lodepng/lodepng.cpp ^
    -o %objdir%lodepng.o



:: Mine

:: Utility
g++ -Ofast %include% -c %srcdir%util/Utility.cpp ^
    -o %objdir%Utility.o

:: Math
g++ -Ofast %include% -c %srcdir%util/Math.cpp ^
    -o %objdir%Math.o

:: Log
g++ -Ofast %include% -c %srcdir%util/Log.cpp ^
    -o %objdir%Log.o

:: Vec
g++ -Ofast %include% -c %srcdir%geometry/Vec.cpp ^
    -o %objdir%Vec.o

:: Tri
g++ -Ofast %include% -c %srcdir%geometry/Tri.cpp ^
    -o %objdir%Tri.o

:: Mesh
g++ -Ofast %include% -c %srcdir%geometry/Mesh.cpp ^
    -o %objdir%Mesh.o

:: Camera
g++ -Ofast %include% -c %srcdir%geometry/Camera.cpp ^
    -o %objdir%Camera.o

:: Gui
g++ -Ofast %include% -c %srcdir%gui/Gui.cpp ^
    -o %objdir%Gui.o

:: Drawer
g++ -Ofast %include% -c %srcdir%gui/Drawer.cpp ^
    -o %objdir%Drawer.o

:: State
g++ -Ofast %include% -c %srcdir%gui/State.cpp ^
    -o %objdir%State.o

:: ObjectSet
g++ -Ofast %include% -c %srcdir%physics/ObjectSet.cpp ^
    -o %objdir%ObjectSet.o

:: Bounding
g++ -Ofast %include% -c %srcdir%physics/Bounding.cpp ^
    -o %objdir%Bounding.o

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
