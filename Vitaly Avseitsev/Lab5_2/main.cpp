
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include "Constants.h"
#include "State.h"

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample";

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
            NAME,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
            nullptr,
            nullptr,
            hinstance,
            nullptr
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);


    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void TryDraw(HWND hwnd) {
    if (!params.isDraw) return;

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HBRUSH brush = CreateSolidBrush(params.selectedColor);
    SelectObject(hdc, brush);

    HPEN pen = CreatePen(BS_SOLID, 0, params.selectedColor);
    SelectObject(hdc, pen);


    POINT p[4] = {x, y - 10, x + 5, y, x, y + 10, x - 5, y};
    POINT s[6] = {x - 3, y + 5, x + 5, y - 1, x - 5, y - 1, x + 3, y + 5, x, y - 5, x - 3, y + 5};

    switch (params.selectedShape) {
        case CIRCLE_ID:
            Ellipse(hdc, x, y, x + 10, y + 10);
            break;
        case SQUARE_ID:
            Rectangle(hdc, x, y, x + 10, y + 10);
            break;
        case RHOMBUS_ID:
            Polygon(hdc, p, 4);
            break;
        case STAR_ID:
            Polyline(hdc, s, 6);
            break;
    }

    EndPaint(hwnd, &ps);
}

void UpdateState(LPARAM src) {
    auto received = (PCOPYDATASTRUCT) src;
    auto data = (DrawParams *) received->lpData;
    params.isDraw = data->isDraw;
    params.selectedShape = data->selectedShape;
    params.selectedColor = data->selectedColor;
}

LRESULT WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    switch (Message) {
        case WM_PAINT:
            TryDraw(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COPYDATA:
            UpdateState(lparam);
            break;
        case WM_LBUTTONUP:
            x = GET_X_LPARAM(lparam);
            y = GET_Y_LPARAM(lparam);
            InvalidateRect(hwnd, nullptr, true);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}
