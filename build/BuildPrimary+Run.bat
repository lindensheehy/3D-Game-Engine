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

:: geometry
@REM g++ -Ofast %include%        -c %srcdir%geometry/Vec.cpp         -o %objdir%geometry-Vec.o
@REM g++ -Ofast %include%        -c %srcdir%geometry/Tri.cpp         -o %objdir%geometry-Tri.o
@REM g++ -Ofast %include%        -c %srcdir%geometry/Mesh.cpp        -o %objdir%geometry-Mesh.o
@REM g++ -Ofast %include%        -c %srcdir%geometry/Camera.cpp      -o %objdir%geometry-Camera.o

:: gui
@REM g++ -Ofast %include%        -c %srcdir%gui/Core.cpp             -o %objdir%gui-Core.o
@REM g++ -Ofast %include%        -c %srcdir%gui/Display.cpp          -o %objdir%gui-Display.o
@REM g++ -Ofast %include%        -c %srcdir%gui/Drawer.cpp           -o %objdir%gui-Drawer.o
@REM g++ -Ofast %include%        -c %srcdir%gui/GUI.cpp              -o %objdir%gui-GUI.o
@REM g++ -Ofast %include%        -c %srcdir%gui/PixelTracker.cpp     -o %objdir%gui-PixelTracker.o
@REM g++ -Ofast %include%        -c %srcdir%gui/State.cpp            -o %objdir%gui-State.o
@REM g++ -Ofast %include%        -c %srcdir%gui/Window.cpp           -o %objdir%gui-Window.o

:: physics
@REM g++ -Ofast %include%        -c %srcdir%physics/ObjectSet.cpp    -o %objdir%physics-ObjectSet.o
@REM g++ -Ofast %include%        -c %srcdir%physics/Bounding.cpp     -o %objdir%physics-Bounding.o

:: png
:: This one cant be compiled yet as i havent rewritten it since i removed LodePNG (an external lib i used in the past)

:: ui
g++ -Ofast %include%        -c %srcdir%ui/Action.cpp            -o %objdir%ui-Action.o
g++ -Ofast %include%        -c %srcdir%ui/BindFuncs.cpp         -o %objdir%ui-BindFuncs.o
g++ -Ofast %include%        -c %srcdir%ui/BindManager.cpp       -o %objdir%ui-BindManager.o
g++ -Ofast %include%        -c %srcdir%ui/Core.cpp              -o %objdir%ui-Core.o
g++ -Ofast %include%        -c %srcdir%ui/UI.cpp                -o %objdir%ui-UI.o
g++ -Ofast %include%        -c %srcdir%ui/Window.cpp            -o %objdir%ui-Window.o
g++ -Ofast %include%        -c %srcdir%ui/WindowElement.cpp     -o %objdir%ui-WindowElement.o

:: util
@REM g++ -Ofast %include%        -c %srcdir%util/Utility.cpp         -o %objdir%util-Utility.o
@REM g++ -Ofast %include%        -c %srcdir%util/Math.cpp            -o %objdir%util-Math.o
@REM g++ -Ofast %include%        -c %srcdir%util/Log.cpp             -o %objdir%util-Log.o
@REM g++ -Ofast %include%        -c %srcdir%util/FileReader.cpp      -o %objdir%util-FileReader.o

:: xml
@REM g++ -Ofast %include%        -c %srcdir%xml/Core.cpp             -o %objdir%xml-Core.o
@REM g++ -Ofast %include%        -c %srcdir%xml/ElementSet.cpp       -o %objdir%xml-ElementSet.o
@REM g++ -Ofast %include%        -c %srcdir%xml/ParameterInfo.cpp    -o %objdir%xml-ParameterInfo.o
@REM g++ -Ofast %include%        -c %srcdir%xml/TagSequence.cpp      -o %objdir%xml-TagSequence.o
@REM g++ -Ofast %include%        -c %srcdir%xml/XML.cpp              -o %objdir%xml-XML.o
@REM g++ -Ofast %include%        -c %srcdir%xml/XMLFile.cpp          -o %objdir%xml-XMLFile.o


:: Build main
g++ -Ofast %include% ^
    ../main.cpp ^
    %objdir%*.o ^
    -o GameEngine.exe ^
    -mwindows

GameEngine.exe

:: pause for debugging purposes
pause
