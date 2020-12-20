
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

void SetupAppIcon(HWND__ *hwnd);

#define START_ID 1000
#define STOP_ID 1001

#define TIMER_ID 10000

#define HELLO L" Hello world!! "


const int WIDTH = 600;
const int HEIGHT = 600;

HMENU InitMenu() {
    auto menu = CreateMenu();
    AppendMenu(menu, MF_STRING, START_ID, L"Start");
    AppendMenu(menu, MF_STRING, STOP_ID, L"Stop");
    return menu;
}

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

    HMENU menu = InitMenu();

    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Sample window title",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
            nullptr,
            menu,
            hinstance,
            nullptr
    );
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

//
void ButtonPressed(WPARAM from, HWND hwnd) {
    switch (from) {
        case START_ID:
            SetTimer(hwnd, TIMER_ID, 100, nullptr);
            break;
        case STOP_ID:
            KillTimer(hwnd, TIMER_ID);
            break;
    }
}

RECT rcCurrent = {0, 0, 85, 20};
int X = 2;
BOOL fVisible = FALSE;
HDC hdc;

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    PAINTSTRUCT ps;
    RECT rc;

    switch (message) {
        case WM_CREATE:
            GetClientRect(hwnd, &rc);
            OffsetRect(&rcCurrent, rc.right / 2, rc.bottom / 2);
            hdc = GetDC(hwnd);
            SetViewportOrgEx(hdc, rcCurrent.left, rcCurrent.top, nullptr);
            SetROP2(hdc, R2_NOT);
            return 0L;

        case WM_DESTROY:
            KillTimer(hwnd, TIMER_ID);
            PostQuitMessage(0);
            return 0L;

        case WM_SIZE:
            switch (wparam) {
                case SIZE_RESTORED:
                    if (rcCurrent.right > (int) LOWORD(lparam)) {
                        rcCurrent.left = (rcCurrent.right = (int) LOWORD(lparam)) - 20;
                    }
                    if (rcCurrent.bottom > (int) HIWORD(lparam)) {
                        rcCurrent.top = (rcCurrent.bottom = (int) HIWORD(lparam)) - 20;
                    }
            }
            return 0L;
        case WM_TIMER:
            GetClientRect(hwnd, &rc);
            if (rcCurrent.left + X < rc.left ||
                rcCurrent.right + X > rc.right)
                X = -X;
            OffsetRect(&rcCurrent, X, 0);
            SetViewportOrgEx(hdc, rcCurrent.left,
                             rcCurrent.top, nullptr);
            fVisible = TextOut(hdc, 0, 0, HELLO, 15);
            return 0L;

        case WM_ERASEBKGND:
            fVisible = FALSE;
            return DefWindowProc(hwnd, message, wparam, lparam);

        case WM_PAINT:
            BeginPaint(hwnd, &ps);
            if (!fVisible)
                fVisible = TextOut(hdc, 0, 0, HELLO, 15);
            EndPaint(hwnd, &ps);
            return 0L;
        case WM_COMMAND:
            ButtonPressed(wparam, hwnd);
            break;

    }
    return DefWindowProc(hwnd, message, wparam, lparam);
}
