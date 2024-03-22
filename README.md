# 3dgraphicsCpp
3d graphics engine I wrote in C++. A lot of the code is from the same project I made in python, but I was running into performance issues so wanted to give it a shot in C++.
This project uses SDL2 to create a window and access the pixel buffer. Although SDL2 has plenty of features I could use, I chose to do it all myself and restricted myself to only using the pixel buffer.
All the drawing to the screen is done manually by modifying the hex values in an array.
I wanted to challenge myself, mostly to learn more about C++, so I restricted the libraries I'm using to in my opinion the bare minimum. 
The libraries are used are just 'chrono' and 'SDL2.h' for the actual logic, and I also used 'iostream', 'fstream' and 'iomanip' purely for debugging purposes.
