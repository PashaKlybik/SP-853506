// lab12_event.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab12_event.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


HWND hMainWnd;
int width = 700;
int height = 500;

#define MODE 0 //change mode 0 - event; other - critical section
HANDLE thread1, thread2, thread3;

HANDLE hEvent1, hEvent2, hEvent3;
DWORD WINAPI ChangeColor_1();
DWORD WINAPI ChangeColor_2();
DWORD WINAPI ChangeColor_3();

int color = 0;

int color_1 = 0;
int color_2 = 1;
int color_3 = 2;



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
    LoadStringW(hInstance, IDC_LAB12EVENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB12EVENT));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB12EVENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB12EVENT);
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

   hEvent1 = CreateEvent(NULL, FALSE, TRUE, NULL);
   hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
   hEvent3 = CreateEvent(NULL, FALSE, FALSE, NULL);
   thread1 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeColor_1, &color_1, 0, NULL);
   thread2 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeColor_2, &color_2, 0, NULL);
   thread3 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)ChangeColor_3, &color_3, 0, NULL);

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
        switch (wmId)
        {

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_SIZE:
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
        switch (color)
        {
        case 0:
            hBrush = CreateSolidBrush(RGB(0, 0, 255));
            break;
        case 1:
            hBrush = CreateSolidBrush(RGB(255, 0, 0));
            break;
        case 2:
            hBrush = CreateSolidBrush(RGB(0, 255, 0));
            break;
        default:
            break;
        }
        SelectObject(hdc, hBrush);
        Rectangle(hdc, -1, -1, width + 1, height + 1);
        DeleteObject(hBrush);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, TRUE);
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
DWORD WINAPI ChangeColor_1()
{
    while (true)
    {
        WaitForSingleObject(hEvent1, INFINITE);
        color = 0;
        Sleep(1000);
        InvalidateRect(hMainWnd, NULL, TRUE);
        SetEvent(hEvent2);
    }
    return 0;
}

DWORD WINAPI ChangeColor_2()
{
    while (true)
    {
        WaitForSingleObject(hEvent2, INFINITE);
        color = 1;
        Sleep(1000);
        InvalidateRect(hMainWnd, NULL, TRUE);
        SetEvent(hEvent3);
    }
    return 0;
}

DWORD WINAPI ChangeColor_3()
{
    while (true)
    {
        WaitForSingleObject(hEvent3, INFINITE);
        color = 2;
        Sleep(1000);
        InvalidateRect(hMainWnd, NULL, TRUE);
        SetEvent(hEvent1);
    }
    return 0;
}