#ifndef FrameStateClass
#define FrameStateClass

#include <SDL2/SDL.h>

class FrameState {

    public:

        class MouseState {
            
            public:

                // Instance variables
                bool leftButtonIsDown;
                bool rightButtonIsDown;
                bool middleButtonIsDown;
                int posX;
                int posY;

                // Contructor
                MouseState();
                
                // Instance functions
                void setState(MouseState* state);
                void leftButtonDown();
                void leftButtonUp();
                void middleButtonDown();
                void middleButtonUp();
                void rightButtonDown();
                void rightButtonUp();
                void setPos(int x, int y);

        };

        class KeyboardState {

            public:

                // Instance variables
                bool* letterKeys;
                bool* numKeys;
                bool* miscKeys;

                // Constructor
                KeyboardState();

                // Destructor
                ~KeyboardState();

                // Instance variables
                void setState(KeyboardState* state);
                bool* getKeyRef(int keyCode);
                void keyDown(int keyCode);
                void keyUp(int keyCode);
                bool keyIsDown(int keyCode);

            private:

                // Indexes for each key
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

                enum miscKeyIndex : int {
                    space = 0,
                    control = 1,
                    shift = 2,
                    alt = 3,
                    capslock = 4,
                    tab = 5,
                    enter = 6,
                    escape = 7,
                    backspace = 8
                };

        };

        // Instance variables
        int frameCount;
        MouseState* mouse;
        KeyboardState* keys;
        FrameState* lastFrame;

        // Contructor
        FrameState(bool hasChild = true);

        // Destructor
        ~FrameState();

        // Instance functions
        void addEvent(SDL_Event* event);
        void nextFrame();
        bool wasLeftJustPressed();
        bool wasRightJustPressed();
        bool wasLeftJustReleased();
        bool wasRightJustReleased();
        int deltaMousePosX();
        int deltaMousePosY();
        bool keyIsDown(int keyCode);
        
    private:

        void setState(FrameState* state);

};

#endif