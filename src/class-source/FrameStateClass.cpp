#include "../class-headers/FrameStateClass.h"


/*  ------------------------------------  */
/*  ----------   MouseState   ----------  */
/*  ------------------------------------  */

// Contructor
FrameState::MouseState::MouseState() {
    this->leftButtonIsDown = false;
    this->rightButtonIsDown = false;
    this->posX = 0;
    this->posY = 0;
}

// Instance functions
void FrameState::MouseState::setState(MouseState* state) {
    this->leftButtonIsDown = state->leftButtonIsDown;
    this->rightButtonIsDown = state->rightButtonIsDown;
    this->middleButtonIsDown = state->middleButtonIsDown;
    this->posX = state->posX;
    this->posY = state->posY;
}

void FrameState::MouseState::leftButtonDown() {
    this->leftButtonIsDown = true;
}

void FrameState::MouseState::leftButtonUp() {
    this->leftButtonIsDown = false;
}

void FrameState::MouseState::middleButtonDown() {
    this->middleButtonIsDown = true;
}

void FrameState::MouseState::middleButtonUp() {
    this->middleButtonIsDown = false;
}

void FrameState::MouseState::rightButtonDown() {
    this->rightButtonIsDown = true;
}

void FrameState::MouseState::rightButtonUp() {
    this->rightButtonIsDown = false;
}

void FrameState::MouseState::setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
}



/*  -------------------------------------  */
/*  ---------   KeyboardState   ---------  */
/*  -------------------------------------  */

// Constructor
FrameState::KeyboardState::KeyboardState() {

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
FrameState::KeyboardState::~KeyboardState() {
    delete[] this->letterKeys;
    delete[] this->numKeys;
    delete[] this->miscKeys;
}

// Instance variables
void FrameState::KeyboardState::setState(KeyboardState* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called FrameState::KeyboardState->setState(KeyboardState*) on a null pointer!", true);
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

bool* FrameState::KeyboardState::getKeyRef(int keyCode) {

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

void FrameState::KeyboardState::keyDown(int keyCode) {

    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = true;

    return;

}

void FrameState::KeyboardState::keyUp(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) (*key) = false;

    return;

}

bool FrameState::KeyboardState::keyIsDown(int keyCode) {
    
    bool* key = this->getKeyRef(keyCode);
    if (key != nullptr) return (*key) == true;
    else return false;

}



/*  ------------------------------------  */
/*  ----------   FrameState   ----------  */
/*  ------------------------------------  */

FrameState::// Contructor
FrameState(bool hasChild /* default value = true */) {

    this->frameCount = 0;
    this->mouse = new MouseState();
    this->keys = new KeyboardState();

    if (hasChild) this->lastFrame = new FrameState(false);
    else this->lastFrame = nullptr;

}

// Destructor
FrameState::~FrameState() {
    if (this->mouse != nullptr) delete this->mouse;
    if (this->keys != nullptr) delete this->keys;
    if (this->lastFrame != nullptr) delete this->lastFrame;
}

// Instance functions
void FrameState::addEvent(SDL_Event* event) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (event == nullptr) {
        logWrite("Called FrameState->addEvent(SDL_Event*) on a null pointer!", true);
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
        this->keys->keyDown((*event).key.keysym.sym);
    }

    // Keyboard buttons up
    if ((*event).type == SDL_KEYUP) {
        this->keys->keyUp((*event).key.keysym.sym);
    }

    return;
}

void FrameState::nextFrame() {

    if (this->lastFrame == nullptr) return;

    this->lastFrame->setState(this);
    this->frameCount++;

    return;

}

bool FrameState::wasLeftJustPressed() {
    return (this->mouse->leftButtonIsDown && !this->lastFrame->mouse->leftButtonIsDown);
}

bool FrameState::wasRightJustPressed() {
    return (this->mouse->rightButtonIsDown && !this->lastFrame->mouse->rightButtonIsDown);
}

bool FrameState::wasLeftJustReleased() {
    return (!this->mouse->leftButtonIsDown && this->lastFrame->mouse->leftButtonIsDown);
}

bool FrameState::wasRightJustReleased() {
    return (!this->mouse->rightButtonIsDown && this->lastFrame->mouse->rightButtonIsDown);
}

int FrameState::deltaMousePosX() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posX) - (this->lastFrame->mouse->posX);
}

int FrameState::deltaMousePosY() {
    if (this->lastFrame == nullptr) return 0;
    return (this->mouse->posY) - (this->lastFrame->mouse->posY);
}

bool FrameState::keyIsDown(int keyCode) {
    return this->keys->keyIsDown(keyCode);
}

void FrameState::setState(FrameState* state) {

    // Address error case, but dont kill the process yet in case its not fatal
    if (state == nullptr) {
        logWrite("Called FrameState->setState(FrameState*) on a null pointer!", true);
        return;
    }

    this->frameCount = state->frameCount;
    this->mouse->setState(state->mouse);
    this->keys->setState(state->keys);
}
