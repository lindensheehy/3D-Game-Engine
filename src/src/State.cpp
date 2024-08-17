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

    this->letterKeys = new bool[26];
    this->numKeys = new bool[10];
    this->miscKeys = new bool[9];

    for (int i = 0; i < 26; i++) {

        this->letterKeys[i] = false;

        if (i < 10) 
            this->numKeys[i] = false;

        if (i < 9) 
            this->miscKeys[i] = false;
            
    }

    return;
}

// Destructor
State::KeyboardState::~KeyboardState() {
    delete[] this->letterKeys;
    delete[] this->numKeys;
    delete[] this->miscKeys;
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
            break;
        case SDLK_b:
            return &( this->letterKeys[letterKeyIndex::b] );
            break;
        case SDLK_c:
            return &( this->letterKeys[letterKeyIndex::c] );
            break;
        case SDLK_d:
            return &( this->letterKeys[letterKeyIndex::d] );
            break;
        case SDLK_e:
            return &( this->letterKeys[letterKeyIndex::e] );
            break;
        case SDLK_f:
            return &( this->letterKeys[letterKeyIndex::f] );
            break;
        case SDLK_g:
            return &( this->letterKeys[letterKeyIndex::g] );
            break;
        case SDLK_h:
            return &( this->letterKeys[letterKeyIndex::h] );
            break;
        case SDLK_i:
            return &( this->letterKeys[letterKeyIndex::i] );
            break;
        case SDLK_j:
            return &( this->letterKeys[letterKeyIndex::j] );
            break;
        case SDLK_k:
            return &( this->letterKeys[letterKeyIndex::k] );
            break;
        case SDLK_l:
            return &( this->letterKeys[letterKeyIndex::l] );
            break;
        case SDLK_m:
            return &( this->letterKeys[letterKeyIndex::m] );
            break;
        case SDLK_n:
            return &( this->letterKeys[letterKeyIndex::n] );
            break;
        case SDLK_o:
            return &( this->letterKeys[letterKeyIndex::o] );
            break;
        case SDLK_p:
            return &( this->letterKeys[letterKeyIndex::p] );
            break;
        case SDLK_q:
            return &( this->letterKeys[letterKeyIndex::q] );
            break;
        case SDLK_r:
            return &( this->letterKeys[letterKeyIndex::r] );
            break;
        case SDLK_s:
            return &( this->letterKeys[letterKeyIndex::s] );
            break;
        case SDLK_t:
            return &( this->letterKeys[letterKeyIndex::t] );
            break;
        case SDLK_u:
            return &( this->letterKeys[letterKeyIndex::u] );
            break;
        case SDLK_v:
            return &( this->letterKeys[letterKeyIndex::v] );
            break;
        case SDLK_w:
            return &( this->letterKeys[letterKeyIndex::w] );
            break;
        case SDLK_x:
            return &( this->letterKeys[letterKeyIndex::x] );
            break;
        case SDLK_y:
            return &( this->letterKeys[letterKeyIndex::y] );
            break;
        case SDLK_z:
            return &( this->letterKeys[letterKeyIndex::z] );
            break;

        // Number keys
        case SDLK_0:
            return &( this->numKeys[numKeyIndex::zero] );
            break;
        case SDLK_1:
            return &( this->numKeys[numKeyIndex::one] );
            break;
        case SDLK_2:
            return &( this->numKeys[numKeyIndex::two] );
            break;
        case SDLK_3:
            return &( this->numKeys[numKeyIndex::three] );
            break;
        case SDLK_4:
            return &( this->numKeys[numKeyIndex::four] );
            break;
        case SDLK_5:
            return &( this->numKeys[numKeyIndex::five] );
            break;
        case SDLK_6:
            return &( this->numKeys[numKeyIndex::six] );
            break;
        case SDLK_7:
            return &( this->numKeys[numKeyIndex::seven] );
            break;
        case SDLK_8:
            return &( this->numKeys[numKeyIndex::eight] );
            break;
        case SDLK_9:
            return &( this->numKeys[numKeyIndex::nine] );
            break;

        // Misc keys
        case SDLK_BACKSPACE:
            return &( this->miscKeys[miscKeyIndex::backspace] );
            break;
        case SDLK_TAB:
            return &( this->miscKeys[miscKeyIndex::tab] );
            break;
        case SDLK_RETURN:
            return &( this->miscKeys[miscKeyIndex::enter] );
            break;
        case SDLK_ESCAPE:
            return &( this->miscKeys[miscKeyIndex::escape] );
            break;
        case SDLK_SPACE:
            return &( this->miscKeys[miscKeyIndex::space] );
            break;
        case SDLK_CAPSLOCK:
            return &( this->miscKeys[miscKeyIndex::capslock] );
            break;
        case SDLK_LCTRL:
            return &( this->miscKeys[miscKeyIndex::control] );
            break;
        case SDLK_LSHIFT:
            return &( this->miscKeys[miscKeyIndex::shift] );
            break;
        case SDLK_LALT:
            return &( this->miscKeys[miscKeyIndex::alt] );
            break;

    }

    return nullptr;
}

void State::KeyboardState::setKeyDown(int keyCode) {

    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = true;

    return;

}

void State::KeyboardState::setKeyUp(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = false;

    return;

}

bool State::KeyboardState::keyDown(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) return (*key) == true;
    else return false;

}



/*  ------------------------------------  */
/*  ----------   State   ----------  */
/*  ------------------------------------  */

// Contructor
State::State(bool hasChild /* default value = true */) {

    this->time = new TimeState();
    this->mouse = new MouseState();
    this->keys = new KeyboardState();

    if (hasChild) this->lastFrame = new State(false);
    else this->lastFrame = nullptr;

}

// Destructor
State::~State() {
    if (this->time != nullptr) delete this->time;
    if (this->mouse != nullptr) delete this->mouse;
    if (this->keys != nullptr) delete this->keys;
    if (this->lastFrame != nullptr) delete this->lastFrame;
}

// Instance functions
void State::addEvent(SDL_Event* event) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (event == nullptr) {
        logWrite("Called State->addEvent(SDL_Event*) on a null pointer!", true);
        return;
    }

    // Mouse buttons down
    if ((*event).type == SDL_MOUSEBUTTONDOWN) {

        if ((*event).button.button == SDL_BUTTON_LEFT) {
            this->mouse->leftButtonDown();
        }

        if ((*event).button.button == SDL_BUTTON_RIGHT) {
            this->mouse->rightButtonDown();
        }

        if ((*event).button.button == SDL_BUTTON_MIDDLE) {
            this->mouse->middleButtonDown();
        }

        return;

    }

    // Mouse buttons up
    if ((*event).type == SDL_MOUSEBUTTONUP) {

        if ((*event).button.button == SDL_BUTTON_LEFT) {
            this->mouse->leftButtonUp();
        }

        if ((*event).button.button == SDL_BUTTON_RIGHT) {
            this->mouse->rightButtonUp();
        }

        if ((*event).button.button == SDL_BUTTON_MIDDLE) {
            this->mouse->middleButtonUp();
        }

        return;

    }

    // Keyboard buttons down
    if ((*event).type == SDL_KEYDOWN) {
        this->keys->setKeyDown((*event).key.keysym.sym);
    }

    // Keyboard buttons up
    if ((*event).type == SDL_KEYUP) {
        this->keys->setKeyUp((*event).key.keysym.sym);
    }

    return;
}

void State::nextFrame() {

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

bool State::keyIsDown(int keyCode) {
    return this->keys->keyDown(keyCode);
}

bool State::keyJustDown(int keyCode) {

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
