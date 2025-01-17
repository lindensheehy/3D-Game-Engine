# 3D Graphics Engine in C++

This is a 3D graphics engine written in C++ using `windows.h` <ins>as my **only** include</ins>. This limitation was based on my goal of learning as much as possible about C++. This meant, if I wanted high level abstractions, I would have to write them myself, therefore I would be writing much more code and I would have to know how everything works. For example, instead of using `<math.h>`, I did the necessary research to implement the needed functions myself; and this applies to higher level concepts as well like my `Mesh` class.

Everything in this repository was written 100% by Linden Sheehy (me).

## Key Features:

### Rendering
- **Projection** Uses perspective projection to simulate a 3D scene on a 2d window.
- **Depth Buffering:** Implements a depth buffer to ensure that objects are rendered correctly with respect to their depth in the scene.
- **Transparency Handling:** Support for objects with varying levels of opacity.

### UI
- **Custom UI Elements:** Supports a range of UI components, including buttons, textboxes, dividers, etc., with the ability to dynamically handle inputs and render windows on the screen.
- **UI Hierarchy System:** The UI elements are organized hierarchically, with a parent-child relationship, making it easy to manage complex window layouts.
- **Custom XML Structure (Future Plan):** UI elements will be stored in XML files, which will be parsed by my code, to generate individual elements or whole windows. 


### Physics (Work in Progress)
- **Physics Framework Setup:** As of now, objects can have velocities and acceleration.
- **Collision System (Future Plan):** The groundwork for a collision system has been set up, but the logic to handle collisions is still in the works

### Custom Test Suite
- **Output Tetst:** A modular, reusable system built to easily test outputs of functions for various input parameters.
- **Speed Tests:** Pretty basic system to test the performance of my app.

## Libraries & Dependencies:
- **Windows API:** Used for window creation, handling input, painting a pixel buffer to the window.
- **<ins>NO</ins> Standard C++ Libraries:** 
- **Self Written Libraries:** This project heavily relies on libraries written by me for the vast majority of the functionality. These can be seen in `src/include/` and `src/src/`

## Controls:
- **W, A, S, D:** Move the camera along the x,z axes
- **Space, Ctrl:** Ascend and descend along the y-axis respectively
- **Shift:** Sprint (increases movement speed in all directions)
- **Left Click + Mouse Movement:** Look around (rotate the camera)
- **Q, E:** Select objects and cycle through them (will also create a 'Transform' window)
- **J, K, L:** Rotate the selected object about each axis
- **U, I:** Translate the selected object along the X-axis
- **T, Y:** Translate the selected object along the Z-axis
- **O, P:** Translate the selected object along the Y-axis
- **G:** Toggle gravity on or off (only affects objects, not the camera)
- **Z:** Make all the objects 'jump' (just gives some vertical veloctiy)
- **N:** Show normals on all rendered triangles, appearing as small red lines. This also makes the objects partially transparent

## How to Run:
1. Clone the repository
2. Navigate to the project directory
3. Run `BuildAll+Run.bat` (Windows) to compile and run the project. This will compile each dependancy to a .o file, then compile and run main.

## Conclusion
This is very much a passion project for me. As much as it is a learning opportunity to develop my skills, it's also driven by my interest in 3D graphics and my love for building things from scratch. I could talk for hours about any individual part of this project, because a lot of time and thought went into everything.
