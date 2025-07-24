#include "graphics/gui/Gui.h"

using namespace Graphics::Gui;


Window::Window(WindowProcFunc windowProcFunc, int windowWidth, int windowHeight, LPCSTR windowTitle) {

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->windowTitle = windowTitle;

    this->buffer = new uint32[PIXEL_BUFFER_WIDTH * PIXEL_BUFFER_HEIGHT];
    memset(this->buffer, 0x00, (PIXEL_BUFFER_WIDTH * PIXEL_BUFFER_HEIGHT) * sizeof(uint32));

    // Get hInstance manually, since I'm not using WinMain
    this->hInstance = GetModuleHandle(nullptr);

    // Create and register the Window Class
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = windowProcFunc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = this->hInstance;
    wc.hIcon = LoadIcon(this->hInstance, MAKEINTRESOURCE(101));
    wc.hIconSm = LoadIcon(this->hInstance, MAKEINTRESOURCE(101));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = this->windowTitle;

    if (!RegisterClassEx(&wc)) {
        logWrite("Failed to create window class", true);
        return;
    }

    // Create Window
    this->hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        this->windowTitle,              // Window class
        this->windowTitle,              // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Position
        0, 0, 
        
        // Size
        windowWidth, windowHeight,

        nullptr,            // Parent window    
        nullptr,            // Menu
        this->hInstance,    // Instance handle
        nullptr             // Additional application data
    );

    if (this->hwnd == NULL) {
        logWrite("Failed to create window.", true);
        return;
    }

    // Show the window
    ShowWindow(this->hwnd, SW_SHOW);

    this->hdc = GetDC(this->hwnd);
    this->memDC = CreateCompatibleDC(this->hdc);
    this->hBitmap = CreateCompatibleBitmap(this->hdc, this->windowWidth, this->windowHeight);
    SelectObject(this->memDC, this->hBitmap);

    // Set up the BITMAPINFO structure
    this->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    this->bitmapInfo.bmiHeader.biWidth = this->windowWidth;
    this->bitmapInfo.bmiHeader.biHeight = -this->windowHeight;  // Negative to indicate top-down bitmap
    this->bitmapInfo.bmiHeader.biPlanes = 1;
    this->bitmapInfo.bmiHeader.biBitCount = 32;  // 32 bits per pixel
    this->bitmapInfo.bmiHeader.biCompression = BI_RGB;

    this->handleMessages();
    this->flip();

    // Load the cursor handles
    this->hCursorArrow = LoadCursor(NULL, IDC_ARROW);
    this->hCursorHand = LoadCursor(NULL, IDC_HAND);
    this->hCursorText = LoadCursor(NULL, IDC_IBEAM);

    return;

}

Window::~Window() {

    delete[] this->buffer;

    DestroyWindow(this->hwnd);
    UnregisterClass(this->windowTitle, this->hInstance);

    return;
    
}

void Window::updateDimensions(int width, int height) {

    if (width > PIXEL_BUFFER_WIDTH) {
        logWrite("Drawer::updateBounds() tried to set the width beyond the max range!", true);
        logWrite(" -> Tried to set ");
        logWrite(width);
        logWrite(" while the max allowed is ");
        logWrite( (int) PIXEL_BUFFER_WIDTH, true );
        return;
    }

    if (height > PIXEL_BUFFER_HEIGHT) {
        logWrite("Drawer::updateBounds() tried to set the height beyond the max range!", true);
        logWrite(" -> Tried to set ");
        logWrite(height);
        logWrite(" while the max allowed is ");
        logWrite( (int) PIXEL_BUFFER_HEIGHT, true );
        return;
    }

    this->windowWidth = width;
    this->windowHeight = height;

    // Get a new bitmap + pause execution
    this->hBitmap = CreateCompatibleBitmap(this->hdc, this->windowWidth, this->windowHeight);
    SelectObject(this->memDC, this->hBitmap);

    // Set up the BITMAPINFO structure
    this->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    this->bitmapInfo.bmiHeader.biWidth = this->windowWidth;
    this->bitmapInfo.bmiHeader.biHeight = -this->windowHeight;  // Negative to indicate top-down bitmap
    this->bitmapInfo.bmiHeader.biPlanes = 1;
    this->bitmapInfo.bmiHeader.biBitCount = 32;  // 32 bits per pixel
    this->bitmapInfo.bmiHeader.biCompression = BI_RGB;

    return;

}

void Window::flip() const {

    if (!this->hdc) return;

    // Transfer the buffer to the bitmap
    SetDIBitsToDevice(
        this->memDC, 
        0, 0, 
        this->windowWidth, this->windowHeight, 
        0, 0, 
        0, this->windowHeight, 
        this->buffer, 
        &this->bitmapInfo, 
        DIB_RGB_COLORS
    );

    // Blit the bitmap to the window's device context
    BitBlt(
        this->hdc, 
        0, 0, 
        this->windowWidth, this->windowHeight, 
        this->memDC, 
        0, 0, 
        SRCCOPY
    );

    this->handleMessages();

    return;

}

void Window::handleMessages() const {

    MSG msg;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

        if (msg.message == WM_QUIT) return;
        if (msg.message == WM_PAINT) return;

        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }

    return;

}

void Window::setCursorState(CursorState cursorState) {

    switch (cursorState) {

        case CURSOR_ARROW:
            SetCursor(this->hCursorArrow);
            break;

        case CURSOR_HAND:
            SetCursor(this->hCursorHand);
            break;

        case CURSOR_TEXT:
            SetCursor(this->hCursorText);
            break;

        default:
            logWrite("setCursorState() wants to set the cursor to an unrecognized state!", true);
            break;

    }

    return;

}
