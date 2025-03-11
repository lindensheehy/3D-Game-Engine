#include "gui/State.h"


/*  -----------------------------------  */
/*  ----------   TimeState   ----------  */
/*  -----------------------------------  */

// Constructor
Gui::State::TimeState::TimeState() {

    // Variable initialization
    this->totalFrameCount = 0;
    this->dt = 0;
    this->fps = 0;

    this->framesSinceLastSecond = 0;
    this->nextSecondMillis = 0;


    // Get time
    this->initTimer();
    this->update();

}

// Instance functions
void Gui::State::TimeState::updateDt() {

    this->lastFrameTime = this->frameTime;

    QueryPerformanceCounter( &(this->frameTime) );

    long long frameTimeQP = this->frameTime.QuadPart;
    long long lastFrameTimeQP = this->lastFrameTime.QuadPart;
    long long frequencyQP = this->frequency.QuadPart;

    this->dt = (double) (frameTimeQP - lastFrameTimeQP) / frequencyQP;
    this->dt *= 1000;

}

void Gui::State::TimeState::updateFps() {

    double frameTimeMillis = (double) (this->frameTime.QuadPart) / this->frequency.QuadPart;
    frameTimeMillis *= 1000;

    if (frameTimeMillis > this->nextSecondMillis) {

        // Reset next second
        long long temp = (long long) ((frameTimeMillis + 1000) / 1000);
        this->nextSecondMillis = (double) temp * 1000;

        // Store fps
        this->fps = this->framesSinceLastSecond;

        // Reset counter
        this->framesSinceLastSecond = 0;

    }

}

void Gui::State::TimeState::update() {

    this->totalFrameCount++;
    this->framesSinceLastSecond++;

    this->updateDt();
    this->updateFps();

}

double Gui::State::TimeState::getTimeMillis() {

    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    double temp = (double) (currentTime.QuadPart) / frequency.QuadPart;
    return temp * 1000;

}

void Gui::State::TimeState::initTimer() {

    QueryPerformanceFrequency( &(this->frequency) );
    QueryPerformanceCounter( &(this->frameTime) );

}



/*  ------------------------------------  */
/*  ----------   MouseState   ----------  */
/*  ------------------------------------  */

// Contructor
Gui::State::MouseState::MouseState() {
    this->leftButtonIsDown = false;
    this->rightButtonIsDown = false;
    this->posX = 0;
    this->posY = 0;
}

// Instance functions
void Gui::State::MouseState::setState(MouseState* state) {
    this->leftButtonIsDown = state->leftButtonIsDown;
    this->rightButtonIsDown = state->rightButtonIsDown;
    this->middleButtonIsDown = state->middleButtonIsDown;
    this->posX = state->posX;
    this->posY = state->posY;
}

void Gui::State::MouseState::buttonDown(WPARAM wParam) {

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

void Gui::State::MouseState::buttonUp(WPARAM wParam) {
    
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

void Gui::State::MouseState::leftButtonDown() {
    this->leftButtonIsDown = true;
}

void Gui::State::MouseState::leftButtonUp() {
    this->leftButtonIsDown = false;
}

void Gui::State::MouseState::middleButtonDown() {
    this->middleButtonIsDown = true;
}

void Gui::State::MouseState::middleButtonUp() {
    this->middleButtonIsDown = false;
}

void Gui::State::MouseState::rightButtonDown() {
    this->rightButtonIsDown = true;
}

void Gui::State::MouseState::rightButtonUp() {
    this->rightButtonIsDown = false;
}

void Gui::State::MouseState::setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
}



/*  -------------------------------------  */
/*  ---------   KeyboardState   ---------  */
/*  -------------------------------------  */

// Constructor
Gui::State::KeyboardState::KeyboardState() {
    this->keyStates = new bool[this->keyStatesLength] {};
}

// Destructor
Gui::State::KeyboardState::~KeyboardState() {
    delete[] this->keyStates;
}

// Instance functions
void Gui::State::KeyboardState::setState(KeyboardState* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called State::KeyboardState->setState(KeyboardState*) on a null pointer!", true);
        return;
    }

    for (int i = 0; i < this->keyStatesLength; i++)
        this->keyStates[i] = state->keyStates[i];

    return;

}

bool* Gui::State::KeyboardState::getKeyRef(KeyCode keyCode) {

    /*
        Returns a pointer to the key boolean value within the instance variables
        This is reused in other instance functions
    */
    
    // Invalid value
    if ( (int) keyCode > 0xFF ) return nullptr;

    return &(this->keyStates[ (int) keyCode ]);

}

void Gui::State::KeyboardState::keyDown(KeyCode keyCode) {

    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = true;

    return;

}

void Gui::State::KeyboardState::keyUp(KeyCode keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = false;

    return;

}

bool Gui::State::KeyboardState::keyIsDown(KeyCode keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) return (*key) == true;
    else return false;

}



/*  -------------------------------  */
/*  ----------   State   ----------  */
/*  -------------------------------  */

// Contructor
Gui::State::State(HWND hwnd, bool hasChild /* default value = true */) {

    this->newKeyPresses = new KeyCode[3] {KeyCode::NONE, KeyCode::NONE, KeyCode::NONE};
    this->newKeyPressesIndex = 0;

    this->time = new TimeState();
    this->mouse = new MouseState();
    this->keys = new KeyboardState();

    this->hwnd = hwnd;

    if (hasChild) this->lastFrame = new State(hwnd, false);
    else this->lastFrame = nullptr;

}

// Destructor
Gui::State::~State() {
    if (this->newKeyPresses != nullptr) delete[] this->newKeyPresses;
    if (this->time != nullptr)          delete this->time;
    if (this->mouse != nullptr)         delete this->mouse;
    if (this->keys != nullptr)          delete this->keys;
    if (this->lastFrame != nullptr)     delete this->lastFrame;
}

// Instance functions
int Gui::State::handleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {

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

    // If the message was not handled in the switch, return 1 to signify this
    return 2;

}

void Gui::State::nextFrame() {

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

bool Gui::State::wasLeftJustPressed() {
    return (this->mouse->leftButtonIsDown && !this->lastFrame->mouse->leftButtonIsDown);
}

bool Gui::State::wasRightJustPressed() {
    return (this->mouse->rightButtonIsDown && !this->lastFrame->mouse->rightButtonIsDown);
}

bool Gui::State::wasLeftHeld() {

    return (
        this->mouse->leftButtonIsDown &&
        this->lastFrame->mouse->leftButtonIsDown
    );

}

bool Gui::State::wasRightHeld() {

    return (
        this->mouse->rightButtonIsDown &&
        this->lastFrame->mouse->rightButtonIsDown
    );

}

bool Gui::State::wasLeftJustReleased() {
    return (!this->mouse->leftButtonIsDown && this->lastFrame->mouse->leftButtonIsDown);
}

bool Gui::State::wasRightJustReleased() {
    return (!this->mouse->rightButtonIsDown && this->lastFrame->mouse->rightButtonIsDown);
}

void Gui::State::updateMousePos() {

    POINT point;

    GetCursorPos(&point);
    ScreenToClient(this->hwnd, &point);

    this->mouse->posX = point.x;
    this->mouse->posY = point.y;

}

int Gui::State::deltaMousePosX() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posX) - (this->lastFrame->mouse->posX);
}

int Gui::State::deltaMousePosY() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posY) - (this->lastFrame->mouse->posY);
}

bool Gui::State::keyIsDown(KeyCode keyCode) {
    return this->keys->keyIsDown(keyCode);
}

bool Gui::State::keyJustDown(KeyCode keyCode) {

    bool isDown = this->keys->keyIsDown(keyCode);
    bool wasDown = this->lastFrame->keys->keyIsDown(keyCode);

    return (isDown && !wasDown);

}

void Gui::State::setState(State* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called State->setState(State*) on a null pointer!", true);
        return;
    }

    this->mouse->setState(state->mouse);
    this->keys->setState(state->keys);
}
