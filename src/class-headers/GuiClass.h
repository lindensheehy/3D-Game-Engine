#pragma once

#include <SDL2/SDL.h>

#include "../log/log.cpp"

class Gui {

    /*
        This class serves to simplify the process of creating an SDL2 window.
        The whole process of creating many objects and checking if they were initialized properly is now done automatically when init is run.
        All this class requires if a window size (width, height) and it does the rest when instance->init() is called.
        This also serves as a base for the DrawerClass, as it handles the pixel buffer getting and setting
    */

    public:

        /* --- Instance variables --- */

        // Window size
        int windowWidth, windowHeight;

        // SDL stuff for drawing to the window
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        // Pixel buffer
        Uint32* buffer;


        // Constructor
        Gui(int windowWidth, int windowHeight);

        // Destructor
        ~Gui();


        /*   Instance functions   */

        // Create all SDL2 objects, and ensure creating went properly.
        int init();

        // Closes the SDL2 window.
        void exit();

        // Gets the pixel buffer, and locks the screen until flip is called.
        void getBuffer();
        
        // Sets the window to the pixel buffer.
        void flip();

};
