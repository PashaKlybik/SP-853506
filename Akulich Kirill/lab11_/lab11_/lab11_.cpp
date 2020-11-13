// lab11_.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab11_.h"

#define MAX_LOADSTRING 100
#define BUTTON_START 1
#define BUTTON_END 2

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//
DWORD WINAPI MoveText_1();
DWORD WINAPI MoveText_2();
DWORD WINAPI MoveText_3();


TCHAR text_1[] = L"I";
TCHAR text_2[] = L"<3";
TCHAR text_3[] = L"ISP";

int x_1 = 0;
int y_1 = 0;
int x_2 = 200;
int y_2 = 100;
int x_3 = 100;
int y_3 = 200;

#define TIMER_ID 1
#define TIMER_DELAY 20

bool animStarted = false;
int width = 700;
int height = 500;


HANDLE thread1, thread2, thread3;
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
    LoadStringW(hInstance, IDC_LAB11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB11));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
   thread1 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveText_1, NULL, 0, NULL);
   SuspendThread(thread1);

   thread2 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveText_2, NULL, 0, NULL);
   SuspendThread(thread2);

   thread3 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveText_3, NULL, 0, NULL);
   SuspendThread(thread3);
   hStart = CreateWindow(L"BUTTON", L"Start", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       340, 40, 80, 30, hWnd, (HMENU)BUTTON_START, hInstance, NULL);

   hStop = CreateWindow(L"BUTTON", L"Stop", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
       190, 80, 80, 30, hWnd, (HMENU)BUTTON_END, hInstance, NULL);

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
        for (int i = 0; i < lstrlen(text_1); ++i) {
            TextOut(hdc, x_1 + i * 20, y_1, &text_1[i], 1);
        }
        for (int i = 0; i < lstrlen(text_2); ++i) {
            TextOut(hdc, x_2 + i * 20, y_2, &text_2[i], 1);
        }
        for (int i = 0; i < lstrlen(text_3); ++i) {
            TextOut(hdc, x_3 + i * 20, y_3, &text_3[i], 1);
        }
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


DWORD WINAPI MoveText_1()
{
    while (true)
    {
        x_1 = (x_1 + 3) % width;
        y_1 = (y_1 + 4) % height;
        Sleep(TIMER_DELAY);
    }
    return 0;
}

DWORD WINAPI MoveText_2()
{
    while (true)
    {
        x_2 = (x_2 - 6) % width;
        if (x_2 < 0)
            x_2 = width;
        y_2 = (y_2 + 5) % height;
        Sleep(TIMER_DELAY);
    }
    return 0;
}

DWORD WINAPI MoveText_3()
{
    while (true)
    {
        x_3 = (x_3 + 7) % width;
        y_3 = (y_3 + 0) % height;
        Sleep(TIMER_DELAY);
    }
    return 0;
}

