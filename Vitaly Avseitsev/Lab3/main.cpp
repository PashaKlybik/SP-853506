
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>
#include "Views.h"

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

void SetupAppIcon(HWND__ *hwnd);

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

    SetupAppIcon(hwnd);


    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void SetupAppIcon(HWND__ *hwnd) {
    HANDLE hIcon = LoadImage(nullptr, L"../icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    if (hIcon) {
        //Change both icons to the same icon handle.
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM) hIcon);

        //This will ensure that the application icon gets changed too.
        SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
        SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM) hIcon);
    } else {
        printf("Load image error\n");
    }
}

bool isDraw = false;

void PerformAction(HWND hwnd, WPARAM src) {
    isDraw = src == DRAW_ID;
    InvalidateRect(hwnd, nullptr, true);
}

void DrawImage(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HPEN pen;
    HBRUSH brush;
    if (isDraw) {
        brush = CreateSolidBrush(YELLOW);
        SelectObject(hdc, brush);
        Rectangle(hdc, 260, 400, 420, 200);

        Rectangle(hdc, 300, 260, 380, 220);

        brush = CreateSolidBrush(DARK_GRAY);
        SelectObject(hdc, brush);

        POINT p1[5] = {456, 320, 420, 280, 121, 267, 285, 112, 300, 280};
        Polygon(hdc, p1, 5);

        brush = CreateSolidBrush(GRAY);
        SelectObject(hdc, brush);

        POINT p2[5] = {151, 151, 122, 315, 211, 77, 125, 122, 523, 124};
        Polygon(hdc, p2, 5);

        pen = CreatePen(BS_SOLID, 2, PURPLE);
        SelectObject(hdc, pen);
        MoveToEx(hdc, 305, 320, NULL);
        LineTo(hdc, 305, 280);
        LineTo(hdc, 325, 280);

        pen = CreatePen(BS_SOLID, 0, BLACK);
        SelectObject(hdc, pen);
        brush = CreateSolidBrush(CIAN);
        SelectObject(hdc, brush);
        Ellipse(hdc, 120, 120, 200, 230);
        brush = CreateSolidBrush(PURPLE);
        SelectObject(hdc, brush);
        Ellipse(hdc, 130, 130, 210, 240);
        brush = CreateSolidBrush(BLACK);
        SelectObject(hdc, brush);
        Ellipse(hdc, 125, 125, 205, 235);

        pen = CreatePen(BS_SOLID, 2, BLACK);
        SelectObject(hdc, pen);

        Arc(hdc, 123, 125, 65, 73, 350, 120, 224, 225);
        Arc(hdc, 123, 456, 456, 123, 350, 120, 224, 225);
    }
    EndPaint(hwnd, &ps);
}

LRESULT WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    switch (Message) {
        case WM_PAINT:
            DrawImage(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            PerformAction(hwnd, wparam);
            break;
        case WM_DRAWITEM:
            DrawView((LPDRAWITEMSTRUCT) lparam);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}
