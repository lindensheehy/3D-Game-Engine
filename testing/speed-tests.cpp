#define SDL_MAIN_HANDLED

#include "../src/include/Drawer.h"
#include "../src/include/State.h"
#include "../src/include/Camera.h"
#include "../src/include/Mesh.h"
#include "../src/include/Gui.h"
#include "../src/include/Log.h"
#include "../src/include/ObjectSet.h"

Gui* gui = nullptr;
ObjectSet* objects;
Font* font;

void drawSky(Drawer* drawer, Camera* camera, Display* display) {

    // Because of how this function is called from drawGraphics, none of these should ever be null but it doesnt really hurt to check

    // Address error cases, but dont kill the process yet in case its not fatal
    if (drawer == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'drawer' as a null pointer!", true);
        return;
    }

    if (camera == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'camera' as a null pointer!", true);
        return;
    }

    if (display == nullptr) {
        logWrite("Called drawSky(Drawer*, Camera*, Display*) with 'display' as a null pointer!", true);
        return;
    }

    // Find the height on the display to draw the skyline
    Vec2* heightVec = new Vec2(display->height, 0);
    heightVec->rotate(camera->pitch);
    double height = (display->height / 2) + heightVec->y;
    delete heightVec;

    // If the camera is facing down enough that no sky is visible
    if (height < 0) {
        drawer->fillScreen(Color::BLACK);
        return;
    }

    // Draw the rectangles
    uint32_t skyColorLight = 0xFF323296; // o->FF, r->32, g->32, b->96
    uint32_t skyColorDark = 0xFF161648; // o->FF, r->16, g->16, b->48

    drawer->drawRect(
        skyColorLight, 
        display->widthOffset, 
        display->heightOffset, 
        display->widthOffset + display->width, 
        display->heightOffset + (height - (double) 25)
    );
    drawer->drawRect(
        skyColorDark, 
        display->widthOffset, 
        display->heightOffset + (height - (double) 25), 
        display->widthOffset + display->width, 
        display->heightOffset + height
    );
    drawer->drawRect(
        Color::BLACK, 
        display->widthOffset, 
        display->heightOffset + height, 
        display->widthOffset + display->width, 
        display->heightOffset + display->height
    );

    return;

}

void initGraphics() {

    font = new Font();
    font->init();

    objects = new ObjectSet();
    Object* newObject;

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(15)->move(0, 0, 50)->setColor(Color::WHITE);
    objects->pushBack(newObject, 1);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(5)->move(0, 20, 50)->setColor(Color::GREY);
    objects->pushBack(newObject, 2);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(10, 5, 15)->move(30, 10, 40)->rotateSelf(10, 0, 0)->setColor(Color::BLUE);
    objects->pushBack(newObject, 3);

    newObject = new Object();
    newObject->mesh = Mesh::capsuleMesh->copy()->scale(15)->move(0, -20, 50)->setColor(Color::GREEN);
    objects->pushBack(newObject, 4);

    newObject = new Object();
    newObject->mesh = Mesh::sphereMesh->copy()->scale(15, 40, 15)->move(-30, 0, 50)->setColor(Color::BLUE);
    objects->pushBack(newObject, 5);

    newObject = new Object();
    newObject->mesh = Mesh::sphereMesh->copy()->scale(25)->move(-30, 0, 50)->setColor(Color::WHITE);
    objects->pushBack(newObject, 6);

    newObject = new Object();
    newObject->mesh = Mesh::cubeMesh->copy()->scale(10)->move(0, 10, 50)->setColor(Color::BLUE);
    objects->pushBack(newObject, 7);

}

int main(int argc, char* argv[]) {

    // Start the gui window
    gui = new Gui(1000, 600);
    gui->init();

    // Sets up the objects to be drawn and the camera
    Mesh::initMeshes();
    initGraphics();

    State* state = new State();
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


    double startTime;
    double endTime;
    double runningTotal;


    // Main event loop, runs for 500 frames, 10 times
    bool leave = false;

    for (int i = 0; i < 25; i++) {

        startTime = state->time->getTimeMillis();    

        for (int i = 0; i < 500; i++) {

            // Mouse position
            SDL_GetMouseState(&mouseX, &mouseY);
            state->mouse->setPos(mouseX, mouseY);
            
            // Handle SDL events
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) { leave = true; std::cout<<"closed"; }
                else state->addEvent(&event);
            }

            if (leave) break;

            // Draw stuff
            gui->getBuffer();
            drawer->buffer = gui->buffer;
            drawer->resetDepthBuffer();

            drawSky(drawer, camera1, display1);
            objects->drawAll(drawer, camera1, display1);
            drawer->drawRect(Color::BLACK, 0, 0, 30, 13);
            font->drawer = drawer;
            font->drawInt(state->time->fps, 6, 3, Color::WHITE);

            gui->flip();

            // Make current state become last frame
            state->nextFrame();

        }

        endTime = state->time->getTimeMillis();

        double elapsedTime = endTime - startTime;
        std::cout << "executed in " << elapsedTime << " ms" << std::endl;

        runningTotal += elapsedTime;

    }

    delete state;
    delete camera1;
    delete display1;

    // Destroy the window and quit SDL
    gui->exit();

    double elapsedTime = endTime - startTime;
    std::cout << "average execution time:  " << runningTotal / 25 << " ms" << std::endl;

    return 0;

}
