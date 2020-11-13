// Lab8.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab8.h"

#define MAX_LOADSTRING 100
#define DRAW_ID 1
#define CLEAR_ID 2

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


HWND hButtonDraw, hButtonClear;
bool isPictureVisible = false;

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
    LoadStringW(hInstance, IDC_LAB8, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB8));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB8));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB8);
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
   hButtonDraw = CreateWindow(L"BUTTON", NULL, BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       40, 40, 60, 60, hWnd, (HMENU)DRAW_ID, hInstance, NULL);

   hButtonClear = CreateWindow(L"BUTTON", NULL, BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       160, 40, 60, 60, hWnd, (HMENU)CLEAR_ID, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

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
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
             case DRAW_ID:
                    isPictureVisible = true;
                    InvalidateRect(hWnd, NULL, true);
                    break;
            case CLEAR_ID:
                    isPictureVisible = false;
                    InvalidateRect(hWnd, NULL, true);
                    break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DRAWITEM:
    {
        DRAWITEMSTRUCT* draw = (DRAWITEMSTRUCT*)lParam;
        HBRUSH brush;
        HPEN pen;

        switch (draw->CtlID)
        {
        case DRAW_ID:
        {
            HDC hdc = draw->hDC;
            if (draw->itemAction == ODA_SELECT) {
                brush = CreateSolidBrush(RGB(0, 0, 255));
            }
            else {
                brush = CreateSolidBrush(RGB(0, 255, 0));
            }
            pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

            SelectObject(hdc, brush);
            SelectObject(hdc, pen);

            Ellipse(hdc, 0, 0, 60, 60);
            MoveToEx(hdc, 13, 31, NULL);
            LineTo(hdc, 24, 43);
            LineTo(hdc, 49, 19);
        }
        break;
        case CLEAR_ID:
        {
            HDC hdc = draw->hDC;
            if (draw->itemAction == ODA_SELECT) {
                brush = CreateSolidBrush(RGB(0, 0, 255));
            }
            else {
                brush = CreateSolidBrush(RGB(255, 0, 0));
            }
            pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

            SelectObject(hdc, brush);
            SelectObject(hdc, pen);

            Ellipse(hdc, 0, 0, 60, 60);
            MoveToEx(hdc, 20, 20, NULL);
            LineTo(hdc, 40, 40);
            MoveToEx(hdc, 40, 20, NULL);
            LineTo(hdc, 20, 40);
        }
        break;
        default:
            break;
        }
        break;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HBRUSH brush;
            HPEN pen;
            if (isPictureVisible)
            {
                brush = CreateSolidBrush(RGB(50, 50, 50));
                SelectObject(hdc, brush);

                Ellipse(hdc, 160, 360, 280, 480);
                Ellipse(hdc, 400, 360, 520, 480);

                brush = CreateSolidBrush(RGB(255, 133, 0));
                SelectObject(hdc, brush);
                pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
                SelectObject(hdc, pen);

                POINT p[16] = { 290, 420,
                    390, 420, 400, 350, 510, 350, 530, 420,
                    540, 420, 540, 300, 400, 290,
                    380, 150,
                    300, 150,
                    280, 290, 140, 300, 140, 420,
                    150, 420, 170, 350, 280, 350
                };
                Polygon(hdc, p, 16);

                pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                brush = CreateSolidBrush(RGB(149, 184, 242));
                SelectObject(hdc, brush);

                POINT p2[3] = { 350, 170, 350, 285, 385, 285 };
                Polygon(hdc, p2, 3);

                POINT p3[3] = { 330, 170, 330, 285, 295, 285 };
                Polygon(hdc, p3, 3);

                pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                MoveToEx(hdc, 340, 150, NULL);
                LineTo(hdc, 340, 420);
            }
            EndPaint(hWnd, &ps);
        }
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
