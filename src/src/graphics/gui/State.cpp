#include "graphics/gui/State.h"

using namespace Graphics::Gui;


/*  -----------------------------------  */
/*  ----------   TimeState   ----------  */
/*  -----------------------------------  */

State::TimeState::TimeState() {

    this->totalFrameCount = 0;
    this->dt = 0;
    this->fps = 0;

    this->framesSinceLastSecond = 0;
    this->nextSecondMillis = 0;

    // Set up
    this->initTimer();
    this->update();

    return;

}

void State::TimeState::updateDt() {

    this->lastFrameTime = this->frameTime;

    QueryPerformanceCounter( &(this->frameTime) );

    const long long frameTimeQP = this->frameTime.QuadPart;
    const long long lastFrameTimeQP = this->lastFrameTime.QuadPart;
    const long long frequencyQP = this->frequency.QuadPart;

    this->dt = (double) (frameTimeQP - lastFrameTimeQP) / frequencyQP;
    this->dt *= 1000;

    return;

}

void State::TimeState::updateFps() {

    double frameTimeMillis = (double) (this->frameTime.QuadPart) / this->frequency.QuadPart;
    frameTimeMillis *= 1000;

    if (frameTimeMillis > this->nextSecondMillis) {

        // Reset next second
        const long long temp = (long long) ((frameTimeMillis + 1000) / 1000);
        this->nextSecondMillis = (double) temp * 1000;

        // Store fps
        this->fps = this->framesSinceLastSecond;

        // Reset counter
        this->framesSinceLastSecond = 0;

    }

    return;

}

void State::TimeState::update() {

    this->totalFrameCount++;
    this->framesSinceLastSecond++;

    this->updateDt();
    this->updateFps();

    return;

}

double State::TimeState::getTimeMillis() const {

    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    const double temp = (double) (currentTime.QuadPart) / frequency.QuadPart;

    return temp * 1000;

}

void State::TimeState::initTimer() {

    QueryPerformanceFrequency( &(this->frequency) );
    QueryPerformanceCounter( &(this->frameTime) );

    return;

}



/*  ------------------------------------  */
/*  ----------   MouseState   ----------  */
/*  ------------------------------------  */

State::MouseState::MouseState() {

    this->leftButtonIsDown = false;
    this->rightButtonIsDown = false;
    this->posX = 0;
    this->posY = 0;

    return;

}

void State::MouseState::setState(const MouseState* state) {

    this->leftButtonIsDown = state->leftButtonIsDown;
    this->rightButtonIsDown = state->rightButtonIsDown;
    this->middleButtonIsDown = state->middleButtonIsDown;
    this->posX = state->posX;
    this->posY = state->posY;

    return;

}

void State::MouseState::buttonDown(WPARAM wParam) {

    switch (wParam) {

        case MK_LBUTTON:
            this->leftButtonDown();
            break;

        case MK_MBUTTON:
            this->middleButtonDown();
            break;

        case MK_RBUTTON:
            this->rightButtonDown();
            break;

        default:
            break;

    }

    return;

}

void State::MouseState::buttonUp(WPARAM wParam) {
    
    switch (wParam) {

        case MK_LBUTTON:
            this->leftButtonUp();
            break;

        case MK_MBUTTON:
            this->middleButtonUp();
            break;

        case MK_RBUTTON:
            this->rightButtonUp();
            break;

        default:
            break;

    }

    return;

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

    return;

}



/*  -------------------------------------  */
/*  ---------   KeyboardState   ---------  */
/*  -------------------------------------  */

State::KeyboardState::KeyboardState() {

    this->keyStates = new bool[this->keyStatesLength];
    memset(this->keyStates, 0x00, this->keyStatesLength * sizeof(bool));

    return;

}

State::KeyboardState::~KeyboardState() {

    delete[] this->keyStates;

    return;

}

void State::KeyboardState::setState(const KeyboardState* state) {

    if (state == nullptr) {
        logWrite("Called State::KeyboardState->setState(KeyboardState*) on a null pointer!", true);
        return;
    }

    for (int i = 0; i < this->keyStatesLength; i++) {
        this->keyStates[i] = state->keyStates[i];
    }

    return;

}

bool* State::KeyboardState::getKeyRef(KeyCode keyCode) const {

    /*
        Returns a pointer to the keys boolean value within the master array
        This is a helper function for other instance functions
    */
    
    // Invalid value
    if ( (int) keyCode > 0xFF ) return nullptr;

    return &(this->keyStates[ (int) keyCode ]);

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

bool State::KeyboardState::keyIsDown(KeyCode keyCode) const {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) return (*key) == true;
    
    return false;

}



/*  -------------------------------  */
/*  ----------   State   ----------  */
/*  -------------------------------  */

State::State(HWND hwnd, bool hasChild /* default value = true */) : hwnd(hwnd) {

    this->newKeyPresses[0] = KeyCode::NONE;
    this->newKeyPresses[1] = KeyCode::NONE;
    this->newKeyPresses[2] = KeyCode::NONE;
    this->newKeyPressesIndex = 0;

    this->time = new TimeState();
    this->mouse = new MouseState();
    this->keys = new KeyboardState();

    if (hasChild) this->lastFrame = new State(hwnd, false);
    else this->lastFrame = nullptr;

    return;

}

State::~State() {

    delete this->time;
    delete this->mouse;
    delete this->keys;
    delete this->lastFrame;

    return;

}

int State::handleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {

    const KeyCode keyCode = (KeyCode) wParam;

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

            // If this is one of the first three keys pressed this frame, store it
            if (this->newKeyPressesIndex < 3) {
                this->newKeyPresses[this->newKeyPressesIndex] = keyCode;
                this->newKeyPressesIndex++;
            }

            this->keys->keyDown(keyCode);
            return 0;

        case WM_KEYUP:
            this->keys->keyUp(keyCode);
            return 0;

    }

    // If the message was not handled in the switch, return 2 to signify this
    return 2;

}

void State::nextFrame() {

    this->newKeyPresses[0] = KeyCode::NONE;
    this->newKeyPresses[1] = KeyCode::NONE;
    this->newKeyPresses[2] = KeyCode::NONE;
    this->newKeyPressesIndex = 0;

    if (this->lastFrame == nullptr) return;

    this->lastFrame->setState(this);

    this->time->update();
    this->updateMousePos();

    return;

}

bool State::wasLeftJustPressed() const {
    return (this->mouse->leftButtonIsDown && !this->lastFrame->mouse->leftButtonIsDown);
}

bool State::wasRightJustPressed() const {
    return (this->mouse->rightButtonIsDown && !this->lastFrame->mouse->rightButtonIsDown);
}

bool State::wasLeftHeld() const {
    return (this->mouse->leftButtonIsDown && this->lastFrame->mouse->leftButtonIsDown);
}

bool State::wasRightHeld() const {
    return (this->mouse->rightButtonIsDown && this->lastFrame->mouse->rightButtonIsDown);
}

bool State::wasLeftJustReleased() const {
    return (!this->mouse->leftButtonIsDown && this->lastFrame->mouse->leftButtonIsDown);
}

bool State::wasRightJustReleased() const {
    return (!this->mouse->rightButtonIsDown && this->lastFrame->mouse->rightButtonIsDown);
}

void State::updateMousePos() {

    POINT point;

    GetCursorPos(&point);
    ScreenToClient(this->hwnd, &point);

    this->mouse->posX = point.x;
    this->mouse->posY = point.y;

    return;

}

int State::deltaMousePosX() const {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posX) - (this->lastFrame->mouse->posX);
}

int State::deltaMousePosY() const {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posY) - (this->lastFrame->mouse->posY);
}

bool State::keyIsDown(KeyCode keyCode) const {
    return this->keys->keyIsDown(keyCode);
}

bool State::keyJustDown(KeyCode keyCode) const {

    bool isDown = this->keys->keyIsDown(keyCode);
    bool wasDown = this->lastFrame->keys->keyIsDown(keyCode);

    return (isDown && !wasDown);

}

void State::setState(const State* state) {

    if (state == nullptr) {
        logWrite("Called State->setState(State*) on a null pointer!", true);
        return;
    }

    this->mouse->setState(state->mouse);
    this->keys->setState(state->keys);

    return;
}
