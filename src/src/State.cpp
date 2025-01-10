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

    this->keyStates = new bool[KEYCODECOUNT] {};
    
    return;

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

    for (int i = 0; i < 26; i++) {

        this->letterKeys[i] = state->letterKeys[i];

        if (i < 10)
            this->numKeys[i] = state->numKeys[i];

        if (i < 9)
            this->miscKeys[i] = state->miscKeys[i];

    }
}

bool* State::KeyboardState::getKeyRef(int keyCode) {

    /*
        Returns a pointer to the key boolean value within the instance variables
        This is reused in other instance functions
    */
    
    switch (keyCode) {

        // Letter keys
        case SDLK_a:
            return &( this->letterKeys[letterKeyIndex::a] );

        case SDLK_b:
            return &( this->letterKeys[letterKeyIndex::b] );

        case SDLK_c:
            return &( this->letterKeys[letterKeyIndex::c] );

        case SDLK_d:
            return &( this->letterKeys[letterKeyIndex::d] );

        case SDLK_e:
            return &( this->letterKeys[letterKeyIndex::e] );

        case SDLK_f:
            return &( this->letterKeys[letterKeyIndex::f] );

        case SDLK_g:
            return &( this->letterKeys[letterKeyIndex::g] );

        case SDLK_h:
            return &( this->letterKeys[letterKeyIndex::h] );

        case SDLK_i:
            return &( this->letterKeys[letterKeyIndex::i] );

        case SDLK_j:
            return &( this->letterKeys[letterKeyIndex::j] );

        case SDLK_k:
            return &( this->letterKeys[letterKeyIndex::k] );

        case SDLK_l:
            return &( this->letterKeys[letterKeyIndex::l] );

        case SDLK_m:
            return &( this->letterKeys[letterKeyIndex::m] );

        case SDLK_n:
            return &( this->letterKeys[letterKeyIndex::n] );

        case SDLK_o:
            return &( this->letterKeys[letterKeyIndex::o] );

        case SDLK_p:
            return &( this->letterKeys[letterKeyIndex::p] );

        case SDLK_q:
            return &( this->letterKeys[letterKeyIndex::q] );

        case SDLK_r:
            return &( this->letterKeys[letterKeyIndex::r] );

        case SDLK_s:
            return &( this->letterKeys[letterKeyIndex::s] );

        case SDLK_t:
            return &( this->letterKeys[letterKeyIndex::t] );

        case SDLK_u:
            return &( this->letterKeys[letterKeyIndex::u] );

        case SDLK_v:
            return &( this->letterKeys[letterKeyIndex::v] );

        case SDLK_w:
            return &( this->letterKeys[letterKeyIndex::w] );

        case SDLK_x:
            return &( this->letterKeys[letterKeyIndex::x] );

        case SDLK_y:
            return &( this->letterKeys[letterKeyIndex::y] );

        case SDLK_z:
            return &( this->letterKeys[letterKeyIndex::z] );


        // Number keys
        case SDLK_0:
            return &( this->numKeys[numKeyIndex::zero] );

        case SDLK_1:
            return &( this->numKeys[numKeyIndex::one] );

        case SDLK_2:
            return &( this->numKeys[numKeyIndex::two] );

        case SDLK_3:
            return &( this->numKeys[numKeyIndex::three] );

        case SDLK_4:
            return &( this->numKeys[numKeyIndex::four] );

        case SDLK_5:
            return &( this->numKeys[numKeyIndex::five] );

        case SDLK_6:
            return &( this->numKeys[numKeyIndex::six] );

        case SDLK_7:
            return &( this->numKeys[numKeyIndex::seven] );

        case SDLK_8:
            return &( this->numKeys[numKeyIndex::eight] );

        case SDLK_9:
            return &( this->numKeys[numKeyIndex::nine] );


        // Misc keys
        case SDLK_BACKSPACE:
            return &( this->miscKeys[miscKeyIndex::backspace] );

        case SDLK_TAB:
            return &( this->miscKeys[miscKeyIndex::tab] );

        case SDLK_RETURN:
            return &( this->miscKeys[miscKeyIndex::enter] );

        case SDLK_ESCAPE:
            return &( this->miscKeys[miscKeyIndex::escape] );

        case SDLK_SPACE:
            return &( this->miscKeys[miscKeyIndex::space] );

        case SDLK_CAPSLOCK:
            return &( this->miscKeys[miscKeyIndex::capslock] );

        case SDLK_LCTRL:
            return &( this->miscKeys[miscKeyIndex::control] );

        case SDLK_LSHIFT:
            return &( this->miscKeys[miscKeyIndex::shift] );

        case SDLK_LALT:
            return &( this->miscKeys[miscKeyIndex::alt] );

        case SDLK_UP:
            return &( this->miscKeys[miscKeyIndex::arrowup] );

        case SDLK_DOWN:
            return &( this->miscKeys[miscKeyIndex::arrowdown] );

        case SDLK_LEFT:
            return &( this->miscKeys[miscKeyIndex::arrowleft] );

        case SDLK_RIGHT:
            return &( this->miscKeys[miscKeyIndex::arrowright] );


    }

    return nullptr;
}

void State::KeyboardState::keyDown(int keyCode) {

    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = true;

    return;

}

void State::KeyboardState::keyUp(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = false;

    return;

}

bool State::KeyboardState::keyIsDown(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) return (*key) == true;
    else return false;

}



/*  ------------------------------------  */
/*  ----------   State   ----------  */
/*  ------------------------------------  */

// Contructor
State::State(bool hasChild /* default value = true */) {

    this->newKeyPresses = new SDL_Keycode[3] {SDLK_UNKNOWN, SDLK_UNKNOWN, SDLK_UNKNOWN};
    this->newKeyPressesIndex = 0;

    this->time = new TimeState();
    this->mouse = new MouseState();
    this->keys = new KeyboardState();

    if (hasChild) this->lastFrame = new State(false);
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
void State::addEvent(UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

        // Handle window close events
        case WM_CLOSE:
        case WM_DESTROY:
            PostQuitMessage(0);
            return;

        // Handle mouse button events
        case WM_MBUTTONDOWN:
            this->mouse->buttonDown(wParam);
            return;

        case WM_MBUTTONUP:
            this->mouse->buttonUp(wParam);

        // Handle keyboard events
        case WM_KEYDOWN:

            // If it wasnt down last frame, add it to newKeyPresses
            if (
                this->lastFrame->keys->keyIsDown(wParam) && 
                this->newKeyPressesIndex < 3
            ) {
                this->newKeyPresses[this->newKeyPressesIndex] = wParam;
                this->newKeyPressesIndex++;
            }

            this->keys->keyDown(wParam);
            return;

        case WM_KEYUP:
            this->keys->keyUp(wParam);
            return;

    }

    return;
}

void State::nextFrame() {

    this->newKeyPresses[0] = SDLK_UNKNOWN;
    this->newKeyPresses[1] = SDLK_UNKNOWN;
    this->newKeyPresses[2] = SDLK_UNKNOWN;
    this->newKeyPressesIndex = 0;

    if (this->lastFrame == nullptr) return;

    this->lastFrame->setState(this);

    this->time->update();

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

int State::deltaMousePosX() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posX) - (this->lastFrame->mouse->posX);
}

int State::deltaMousePosY() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posY) - (this->lastFrame->mouse->posY);
}

bool State::keyIsDown(KeyCode keyCode) {
    return this->keys->keyDown(keyCode);
}

bool State::keyJustDown(KeyCode keyCode) {

    bool isDown = this->keys->keyDown(keyCode);
    bool wasDown = this->lastFrame->keys->keyDown(keyCode);

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
