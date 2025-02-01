#pragma once

#include "util/Utility.h"

// This is the list of keycodes my program tracks.
// These values coorespond to both the given values from Windows, as well as the indexing of the keyStates array
enum KeyCode : unsigned int {

    // Null
    KEY_NULL = 0x00,

    // Letter Keys
    KEY_A = 0x41,
    KEY_B = 0x42,
    KEY_C = 0x43,
    KEY_D = 0x44,
    KEY_E = 0x45,
    KEY_F = 0x46,
    KEY_G = 0x47,
    KEY_H = 0x48,
    KEY_I = 0x49,
    KEY_J = 0x4A,
    KEY_K = 0x4B,
    KEY_L = 0x4C,
    KEY_M = 0x4D,
    KEY_N = 0x4E,
    KEY_O = 0x4F,
    KEY_P = 0x50,
    KEY_Q = 0x51,
    KEY_R = 0x52,
    KEY_S = 0x53,
    KEY_T = 0x54,
    KEY_U = 0x55,
    KEY_V = 0x56,
    KEY_W = 0x57,
    KEY_X = 0x58,
    KEY_Y = 0x59,
    KEY_Z = 0x5A,

    // Number Keys
    KEY_0 = 0x30,
    KEY_1 = 0x31,
    KEY_2 = 0x32,
    KEY_3 = 0x33,
    KEY_4 = 0x34,
    KEY_5 = 0x35,
    KEY_6 = 0x36,
    KEY_7 = 0x37,
    KEY_8 = 0x38,
    KEY_9 = 0x39,

    // Misc Keys
    KEY_SPACE = 0x20,
    KEY_TAB = 0x09,
    KEY_ENTER = 0x0D,
    KEY_ESCAPE = 0x1B,
    KEY_BACKSPACE = 0x08,
    KEY_CAPSLOCK = 0x14,
    KEY_PERIOD = 0xBE,
    KEY_MINUS = 0xBD,

    // Function Keys
    KEY_F1 = 0x70,
    KEY_F2 = 0x71,
    KEY_F3 = 0x72,
    KEY_F4 = 0x73,
    KEY_F5 = 0x74,
    KEY_F6 = 0x75,
    KEY_F7 = 0x76,
    KEY_F8 = 0x77,
    KEY_F9 = 0x78,
    KEY_F10 = 0x79,
    KEY_F11 = 0x7A,
    KEY_F12 = 0x7B,

    // Modifier Keys
    KEY_CONTROL = 0x11,
    KEY_SHIFT = 0x10,
    KEY_ALT = 0xA4,

    // Arrow Keys
    KEY_ARROWUP = 0x26,
    KEY_ARROWDOWN = 0x28,
    KEY_ARROWLEFT = 0x25,
    KEY_ARROWRIGHT = 0x27

};


class State {

    /*
        This class serves to handle events from frame to frame.
        It keeps track of the events currently happening on this frame, and which events happened last frame.
        Subclasses MouseState and KeyboardState keep track of their respective events.
    */

    public:

        class TimeState {

            /*
                Stores everything time related needed for the code, in milliseconds.
                This holds current time, delta time since last frame, and fps variables.
                This also holds anything which counts frames.
            */

            public:

                /*   Instance Variables   */

                // Value which increments every frame
                int totalFrameCount;

                // Delta time, in milliseconds, since last frame. requires updateDt() to be called
                double dt;

                // Frames per second
                int fps;
                
                
                // Constructor
                TimeState();

                /*   Instance Functions   */

                // Updates the dt and frameTime variables
                void updateDt();

                // Updates the fps counter, or adds to framesSinceLastSecond
                void updateFps();

                // Does everything for the next frame. Including calling the above functions
                void update();

                // Returns the current time in milliseconds
                double getTimeMillis();

            private:

                // Used for getting time with Windows
                LARGE_INTEGER frequency;
                LARGE_INTEGER frameTime;
                LARGE_INTEGER lastFrameTime;

                // Counts the frames since the last full second
                double framesSinceLastSecond;

                // Saves the last full second + 1 (in ms, so a multiple of 1000) as a tell for when to update fps
                double nextSecondMillis;

                // Sets up the timer
                void initTimer();

        };

        class MouseState {

            /*
                Keeps track of mouse events.
                position (x, y) in pixels, and buttons down.
                Instance functions are for writing, instance variables are for reading.
            */
            
            public:

                // Instance variables
                bool leftButtonIsDown, rightButtonIsDown, middleButtonIsDown;
                int posX, posY;


                // Contructor
                MouseState();
                

                /*   Instance functions   */

                // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
                void setState(MouseState* state);

                // These are SETTERS for all the mouse buttons
                // To GET the value, simply use the variable since its public

                // General
                void buttonDown(WPARAM wParam);
                void buttonUp(WPARAM wParam);

                // Specified
                void leftButtonDown();
                void leftButtonUp();

                void middleButtonDown();
                void middleButtonUp();

                void rightButtonDown();
                void rightButtonUp();

                // Set the (x, y) position of the mouse
                void setPos(int x, int y);

        };

        class KeyboardState {

            /*
                Keeps track of keyboard events.
                Not every key is tracked, but all the common ones are. The list of keys is under private in the enums
                each 'type' of key has its own array, and these arrays are indexed via instance functions which take inputs from the SDL2 keycode system.
            */

            public:

                // Constructor
                KeyboardState();

                // Destructor
                ~KeyboardState();

                /*   Instance variables   */

                // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
                void setState(KeyboardState* state);

                // Returns a pointer to a keystate within one of the instance arrays, based on a given keycode from SDL2
                bool* getKeyRef(KeyCode keyCode);

                // Setters for keys
                void keyDown(KeyCode keyCode);
                void keyUp(KeyCode keyCode);

                // Getter for keys
                bool keyIsDown(KeyCode keyCode);

            private:

                // Instance variable
                bool* keyStates;                        // Holds the states on all keys on the given frame
                const int keyStatesLength = 0x100;      // Just a const value to use in loops and array declarations

        };

        /*   Instance variables   */

        // Stores a set of at most 3 keys which were just pressed this frame. will store the first 3 given by SDL
        KeyCode* newKeyPresses;
        int newKeyPressesIndex;

        // Subclasses
        TimeState* time;
        MouseState* mouse;
        KeyboardState* keys;

        // This is another State object which holds the state of the previous frame.
        // Used to let things happen once, when an event happens, rather than repeating while its held.
        State* lastFrame;

        // Handle to the window. Used for some functions
        HWND hwnd; 


        /*   Constructor   */

        // hasChild determines if the lastFrame instance variable should be created.
        // This is set to true for the version created in the program, then false for the actual lastFrame instance.
        // The option therefore exists to create State with no child, but there is no reason to do this.
        State(HWND hwnd, bool hasChild = true);


        // Destructor
        ~State();


        /*   Instance functions   */

        // Takes a message from Windows, and does the appropriate action. Returns non-zero if the message was not able to be handled
        int handleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        // Updates everything to be ready for the next frame. Makes this become this->lastFrame
        void nextFrame();


        // Checks for single mouse click events. checks if it is pressed on this frame, but wasnt pressed last frame.
        // Or the other way around for releases

        // Returns true when the mouse button is down this frame, but was up last frame
        bool wasLeftJustPressed();
        bool wasRightJustPressed();

        // Returns true when the mouse button is down this frame, and was down last frame
        bool wasLeftHeld();
        bool wasRightHeld();

        // Returns true when the mouse button is up this frame, but was down last frame
        bool wasLeftJustReleased();
        bool wasRightJustReleased();

        // Updates the instance variables for mouse position
        void updateMousePos();

        // Returns the distance in pixels that the mouse has moved since last frame in the respective direction
        int deltaMousePosX();
        int deltaMousePosY();

        // Simply returns the bool for the key state. Does not cross check with lastFrame.
        bool keyIsDown(KeyCode keyCode);

        // Returns true only if the key was pressed this frame, but not last frame
        bool keyJustDown(KeyCode keyCode);

        /*   Static helper functions   */

        static bool hasValidChar(KeyCode key);

        static char keyCodeToChar(KeyCode key);
        
    private:

        // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
        void setState(State* state);

};
