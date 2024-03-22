#define SDL_MAIN_HANDLED

#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>

#include "classes/ColorClass.h"
#include "classes/DrawerClass.h"
#include "classes/FrameStateClass.h"
#include "classes/CameraClass.h"
#include "classes/DisplayClass.h"
#include "classes/MeshClass.h"

#include "log.cpp"
#include "graphics.cpp"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 1000;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

Uint32* buffer = NULL;

void getBuffer() {
    int* windowWidthTemp = new int(WINDOW_WIDTH);
    SDL_LockTexture(texture, NULL, (void**) &buffer, windowWidthTemp);
    delete windowWidthTemp;
}

void flip() {
    int* windowWidthTemp = new int(WINDOW_WIDTH);
    SDL_UnlockTexture(texture);
    SDL_UpdateTexture(texture, NULL, buffer, (*windowWidthTemp) * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    buffer = NULL;
    delete windowWidthTemp;
}

void handleInput(FrameState* frameState, Camera* camera, double dt) {

    /*  ---  Directional Movement  ---  */

    // Distance to move
    if (frameState->keyIsDown(SDLK_LSHIFT)) camera->movementSpeed = 10;
    else camera->movementSpeed = 3;
    double dist = ((double) camera->movementSpeed) * (dt / 1000);

    if (frameState->keyIsDown(SDLK_SPACE)) camera->pos->y += dist; // Up
    if (frameState->keyIsDown(SDLK_LCTRL)) camera->pos->y -= dist; // Down
    
    Vec2* cameraMovVec = new Vec2();
    if (frameState->keyIsDown(SDLK_w)) cameraMovVec->y += dist; // Forward
    if (frameState->keyIsDown(SDLK_s)) cameraMovVec->y -= dist; // Backward
    if (frameState->keyIsDown(SDLK_a)) cameraMovVec->x -= dist; // Left
    if (frameState->keyIsDown(SDLK_d)) cameraMovVec->x += dist; // Right

    // Move camera based on its rotation
    cameraMovVec->rotate(camera->yaw);
    camera->pos->x += cameraMovVec->x;
    camera->pos->z += cameraMovVec->y;
    delete cameraMovVec;

    /*  ---  Camera Rotation  ---  */
    if (frameState->mouse->leftButtonIsDown) {
        camera->rotate( (double) (frameState->deltaMousePosX()) * (double) 0.2, 0, 0 );
        camera->rotate( 0, (double) (frameState->deltaMousePosY()) * (double) -0.2, 0 );
    }

}

int main(int argc, char* argv[]) {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "SDL_Init Failed! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "CreateWindow Failed! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "CreateRenderer Failed! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create texture
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (texture == NULL) {
        fprintf(stderr, "CreateTexture Failed! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Log stuff
    logInit("log.txt");
    logClear();
    logWrite("Starting...", true);

    // Sets up the objects to be drawn and the camera
    Mesh::initMeshes();
    initGraphics();

    FrameState* frameState = new FrameState();
    Drawer* drawer;
    SDL_Event event;

    // Init main camera and the associated display
    Display* display1 = new Display(WINDOW_WIDTH, WINDOW_HEIGHT);
    Camera* camera1 = new Camera();
    camera1->setPos(0, 0, -10);
    camera1->setFov(90, 54);

    // Time stuff
    auto timeVar = std::chrono::high_resolution_clock::now();
    double appStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
    double lastFrameTime = appStartTime;
    double thisFrameTime = appStartTime;
    double dt;

    // Main event loop
    bool leave = false;
    while (!leave) {

        logWrite("Frame ", false);
        logWrite(frameState->frameCount, true);

        // Delta time
        timeVar = std::chrono::high_resolution_clock::now();
        lastFrameTime = thisFrameTime;
        thisFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
        dt = thisFrameTime - lastFrameTime;

        // Mouse position
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        frameState->mouse->setPos(mouseX, mouseY);

        // std::cout << "(" << frameState->mouse->posX << ", " << frameState->mouse->posY << ")" << std::endl;
        
        // Handle SDL events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) { leave = true; std::cout<<"closed"; }
            else frameState->addEvent(&event);
        }

        // Does all the user input handling
        handleInput(frameState, camera1, dt);

        getBuffer();

        drawer = new Drawer(buffer, (int) WINDOW_WIDTH, (int) WINDOW_HEIGHT);
        drawer->fillScreen(Color::BLACK);
        drawGraphics(drawer, frameState, camera1, display1); // from graphics.cpp
        delete drawer;

        std::cout << "(" << camera1->yaw << ", " << camera1->pitch << ")";
        std::cout << " - (" << camera1->pos->x << ", " << camera1->pos->y << ", " << camera1->pos->z << ")" << std::endl;

        flip();

        // Make current frameState become last frame
        frameState->nextFrame();
    }

    delete frameState;
    delete camera1;
    delete display1;

    // Destroy the window and quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
