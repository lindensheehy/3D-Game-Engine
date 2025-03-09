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
g++ -Ofast %include%        -c %srcdir%util/Utility.cpp         -o %objdir%util-Utility.o
g++ -Ofast %include%        -c %srcdir%util/Math.cpp            -o %objdir%util-Math.o
g++ -Ofast %include%        -c %srcdir%util/Log.cpp             -o %objdir%util-Log.o
g++ -Ofast %include%        -c %srcdir%util/FileReader.cpp      -o %objdir%util-FileReader.o

:: geometry
g++ -Ofast %include%        -c %srcdir%geometry/Vec.cpp         -o %objdir%geometry-Vec.o
g++ -Ofast %include%        -c %srcdir%geometry/Tri.cpp         -o %objdir%geometry-Tri.o
g++ -Ofast %include%        -c %srcdir%geometry/Mesh.cpp        -o %objdir%geometry-Mesh.o
g++ -Ofast %include%        -c %srcdir%geometry/Camera.cpp      -o %objdir%geometry-Camera.o

:: gui
g++ -Ofast %include%        -c %srcdir%gui/Display.cpp          -o %objdir%gui-Display.o
g++ -Ofast %include%        -c %srcdir%gui/Drawer.cpp           -o %objdir%gui-Drawer.o
g++ -Ofast %include%        -c %srcdir%gui/Gui.cpp              -o %objdir%gui-Gui.o
g++ -Ofast %include%        -c %srcdir%gui/State.cpp            -o %objdir%gui-State.o

:: physics
g++ -Ofast %include%        -c %srcdir%physics/ObjectSet.cpp    -o %objdir%physics-ObjectSet.o
g++ -Ofast %include%        -c %srcdir%physics/Bounding.cpp     -o %objdir%physics-Bounding.o

:: ui
g++ -Ofast %include%        -c %srcdir%ui/Action.cpp            -o %objdir%ui-Action.o
g++ -Ofast %include%        -c %srcdir%ui/BindFuncs.cpp         -o %objdir%ui-BindFuncs.o
g++ -Ofast %include%        -c %srcdir%ui/BindManager.cpp       -o %objdir%ui-BindManager.o
g++ -Ofast %include%        -c %srcdir%ui/Core.cpp              -o %objdir%ui-Core.o
g++ -Ofast %include%        -c %srcdir%ui/UI.cpp                -o %objdir%ui-UI.o
g++ -Ofast %include%        -c %srcdir%ui/Window.cpp            -o %objdir%ui-Window.o
g++ -Ofast %include%        -c %srcdir%ui/WindowElement.cpp     -o %objdir%ui-WindowElement.o

:: xml
g++ -Ofast %include%        -c %srcdir%xml/Core.cpp             -o %objdir%xml-Core.o
g++ -Ofast %include%        -c %srcdir%xml/ElementSet.cpp       -o %objdir%xml-ElementSet.o
g++ -Ofast %include%        -c %srcdir%xml/ParameterInfo.cpp    -o %objdir%xml-ParameterInfo.o
g++ -Ofast %include%        -c %srcdir%xml/TagSequence.cpp      -o %objdir%xml-TagSequence.o
g++ -Ofast %include%        -c %srcdir%xml/XML.cpp              -o %objdir%xml-XML.o
g++ -Ofast %include%        -c %srcdir%xml/XMLFile.cpp          -o %objdir%xml-XMLFile.o


:: Build main
g++ -Ofast %include% ^
    ../main.cpp ^
    %objdir%*.o ^
    -o GameEngine.exe ^
    -mwindows

GameEngine.exe

:: pause for debugging purposes
pause
