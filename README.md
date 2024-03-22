# 3d-graphics-engine
Python program which can project points and shapes in 3d space to a 2d window.   
I've been working on this project on and off for roughly 6 months.   
it pretty much barely works but hopefully it soon will act as a game engine :)

im very aware that there are many game engines which accomplish exaclty what my goal is here, 
but i wanted to try it myself for fun but also to learn more about how video games work on the most basic level.
That is also the reason i chose to use very limited tools provided by pygame. 
Pygame is an extensive library but i wanted to do most things on my own, so the only functions i used to create this project are ones which draw 2d shapes to the screen.
I also used the pygame text rendering functionality for the fps counter and some other debug stuff.

During the development of this project i was in need of a library for vectors, so i addition to this 3d engine I also made fairly extensive 2d and 3d vectors libraries (vectors_lib folder)
This library is also in a seperate project on my github

Current version notes:
- wasd to move around on the xz axis, space and ctrl to ascend and descend respectively
- The red lines on the cube are the normals of the triangles which make up the cube. Theres no arrows but they are pointing outwards from the shape
- Made fov smaller so the fisheye effet is reduced
- only 1 cube is shown on screen but the cube can be rotated around the y, x and z axis using the keys j, k and l repesctively
- gravity and jumping physics work camera by pressing g but there is no on ground check so you can jump infinitly
- objects dont yet have physics