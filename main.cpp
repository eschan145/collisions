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
        float dx = (rand() % 5) + 1;
        float dy = (rand() % 5) + 1;

        objects.emplace_back(position, -1, -1);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HDC hdcBuffer;

    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);
        FillRect(hdcBuffer, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        for (const auto& object : objects) {
            object.draw(hdc);
        }

        BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcBuffer, 0, 0, SRCCOPY);

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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "Object Demonstration";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Moving Objects",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    initialize(3, 800, 600);

    SetTimer(hwnd, 1, 16, nullptr);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

extern "C" {
    int main() {
        HINSTANCE hInstance = GetModuleHandle(nullptr);
        return WinMain(hInstance, nullptr, GetCommandLineA(), SW_SHOWNORMAL);
    }
}
