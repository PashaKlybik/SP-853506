#include <iostream>

    #ifndef UNICODE
    #define UNICODE
    #endif

#include <windows.h>

#include "Constants.h"
#include "Actions.h"
#include "Views.h"

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample";
    WNDCLASS wc = {};
    wc.hInstance = hinstance;
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Sample window title",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, WIDTH + 15, HEIGHT,
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

void AddPressed() {
    int length = GetWindowTextLengthW(views.input) + 1;
    auto item = new WCHAR[length];
    GetWindowText(views.input, item, length);
    if (Add(item)) {
        SendMessage(views.listLeft, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(item));
    }
    delete[] item;
    SetWindowText(views.input, L"");
}

void DeletePressed() {
    auto index = SendMessage(views.listLeft, LB_GETCURSEL, 0, 0);
    if (index == LB_ERR) return;
    SendMessage(views.listLeft, LB_DELETESTRING, index, 0);
    auto rIndex = FindRight(index);
    if (rIndex != -1) {
        SendMessage(views.listRight, LB_DELETESTRING, rIndex, 0);
    }
    Delete(index);
}

void ToRightPressed() {
    auto index = SendMessage(views.listLeft, LB_GETCURSEL, 0, 0);
    if (index == LB_ERR) return;
    auto item = ToRight(index);
    if (item != nullptr) {
        SendMessage(views.listRight, LB_ADDSTRING, 0, (LPARAM) item);
    }
}

void ClearPressed() {
    SendMessage(views.listLeft , LB_RESETCONTENT , 0 , 0);
    SendMessage(views.listRight , LB_RESETCONTENT , 0 , 0);
    Clear();
}

void ButtonPressed(WPARAM from) {
    switch (from) {
        case ADD_ID:
            AddPressed();
            break;
        case CLEAR_ID:
            ClearPressed();
            break;
        case TO_RIGHT_ID:
            ToRightPressed();
            break;
        case DELETE_ID:
            DeletePressed();
            break;
    }
}


LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    PAINTSTRUCT ps;
    HDC hdc;
    auto gray = RGB(230, 230, 230);
    switch (Message) {
        case WM_CREATE:
            InitView(((LPCREATESTRUCT) lparam)->hInstance, hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            ButtonPressed(wparam);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}

