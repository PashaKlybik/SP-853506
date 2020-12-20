
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

    HCURSOR hCursor = LoadCursorFromFile(L"../cursor.cur");

    WNDCLASS wc = {};
    wc.hInstance = hinstance;
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wc.lpszMenuName = nullptr;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    if (hCursor) {
        wc.hCursor = hCursor;
    }

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
    if (isDraw)
    {
        brush = CreateSolidBrush(RGB(224, 14, 48));
        SelectObject(hdc, brush);
        Rectangle(hdc, 260, 400, 420, 200);

        brush = CreateSolidBrush(RGB(50, 50, 50));
        SelectObject(hdc, brush);

        Rectangle(hdc, 300, 260, 380, 220);

        pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
        SelectObject(hdc, pen);

        POINT p1[5] = { 270, 320, 270, 280, 285, 280, 285, 295, 270, 280 };
        Polygon(hdc, p1, 5);

        // O-Letter
        MoveToEx(hdc, 305, 320, NULL);
        LineTo(hdc, 305, 280);
        LineTo(hdc, 325, 280);
        LineTo(hdc, 325, 320);
        LineTo(hdc, 305, 320);

        //S-letter
        MoveToEx(hdc, 335, 320, NULL);
        LineTo(hdc, 355, 320);
        LineTo(hdc, 355, 300);
        LineTo(hdc, 335, 300);
        LineTo(hdc, 335, 280);
        LineTo(hdc, 355, 280);

        // T-letter
        MoveToEx(hdc, 365, 280, NULL);
        LineTo(hdc, 385, 280);
        LineTo(hdc, 375, 280);
        LineTo(hdc, 375, 320);


        // Mail-painting
        pen = CreatePen(BS_SOLID, 2, RGB(255, 255, 255));
        SelectObject(hdc, pen);
        MoveToEx(hdc, 270, 330, NULL);
        LineTo(hdc, 270, 380);
        LineTo(hdc, 410, 380);
        LineTo(hdc, 410, 330);
        LineTo(hdc, 270, 330);
        LineTo(hdc, 340, 360);
        LineTo(hdc, 410, 330);
    }else{
        brush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, brush);
        pen = CreatePen(BS_SOLID, 2, RGB(255, 255, 255));
        SelectObject(hdc, pen);
        Rectangle(hdc, 260, 400, 420, 200);
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
