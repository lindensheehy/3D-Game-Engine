#include "../class-headers/GuiClass.h"

#include <SDL2/SDL.h>

#include "../log/log.h"

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
        Gui(int windowWidth, int windowHeight) {

            this->windowWidth = windowWidth;
            this->windowHeight = windowHeight;

            this->window = nullptr;
            this->renderer = nullptr;
            this->texture = nullptr;

            this->buffer = new Uint32[windowWidth * windowHeight];

        }

        // Destructor
        ~Gui() {

            // SDL2 objects
            if (this->window != nullptr) delete this->window;
            if (this->renderer != nullptr) delete this->renderer;
            if (this->texture != nullptr) delete this->texture;

            // Pixel buffer
            if (this->buffer != nullptr) delete this->buffer;

            return;

        }

        // Instance functions
        int init() {

            // Initialize SDL
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                logWrite("SDL init failed! from GuiClass.h in init()", true);
                return 1;
            }

            // Create a window
            this->window = SDL_CreateWindow(
                "SDL2 Window", 
                SDL_WINDOWPOS_UNDEFINED, 
                SDL_WINDOWPOS_UNDEFINED, 
                this->windowWidth, 
                this->windowHeight, 
                SDL_WINDOW_SHOWN
            );

            if (this->window == nullptr) {
                logWrite("SDL create window failed! from GuiClass.h in init()", true);
                return 1;
            }

            // Create renderer
            this->renderer = SDL_CreateRenderer(
                this->window, 
                -1, 
                SDL_RENDERER_ACCELERATED
            );

            if (this->renderer == nullptr) {
                logWrite("SDL create renderer failed! from GuiClass.h in init()", true);
                return 1;
            }
            
            // Create texture
            this->texture = SDL_CreateTexture(
                this->renderer, 
                SDL_PIXELFORMAT_ARGB8888, 
                SDL_TEXTUREACCESS_STREAMING, 
                this->windowWidth, 
                this->windowHeight
            );

            if (this->texture == nullptr) {
                logWrite("SDL create texture failed! from GuiClass.h in init()", true);
                return 1;
            }

            return 0;
        }
        
        void exit() {
            SDL_DestroyWindow(this->window);
            SDL_Quit();
        }

        void getBuffer() {
            int windowWidthTemp = this->windowWidth;
            SDL_LockTexture(this->texture, nullptr, (void**) &(this->buffer), &windowWidthTemp);
        }

        void flip() {
            int windowWidthTemp = this->windowWidth;
            SDL_UnlockTexture(this->texture);
            SDL_UpdateTexture(this->texture, nullptr, this->buffer, windowWidthTemp * sizeof(Uint32));
            SDL_RenderClear(this->renderer);
            SDL_RenderCopy(this->renderer, this->texture, nullptr, nullptr);
            SDL_RenderPresent(this->renderer);
        }

    private:
};