:: Build libraries

:: Paths
set include=-I../src/include
set srcdir=../src/src/
set objdir=../src/obj/


:: Create obj dir if it doesnt exist
if not exist "%objdir%" (
    mkdir "%objdir%"
)


:: Build dependancies

:: util
g++ -Ofast %include%        -c %srcdir%util/Utility.cpp         -o %objdir%Utility.o
g++ -Ofast %include%        -c %srcdir%util/Math.cpp            -o %objdir%Math.o
g++ -Ofast %include%        -c %srcdir%util/Log.cpp             -o %objdir%Log.o
g++ -Ofast %include%        -c %srcdir%util/FileReader.cpp      -o %objdir%FileReader.o

:: geometry
g++ -Ofast %include%        -c %srcdir%geometry/Vec.cpp         -o %objdir%Vec.o
g++ -Ofast %include%        -c %srcdir%geometry/Tri.cpp         -o %objdir%Tri.o
g++ -Ofast %include%        -c %srcdir%geometry/Mesh.cpp        -o %objdir%Mesh.o
g++ -Ofast %include%        -c %srcdir%geometry/Camera.cpp      -o %objdir%Camera.o

:: gui
g++ -Ofast %include%        -c %srcdir%gui/Gui.cpp              -o %objdir%Gui.o
g++ -Ofast %include%        -c %srcdir%gui/Drawer.cpp           -o %objdir%Drawer.o
g++ -Ofast %include%        -c %srcdir%gui/State.cpp            -o %objdir%State.o

:: physics
g++ -Ofast %include%        -c %srcdir%physics/ObjectSet.cpp    -o %objdir%ObjectSet.o
g++ -Ofast %include%        -c %srcdir%physics/Bounding.cpp     -o %objdir%Bounding.o

:: ui
g++ -Ofast %include%        -c %srcdir%ui/Action.cpp            -o %objdir%Action.o
g++ -Ofast %include%        -c %srcdir%ui/WindowElement.cpp     -o %objdir%WindowElement.o
g++ -Ofast %include%        -c %srcdir%ui/Window.cpp            -o %objdir%Window.o
g++ -Ofast %include%        -c %srcdir%ui/UI.cpp                -o %objdir%UI.o
g++ -Ofast %include%        -c %srcdir%ui/XML.cpp               -o %objdir%XML.o


:: Build main
g++ -Ofast %include% ^
    ../main.cpp ^
    %objdir%*.o ^
    -o GameEngine.exe ^
    -mwindows

GameEngine.exe

:: pause for debugging purposes
pause
