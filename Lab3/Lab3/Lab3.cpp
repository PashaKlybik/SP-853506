
#include "framework.h"
#include "Lab3.h"

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
bool drawImage = false;

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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB3);
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
    hButtonDraw = CreateWindow(L"BUTTON", NULL, BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        40, 40, 120, 60, hWnd, (HMENU)DRAW_ID, hInstance, NULL);

    hButtonClear = CreateWindow(L"BUTTON", NULL, BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        600, 40, 120, 60, hWnd, (HMENU)CLEAR_ID, hInstance, NULL);
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
            drawImage = true;
            InvalidateRect(hWnd, NULL, true);
            break;
        case CLEAR_ID:
            drawImage = false;
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
                brush = CreateSolidBrush(RGB(228, 228, 228));
            }
            else {
                brush = CreateSolidBrush(RGB(0, 255, 0));
            }
            pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

            SelectObject(hdc, brush);
            SelectObject(hdc, pen);

            Rectangle(hdc, 0, 0, 120, 60);
        }
        break;
        case CLEAR_ID:
        {
            HDC hdc = draw->hDC;
            if (draw->itemAction == ODA_SELECT) {
                brush = CreateSolidBrush(RGB(228, 228, 228));
            }
            else {
                brush = CreateSolidBrush(RGB(255, 0, 0));
            }
            pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

            SelectObject(hdc, brush);
            SelectObject(hdc, pen);

            Rectangle(hdc, 0, 0, 120, 60);

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
        HPEN pen;
        HBRUSH brush;
        if (drawImage)
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
