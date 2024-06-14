#ifndef GuiClass
#define GuiClass

#include <SDL2/SDL.h>

#include "../log/log.cpp"

class Gui {
    public:

        /* --- Instance variables --- */

        // Window size
        int windowWidth;
        int windowHeight;

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

        // Instance functions
        int init();
        void exit();
        void getBuffer();
        void dumpBuffer();
        void flip();

};

#endif