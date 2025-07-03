:: This file has commands to build everything in the project
:: The intent is to comment out pieces that dont need to be compiled for a certain part of the development cycle
:: Its a relatively lightweight way to speed up compile times

:: Paths
set include=-I..\src\include
set srcdir=..\src\src\
set objdir=..\src\obj\


:: Create obj dir if it doesnt exist
if not exist "%objdir%" (
    mkdir "%objdir%"
)


:: Build dependancies

:: geometry
set dir=%srcdir%geometry\
set out=%objdir%geometry-
@REM g++ -Ofast %include%        -c %dir%Matrix.cpp      -o %out%Matrix.o
@REM g++ -Ofast %include%        -c %dir%Mesh.cpp        -o %out%Mesh.o
@REM g++ -Ofast %include%        -c %dir%Tri.cpp         -o %out%Tri.o
@REM g++ -Ofast %include%        -c %dir%Vec.cpp         -o %out%Vec.o


:: graphics

    :: drawing
    set dir=%srcdir%graphics\drawing\
    set out=%objdir%graphics-drawing-
    @REM g++ -Ofast %include%        -c %dir%Drawer.cpp           -o %out%Drawer.o
    @REM g++ -Ofast %include%        -c %dir%PixelDrawer.cpp      -o %out%PixelDrawer.o
    @REM g++ -Ofast %include%        -c %dir%PixelTracker.cpp     -o %out%PixelTracker.o

    :: font
    set dir=%srcdir%graphics\font\
    set out=%objdir%graphics-font-
    @REM g++ -Ofast %include%        -c %dir%FontDrawer.cpp       -o %out%FontDrawer.o

    :: gui
    set dir=%srcdir%graphics\gui\
    set out=%objdir%graphics-gui-
    @REM g++ -Ofast %include%        -c %dir%GUI.cpp              -o %out%GUI.o
    @REM g++ -Ofast %include%        -c %dir%State.cpp            -o %out%State.o
    @REM g++ -Ofast %include%        -c %dir%Window.cpp           -o %out%Window.o

    :: png (Future Plan)
    set dir=%srcdir%graphics\png\
    set out=%objdir%graphics-png-

    :: rendering
    set dir=%srcdir%graphics\rendering\
    set out=%objdir%graphics-rendering-
    @REM g++ -Ofast %include%        -c %dir%Camera.cpp           -o %out%Camera.o
    @REM g++ -Ofast %include%        -c %dir%Display.cpp          -o %out%Display.o
    @REM g++ -Ofast %include%        -c %dir%Renderer.cpp         -o %out%Renderer.o


:: physics
set dir=%srcdir%physics\
set out=%objdir%physics-
@REM g++ -Ofast %include%        -c %dir%Bounding.cpp          -o %out%Bounding.o
@REM g++ -Ofast %include%        -c %dir%ObjectSet.cpp         -o %out%ObjectSet.o

:: ui
set dir=%srcdir%ui\
set out=%objdir%ui-
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
@REM g++ -Ofast %include%        -c %dir%FileNavigator.cpp     -o %out%FileNavigator.o
@REM g++ -Ofast %include%        -c %dir%FileReader.cpp        -o %out%FileReader.o
@REM g++ -Ofast %include%        -c %dir%KeyCodes.cpp          -o %out%KeyCodes.o
@REM g++ -Ofast %include%        -c %dir%Log.cpp               -o %out%Log.o
@REM g++ -Ofast %include%        -c %dir%Math.cpp              -o %out%Math.o
@REM g++ -Ofast %include%        -c %dir%Utility.cpp           -o %out%Utility.o

:: xml
set dir=%srcdir%xml\
set out=%objdir%xml-
@REM g++ -Ofast %include%        -c %dir%Core.cpp              -o %out%Core.o
@REM g++ -Ofast %include%        -c %dir%ElementSet.cpp        -o %out%ElementSet.o
@REM g++ -Ofast %include%        -c %dir%ParameterInfo.cpp     -o %out%ParameterInfo.o
@REM g++ -Ofast %include%        -c %dir%TagSequence.cpp       -o %out%TagSequence.o
@REM g++ -Ofast %include%        -c %dir%XML.cpp               -o %out%XML.o
@REM g++ -Ofast %include%        -c %dir%XMLFile.cpp           -o %out%XMLFile.o


:: Build main
set dir=%srcdir%app\
g++ -Ofast %include% ^
    %dir%main.cpp ^
    %objdir%*.o ^
    -o GameEngine.exe ^
    -mwindows

GameEngine.exe

:: pause for debugging purposes
pause
