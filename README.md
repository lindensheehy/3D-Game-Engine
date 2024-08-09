# 3D Graphics Written in C++
This is a 3d graphics engine I wrote in C++. A lot of the code is from the same project I made in python, but I was running into performance issues so wanted to give it a shot in C++. Though, since C++ has less provided utility than python, I still had to rewrite a lot of the code chunks.<br>
This project uses SDL2 to create a window and give me a reference to the pixel buffer, which allowed me to write directly to that, then call another SDL function to write those pixels to the window. <br>

Although SDL2 has plenty of features I could use, I wanted to do everything I fealisbly could by myself. The only SDL2 features I used are:
- Creating a window
- Getting and setting the pixel buffer
- Recording input events on each frame, such as mouse movement and key presses

I wanted to challenge myself, mostly to learn more about C++ so, alongside my limited use of SDL2, I restricted the libraries I'm using to, in my opinion, the bare minimum. Those being:
- 'SDL2' of course
- 'chrono' to get delta time on each frame

I also used the following libraries for debugging, but the core of the project can run just fine without these:
- 'iostream'
- 'fstream'
- 'iomanip'

Because I restricted my library use so much, I had to write an extensive set of dependancies before I could even start anything graphics related. Those being:
- 'math' which contains every math function I would need from a library like cmath.
- 'log' used to write data to an output file rather than the console. This if helpful for a case when you need to record events between frames, and are logging many lines every frame because you can scroll through and ctrl+f.
- 'Vec2' and 'Vec3' are extensive vector libraries. These are used to almost every functional value in this project.
- 'FrameState' which takes the events grabbed by SDL and saves them into an object such that they can more easily be worked with.
- 'Drawer' does all the drawing to the pixel buffer, including rectangles, triangles, and elipses.

To run this project, simply run "BuildAll+Run.bat". This script file compiles all the dependancies to .o files, and then builds and runs main.

I added the SDL2 includes to this directory. They are the 64 bit versions, so if you are on a 32 bit system, read the README in the SDL2 folder for instructions to build/run