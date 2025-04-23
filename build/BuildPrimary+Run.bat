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
@REM set dir=%srcdir%geometry\
@REM set out=%objdir%geometry-
@REM g++ -Ofast %include%        -c %dir%Vec.cpp         -o %out%Vec.o
@REM g++ -Ofast %include%        -c %dir%Tri.cpp         -o %out%Tri.o
@REM g++ -Ofast %include%        -c %dir%Mesh.cpp        -o %out%Mesh.o
@REM g++ -Ofast %include%        -c %dir%Matrix.cpp      -o %out%Matrix.o


:: graphics

    :: drawing
    @REM set dir=%srcdir%graphics\drawing\
    @REM set out=%objdir%graphics-drawing-
    @REM g++ -Ofast %include%        -c %dir%Drawer.cpp           -o %out%Drawer.o
    @REM g++ -Ofast %include%        -c %dir%PixelDrawer.cpp      -o %out%PixelDrawer.o
    @REM g++ -Ofast %include%        -c %dir%PixelTracker.cpp     -o %out%PixelTracker.o

    :: font
    @REM set dir=%srcdir%graphics\font\
    @REM set out=%objdir%graphics-font-
    @REM g++ -Ofast %include%        -c %dir%FontDrawer.cpp       -o %out%FontDrawer.o

    :: gui
    @REM set dir=%srcdir%graphics\gui\
    @REM set out=%objdir%graphics-gui-
    @REM g++ -Ofast %include%        -c %dir%GUI.cpp              -o %out%GUI.o
    @REM g++ -Ofast %include%        -c %dir%State.cpp            -o %out%State.o
    @REM g++ -Ofast %include%        -c %dir%Window.cpp           -o %out%Window.o

    :: png (Future Plan)
    @REM set dir=%srcdir%graphics\png\
    @REM set out=%objdir%graphics-png-

    :: rendering
    @REM set dir=%srcdir%graphics\rendering\
    @REM set out=%objdir%graphics-rendering-
    @REM g++ -Ofast %include%        -c %dir%Camera.cpp           -o %out%Camera.o
    @REM @REM g++ -Ofast %include%        -c %dir%Display.cpp          -o %out%Display.o
    @REM g++ -Ofast %include%        -c %dir%Renderer.cpp         -o %out%Renderer.o


:: physics
@REM set dir=%srcdir%physics\
@REM set out=%objdir%physics-
@REM g++ -Ofast %include%        -c %dir%ObjectSet.cpp         -o %out%ObjectSet.o
@REM g++ -Ofast %include%        -c %dir%Bounding.cpp          -o %out%Bounding.o

:: ui
@REM set dir=%srcdir%ui\
@REM set out=%objdir%ui-
@REM g++ -Ofast %include%        -c %dir%Action.cpp            -o %out%Action.o
@REM g++ -Ofast %include%        -c %dir%BindFuncs.cpp         -o %out%BindFuncs.o
@REM g++ -Ofast %include%        -c %dir%BindManager.cpp       -o %out%BindManager.o
@REM g++ -Ofast %include%        -c %dir%Core.cpp              -o %out%Core.o
@REM g++ -Ofast %include%        -c %dir%UI.cpp                -o %out%UI.o
@REM g++ -Ofast %include%        -c %dir%Window.cpp            -o %out%Window.o
@REM g++ -Ofast %include%        -c %dir%WindowElement.cpp     -o %out%WindowElement.o

:: util
set dir=%srcdir%util\
set out=%objdir%util-
g++ -Ofast %include%        -c %dir%FileNavigator.cpp     -o %out%FileNavigator.o
g++ -Ofast %include%        -c %dir%FileReader.cpp        -o %out%FileReader.o
@REM g++ -Ofast %include%        -c %dir%KeyCodes.cpp          -o %out%KeyCodes.o
@REM g++ -Ofast %include%        -c %dir%Utility.cpp           -o %out%Utility.o
@REM g++ -Ofast %include%        -c %dir%Math.cpp              -o %out%Math.o
@REM g++ -Ofast %include%        -c %dir%Log.cpp               -o %out%Log.o

:: xml
@REM set dir=%srcdir%xml\
@REM set out=%objdir%xml-
@REM g++ -Ofast %include%        -c %dir%Core.cpp              -o %out%Core.o
@REM g++ -Ofast %include%        -c %dir%ElementSet.cpp        -o %out%ElementSet.o
@REM g++ -Ofast %include%        -c %dir%ParameterInfo.cpp     -o %out%ParameterInfo.o
@REM g++ -Ofast %include%        -c %dir%TagSequence.cpp       -o %out%TagSequence.o
@REM g++ -Ofast %include%        -c %dir%XML.cpp               -o %out%XML.o
@REM g++ -Ofast %include%        -c %dir%XMLFile.cpp           -o %out%XMLFile.o


:: Build main
g++ -Ofast %include% ^
    ../main.cpp ^
    %objdir%*.o ^
    -o GameEngine.exe ^
    -mwindows

GameEngine.exe

:: pause for debugging purposes
pause
