#include "../include/State.h"


/*  -----------------------------------  */
/*  ----------   TimeState   ----------  */
/*  -----------------------------------  */

// Constructor
State::TimeState::TimeState() {

    // Variable initialization
    this->totalFrameCount = 0;
    this->framesSinceLastSecond = 0;
    this->fps = 0;
    this->nextSecond = 0;
    this->dt = 0;


    // Get time
    auto timeVar = std::chrono::high_resolution_clock::now();
    this->frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
    this->lastFrameTime = frameTime;

    this->updateFps();

}

// Instance functions
void State::TimeState::updateDt() {

    auto timeVar = std::chrono::high_resolution_clock::now();
    this->lastFrameTime = this->frameTime;
    this->frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
    this->dt = this->frameTime - this->lastFrameTime;

}

void State::TimeState::updateFps() {

    if (this->frameTime > this->nextSecond) {

        // Reset next second
        long long temp = (long long) ((frameTime + 1000) / 1000);
        this->nextSecond = (double) temp * 1000;

        // Store fps
        this->fps = this->framesSinceLastSecond;

        // Reset counter
        this->framesSinceLastSecond = 0;

    }

}

void State::TimeState::update() {

    this->totalFrameCount++;
    this->framesSinceLastSecond++;

    this->updateDt();
    this->updateFps();

}

double State::TimeState::getTimeMillis() {

    auto timeVar = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();

}



/*  ------------------------------------  */
/*  ----------   MouseState   ----------  */
/*  ------------------------------------  */

// Contructor
State::MouseState::MouseState() {
    this->leftButtonIsDown = false;
    this->rightButtonIsDown = false;
    this->posX = 0;
    this->posY = 0;
}

// Instance functions
void State::MouseState::setState(MouseState* state) {
    this->leftButtonIsDown = state->leftButtonIsDown;
    this->rightButtonIsDown = state->rightButtonIsDown;
    this->middleButtonIsDown = state->middleButtonIsDown;
    this->posX = state->posX;
    this->posY = state->posY;
}

void State::MouseState::buttonDown(WPARAM wParam) {

    switch (wParam) {

        case MK_LBUTTON:
            this->leftButtonDown();
            return;

        case MK_MBUTTON:
            this->middleButtonDown();
            return;

        case MK_RBUTTON:
            this->rightButtonDown();
            return;

    }

}

void State::MouseState::buttonUp(WPARAM wParam) {
    
    switch (wParam) {

        case MK_LBUTTON:
            this->leftButtonUp();
            return;

        case MK_MBUTTON:
            this->middleButtonUp();
            return;

        case MK_RBUTTON:
            this->rightButtonUp();
            return;

    }

}

void State::MouseState::leftButtonDown() {
    this->leftButtonIsDown = true;
}

void State::MouseState::leftButtonUp() {
    this->leftButtonIsDown = false;
}

void State::MouseState::middleButtonDown() {
    this->middleButtonIsDown = true;
}

void State::MouseState::middleButtonUp() {
    this->middleButtonIsDown = false;
}

void State::MouseState::rightButtonDown() {
    this->rightButtonIsDown = true;
}

void State::MouseState::rightButtonUp() {
    this->rightButtonIsDown = false;
}

void State::MouseState::setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
}



/*  -------------------------------------  */
/*  ---------   KeyboardState   ---------  */
/*  -------------------------------------  */

// Constructor
State::KeyboardState::KeyboardState() {
    this->keyStates = new bool[this->keyStatesLength] {};
}

// Destructor
State::KeyboardState::~KeyboardState() {
    delete[] this->keyStates;
}

// Instance functions
void State::KeyboardState::setState(KeyboardState* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called State::KeyboardState->setState(KeyboardState*) on a null pointer!", true);
        return;
    }

    for (int i = 0; i < this->keyStatesLength; i++)
        this->keyStates[i] = state->keyStates[i];

    return;

}

bool* State::KeyboardState::getKeyRef(KeyCode keyCode) {

    /*
        Returns a pointer to the key boolean value within the instance variables
        This is reused in other instance functions
    */
    
    // Invalid value
    if (keyCode > 0xFF) return nullptr;

    return &(this->keyStates[keyCode]);

}

void State::KeyboardState::keyDown(KeyCode keyCode) {

    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = true;

    return;

}

void State::KeyboardState::keyUp(KeyCode keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = false;

    return;

}

bool State::KeyboardState::keyIsDown(KeyCode keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) return (*key) == true;
    else return false;

}



/*  ------------------------------------  */
/*  ----------   State   ----------  */
/*  ------------------------------------  */

// Contructor
State::State(HWND hwnd, bool hasChild /* default value = true */) {

    this->newKeyPresses = new KeyCode[3] {KEY_NULL, KEY_NULL, KEY_NULL};
    this->newKeyPressesIndex = 0;

    this->time = new TimeState();
    this->mouse = new MouseState();
    this->keys = new KeyboardState();

    this->hwnd = hwnd;

    if (hasChild) this->lastFrame = new State(hwnd, false);
    else this->lastFrame = nullptr;

}

// Destructor
State::~State() {
    if (this->newKeyPresses != nullptr) delete[] this->newKeyPresses;
    if (this->time != nullptr)          delete this->time;
    if (this->mouse != nullptr)         delete this->mouse;
    if (this->keys != nullptr)          delete this->keys;
    if (this->lastFrame != nullptr)     delete this->lastFrame;
}

// Instance functions
int State::handleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {

    KeyCode keyCode = (KeyCode) wParam;

    switch (msg) {

        // Paint the window, dont need to do anything here
        case WM_PAINT:
            return 0;

        // Handle window close events
        case WM_CLOSE:
        case WM_DESTROY:
            PostQuitMessage(0);
            return 1;

        // Handle mouse button events
        case WM_LBUTTONDOWN:
            this->mouse->leftButtonDown();
            return 0;

        case WM_MBUTTONDOWN:
            this->mouse->middleButtonDown();
            return 0;

        case WM_RBUTTONDOWN:
            this->mouse->rightButtonDown();
            return 0;

        case WM_LBUTTONUP:
            this->mouse->leftButtonUp();
            return 0;

        case WM_MBUTTONUP:
            this->mouse->middleButtonUp();
            return 0;

        case WM_RBUTTONUP:
            this->mouse->rightButtonUp();
            return 0;

        // Handle keyboard events
        case WM_KEYDOWN:

            // If it wasnt down last frame, add it to newKeyPresses
            if (
                this->lastFrame->keys->keyIsDown(keyCode) && 
                this->newKeyPressesIndex < 3
            ) {
                this->newKeyPresses[this->newKeyPressesIndex] = keyCode;
                this->newKeyPressesIndex++;
            }

            this->keys->keyDown(keyCode);
            return 0;

        case WM_KEYUP:
            this->keys->keyUp(keyCode);
            return 0;

    }

    // If the message was not handled in the switch, return 1 to signify this
    return 2;

}

void State::nextFrame() {

    this->newKeyPresses[0] = KEY_NULL;
    this->newKeyPresses[1] = KEY_NULL;
    this->newKeyPresses[2] = KEY_NULL;
    this->newKeyPressesIndex = 0;

    if (this->lastFrame == nullptr) return;

    this->lastFrame->setState(this);

    this->time->update();
    this->updateMousePos();

    return;

}

bool State::wasLeftJustPressed() {
    return (this->mouse->leftButtonIsDown && !this->lastFrame->mouse->leftButtonIsDown);
}

bool State::wasRightJustPressed() {
    return (this->mouse->rightButtonIsDown && !this->lastFrame->mouse->rightButtonIsDown);
}

bool State::wasLeftHeld() {

    return (
        this->mouse->leftButtonIsDown &&
        this->lastFrame->mouse->leftButtonIsDown
    );

}

bool State::wasRightHeld() {

    return (
        this->mouse->rightButtonIsDown &&
        this->lastFrame->mouse->rightButtonIsDown
    );

}

bool State::wasLeftJustReleased() {
    return (!this->mouse->leftButtonIsDown && this->lastFrame->mouse->leftButtonIsDown);
}

bool State::wasRightJustReleased() {
    return (!this->mouse->rightButtonIsDown && this->lastFrame->mouse->rightButtonIsDown);
}

void State::updateMousePos() {

    POINT point;

    GetCursorPos(&point);
    ScreenToClient(this->hwnd, &point);

    this->mouse->posX = point.x;
    this->mouse->posY = point.y;

}

int State::deltaMousePosX() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posX) - (this->lastFrame->mouse->posX);
}

int State::deltaMousePosY() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posY) - (this->lastFrame->mouse->posY);
}

bool State::keyIsDown(KeyCode keyCode) {
    return this->keys->keyIsDown(keyCode);
}

bool State::keyJustDown(KeyCode keyCode) {

    bool isDown = this->keys->keyIsDown(keyCode);
    bool wasDown = this->lastFrame->keys->keyIsDown(keyCode);

    return (isDown && !wasDown);

}

void State::setState(State* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called State->setState(State*) on a null pointer!", true);
        return;
    }

    this->mouse->setState(state->mouse);
    this->keys->setState(state->keys);
}
