#include "../include/Gui.h"


// Constructor
Gui::Gui(WindowProcFunc windowProcFunc, int windowWidth, int windowHeight, const wchar_t* windowTitle /* default value = "Window" */) {

    this->hwnd = nullptr;
    this->buffer = nullptr;

    this->windowProcFunc = windowProcFunc;

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    this->windowTitle = windowTitle;

    // Get hInstance, since I'm not using WinMain
    this->hInstance = GetModuleHandle(nullptr);

    // Create and register Window Class
    WNDCLASS wc = {};
    wc.lpfnWndProc = windowProcFunc;
    wc.hInstance = this->hInstance;
    wc.lpszClassName = this->windowTitle;
    RegisterClass(&wc);

    // Create Window
    this->hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        this->windowTitle,                    // Window class
        this->windowTitle,                    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        nullptr,        // Parent window    
        nullptr,        // Menu
        this->hInstance,      // Instance handle
        nullptr         // Additional application data
    );

    if (!this->hwnd) {
        logWrite("Failed to create window.", true);
        return;
    }

    // Link this instance to the HWND
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    // Show the window
    ShowWindow(hwnd, SW_SHOW);

    // Initialize the pixel buffer
    this->buffer = new uint32[this->windowWidth * this->windowHeight]{};

    // Set up the BITMAPINFO structure
    this->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    this->bitmapInfo.bmiHeader.biWidth = this->windowWidth;
    this->bitmapInfo.bmiHeader.biHeight = -this->windowHeight;  // Negative to indicate top-down bitmap
    this->bitmapInfo.bmiHeader.biPlanes = 1;
    this->bitmapInfo.bmiHeader.biBitCount = 32;  // 32 bits per pixel
    this->bitmapInfo.bmiHeader.biCompression = BI_RGB;

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

    this->handleMessages();

    return;

}

void Gui::handleMessages() {

    MSG msg;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return;

}