#pragma once

#include "Vec.h"
#include "Drawer.h"
#include "LinkedList.h"




class WindowElement {

    public:

        /*   Pre Defined Variables   */

        Uint32 color;

        /*   Instance Variables   */

        Vec2* pos; // Relative to parent
        Vec2* size;

        LinkedList<WindowElement*>* children;

        // Constructor
        WindowElement(int posx, int posy, int sizex, int sizey);

        // Destructor
        ~WindowElement();

        /*   Instance Functions   */

        // Offset should be the position of the parent, since all elements are stored in relative positions
        virtual void draw(Drawer* drawer, Vec2* offset);

        void addChild(WindowElement* child);

        /*   Class Functions   */
        
        // Returns a NEW WindowElement for the top bar of a window containing the window title, and the buttons
        static WindowElement* createTopBar(int width, const char* title);

        static WindowElement* createSlider(int width);

        static WindowElement* createTextBox(int width);

    protected:

        // Also used for drawing, only used for CIRCLE types
        Vec2* middle;
        int radius;

        // This function assumes the given offset already accounts for this->pos
        void drawChildren(Drawer* drawer, Vec2* offset);

};


class WindowFilledRect : public WindowElement {

    public:

        // Constructor
        WindowFilledRect(int posx, int posy, int sizex, int sizey);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        // Used for drawing, stores the coordinates of pos + size
        Vec2* endPos;

};


class WindowOutlinedRect : public WindowElement {

    public:

        // Constructor
        WindowOutlinedRect(int posx, int posy, int sizex, int sizey);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        // Used for drawing, stores the coordinates of pos + size
        Vec2* endPos;

};


class WindowCircle : public WindowElement {

    public:

        // Constructor
        WindowCircle(int posx, int posy, int size);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        // Used for drawing, stores the center of the circle and the radius
        Vec2* middle;
        int radius;

};


class WindowText : public WindowElement {

    public:

        // Constructor
        WindowText(int posx, int posy, int sizex, int sizey, const char* text);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        const char* text;

};


class WindowTexture : public WindowElement {

    public:

        // Constructor
        WindowTexture(int posx, int posy, int sizex, int sizey, PNG* texture);

        // Instance Function
        void draw(Drawer* drawer, Vec2* offset) override;

    private:

        PNG* texture;

};


class Window {

    public:

        /*   Pre Defined Variables   */

        Uint32 COLOR_BASE = Color::BACKGROUND;
        Uint32 COLOR_ACCENT = Color::ACCENT;
        Uint32 COLOR_TEXT = Color::BLACK;

        /*   Instance Variables   */

        Vec2* pos;
        Vec2* size;
        int layer; // Front to back - 0 is at the front, 1 behind, and so on

        LinkedList<WindowElement*>* elements;

        // Constructors
        Window(int posx, int posy, int sizex, int sizey, int layer = 0);
        Window(Vec2* pos, Vec2* size, int layer = 0); // References are stored, the Vec2's should not be deleted after calling this

        // Destructor
        ~Window();

        /*   Instance Functions   */

        void draw(Drawer* drawer);

        void addElement(WindowElement* element);

    private:

        Vec2* endPos; // Used for drawing, stores the coordinates of pos + size

};
