#include "framework.h"
#include "lab8.h"
#include <TlHelp32.h>
#include <windowsx.h>

#define MAX_LOADSTRING 100
#define HPROCESSES_ID 10001
#define HMODULES_ID 10002


#define ID_IDLE 10
#define ID_NORMAL 11
#define ID_HIGH 12
#define ID_REAL_TIME 13

// Global Variables:
HINSTANCE hInst;
HWND hProcesses, hModules;
HMENU hPopupMenu;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


HWND hMainWnd;
void ClearListBox(HWND listBox);
void ShowProcesses();
void ShowModules(PROCESSENTRY32 proc);
void SetPriority(DWORD priorityClass);

int width = 700;
int height = 700;

int procCount = 0;
PROCESSENTRY32 procs[500];

int moduleCount = 0;
MODULEENTRY32 modules[500];

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
	LoadStringW(hInstance, IDC_LAB8, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_LAB8));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB8);
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
	hProcesses = CreateWindow(L"LISTBOX", L"Processes", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
		20, 20, 250, 500, hWnd, (HMENU)HPROCESSES_ID, hInst, NULL);
	hModules = CreateWindow(L"LISTBOX", L"Modules", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
		300, 20, 250, 500, hWnd, (HMENU)HMODULES_ID, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	ShowProcesses();

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
		wmEvent = HIWORD(wParam); switch (wmId)
		{
		case HPROCESSES_ID:
			if (wmEvent == LBN_SELCHANGE)
			{
				int itemId = SendMessage(hProcesses, LB_GETCURSEL, 0, NULL);
				if (itemId != -1)
					ShowModules(procs[itemId]);
			}
			break;
		case ID_IDLE:
			SetPriority(IDLE_PRIORITY_CLASS);
			break;
		case ID_NORMAL:
			SetPriority(NORMAL_PRIORITY_CLASS);
			break;
		case ID_HIGH:
			SetPriority(HIGH_PRIORITY_CLASS);
			break;
		case ID_REAL_TIME:
			SetPriority(REALTIME_PRIORITY_CLASS);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CONTEXTMENU:
		if ((HWND)wParam == hProcesses) {
			int itemId = SendMessage(hProcesses, LB_GETCURSEL, 0, NULL);
			if (itemId != -1) {
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procs[itemId].th32ProcessID);
				int pC = GetPriorityClass(hProcess);
				CloseHandle(hProcess);

				hPopupMenu = CreatePopupMenu();
				AppendMenu(hPopupMenu, pC == IDLE_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, ID_IDLE, L"Idle");
				AppendMenu(hPopupMenu, pC == NORMAL_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, ID_NORMAL, L"Normal");
				AppendMenu(hPopupMenu, pC == HIGH_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, ID_HIGH, L"High");
				AppendMenu(hPopupMenu, pC == REALTIME_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, ID_REAL_TIME, L"Real time");
				TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, hWnd, NULL);
			}
		}
		break;
	case WM_SIZE:
		width = LOWORD(lParam);
		height = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
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

void SetPriority(DWORD priorityClass)
{
	int itemId = SendMessage(hProcesses, LB_GETCURSEL, 0, NULL);
	if (itemId != -1) {
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procs[itemId].th32ProcessID);
		SetPriorityClass(hProcess, priorityClass);
		CloseHandle(hProcess);
	}
}

void ClearListBox(HWND listBox)
{
	while (SendMessage(listBox, LB_GETCOUNT, 0, NULL))
		SendMessage(listBox, LB_DELETESTRING, 0, NULL);
}

void ShowProcesses()
{
	procCount = 0;
	procs[0].dwSize = sizeof(PROCESSENTRY32);

	HANDLE toolHelp = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	bool result = Process32First(toolHelp, &procs[0]);
	while (result)
	{
		procCount++;
		procs[procCount].dwSize = sizeof(PROCESSENTRY32);
		result = Process32Next(toolHelp, &procs[procCount]);
	}
	CloseHandle(toolHelp);

	ClearListBox(hProcesses);
	for (int i = 0; i < procCount; i++)
		SendMessage(hProcesses, LB_ADDSTRING, 0, (LPARAM)procs[i].szExeFile);
}

void ShowModules(PROCESSENTRY32 proc)
{
	moduleCount = 0;
	modules[0].dwSize = sizeof(MODULEENTRY32);

	HANDLE toolHelp = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc.th32ProcessID);
	bool result = Module32First(toolHelp, &modules[0]);
	while (result)
	{
		moduleCount++;
		modules[moduleCount].dwSize = sizeof(MODULEENTRY32);
		result = Module32Next(toolHelp, &modules[moduleCount]);
	}
	CloseHandle(toolHelp);

	ClearListBox(hModules);
	for (int i = 0; i < moduleCount; ++i)
		SendMessage(hModules, LB_ADDSTRING, 0, (LPARAM)modules[i].szModule);
}