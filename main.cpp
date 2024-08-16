#define SDL_MAIN_HANDLED

#include "src/include/Drawer.h"
#include "src/include/FrameState.h"
#include "src/include/Camera.h"
#include "src/include/Mesh.h"
#include "src/include/Gui.h"
#include "src/include/Log.h"

#include "graphics.cpp"

Gui* gui = nullptr;

void handleInput(FrameState* frameState, Camera* camera) {

    /*
        ---  Directional Movement  ---

        The camera movement depends on facing direction for x,z movement (using WASD), while the up and down movement do not change based on facing direction
        First a value 'dist' is found which determines how far the camera should move based on the dt (delta time)
        Then the up and down movement are simple because the camera y position is just added or subtracted by the dist amount
        The x,z movement is a bit more complicated because it uses a 2d vector to hold the actual movement where the x and y components hold the left-right and front-back
        then rotates it based on the camera yaw and adds that to position.
    */

    // Find distance to move based on the delta time of the frame
    double dist = camera->movementSpeed * (frameState->time->dt / 1000);

    if (frameState->keyIsDown(SDLK_LSHIFT)) 
        dist *= camera->sprintFactor;

    // Vertical Movement
    if (frameState->keyIsDown(SDLK_SPACE)) camera->pos->y += dist; // Up
    if (frameState->keyIsDown(SDLK_LCTRL)) camera->pos->y -= dist; // Down

    // Horizontal Movement
    Vec2* cameraMovVec = new Vec2();
    if (frameState->keyIsDown(SDLK_w)) cameraMovVec->y += dist; // Forward
    if (frameState->keyIsDown(SDLK_s)) cameraMovVec->y -= dist; // Backward
    if (frameState->keyIsDown(SDLK_a)) cameraMovVec->x -= dist; // Left
    if (frameState->keyIsDown(SDLK_d)) cameraMovVec->x += dist; // Right

    // Move camera based on its rotation
    cameraMovVec->rotate(-camera->yaw);
    camera->pos->x += cameraMovVec->x;
    camera->pos->z += cameraMovVec->y;
    delete cameraMovVec;

    /*  ---  Camera Rotation  ---  */
    if (frameState->mouse->leftButtonIsDown) {

        // 0.2 is just a random number I chose becuase it felt good in the app
        double mouseSensitivity = 0.2;
        double camDeltaYaw = (double) frameState->deltaMousePosX();
        double camDeltaPitch = (double) frameState->deltaMousePosY();
        camera->rotate( camDeltaYaw * mouseSensitivity, -camDeltaPitch * mouseSensitivity, 0 );

    }

}

int main(int argc, char* argv[]) {

    // Start the gui window
    gui = new Gui(1000, 600);
    gui->init();

    // Log stuff
    logInit("log.txt");
    logClear();
    logWrite("Starting...", true);

    // Sets up the objects to be drawn and the camera
    Mesh::initMeshes();
    initGraphics();

    FrameState* frameState = new FrameState();
    Drawer* drawer = new Drawer(gui->windowWidth, gui->windowHeight);
    SDL_Event event;
    int mouseX, mouseY;

    // Init main camera and the associated display
    Display* display1 = new Display(gui->windowWidth, gui->windowHeight);
    Camera* camera1 = new Camera();
    camera1->setPos(0, 0, -10);
    camera1->setFov(90, 54);
    camera1->setLightingVec(1, -5, 2); // downfacing off axis lighting
    camera1->movementSpeed = 50;


    // Main event loop
    bool leave = false;
    while (!leave) {

        // Mouse position
        SDL_GetMouseState(&mouseX, &mouseY);
        frameState->mouse->setPos(mouseX, mouseY);
        
        // Handle SDL events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) { leave = true; std::cout<<"closed"; }
            else frameState->addEvent(&event);
        }

        // Does all the user input handling
        handleInput(frameState, camera1);

        // Draw stuff
        gui->getBuffer();
        drawer->buffer = gui->buffer;
        drawer->resetDepthBuffer();
        drawer->fillScreen(Color::BLACK);
        drawGraphics(drawer, frameState, camera1, display1); // from graphics.cpp
        gui->flip();

        // Make current frameState become last frame
        frameState->nextFrame();
    }

    delete frameState;
    delete camera1;
    delete display1;

    // Destroy the window and quit SDL
    gui->exit();

    return 0;

}
