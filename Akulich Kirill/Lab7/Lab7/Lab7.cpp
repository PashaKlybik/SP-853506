// Lab7.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab7.h"

#define MAX_LOADSTRING 100
#define EDIT_FIELD_ID 1
#define ADD_ID 2
#define CLEAR_ID 3
#define TORIGHT_ID 4
#define DELETE_ID 5
#define LIST1_ID 6
#define LIST2_ID 7

HWND hEdit, hButtonAdd, hButtonClear, hButtonToRight, hButtonDelete, hListBox1, hListBox2;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


bool DeleteSelectedItem(HWND hWnd, HWND hListBox);
void ToRight(HWND hWnd);
bool ContainsString(HWND hListBox, TCHAR* s);
void UpdateListBoxScroll(HWND hWnd, HWND hListBox, int itemId);
void AddStringInListBox(HWND hWnd, HWND hListBox, TCHAR* s);
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
    LoadStringW(hInstance, IDC_LAB7, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB7));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB7));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB7);
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
   hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Edit", WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
       40, 40, 280, 30, hWnd, (HMENU)EDIT_FIELD_ID, hInst, NULL);

   hButtonAdd = CreateWindow(L"BUTTON", L"Add", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
       340, 40, 80, 30, hWnd, (HMENU)ADD_ID, hInst, NULL);

   hButtonClear = CreateWindow(L"BUTTON", L"Clear", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
       190, 80, 80, 30, hWnd, (HMENU)CLEAR_ID, hInst, NULL);

   hButtonToRight = CreateWindow(L"BUTTON", L"ToRight", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
       190, 145, 80, 30, hWnd, (HMENU)TORIGHT_ID, hInst, NULL);

   hButtonDelete = CreateWindow(L"BUTTON", L"Delete", WS_TABSTOP | WS_CHILD | WS_VISIBLE,
       190, 210, 80, 30, hWnd, (HMENU)DELETE_ID, hInst, NULL);

   hListBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL | LBS_MULTIPLESEL,
       40, 80, 140, 160, hWnd, (HMENU)LIST1_ID, hInst, NULL);

   hListBox2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | LBS_MULTIPLESEL,
       280, 80, 140, 160, hWnd, (HMENU)LIST2_ID, hInst, NULL);

   SendDlgItemMessage(hWnd, EDIT_FIELD_ID, (UINT)LB_SETHORIZONTALEXTENT, (WPARAM)1024, (LPARAM)0);

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
            //wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);
            switch (wmEvent)
            {
            case BN_CLICKED:
                switch (wmId)
                {
                case ADD_ID:
                    int length;
                    length = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
                    if (length == 0)
                        MessageBox(hWnd, L"Empty input", L"Error", MB_OK);
                    else {
                        TCHAR* buffer = new TCHAR[length];
                        SendMessage(hEdit, WM_GETTEXT, length + 1, (LPARAM)buffer);

                        AddStringInListBox(hWnd, hListBox1, buffer);
                        SetWindowText(GetDlgItem(hWnd, EDIT_FIELD_ID), L"");
                    }
                    break;
                case CLEAR_ID:
                    SendMessage(hListBox1, LB_RESETCONTENT, 0, 0);
                    SendMessage(hListBox2, LB_RESETCONTENT, 0, 0);
                    UpdateListBoxScroll(hWnd, hListBox1, -1);
                    UpdateListBoxScroll(hWnd, hListBox2, -1);
                    break;
                case TORIGHT_ID:
                    ToRight(hWnd);
                    break;
                case DELETE_ID:
                    DeleteSelectedItem(hWnd, hListBox1);
                    DeleteSelectedItem(hWnd, hListBox2);
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
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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

bool DeleteSelectedItem(HWND hWnd, HWND hListBox)
{
    int selCount = SendMessage(hListBox, LB_GETSELCOUNT, 0, 0);
    int countBuffer[100];
    SendMessage(hListBox, LB_GETSELITEMS, 100, (LPARAM)countBuffer);

    for (int i = selCount - 1; i >= 0; --i) {
        int itemId = countBuffer[i];
        SendMessage(hListBox, LB_DELETESTRING, itemId, 0);
    }

    UpdateListBoxScroll(hWnd, hListBox, -1);
    return true;
}

void ToRight(HWND hWnd)
{
    int selCount = SendMessage(hListBox1, LB_GETSELCOUNT, 0, 0);
    int countBuffer[100];
    SendMessage(hListBox1, LB_GETSELITEMS, 100, (LPARAM)countBuffer);

    if (selCount == 0) {
        MessageBox(hWnd, L"Select item in first ListBox", L"Error", MB_OK);
    }
    else {
        for (int i = selCount - 1; i >= 0; --i) {
            int itemId = countBuffer[i];
            TCHAR buffer[256];
            SendMessage(hListBox1, LB_GETTEXT, itemId, (LPARAM)buffer);
            AddStringInListBox(hWnd, hListBox2, buffer);
        }
    }
}

bool ContainsString(HWND hListBox, TCHAR* s)
{
    int count = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
    for (int i = 0; i < count; i++) {
        TCHAR buffer[256];
        CHAR buff[256];
        CHAR t_buff[256];
        size_t nNumCharConverted;
        wcstombs_s(&nNumCharConverted,t_buff, 256,
            s, 256);
        SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)buffer);
        wcstombs_s(&nNumCharConverted, buff, 256,
            buffer, 256);
        if (!strcmp(buff, t_buff))
            return true;
    }
    return false;
}

void UpdateListBoxScroll(HWND hWnd, HWND hListBox, int itemId)
{
    int count = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
    if (count == 0) SendDlgItemMessage(hWnd, hListBox == hListBox1 ? LIST1_ID : LIST2_ID, (UINT)LB_SETHORIZONTALEXTENT, (WPARAM)0, (LPARAM)0);
    TCHAR buffer[256];

    for (int i = 0; i < count; i++) {
        if (i == itemId) continue;
        SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)buffer);
        int SizeOfHBListBox = wcslen(buffer) * 8;
        SendDlgItemMessage(hWnd, hListBox == hListBox1 ? LIST1_ID : LIST2_ID, (UINT)LB_SETHORIZONTALEXTENT, (WPARAM)SizeOfHBListBox, (LPARAM)0);
    }
}

void AddStringInListBox(HWND hWnd, HWND hListBox, TCHAR* s)
{
    if (!ContainsString(hListBox, s)) {
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)s);
        UpdateListBoxScroll(hWnd, hListBox, -1);
    }
}