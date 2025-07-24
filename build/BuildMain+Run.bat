:: This only builds main.cpp, anything changed in the dependancy files will not take effect when building this way

:: Paths
set include=-I..\src\include
set srcdir=..\src\src\
set objdir=..\src\obj\


:: Build icon
set dir=..\src\assets\icon\
set out=%objdir%icon-
windres %dir%resource.rc -O coff -o %out%resource.o

:: Compile main.exe
set dir=%srcdir%app\
g++ -Ofast %include% ^
    %dir%main.cpp ^
    %objdir%*.o ^
    -o Kiwi3D.exe ^
    -mwindows

Kiwi3D.exe

:: pause for debugging purposes
pause
