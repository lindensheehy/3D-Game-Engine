#pragma once

#include "graphics/gui/Core.h"


namespace Graphics {
namespace Gui {

class State {

    /*
        This class serves to handle events from frame to frame.
        It keeps track of the events currently happening on this frame, and which events happened last frame.
        Subclasses MouseState and KeyboardState keep track of their respective events.

        Also contains subclass TimeState, which offers utility functions for time
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

                void updateDt();

                // Updates the fps counter, or increments framesSinceLastSecond
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

                // Sets up the timer that allows getTimeMillis() to work
                void initTimer();

        };

        class MouseState {

            /*
                Keeps track of mouse events.
                position (x, y) in pixels, and button states.
                Instance functions are for writing data states, instance variables are for reading.
            */
            
            public:

                /*   Instance variables   */
                
                bool leftButtonIsDown, rightButtonIsDown, middleButtonIsDown;
                int posX, posY;


                // Contructor
                MouseState();
                

                /*   Instance Functions   */

                // Basically a 'set-all' function. It sets every instance variable of this instance to that of another instance.
                void setState(MouseState* state);

                // These are SETTERS for the mouse button states
                // To GET the states, simply use the member variables

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
                Not every key is tracked, but all the common ones are (see util/KeyCodes.h)
                There is one master array, of size 256 (keyStatesLength). The array is indexed by the KeyCode int value
            */

            public:

                // Constructor
                KeyboardState();

                // Destructor
                ~KeyboardState();


                /*   Instance Functions   */

                // Basically a 'set-all' function. It sets every instance variable of this instance to that of another instance.
                void setState(KeyboardState* state);

                // Returns a pointer to a keystate within the master array
                bool* getKeyRef(KeyCode keyCode);

                // Setters for keys
                void keyDown(KeyCode keyCode);
                void keyUp(KeyCode keyCode);

                // Getter for keys
                bool keyIsDown(KeyCode keyCode);

            private:

                // Instance variable
                bool* keyStates;                        // Holds the states on all keys on the given frame
                const int keyStatesLength = 0x100;      // Just a const value to use in loops and array definitions

        };

        /*   Instance Variables   */

        // Subclasses
        TimeState* time;
        MouseState* mouse;
        KeyboardState* keys;

        // This is another State object which holds the state of the previous frame.
        // Used to let things happen once, when an event happens, rather than repeating while its held.
        State* lastFrame;

        // Handle to the window. Used for some functions
        HWND hwnd; 

        // Stores a set of at most 3 keys which were just pressed this frame. Will store the first 3 given by Windows
        KeyCode newKeyPresses[3];
        int newKeyPressesIndex;


        /*   Constructor   */

        // 'hasChild' determines if the 'lastFrame' instance variable should be created.
        // This exists because 'lastFrame' must not contain its own 'lastFrame'
        // The option therefore exists to create a State with no 'lastFrame', but this breaks a lot of functionality.
        State(HWND hwnd, bool hasChild = true);

        // Destructor
        ~State();


        /*   Instance Functions   */

        // Takes a message from Windows, and writes the appropriate data. Returns non-zero if the message was not handled
        int handleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        // Updates everything to be ready for the next frame. Should be called at the end of each frame
        void nextFrame();

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

        // Returns the distance in pixels that the mouse has moved since last frame
        int deltaMousePosX();
        int deltaMousePosY();

        // Simply returns the bool for the key state. Does not cross check with lastFrame.
        bool keyIsDown(KeyCode keyCode);

        // Returns true only if the key was down this frame, but up last frame
        bool keyJustDown(KeyCode keyCode);

        
    private:

        // Basically a 'set-all' function. It sets every instance variable of this instance, to that of another instance.
        void setState(State* state);

};

}
}
