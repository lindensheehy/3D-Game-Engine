#define SDL_MAIN_HANDLED

#include <iostream>
#include <chrono>

#include "src/class-headers/ColorClass.h"
#include "src/class-headers/DrawerClass.h"
#include "src/class-headers/FrameStateClass.h"
#include "src/class-headers/CameraClass.h"
#include "src/class-headers/DisplayClass.h"
#include "src/class-headers/MeshClass.h"
#include "src/class-headers/GuiClass.h"

#include "src/log/log.cpp"
#include "graphics.cpp"

Gui* gui = nullptr;

void handleInput(FrameState* frameState, Camera* camera, double dt) {

    /*
        ---  Directional Movement  ---

        The camera movement depends on facing direction for x,z movement (using WASD), while the up and down movement do not change based on facing direction
        First a value 'dist' is found which determines how far the camera should move based on the dt (delta time)
        Then the up and down movement are simple because the camera y position is just added or subtracted by the dist amount
        The x,z movement is a bit more complicated because it uses a 2d vector to hold the actual movement where the x and y components hold the left-right and front-back
        then rotates it based on the camera yaw and adds that to position.
    */

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

    try {

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
        Drawer* drawer;
        SDL_Event event;
        int mouseX, mouseY;

        // Init main camera and the associated display
        Display* display1 = new Display(gui->windowWidth, gui->windowHeight);
        Camera* camera1 = new Camera();
        camera1->setPos(0, 0, -10);
        camera1->setFov(90, 54);
        camera1->setLightingVec(1, -5, 2); // downfacing off axis lighting

        // Time stuff
        auto timeVar = std::chrono::high_resolution_clock::now();
        double appStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
        double lastFrameTime = appStartTime;
        double thisFrameTime = appStartTime;
        double dt;

        // Main event loop
        bool leave = false;
        while (!leave) {

            // Logging
            logWrite("Frame ", false);
            logWrite(frameState->frameCount, true);

            // Delta time
            timeVar = std::chrono::high_resolution_clock::now();
            lastFrameTime = thisFrameTime;
            thisFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
            dt = thisFrameTime - lastFrameTime;

            // Mouse position
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
            gui->getBuffer();

            drawer = new Drawer(gui->buffer, gui->windowWidth, gui->windowHeight);
            drawer->fillScreen(Color::BLACK);
            drawGraphics(drawer, frameState, camera1, display1); // from graphics.cpp
            gui->flip();
            delete drawer;

            std::cout << "(" << camera1->yaw << ", " << camera1->pitch << ")";
            //std::cout << " - (" << camera1->pos->x << ", " << camera1->pos->y << ", " << camera1->pos->z << ")" << std::endl;
            std::cout << " - (" << camera1->facingDirection->x << ", " << camera1->facingDirection->y << ", " << camera1->facingDirection->z << ")" << std::endl;

            // Make current frameState become last frame
            frameState->nextFrame();
        }

        delete frameState;
        delete camera1;
        delete display1;

        // Destroy the window and quit SDL
        gui->exit();

        return 0;

    } catch (const std::exception &e) {
        logWrite("Caught an exception!", true);
        logWrite(e.what(), true);
    }
}
