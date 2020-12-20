
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include "Constants.h"
#include "State.h"

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

void InitState() {
    BallState[0] = LoadImage(nullptr, L"../s1.bmp", IMAGE_BITMAP, BALL_SIZE, BALL_SIZE, LR_LOADFROMFILE);
    BallState[1] = LoadImage(nullptr, L"../s2.bmp", IMAGE_BITMAP, BALL_SIZE, BALL_SIZE, LR_LOADFROMFILE);
    BallState[2] = LoadImage(nullptr, L"../s3.bmp", IMAGE_BITMAP, BALL_SIZE, BALL_SIZE, LR_LOADFROMFILE);
    BallState[3] = LoadImage(nullptr, L"../s4.bmp", IMAGE_BITMAP, BALL_SIZE, BALL_SIZE, LR_LOADFROMFILE);
}

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

    InitState();

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    SetTimer(hwnd, (UINT_PTR) nullptr, DELAY, nullptr);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void onMouseClick(int x, int y) {
    TX = x - BALL_SIZE / 2;
    TY = y - BALL_SIZE / 2;
}

int GetDelta(int target, int value) {
    return ((target - value) >> 31) * 2 + 1;
}

/// True - needed to repaint , false - not
bool TryMove() {
    if (TX == X && TY == Y) return false;

    if (TX != X) {
        X += GetDelta(TX, X);
    }

    if (TY != Y) {
        Y += GetDelta(TY, Y);
    }

    return true;
}

void DrawBall(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HDC hCompatibleDC = CreateCompatibleDC(hdc);
    SelectObject(hCompatibleDC, BallState[State]);
    StretchBlt(hdc, X, Y, BALL_SIZE, BALL_SIZE, hCompatibleDC, 0, 0, BALL_SIZE, BALL_SIZE, SRCCOPY);
    DeleteDC(hCompatibleDC);
    EndPaint(hwnd, &ps);
}

LRESULT WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    switch (Message) {
        case WM_PAINT:
            DrawBall(hwnd);
            break;
        case WM_TIMER:
            if (TryMove()) {
                State = (State + 1) % 4;
                InvalidateRect(hwnd, nullptr, true);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_LBUTTONUP:
            onMouseClick(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
            break;
        case WM_DRAWITEM:
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}
