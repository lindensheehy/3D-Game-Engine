#include "util/Utility.h"
#include "util/FileNavigator.h"

#include "graphics/rendering/Camera.h"
#include "graphics/rendering/Renderer.h"
#include "graphics/gui/GUI.h"
#include "geometry/Mesh.h"
#include "ui/UI.h"

#include "xml/XML.h"
#include "xml/XMLFile.h"

// Global declarations
Graphics::Gui::GUI* gui;
Graphics::Rendering::Camera* camera;

Graphics::Drawing::Drawer* drawer;
Graphics::Rendering::Renderer* renderer;

int selectedObjectId;
Physics::Object* selectedObject;

Physics::ObjectSet* objects;

bool drawNormals;
bool gravity;

Ui::UI* ui;

Ui::WindowHandle* navBar;
Ui::WindowHandle* windowTransform;
Ui::WindowHandle* windowObjects;

void giveUiData() {

    // Transform window
    if (windowTransform != nullptr) {
        if (selectedObject != nullptr) {
            if (windowTransform->hasNoContext()) {

                windowTransform->setContext( new Ui::ContextTransform(selectedObject) );

                // Rebind with new context
                ui->bindManager->rebind(windowTransform);

            }
        }
    }

    // Objects window
    if (windowObjects != nullptr) {

        // Only give it new context if it does not have one
        if ( windowObjects->hasNoContext() ) {
            windowObjects->setContext( new Ui::ContextObjects(objects) );
        }

    }

}

void handleInput() {

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
    Graphics::Gui::CursorState cursorState;
    bool inputHandled = ui->doInput(gui->state, &cursorState);
    gui->window->setCursorState(cursorState);
    if (inputHandled) return;

    // Find distance to move based on the delta time of the frame
    float dist = camera->movementSpeed * (gui->state->time->dt / 1000);

    if (gui->state->keyIsDown(KeyCode::SHIFT))
        dist *= camera->sprintFactor;

    // Vertical Movement
    if (gui->state->keyIsDown(KeyCode::SPACE)) camera->pos.y += dist; // Up
    if (gui->state->keyIsDown(KeyCode::CONTROL)) camera->pos.y -= dist; // Down

    // Horizontal Movement
    Geometry::Vec2 cameraMovVec;
    cameraMovVec.set(0, 0);
    if (gui->state->keyIsDown(KeyCode::W)) cameraMovVec.y += dist; // Forward
    if (gui->state->keyIsDown(KeyCode::S)) cameraMovVec.y -= dist; // Backward
    if (gui->state->keyIsDown(KeyCode::A)) cameraMovVec.x -= dist; // Left
    if (gui->state->keyIsDown(KeyCode::D)) cameraMovVec.x += dist; // Right

    // Move camera based on its rotation
    cameraMovVec.rotate(camera->facingAngle.y);
    camera->pos.x += cameraMovVec.x;
    camera->pos.z += cameraMovVec.y;


    /*  ---  Camera Rotation  ---  */

    if (gui->state->mouse->leftButtonIsDown) {

        // 0.2 is just a random number I chose becuase it felt good in the app
        float mouseSensitivity = 0.2;
        float camDeltaYaw = (float) gui->state->deltaMousePosX();
        float camDeltaPitch = (float) gui->state->deltaMousePosY();
        camera->rotate( -camDeltaPitch * mouseSensitivity, -camDeltaYaw * mouseSensitivity, 0 );

    }

    if (gui->state->keyJustDown(KeyCode::K)) {
        logWrite("Camera Angle: ");
        camera->facingAngle.log();
        logNewLine();
        logWrite("Camera Facing Vec: ");
        camera->facingVec.log();
        logNewLine();
        logNewLine();
    }


    /*   Object Selection   */

    // Object selection is done by requesting to the Drawer which pixel to watch
    // So then, on the next frame, the information about which Object drew there now exists
    // So before requesting the next selection, I process whatever exists from last frame

    // Check if an object was selected last frame
    if (renderer->pixelDrawer->pixelTracker.watchingPixelWrites) {

        Physics::Object* newSelection = renderer->pixelDrawer->pixelTracker.foundObject;

        // First make sure its non-null, otherwise the object would be instantly deselected after selection
        if (newSelection != nullptr) {

            // Reset opacity of old selectedObject if needed
            if (selectedObject != nullptr) selectedObject->opacity = 1;

            selectedObject = newSelection;

            // Now I update the opacity, and pass it to the UI, rebinding the Transform Window as well
            selectedObject->opacity = 0.5;

            ui->validateWindowHandle(&windowTransform);

            if (windowTransform != nullptr) {
                windowTransform->setContext( new Ui::ContextTransform(selectedObject) );
                ui->bindManager->rebind(windowTransform);
            }

        }

        // Also set it back to null, so as to not carry the information over unnecessarily
        renderer->pixelDrawer->pixelTracker.foundObject = nullptr;

    }

    // Tell Drawer->PixelTracker to watch the pixel the mouse is on
    if (gui->state->wasRightJustPressed()) {

        renderer->pixelDrawer->pixelTracker.watchedPixel.set(
            gui->state->mouse->posX,
            gui->state->mouse->posY
        );

        renderer->pixelDrawer->pixelTracker.watchingPixelWrites = true;

    }

    // Otherwise tell PixelTracker to not track anything
    else {
        renderer->pixelDrawer->pixelTracker.watchingPixelWrites = false;
    }

    // The enter key will deselect the selected object, if it exists
    if (gui->state->keyJustDown(KeyCode::ENTER)) {
        if (selectedObject != nullptr) selectedObject->opacity = 1;
        selectedObject = nullptr;
    }


    /*   Temporary stuff   */

    // Toggle normal vector drawing on key n
    if (gui->state->keyJustDown(KeyCode::N)) {

        drawNormals = !drawNormals;

        if (drawNormals) objects->setOpacityAll(0.5);
        else objects->setOpacityAll(1);

    }

    // Toggles gravity
    if (gui->state->keyJustDown(KeyCode::G)) {
        
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
    if (gui->state->keyJustDown(KeyCode::Z))
        objects->setVelocityAll(0, 25, 0);

}

void init() {

    // Log stuff
    logInit("log.txt");
    logClear();
    logWrite("Starting...", true);

    // Start the gui window
    gui = new Graphics::Gui::GUI(1200, 700, "Game Engine");

    renderer = new Graphics::Rendering::Renderer( &(gui->drawer->pixelDrawer), gui->display );

    camera = new Graphics::Rendering::Camera();
    camera->setPreset(0);

    // Sets up the default meshes
    Geometry::Mesh::initMeshes();

    // Create and populate the object set
    objects = new Physics::ObjectSet();
    Physics::Object* newObject;

    /*   Main Objects   */

    // newObject = new Physics::Object();
    // newObject->mesh = Geometry::Mesh::tempMesh;
    // newObject->scaleBy(15)->move(0, 0, 50)->setColor(Color::WHITE);
    // objects->pushBack(newObject);

    newObject = new Physics::Object();
    newObject->mesh = Geometry::Mesh::cubeMesh;
    newObject->scaleBy(15)->move(0, 0, 50)->setColor(Color::WHITE);
    objects->pushBack(newObject, 1);

    // newObject = new Physics::Object();
    // newObject->mesh = Geometry::Mesh::cubeMesh->copy();
    // newObject->scaleBy(5)->move(0, 20, 50)->setColor(Color::GREY);
    // objects->pushBack(newObject, 2);

    // newObject = new Physics::Object();
    // newObject->mesh = Geometry::Mesh::cubeMesh->copy();
    // newObject->scaleBy(10, 5, 15)->move(30, 10, 40)->rotate(10, 0, 0)->setColor(Color::BLUE);
    // objects->pushBack(newObject, 3);

    // newObject = new Physics::Object();
    // newObject->mesh = Geometry::Mesh::capsuleMesh->copy();
    // newObject->scaleBy(15)->move(0, -20, 50)->setColor(Color::GREEN);
    // objects->pushBack(newObject, 4);

    newObject = new Physics::Object();
    newObject->mesh = Geometry::Mesh::sphereMesh;
    newObject->scaleBy(12)->move(0, 0, 40)->setColor(Color::BLUE);
    objects->pushBack(newObject, 5);

    // newObject = new Physics::Object();
    // newObject->mesh = Geometry::Mesh::sphereMesh->copy();
    // newObject->scaleBy(25)->move(-30, 0, 50)->setColor(Color::WHITE);
    // objects->pushBack(newObject, 6);

    // newObject = new Physics::Object();
    // newObject->mesh = Geometry::Mesh::cubeMesh->copy();
    // newObject->scaleBy(10)->move(0, 10, 50)->setColor(Color::BLUE);
    // objects->pushBack(newObject, 7);


    /*   Floor   */

    // newObject = new Physics::Object();
    // newObject->mesh = Geometry::Mesh::cubeMesh->copy();
    // newObject->scaleBy(100, 1, 100)->move(0, -50, 50)->setColor(Color::DARKGREY);
    // objects->pushBack(newObject, 8);


    gravity = false;
    drawNormals = false;

    selectedObjectId = 1;

    ui = new Ui::UI();

    // Create the navbar
    navBar = ui->createWindow(Ui::File::NAVBAR);

    // Bind the nav bar
    navBar->setContext( new Ui::ContextNavBar(&windowTransform, &windowObjects) );
    ui->bindManager->addBind(navBar, Ui::BindFuncs::NavBar::bind);

    // Move the navbar to the top left
    ui->setWindowPos(navBar, 0, 0);

}

void doFrame() {

    // Does all the user input handling
    handleInput();

    // Give the UI any data it needs
    giveUiData();

    // Handle the physics for the frame
    objects->doAllPhysics(gui->state->time->dt);

    // Prep the pixel and depth buffers
    renderer->pixelDrawer->resetDepthBuffer();
    gui->drawer->drawSky(camera, gui->display); // This acts as a pixel buffer reset since it draws to every pixel

    // // Draw all the objects
    if (drawNormals) objects->drawAllWithNormals(renderer, camera);
    else objects->drawAll(renderer, camera);
    
    // Draw the UI
    gui->drawer->drawFps(gui->state, gui->display);
    ui->draw(gui->drawer);
    gui->drawer->drawCrosshair(gui->display);

    // Tell State that the frame is over
    gui->state->nextFrame();

    // Update the GUI
    gui->window->flip();

    return;

}

void cleanup() {

    delete camera;
    delete gui;
    delete objects;
    delete ui;

}

int main(int argc, char* argv[]) {

    init();

    while ( !(gui->shouldDestroyWindow) ) {
        doFrame();
    }

    cleanup();

    return 0;

}
