#pragma once

#include "gui/Core.h"


namespace Gui {

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
                    Not every key is tracked, but all the common ones are. You can see the list in the KeyCode enum above
                    There is one master list, of size 256 (keyStatesLength), and this is simply indexed by the hex equivalent of the KeyCode
                */

                public:

                    // Constructor
                    KeyboardState();

                    // Destructor
                    ~KeyboardState();

                    /*   Instance variables   */

                    // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
                    void setState(KeyboardState* state);

                    // Returns a pointer to a keystate within one of the instance arrays, this is based on my KeyCode enum defined above
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

            // Stores a set of at most 3 keys which were just pressed this frame. will store the first 3 given by Windows
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

            
        private:

            // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
            void setState(State* state);

    };

}
