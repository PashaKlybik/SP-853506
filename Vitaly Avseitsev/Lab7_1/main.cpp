
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>
#include "State.h"

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

void InitThreads();

HWND root;

DWORD WINAPI DrawBackground(LPVOID arg) {
    auto data = (ColorThreadParams *) arg;
    while (true) {
        WaitForSingleObject(DrawEvent, INFINITE);
        *data->dest = data->src;
        InvalidateRect(root, nullptr, true);
        Sleep(1000);
        SetEvent(DrawEvent);
        Sleep(100);
    }
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample";

    WNDCLASS wc = {};
    wc.hInstance = hinstance;
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wc.lpszMenuName = nullptr;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    RegisterClass(&wc);
    root = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Sample window title",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
            nullptr,
            nullptr,
            hinstance,
            nullptr
    );

    DrawEvent = CreateEvent(
            nullptr,
            TRUE,
            TRUE,
            EVENT_NAME
    );

    InitThreads();

    ShowWindow(root, nCmdShow);
    UpdateWindow(root);


    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void InitThreads() {
    for (int i = 0; i < THREAD_COUNT; ++i) {
        Threads[i] = CreateThread(
                nullptr,
                0,
                DrawBackground,
                &Colors[i],
                0,
                &ThreadIds[i]
        );
    }
}

void UpdateBackground(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    auto brush = CreateSolidBrush(*color);
    SelectObject(hdc, brush);

    Rectangle(hdc, 0, 0, WIDTH, HEIGHT);

    EndPaint(hwnd, &ps);
}

LRESULT WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    switch (Message) {
        case WM_PAINT:
            UpdateBackground(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}