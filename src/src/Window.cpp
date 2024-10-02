#include "../include/Window.h"

/* ----------------------------------- */
/* ---------- WindowElement ---------- */
/* ----------------------------------- */

// Constructor
WindowElement::WindowElement(int posx, int posy, int sizex, int sizey) {

    this->pos = new Vec2(posx, posy);
    this->size = new Vec2(sizex, sizey);

    this->children = new LinkedList<WindowElement*>();

}

// Destrcutor
WindowElement::~WindowElement() {

    if (this->pos != nullptr) delete this->pos;
    if (this->size != nullptr) delete this->size;

}

// Instance Functions
void WindowElement::draw(Drawer* drawer, Vec2* offset) {

    // Log becuase this shouldnt be called ever
    logWrite("Called WindowElement->draw()!", true);

}

void WindowElement::addChild(WindowElement* child) {

    this->children->pushBack(child);
    return;

}

void WindowElement::drawChildren(Drawer* drawer, Vec2* offset) {

    for (this->children->iterStart(0); !this->children->iterIsDone(); this->children->iterNext())
        this->children->iterGetObj()->draw(drawer, offset);

}

// Class Functions
WindowElement* WindowElement::createTopBar(int width, const char* title) {

    WindowElement* mainElement = new WindowFilledRect(1, 1, width - 1, 20);
    mainElement->color = Color::LIGHTER;

    WindowElement* titleElement = new WindowText(6, 6, 0, 0, title);
    titleElement->color = Color::WHITE;

    WindowElement* CloseButtonElement = new WindowFilledRect(width - 21, 0, 20, 20);
    CloseButtonElement->color = Color::RED;

    mainElement->addChild(titleElement);
    mainElement->addChild(CloseButtonElement);

    return mainElement;

}

/* -------------------------------------- */
/* ---------- WindowFilledRect ---------- */
/* -------------------------------------- */

WindowFilledRect::WindowFilledRect(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {

    this->endPos = this->pos->copy()->add(this->size);

}

void WindowFilledRect::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);

    drawer->drawRectFilled(this->color, newOffset, newEndPos);
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newEndPos;

}

/* ---------------------------------------- */
/* ---------- WindowOutlinedRect ---------- */
/* ---------------------------------------- */

WindowOutlinedRect::WindowOutlinedRect(int posx, int posy, int sizex, int sizey) : WindowElement(posx, posy, sizex, sizey) {

    this->endPos = this->pos->copy()->add(this->size);

}

void WindowOutlinedRect::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newEndPos = this->endPos->copy()->add(offset);

    drawer->drawRect(this->color, newOffset, newEndPos);
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newEndPos;

}

/* ---------------------------------- */
/* ---------- WindowCircle ---------- */
/* ---------------------------------- */

WindowCircle::WindowCircle(int posx, int posy, int size) : WindowElement(posx, posy, size, size) {

    this->middle = this->size->copy()->scale(0.5)->add(this->pos);
    this->radius = size;

}

void WindowCircle::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);
    Vec2* newMiddle = this->middle->copy()->add(offset);

    drawer->drawCircle(this->color, newMiddle, this->radius);
    this->drawChildren(drawer, newOffset);

    delete newOffset;
    delete newMiddle;

}

/* -------------------------------- */
/* ---------- WindowText ---------- */
/* -------------------------------- */

WindowText::WindowText(int posx, int posy, int sizex, int sizey, const char* text) : WindowElement(posx, posy, sizex, sizey) {
    
    this->text = text;

}

void WindowText::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    drawer->drawString(this->color, this->text, newOffset);
    this->drawChildren(drawer, newOffset);

    delete newOffset;

}

/* ----------------------------------- */
/* ---------- WindowTexture ---------- */
/* ----------------------------------- */

WindowTexture::WindowTexture(int posx, int posy, int sizex, int sizey, PNG* texture) : WindowElement(posx, posy, sizex, sizey) {
    
    this->texture = texture;

}

void WindowTexture::draw(Drawer* drawer, Vec2* offset) {

    Vec2* newOffset = this->pos->copy()->add(offset);

    drawer->drawpng(this->texture, newOffset);
    this->drawChildren(drawer, newOffset);

    delete newOffset;

}

/* ---------------------------- */
/* ---------- Window ---------- */
/* ---------------------------- */

// Constructors
Window::Window(int posx, int posy, int sizex, int sizey, int layer /* Default value = 0 */) {

    this->pos = new Vec2(posx, posy);
    this->size = new Vec2(sizex, sizey);
    this->layer = layer;

    this->elements = new LinkedList<WindowElement*>();

    this->endPos = this->pos->copy()->add(this->size);

}

Window::Window(Vec2* pos, Vec2* size, int layer /* Default value = 0 */) {

    this->pos = pos;
    this->size = size;
    this->layer = layer;

    this->endPos = this->pos->copy()->add(this->size);

}

// Destructor
Window::~Window() {

    if (this->pos != nullptr) delete this->pos;
    if (this->size != nullptr) delete this->size;

}

void Window::draw(Drawer* drawer) {

    drawer->drawRectFilled(this->COLOR_BASE, this->pos, this->endPos);
    drawer->drawRect(this->COLOR_ACCENT, this->pos, this->endPos);

    for (this->elements->iterStart(0); !this->elements->iterIsDone(); this->elements->iterNext())
        this->elements->iterGetObj()->draw(drawer, this->pos);

}

void Window::addElement(WindowElement* element) {

    this->elements->pushBack(element);
    return;

}
