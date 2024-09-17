#define SDL_MAIN_HANDLED

#include "src/include/Drawer.h"
#include "src/include/State.h"
#include "src/include/Camera.h"
#include "src/include/Mesh.h"
#include "src/include/Gui.h"
#include "src/include/Log.h"

#include "physics.cpp"

// Global declarations
Gui* gui;
State* state;
Drawer* drawer;
Display* display;
Camera* camera;

Object* selectedObject;

ObjectSet* opaqueObjects;
ObjectSet* transparentObjects;

bool drawNormals;
bool gravity;

void handleInput(State* state, Camera* camera) {

    /*
        ---  Directional Movement  ---

        The camera movement depends on facing direction for x,z movement (using WASD), while the up and down movement do not change based on facing direction
        First a value 'dist' is found which determines how far the camera should move based on the dt (delta time)
        Then the up and down movement are simple because the camera y position is just added or subtracted by the dist amount
        The x,z movement is a bit more complicated because it uses a 2d vector to hold the actual movement where the x and y components hold the left-right and front-back
        then rotates it based on the camera yaw and adds that to position.
    */

    // Find distance to move based on the delta time of the frame
    double dist = camera->movementSpeed * (state->time->dt / 1000);

    if (state->keyIsDown(SDLK_LSHIFT))
        dist *= camera->sprintFactor;

    // Vertical Movement
    if (state->keyIsDown(SDLK_SPACE)) camera->pos->y += dist; // Up
    if (state->keyIsDown(SDLK_LCTRL)) camera->pos->y -= dist; // Down

    // Horizontal Movement
    Vec2* cameraMovVec = new Vec2();
    if (state->keyIsDown(SDLK_w)) cameraMovVec->y += dist; // Forward
    if (state->keyIsDown(SDLK_s)) cameraMovVec->y -= dist; // Backward
    if (state->keyIsDown(SDLK_a)) cameraMovVec->x -= dist; // Left
    if (state->keyIsDown(SDLK_d)) cameraMovVec->x += dist; // Right

    // Move camera based on its rotation
    cameraMovVec->rotate(-camera->yaw);
    camera->pos->x += cameraMovVec->x;
    camera->pos->z += cameraMovVec->y;
    delete cameraMovVec;

    /*  ---  Camera Rotation  ---  */
    if (state->mouse->leftButtonIsDown) {

        // 0.2 is just a random number I chose becuase it felt good in the app
        double mouseSensitivity = 0.2;
        double camDeltaYaw = (double) state->deltaMousePosX();
        double camDeltaPitch = (double) state->deltaMousePosY();
        camera->rotate( camDeltaYaw * mouseSensitivity, -camDeltaPitch * mouseSensitivity, 0 );

    }


    /*   Temporary stuff   */

    // Toggle normal vector drawing on key n
    if (state->keyJustDown(SDLK_n))
        drawNormals = !drawNormals;

    Object* affectedObject = nullptr;

    // This rotates the white sphere on the left when pressing keys j,k,l
    if (state->keyIsDown(SDLK_j)) {
        affectedObject = transparentObjects->getById(6);
        if (affectedObject != nullptr) affectedObject->mesh->rotateSelf(1, 0, 0);
    }

    if (state->keyIsDown(SDLK_k)) {
        affectedObject = transparentObjects->getById(6);
        if (affectedObject != nullptr) affectedObject->mesh->rotateSelf(0, 1, 0);
    }

    if (state->keyIsDown(SDLK_l)) {
        affectedObject = transparentObjects->getById(6);
        if (affectedObject != nullptr) affectedObject->mesh->rotateSelf(0, 0, 1);
    }

    // This moves the blue oval inside the white sphere when pressing keys o,p
    if (state->keyIsDown(SDLK_o)) {
        affectedObject = opaqueObjects->getById(5);
        if (affectedObject != nullptr) affectedObject->mesh->move(0, 0.5, 0);
    }

    if (state->keyIsDown(SDLK_p)) {
        affectedObject = opaqueObjects->getById(5);
        if (affectedObject != nullptr) affectedObject->mesh->move(0, -0.5, 0);
    }

    // Toggles gravity
    if (state->keyJustDown(SDLK_g))
        if (gravity) {
            std::cout << "gravity off" << std::endl;
            opaqueObjects->setAllGravity(0.0);
            gravity = false;
        }

        else {
            std::cout << "gravity on" << std::endl;
            opaqueObjects->setAllGravity(-30);
            gravity = true;
        }

    // Gives all the objects some vertical velocity
    if (state->keyJustDown(SDLK_z))
        opaqueObjects->setVelocityAll(0, 25, 0);

}

void init() {

    // Log stuff
    logInit("log.txt");
    logClear();
    logWrite("Starting...", true);

    // Start the gui window
    gui = new Gui(1000, 600);
    gui->init();

    // Init all the working objects
    state = new State();

    display = new Display(gui->windowWidth, gui->windowHeight);
    camera = new Camera();
    camera->setPreset(0);

    drawer = new Drawer(gui->windowWidth, gui->windowHeight);
    drawer->initFont();

    // Sets up the default meshes, and creates the objects to be drawn
    Mesh::initMeshes();


    // Create and populate the object set
    opaqueObjects = new ObjectSet();
    transparentObjects = new ObjectSet();
    Object* newObject;

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(15)->move(0, 0, 50)->setColor(Color::WHITE);
    transparentObjects->pushBack(newObject, 1);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(5)->move(0, 20, 50)->setColor(Color::GREY);
    opaqueObjects->pushBack(newObject, 2);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(10, 5, 15)->move(30, 10, 40)->rotateSelf(10, 0, 0)->setColor(Color::BLUE);
    opaqueObjects->pushBack(newObject, 3);

    newObject = new Object();
    newObject->mesh = Mesh::capsuleMesh->copy()->scale(15)->move(0, -20, 50)->setColor(Color::GREEN);
    opaqueObjects->pushBack(newObject, 4);

    newObject = new Object();
    newObject->mesh = Mesh::sphereMesh->copy()->scale(15, 40, 15)->move(-30, 0, 50)->setColor(Color::BLUE);
    opaqueObjects->pushBack(newObject, 5);

    newObject = new Object();
    newObject->mesh = Mesh::sphereMesh->copy()->scale(25)->move(-30, 0, 50)->setColor(Color::WHITE);
    transparentObjects->pushBack(newObject, 6);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(10)->move(0, 10, 50)->setColor(Color::BLUE);
    opaqueObjects->pushBack(newObject, 7);

    gravity = false;
    drawNormals = false;

}

int main(int argc, char* argv[]) {

    // Starts up everything needed for the main loop
    init();

    // Declarations for the main loop
    SDL_Event event;
    bool leave = false;


    // Main loop
    while (!leave) {

        // Update mouse position
        SDL_GetMouseState(   &(state->mouse->posX),   &(state->mouse->posY)   );
        
        // Handle SDL events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) { leave = true; std::cout<<"closed"; }
            else state->addEvent(&event);
        }

        // Does all the user input handling
        handleInput(state, camera);

        // Handle the physics for the frame
        opaqueObjects->doAllPhysics(state->time->dt);
        transparentObjects->doAllPhysics(state->time->dt);

        // Prep the pixel and depth buffers
        gui->getBuffer();
        drawer->buffer = gui->buffer;
        drawer->resetDepthBuffer();
        drawer->drawSky(camera, display); // This acts as a pixel buffer reset since it draws to every pixel

        // Draw all the objects
        if (drawNormals) {
            opaqueObjects->drawAllWithNormals(drawer, camera, display, 0.5);
            transparentObjects->drawAllWithNormals(drawer, camera, display, 0.2);
        }

        else {
            opaqueObjects->drawAll(drawer, camera, display);
            transparentObjects->drawAll(drawer, camera, display, 0.5);
        }
        
        // Draw the fps counter
        drawer->drawFps(state);

        // Update the GUI
        gui->flip();

        // Tell State that the frame is over
        state->nextFrame();

    }

    delete state;
    delete camera;
    delete display;
    delete drawer;

    // Destroy the window and quit SDL
    gui->exit();
    delete gui;

    return 0;

}
