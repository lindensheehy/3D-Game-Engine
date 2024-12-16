#pragma once

#include <SDL2/SDL.h>
#include <chrono>

#include "Math.h"

// For logging error cases
#include "Log.h"


class State {

    /*
        This class serves to handle events from frame to frame.
        It keeps track of the events currently happening on this frame, and which events happened last frame.
        Subclasses MouseState and KeyboardState keep track of their respective events.
    */

    public:

        class TimeState {

            /*
                Stores everything time related needed for the code.
                This holds current time, delta time since last frame, and fps variables.
                This also holds anything which counts frames.
            */

            public:

                /*   Instance Variables   */

                // Value which increments every frame
                int totalFrameCount;

                // Time stamps
                double frameTime;
                double lastFrameTime;

                // Delta time since last frame. requires updateDt() to be called
                double dt;

                // Counts the frames since the last full second
                double framesSinceLastSecond;

                // Saves the last full second (multiple of 1000) as a tell for when to update dt
                double nextSecond;

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

                // Instance variables
                bool* letterKeys;
                bool* numKeys;
                bool* miscKeys;

                // Constructor
                KeyboardState();

                // Destructor
                ~KeyboardState();

                /*   Instance variables   */

                // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
                void setState(KeyboardState* state);

                // Returns a pointer to a keystate within one of the instance arrays, based on a given keycode from SDL2
                bool* getKeyRef(int keyCode);

                // Setters for keys
                void setKeyDown(int keyCode);
                void setKeyUp(int keyCode);

                // Getter for keys
                bool keyDown(int keyCode);

            private:

                // Indexes for each key
                const int letterKeyCount = 26;
                enum letterKeyIndex : int {
                    a = 0,
                    b = 1,
                    c = 2,
                    d = 3,
                    e = 4,
                    f = 5,
                    g = 6,
                    h = 7,
                    i = 8,
                    j = 9,
                    k = 10,
                    l = 11,
                    m = 12,
                    n = 13,
                    o = 14,
                    p = 15,
                    q = 16,
                    r = 17,
                    s = 18,
                    t = 19,
                    u = 20,
                    v = 21,
                    w = 22,
                    x = 23,
                    y = 24,
                    z = 25
                };

                const int numKeyCount = 10;
                enum numKeyIndex : int {
                    zero = 0,
                    one = 1,
                    two = 2,
                    three = 3,
                    four = 4,
                    five = 5,
                    six = 6,
                    seven = 7,
                    eight = 8,
                    nine = 9
                };

                const int miscKeyCount = 13;
                enum miscKeyIndex : int {
                    space = 0,
                    control = 1,
                    shift = 2,
                    alt = 3,
                    capslock = 4,
                    tab = 5,
                    enter = 6,
                    escape = 7,
                    backspace = 8,
                    arrowup = 9,
                    arrowdown = 10,
                    arrowleft = 11,
                    arrowright = 12,
                };

        };

        /*   Instance variables   */

        // Stores a set of at most 3 keys which were just pressed this frame. will store the first 3 given by SDL
        SDL_Keycode* newKeyPresses;
        int newKeyPressesIndex;

        // Subclasses
        TimeState* time;
        MouseState* mouse;
        KeyboardState* keys;

        // This is another State object which holds the state of the previous frame.
        // Used to let things happen once, when an event happens, rather than repeating while its held.
        State* lastFrame;


        /*   Constructor   */

        // hasChild determines if the lastFrame instance variable should be created.
        // This is set to true for the version created in the program, then false for the actual lastFrame instance.
        // The option therefore exists to create State with no child, but there is no reason to do this.
        State(bool hasChild = true);


        // Destructor
        ~State();


        /*   Instance functions   */

        // Takes an event object from SDL2 and changes the respective value appropriately.
        void addEvent(SDL_Event* event);

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

        // Returns the distance in pixels that the mouse has moved since last frame in the respective direction
        int deltaMousePosX();
        int deltaMousePosY();

        // Simply returns the bool for the key state. Does not cross check with lastFrame.
        bool keyIsDown(int keyCode);

        // Returns true only if the key was pressed this frame, but not last frame
        bool keyJustDown(int keyCode);
        
    private:

        // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
        void setState(State* state);

};
