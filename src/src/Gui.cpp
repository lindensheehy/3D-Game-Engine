#include "../include/Gui.h"


// Constructor
Gui::Gui(WindowProcFunc windowProcFunc, int windowWidth, int windowHeight, LPCSTR windowTitle /* default value = "Window" */) {

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->windowTitle = windowTitle;

    this->buffer = new uint32[this->windowWidth * this->windowHeight] {};

    // Get hInstance, since I'm not using WinMain
    this->hInstance = GetModuleHandle(nullptr);

    // Create and register Window Class
    WNDCLASS wc = {};
    wc.lpfnWndProc = windowProcFunc;
    wc.hInstance = this->hInstance;
    wc.lpszClassName = this->windowTitle;

    if (!RegisterClass(&wc)) {
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

    // Set up the BITMAPINFO structure
    this->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    this->bitmapInfo.bmiHeader.biWidth = this->windowWidth;
    this->bitmapInfo.bmiHeader.biHeight = -this->windowHeight;  // Negative to indicate top-down bitmap
    this->bitmapInfo.bmiHeader.biPlanes = 1;
    this->bitmapInfo.bmiHeader.biBitCount = 32;  // 32 bits per pixel
    this->bitmapInfo.bmiHeader.biCompression = BI_RGB;

    this->handleMessages();
    this->flip();

}

// Destructor
Gui::~Gui() {
    delete[] this->buffer;
    DestroyWindow(this->hwnd);
    UnregisterClass(this->windowTitle, this->hInstance);
}

// Instance functions
void Gui::flip() {

    HDC hdc = GetDC(hwnd);
    if (!hdc) return;

    // Create a compatible device context
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, this->windowWidth, this->windowHeight);

    // Select the bitmap into the memory DC
    SelectObject(memDC, hBitmap);

    // Transfer the buffer to the bitmap
    SetDIBitsToDevice(
        memDC, 
        0, 0, 
        this->windowWidth, this->windowHeight, 
        0, 0, 
        0, this->windowHeight, 
        this->buffer, 
        &this->bitmapInfo, 
        DIB_RGB_COLORS
    );

    // Blit the bitmap to the window's device context
    BitBlt(hdc, 0, 0, this->windowWidth, this->windowHeight, memDC, 0, 0, SRCCOPY);

    // Clean up
    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(hwnd, hdc);

    ShowWindow(hwnd, SW_SHOW);

    this->handleMessages();

    return;

}

void Gui::handleMessages() {

    MSG msg;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

        if (msg.message == WM_QUIT) return;
        if (msg.message == WM_PAINT) return;

        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }

    return;

}
