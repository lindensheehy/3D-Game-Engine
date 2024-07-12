# 3dgraphicsCpp
3d graphics engine I wrote in C++. A lot of the code is from the same project I made in python, but I was running into performance issues so wanted to give it a shot in C++.<br>
This project uses SDL2 to create a window and access the pixel buffer. Although SDL2 has plenty of features I could use, I chose to do it all myself and restricted myself to only using the pixel buffer.<br>
All the drawing to the screen is done manually by modifying the hex values in an array.<br>
I wanted to challenge myself, mostly to learn more about C++, so I restricted the libraries I'm using to in my opinion the bare minimum.<br>
The libraries used are just 'chrono' for delta-time, and 'SDL2.h' for graphics. I also used 'iostream', 'fstream' and 'iomanip' purely for debugging purposes.
I added the SDL2 includes to this directory. They are the 64 bit versions, so if you are on a 32 bit system, read the README in the SDL2 folder for instructions