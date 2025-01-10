#include <windows.h>
#include <stdexcept>

class WindowWrapper {

    public:

        Uint32* pixelBuffer;

        WindowWrapper(int w, int h, const char* title) : hwnd(nullptr), pixelBuffer(nullptr), width(w), height(h) {
            hInstance = GetModuleHandle(nullptr);

            // Register Window Class
            WNDCLASS wc = {};
            wc.lpfnWndProc = StaticWindowProc;
            wc.hInstance = hInstance;
            wc.lpszClassName = "PixelBufferWindowClass";
            RegisterClass(&wc);

            // Create Window
            hwnd = CreateWindowEx(
                0, "PixelBufferWindowClass", title, WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                nullptr, nullptr, hInstance, nullptr
            );
            if (!hwnd) {
                throw std::runtime_error("Failed to create window.");
            }

            // Link this instance to the HWND
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

            // Show the window
            ShowWindow(hwnd, SW_SHOW);

            // Initialize the pixel buffer
            pixelBuffer = new uint32_t[width * height]{};

            // Set up the BITMAPINFO structure
            bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bitmapInfo.bmiHeader.biWidth = width;
            bitmapInfo.bmiHeader.biHeight = -height;  // Negative to indicate top-down bitmap
            bitmapInfo.bmiHeader.biPlanes = 1;
            bitmapInfo.bmiHeader.biBitCount = 32;  // 32 bits per pixel
            bitmapInfo.bmiHeader.biCompression = BI_RGB;
        }

        ~WindowWrapper() {
            delete[] pixelBuffer;
            DestroyWindow(hwnd);
            UnregisterClass("PixelBufferWindowClass", hInstance);
        }

        void ProcessMessages() {
            MSG msg;
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        void SetPixelBuffer(uint32_t* newBuffer) {
            if (newBuffer) {
                std::copy(newBuffer, newBuffer + (width * height), pixelBuffer);
            }
        }

        void Invalidate() {
            InvalidateRect(hwnd, nullptr, FALSE);  // Trigger a redraw
        }

    private:

        int windowWidth, windowHeight;

        const wchar_t* windowTitle;

        HWND hwnd;
        HINSTANCE hInstance;

        BITMAPINFO bitmapInfo;

        // Static Window Procedure (needs to forward messages to class instance)
        static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            WindowWrapper* window = reinterpret_cast<WindowWrapper*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (window) {
                return window->WindowProc(hwnd, uMsg, wParam, lParam);
            }
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        // Instance-specific Window Procedure
        LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            switch (uMsg) {
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                // Render the pixel buffer to the window
                StretchDIBits(
                    hdc, 0, 0, width, height, 0, 0, width, height,
                    pixelBuffer, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY
                );

                EndPaint(hwnd, &ps);
                return 0;
            }
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
            }
        }

};
