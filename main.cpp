#include "util/Utility.h"

#include "geometry/Camera.h"
#include "geometry/Mesh.h"
#include "gui/Drawer.h"
#include "gui/State.h"
#include "gui/Gui.h"
#include "ui/UI.h"

#include "xml/XML.h"
#include "xml/XMLFile.h"

// Global declarations
Gui* gui;
State* state;
Drawer* drawer;
Display* display;
Camera* camera;

int selectedObjectId;
Object* selectedObject;

ObjectSet* objects;

bool drawNormals;
bool gravity;

UI* ui;

WindowHandle windowTransform;
WindowHandle windowNavBar;

bool doMainLoop = true;

void handleInput(State* state, Camera* camera) {

    /*
        ---  Directional Movement  ---

        The camera movement depends on facing direction for x,z movement (using WASD), while the up and down movement do not change based on facing direction
        First a value 'dist' is found which determines how far the camera should move based on the dt (delta time)
        Then the up and down movement are simple because the camera y position is just added or subtracted by the dist amount
        The x,z movement is a bit more complicated because it uses a 2d vector to hold the actual movement where the x and y components hold the left-right and front-back
        then rotates it based on the camera yaw and adds that to position.
    */

    // Give the state to the UI to handle. 
    // If the input is handled through the UI (based on return value), the rest of this is skipped
    // This also updates the mouse cursor state if needed
    CursorState cursorState;
    bool inputHandled = ui->doInput(state, &cursorState);
    gui->setCursorState(cursorState);
    if (inputHandled) return;

    // Find distance to move based on the delta time of the frame
    float dist = camera->movementSpeed * (state->time->dt / 1000);

    if (state->keyIsDown(KEY_SHIFT))
        dist *= camera->sprintFactor;

    // Vertical Movement
    if (state->keyIsDown(KEY_SPACE)) camera->pos->y += dist; // Up
    if (state->keyIsDown(KEY_CONTROL)) camera->pos->y -= dist; // Down

    // Horizontal Movement
    Vec2* cameraMovVec = new Vec2();
    if (state->keyIsDown(KEY_W)) cameraMovVec->y += dist; // Forward
    if (state->keyIsDown(KEY_S)) cameraMovVec->y -= dist; // Backward
    if (state->keyIsDown(KEY_A)) cameraMovVec->x -= dist; // Left
    if (state->keyIsDown(KEY_D)) cameraMovVec->x += dist; // Right

    // Move camera based on its rotation
    cameraMovVec->rotate(-camera->yaw);
    camera->pos->x += cameraMovVec->x;
    camera->pos->z += cameraMovVec->y;
    delete cameraMovVec;

    /*  ---  Camera Rotation  ---  */
    if (state->mouse->leftButtonIsDown) {

        // 0.2 is just a random number I chose becuase it felt good in the app
        float mouseSensitivity = 0.2;
        float camDeltaYaw = (float) state->deltaMousePosX();
        float camDeltaPitch = (float) state->deltaMousePosY();
        camera->rotate( camDeltaYaw * mouseSensitivity, -camDeltaPitch * mouseSensitivity, 0 );

    }


    /*   Temporary stuff   */

    // Toggle normal vector drawing on key n
    if (state->keyJustDown(KEY_N)) {

        drawNormals = !drawNormals;

        if (drawNormals) objects->setOpacityAll(0.5);
        else objects->setOpacityAll(1);

    }

    // Pick object based on id, this cycles through all the objects with ids 1-7
    bool changeObject = false;

    if (state->keyJustDown(KEY_Q)) {
        selectedObjectId--;
        if (selectedObjectId < 1) selectedObjectId += 8;
        changeObject = true;
    }

    if (state->keyJustDown(KEY_E)) {
        selectedObjectId++;
        if (selectedObjectId > 8) selectedObjectId -= 8;
        changeObject = true;
    }

    if (changeObject) {

        if (selectedObject != nullptr) selectedObject->opacity = 1;
        selectedObject = objects->getById(selectedObjectId);
        selectedObject->opacity = 0.5;

        ui->validateWindowHandle(&windowTransform);

        if (windowTransform.id == -1) {
            windowTransform = ui->createWindow(File::TRANSFORM);
        }

        ui->binding->bindTransform(windowTransform, selectedObject);

    }

    if (state->keyJustDown(KEY_ENTER)) {

        if (selectedObject != nullptr) selectedObject->opacity = 1;
        selectedObject = nullptr;

        ui->destroyWindow(&windowTransform);

    }

    // This rotates the selected object when pressing keys j,k,l
    if (state->keyIsDown(KEY_J))
        if (selectedObject != nullptr) selectedObject->rotateSelf(1, 0, 0);

    if (state->keyIsDown(KEY_K))
        if (selectedObject != nullptr) selectedObject->rotateSelf(0, 1, 0);

    if (state->keyIsDown(KEY_L))
        if (selectedObject != nullptr) selectedObject->rotateSelf(0, 0, 1);

    // This moves the selected object along the y-axis when pressing keys o,p
    if (state->keyIsDown(KEY_O))
        if (selectedObject != nullptr) selectedObject->move(0, 0.5, 0);

    if (state->keyIsDown(KEY_P))
        if (selectedObject != nullptr) selectedObject->move(0, -0.5, 0);

    // This moves the selected object along the x-axis when pressing keys o,p
    if (state->keyIsDown(KEY_U))
        if (selectedObject != nullptr) selectedObject->move(0.5, 0, 0);

    if (state->keyIsDown(KEY_I))
        if (selectedObject != nullptr) selectedObject->move(-0.5, 0, 0);

    // This moves the selected object along the z-axis when pressing keys o,p
    if (state->keyIsDown(KEY_T))
        if (selectedObject != nullptr) selectedObject->move(0, 0, 0.5);

    if (state->keyIsDown(KEY_Y))
        if (selectedObject != nullptr) selectedObject->move(0, 0, -0.5);

    // Toggles gravity
    if (state->keyJustDown(KEY_G)) {
        
        if (gravity) {
            objects->setGravityAll(0.0);
            gravity = false;
        }

        else {
            objects->setGravityAll(-30);
            gravity = true;
        }

    }

    // Gives all the objects some vertical velocity
    if (state->keyJustDown(KEY_Z))
        objects->setVelocityAll(0, 25, 0);

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    // Skip manual handling if state is not instantiated yet
    if (state == nullptr) return DefWindowProc(hwnd, uMsg, wParam, lParam);

    int status = state->handleMessage(uMsg, wParam, lParam);

    switch (status) {

        // Message was properly handled
        case 0:
            return 0;

        // Message was a quit message, leave main loop
        case 1:
            doMainLoop = false;
            return 0;

        // Message was not handled, continue the rest of the function
        default:
            break;

    }

    int newWidth;
    int newHeight;

    switch (uMsg) {

        case WM_SIZE: {

            // Skip if gui, display, or drawer are not instantiated yet
            if (gui == nullptr) break;
            if (display == nullptr) break;
            if (drawer == nullptr) break;

            newWidth = LOWORD(lParam);
            newHeight = HIWORD(lParam);

            // Tell display about the new dimensions
            display->updateDimensions(newWidth, newHeight);

            // Tell gui about the new dimensions
            gui->updateDimensions(newWidth, newHeight);
            
            // Tell drawer about the new dimensions
            drawer->updateDimensions(newWidth, newHeight);

            // Also do default handling
            return 0;

        }

        // Default handling
        default:
            break;

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

void init() {

    // Log stuff
    logInit("log.txt");
    logClear();
    logWrite("Starting...", true);

    // Start the gui window
    gui = new Gui(WindowProc, 1200, 700, "Game Engine");

    // Init all the working objects
    state = new State(gui->hwnd);

    display = new Display(gui->windowWidth, gui->windowHeight);
    camera = new Camera();
    camera->setPreset(0);

    drawer = new Drawer(display);
    drawer->initFont();
    drawer->buffer = gui->buffer;

    // Sets up the default meshes
    Mesh::initMeshes();


    // Create and populate the object set
    objects = new ObjectSet();
    Object* newObject;

    /*   Main Objects   */

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(15)->move(0, 0, 50)->setColor(Color::WHITE);
    objects->pushBack(newObject, 1);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy();
    newObject->scaleBy(5)->move(0, 20, 50)->setColor(Color::GREY);
    objects->pushBack(newObject, 2);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy();
    newObject->scaleBy(10, 5, 15)->move(30, 10, 40)->rotateSelf(10, 0, 0)->setColor(Color::BLUE);
    objects->pushBack(newObject, 3);

    newObject = new Object();
    newObject->mesh = Mesh::capsuleMesh->copy();
    newObject->scaleBy(15)->move(0, -20, 50)->setColor(Color::GREEN);
    objects->pushBack(newObject, 4);

    newObject = new Object();
    newObject->mesh = Mesh::sphereMesh->copy();
    newObject->scaleBy(15, 40, 15)->move(-30, 0, 50)->setColor(Color::BLUE);
    objects->pushBack(newObject, 5);

    newObject = new Object();
    newObject->mesh = Mesh::sphereMesh->copy();
    newObject->scaleBy(25)->move(-30, 0, 50)->setColor(Color::WHITE);
    objects->pushBack(newObject, 6);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy();
    newObject->scaleBy(10)->move(0, 10, 50)->setColor(Color::BLUE);
    objects->pushBack(newObject, 7);


    /*   Floor   */

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy();
    newObject->scaleBy(100, 1, 100)->move(0, -50, 50)->setColor(Color::DARKGREY);
    objects->pushBack(newObject, 8);


    gravity = false;
    drawNormals = false;

    selectedObjectId = 1;

    ui = new UI();

    // Create the navbar
    windowNavBar = ui->createWindow(File::NAVBAR);

    // Move the navbar to the top left
    ui->setWindowPos(windowNavBar, 0, 0);

}

int main(int argc, char* argv[]) {

    // Starts up everything needed for the main loop
    init();

    // Main loop
    while (doMainLoop) {

        // Does all the user input handling
        handleInput(state, camera);

        // Handle the physics for the frame
        objects->doAllPhysics(state->time->dt);

        // Prep the pixel and depth buffers
        drawer->resetDepthBuffer();
        drawer->drawSky(camera, display); // This acts as a pixel buffer reset since it draws to every pixel

        // Draw all the objects
        if (drawNormals) objects->drawAllWithNormals(drawer, camera, display);
        else objects->drawAll(drawer, camera, display);
        
        // Draw the UI
        drawer->drawFps(state, display);
        ui->draw(drawer);
        drawer->drawCrosshair(display);

        // Tell State that the frame is over
        state->nextFrame();

        // Update the GUI
        gui->flip();

    }

    delete state;
    delete camera;
    delete display;
    delete drawer;
    delete gui;

    return 0;

}
