#include "framework.h"
#include "lab6.h"
#include <math.h>

#define MAX_LOADSTRING 100
#define BUTTON_START 1
#define BUTTON_END 2

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//
DWORD WINAPI MoveCircle_1();
DWORD WINAPI MoveCircle_2();
DWORD WINAPI MoveCircle_3();
DWORD WINAPI MoveCircle_4();
DWORD WINAPI MoveCircle_5();
DWORD WINAPI MoveCircle_6();


int x_1 = 0, x_2 = 0, x_3 = 0, x_4 = 0, x_5 = 0, x_6 = 0;
int y_1 = 0, y_2 = 0, y_3 = 0, y_4 = 0, y_5 = 0, y_6 = 0;
int deg_1 = 0, deg_2 = 30, deg_3 = 60, deg_4 = 120, deg_5 = 150, deg_6=180;
int circle_rad_1 = 30, circle_rad_2 = 40, circle_rad_3 = 20, circle_rad_4 = 50, circle_rad_5 = 30, circle_rad_6 = 40;
int pos_rad_1 = 100, pos_rad_2 = 150, pos_rad_3 = 100, pos_rad_4 = 170, pos_rad_5 = 220, pos_rad_6 = 190;

int c_pos_x = 600, c_pos_y = 300;

#define TIMER_ID 1
#define TIMER_DELAY 20

bool animStarted = false;
int width = 700;
int height = 500;


HANDLE thread1, thread2, thread3, thread4, thread5, thread6;
HWND hStart, hStop;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB6);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    thread1 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveCircle_1, NULL, 0, NULL);
    SuspendThread(thread1);

    thread2 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveCircle_2, NULL, 0, NULL);
    SuspendThread(thread2);

    thread3 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveCircle_3, NULL, 0, NULL);
    SuspendThread(thread3);

    thread4 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveCircle_4, NULL, 0, NULL);
    SuspendThread(thread4);

    thread5 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveCircle_5, NULL, 0, NULL);
    SuspendThread(thread5);

    thread6 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveCircle_6, NULL, 0, NULL);
    SuspendThread(thread6);
    hStart = CreateWindow(L"BUTTON", L"Start", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        340, 40, 80, 30, hWnd, (HMENU)BUTTON_START, hInstance, NULL);

    hStop = CreateWindow(L"BUTTON", L"Stop", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
        190, 40, 80, 30, hWnd, (HMENU)BUTTON_END, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmEvent)
        {
        case BN_CLICKED:
            switch (wmId)
            {
            case BUTTON_START:
                if (!animStarted)
                {
                    ResumeThread(thread1);
                    ResumeThread(thread2);
                    ResumeThread(thread3);
                    ResumeThread(thread4);
                    ResumeThread(thread5);
                    ResumeThread(thread6);
                    SetTimer(hWnd, TIMER_ID, TIMER_DELAY, NULL);
                    animStarted = true;
                }
                break;
            case BUTTON_END:
                if (animStarted)
                {
                    SuspendThread(thread1);
                    SuspendThread(thread2);
                    SuspendThread(thread3);
                    SuspendThread(thread4);
                    SuspendThread(thread5);
                    SuspendThread(thread6);
                    KillTimer(hWnd, TIMER_ID);
                    animStarted = false;
                }
                break;
            default:
                break;
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
        }
        break;
    case WM_TIMER:
        if (animStarted)
        {
            InvalidateRect(hWnd, NULL, TRUE);
            SetTimer(hWnd, TIMER_ID, TIMER_DELAY, NULL);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        HPEN pen;
        HBRUSH brush;
        brush = CreateSolidBrush(RGB(224, 14, 48));
        SelectObject(hdc, brush);
        Ellipse(hdc, x_1 - circle_rad_1, y_1 + circle_rad_1, x_1 + circle_rad_1, y_1 - circle_rad_1);

        Ellipse(hdc, x_2 - circle_rad_2, y_2 + circle_rad_2, x_2 + circle_rad_2, y_2 - circle_rad_2);

        Ellipse(hdc, x_3 - circle_rad_3, y_3 + circle_rad_3, x_3 + circle_rad_3, y_3 - circle_rad_3);

        Ellipse(hdc, x_4 - circle_rad_4, y_4 + circle_rad_4, x_4 + circle_rad_4, y_4 - circle_rad_4);

        Ellipse(hdc, x_5 - circle_rad_5, y_5 + circle_rad_5, x_5 + circle_rad_5, y_5 - circle_rad_5);

        Ellipse(hdc, x_6 - circle_rad_6, y_6 + circle_rad_6, x_6 + circle_rad_6, y_6 - circle_rad_6);

        EndPaint(hWnd, &ps);
        break;
    case WM_SIZE:
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

double DegToRadian(int deg) {
    return 1.0 * (deg * 3.1415926535 / 180);
}

DWORD WINAPI MoveCircle_1() {
    while (true)
    {
        double radian = DegToRadian(deg_1);
        deg_1 = (deg_1 + 2) % 360;
        x_1 = c_pos_x + sin(radian) * pos_rad_1;
        y_1 = c_pos_y - cos(radian) * pos_rad_1;
        Sleep(TIMER_DELAY);
    }
    return 0;
}

DWORD WINAPI MoveCircle_2() {
    while (true)
    {
        double radian = DegToRadian(deg_2);
        deg_2 = (deg_2 + 2) % 360;
        x_2 = c_pos_x + sin(radian) * pos_rad_2;
        y_2 = c_pos_y - cos(radian) * pos_rad_2;
        Sleep(TIMER_DELAY);
    }
    return 0;
}

DWORD WINAPI MoveCircle_3() {
    while (true)
    {
        double radian = DegToRadian(deg_3);
        deg_3 = (deg_3 + 2) % 360;
        x_3 = c_pos_x + sin(radian) * pos_rad_3;
        y_3 = c_pos_y - cos(radian) * pos_rad_3;
        Sleep(TIMER_DELAY);
    }
    return 0;
}

DWORD WINAPI MoveCircle_4() {
    while (true)
    {
        double radian = DegToRadian(deg_4);
        deg_4 = (deg_4 + 2) % 360;
        x_4 = c_pos_x + sin(radian) * pos_rad_4;
        y_4 = c_pos_y - cos(radian) * pos_rad_4;
        Sleep(TIMER_DELAY);
    }
    return 0;
}

DWORD WINAPI MoveCircle_5() {
    while (true)
    {
        double radian = DegToRadian(deg_5);
        deg_5 = (deg_5 + 2) % 360;
        x_5 = c_pos_x + sin(radian) * pos_rad_5;
        y_5 = c_pos_y - cos(radian) * pos_rad_5;
        Sleep(TIMER_DELAY);
    }
    return 0;
}

DWORD WINAPI MoveCircle_6() {
    while (true)
    {
        double radian = DegToRadian(deg_6);
        deg_6 = (deg_6 + 2) % 360;
        x_6 = c_pos_x + sin(radian) * pos_rad_6;
        y_6 = c_pos_y - cos(radian) * pos_rad_6;
        Sleep(TIMER_DELAY);
    }
    return 0;
}