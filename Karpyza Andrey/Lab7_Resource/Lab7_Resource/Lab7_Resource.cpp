// Lab7_Resource.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab7_Resource.h"

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

HANDLE hEvent1, hEvent2;
DWORD WINAPI SetFlag1();
DWORD WINAPI SetFlag2();

int flag = 0;


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
    LoadStringW(hInstance, IDC_LAB7RESOURCE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB7RESOURCE));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_LAB7RESOURCE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB7RESOURCE);
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

    hEvent1 = CreateEvent(NULL, FALSE, TRUE, NULL);
    hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
    thread1 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)SetFlag1, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)SetFlag2, NULL, 0, NULL);

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
    case WM_CREATE:
    {
        auto hListFirst = CreateWindow(TEXT("LISTBOX"), TEXT("List box #1"), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 200, 230, 300, hWnd, (HMENU)ID_LIST, hInst, NULL);
        SetTimer(hWnd, ID_TIMERSEC, 1000, NULL);
        break;
    }
    case WM_COMMAND:
    {
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        break;
    }
    case WM_SIZE:
    {
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        break;
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_TIMER:
    {
        switch (flag) {
        case 0:
            SendMessageW(GetDlgItem(hWnd, ID_LIST), LB_ADDSTRING, 0, (LPARAM)L"First");
            break;
        case 1:
            SendMessageW(GetDlgItem(hWnd, ID_LIST), LB_ADDSTRING, 0, (LPARAM)L"Second");
            break;
        }
        //InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
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
DWORD WINAPI SetFlag1()
{
    while (true)
    {
        WaitForSingleObject(hEvent1, INFINITE);

        flag = 0;

        Sleep(1000);
        InvalidateRect(hMainWnd, NULL, TRUE);
        SetEvent(hEvent2);
    }
    return 0;
}

DWORD WINAPI SetFlag2()
{
    while (true)
    {
        WaitForSingleObject(hEvent2, INFINITE);

        flag = 1;

        Sleep(1000);
        InvalidateRect(hMainWnd, NULL, TRUE);
        SetEvent(hEvent1);
    }
    return 0;
}