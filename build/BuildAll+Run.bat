:: Build libraries

:: Paths
set include=-I..\src\include
set srcdir=..\src\src\
set objdir=..\src\obj\


:: Create obj dir if it doesnt exist
if not exist "%objdir%" (
    mkdir "%objdir%"
)

:: Delete old .o files
del "%objdir%*.o"


:: Build dependancies

:: geometry
set dir=%srcdir%geometry\
set out=%objdir%geometry-
g++ -Ofast %include%        -c %dir%Matrix.cpp      -o %out%Matrix.o
g++ -Ofast %include%        -c %dir%Mesh.cpp        -o %out%Mesh.o
g++ -Ofast %include%        -c %dir%Tri.cpp         -o %out%Tri.o
g++ -Ofast %include%        -c %dir%Vec.cpp         -o %out%Vec.o


:: graphics

    :: drawing
    set dir=%srcdir%graphics\drawing\
    set out=%objdir%graphics-drawing-
    g++ -Ofast %include%        -c %dir%Drawer.cpp           -o %out%Drawer.o
    g++ -Ofast %include%        -c %dir%PixelDrawer.cpp      -o %out%PixelDrawer.o
    g++ -Ofast %include%        -c %dir%PixelTracker.cpp     -o %out%PixelTracker.o

    :: font
    set dir=%srcdir%graphics\font\
    set out=%objdir%graphics-font-
    g++ -Ofast %include%        -c %dir%FontDrawer.cpp       -o %out%FontDrawer.o

    :: gui
    set dir=%srcdir%graphics\gui\
    set out=%objdir%graphics-gui-
    g++ -Ofast %include%        -c %dir%GUI.cpp              -o %out%GUI.o
    g++ -Ofast %include%        -c %dir%State.cpp            -o %out%State.o
    g++ -Ofast %include%        -c %dir%Window.cpp           -o %out%Window.o

    :: png (Future Plan)
    @REM set dir=%srcdir%graphics\png\
    @REM set out=%objdir%graphics-png-

    :: rendering
    set dir=%srcdir%graphics\rendering\
    set out=%objdir%graphics-rendering-
    g++ -Ofast %include%        -c %dir%Camera.cpp           -o %out%Camera.o
    g++ -Ofast %include%        -c %dir%Display.cpp          -o %out%Display.o
    g++ -Ofast %include%        -c %dir%Renderer.cpp         -o %out%Renderer.o


:: physics
set dir=%srcdir%physics\
set out=%objdir%physics-
g++ -Ofast %include%        -c %dir%ObjectSet.cpp         -o %out%ObjectSet.o
g++ -Ofast %include%        -c %dir%Bounding.cpp          -o %out%Bounding.o

:: ui
set dir=%srcdir%ui\
set out=%objdir%ui-
g++ -Ofast %include%        -c %dir%Action.cpp            -o %out%Action.o
g++ -Ofast %include%        -c %dir%BindFuncs.cpp         -o %out%BindFuncs.o
g++ -Ofast %include%        -c %dir%BindManager.cpp       -o %out%BindManager.o
g++ -Ofast %include%        -c %dir%Core.cpp              -o %out%Core.o
g++ -Ofast %include%        -c %dir%UI.cpp                -o %out%UI.o
g++ -Ofast %include%        -c %dir%Window.cpp            -o %out%Window.o
g++ -Ofast %include%        -c %dir%WindowElement.cpp     -o %out%WindowElement.o

:: util
set dir=%srcdir%util\
set out=%objdir%util-
g++ -Ofast %include%        -c %dir%FileNavigator.cpp     -o %out%FileNavigator.o
g++ -Ofast %include%        -c %dir%Utility.cpp           -o %out%Utility.o
g++ -Ofast %include%        -c %dir%Math.cpp              -o %out%Math.o
g++ -Ofast %include%        -c %dir%Log.cpp               -o %out%Log.o
g++ -Ofast %include%        -c %dir%FileReader.cpp        -o %out%FileReader.o
g++ -Ofast %include%        -c %dir%KeyCodes.cpp          -o %out%KeyCodes.o

:: xml
set dir=%srcdir%xml\
set out=%objdir%xml-
g++ -Ofast %include%        -c %dir%Core.cpp              -o %out%Core.o
g++ -Ofast %include%        -c %dir%ElementSet.cpp        -o %out%ElementSet.o
g++ -Ofast %include%        -c %dir%ParameterInfo.cpp     -o %out%ParameterInfo.o
g++ -Ofast %include%        -c %dir%TagSequence.cpp       -o %out%TagSequence.o
g++ -Ofast %include%        -c %dir%XML.cpp               -o %out%XML.o
g++ -Ofast %include%        -c %dir%XMLFile.cpp           -o %out%XMLFile.o


:: Build main
g++ -Ofast %include% ^
    ..\main.cpp ^
    %objdir%*.o ^
    -o GameEngine.exe ^
    -mwindows

GameEngine.exe

:: pause for debugging purposes
pause
