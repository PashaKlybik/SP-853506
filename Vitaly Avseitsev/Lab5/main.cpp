
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include "Views.h"
#include "../Lab5_2/State.h"

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

const wchar_t CLASS_NAME[] = L"Sample";

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASS wc = {};
    wc.hInstance = hinstance;
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wc.lpszMenuName = nullptr;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);

    RegisterClass(&wc);
    HWND hwnd = CreateWindow(
            CLASS_NAME,
            L"Sample window title",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
            nullptr,
            nullptr,
            hinstance,
            nullptr
    );

    InitView(hwnd, hinstance);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}


void UpdateState(int src, HWND hwnd) {
    switch (src) {
        case DRAW_ID:
            params.isDraw = !params.isDraw;
            break;
        case RED_ID:
            params.selectedColor = RGB(255, 0, 0);
            break;
        case BLUE_ID:
            params.selectedColor = RGB(0, 0, 255);
            break;
        case GREEN_ID:
            params.selectedColor = RGB(0, 255, 0);
            break;
        case RHOMBUS_ID:
        case CIRCLE_ID:
        case SQUARE_ID:
        case STAR_ID:
            params.selectedShape = src;
            break;
    }
    COPYDATASTRUCT pending;
    pending.lpData = &params;
    pending.cbData = sizeof(params);
    pending.dwData = MESSAGE_ID;
    HWND target = FindWindow(CLASS_NAME, SECOND_NAME);
    if (target != nullptr) {
        SendMessage(
                target,
                WM_COPYDATA,
                (WPARAM) (HWND) hwnd,
                (LPARAM) (LPVOID) &pending
        );
    } else {
        MessageBox(hwnd, L"Can't send WM_COPYDATA", L"Error", MB_OK);
    }
}

LRESULT WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    switch (Message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            UpdateState(wparam, hwnd);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}
