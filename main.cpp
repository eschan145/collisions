#include <windows.h>
#include <vector>
#include <cstdlib>

#include "object.cpp"

std::vector<Object> objects;


void initialize(int count, int width, int height) {
    for (int i = 0; i < count; ++i) {
        Point position = Point(
            rand() % (width - 50),
            rand() % (height - 50));
        int dx = (rand() % 5) + 1;
        int dy = (rand() % 5) + 1;

        objects.emplace_back(position, dx, dy);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        for (const auto& object : objects) {
            object.draw(hdc);
        }

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_TIMER: {
        RECT rect;
        GetClientRect(hwnd, &rect);
        for (auto& obj : objects) {
            obj.update();
            obj.bounce(rect.right, rect.bottom);
        }
        InvalidateRect(hwnd, nullptr, TRUE); // Trigger WM_PAINT
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Entry Point
extern "C" {
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Object Demonstration";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Moving Objects",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    initialize(1000, 800, 600);

    SetTimer(hwnd, 1, 16, nullptr);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
}