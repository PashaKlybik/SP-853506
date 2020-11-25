// Lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

	MSG msg;

	// Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: 
	{
		auto hEdit = CreateWindow(TEXT("EDIT"), TEXT("Name Here"), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 230, 20, hWnd, (HMENU)ID_TEXT_EDIT, hInst, NULL);
		auto hAddBtn = CreateWindow(L"BUTTON", L"Add to list",	WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 40, 230, 30, hWnd, (HMENU)ID_SAVE_BTN_CLICKED, hInst,	NULL);
		auto hToRightBtn = CreateWindow(L"BUTTON", L"To right", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 80, 230, 30, hWnd, (HMENU)ID_TORIGHT_BTN_CLICKED, hInst, NULL);
		auto hDeleteBtn = CreateWindow(L"BUTTON", L"Delete", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 120, 230, 30, hWnd, (HMENU)ID_DELETE_BTN_CLICKED, hInst, NULL);
		auto hClearBtn = CreateWindow(L"BUTTON", L"Clear", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 160, 230, 30, hWnd, (HMENU)ID_CLEAR_BTN_CLICKED, hInst, NULL);
		auto hListFirst = CreateWindow(TEXT("LISTBOX"), TEXT("List box #1"), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 200, 230, 300, hWnd, (HMENU)ID_LISTBOX_FIRST, hInst, NULL);
		auto hListSecound = CreateWindow(TEXT("LISTBOX"), TEXT("List box #2"), WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 10, 230,490, hWnd, (HMENU)ID_LISTBOX_SECOND, hInst, NULL);
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_SAVE_BTN_CLICKED:
		{
			TCHAR StrA[64];
			auto len = GetWindowText(GetDlgItem(hWnd, ID_TEXT_EDIT), StrA, 64);
			auto finded = SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_FINDSTRINGEXACT, 0, (LPARAM)StrA);
			if (finded == -1) {
				SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_ADDSTRING, 0, (LPARAM)StrA);
				SetWindowText(GetDlgItem(hWnd, ID_TEXT_EDIT), L"");
			}
			break;
		}
		case ID_TORIGHT_BTN_CLICKED:
		{
			TCHAR StrA[64];
			auto sel_first = SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_GETSEL, 0, 0);
			SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_GETTEXT, sel_first, (LPARAM)StrA);
			auto is_in_second = SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_SECOND), LB_FINDSTRINGEXACT, 0, (LPARAM)StrA);
			if (is_in_second == -1) {
				SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_SECOND), LB_ADDSTRING, 0, (LPARAM)StrA);
				SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_DELETESTRING, 0, (LPARAM)StrA);
				// Clear current selection
				SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_SETCURSEL, -1, 0);
				SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_SECOND), LB_SETCURSEL, -1, 0);
				//LB_SETCURSEL
			}
			break;
		}
		case ID_DELETE_BTN_CLICKED: 
		{
			auto sel_first = SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_GETSEL, 0, 0);
			auto sel_second = SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_SECOND), LB_GETSEL, 0, 0);
			SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_DELETESTRING, 0, sel_first);
			SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_SECOND), LB_DELETESTRING, 0, sel_second);
			break;
		}
		case ID_CLEAR_BTN_CLICKED:
		{
			SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_FIRST), LB_RESETCONTENT, 0, 0);
			SendMessageW(GetDlgItem(hWnd, ID_LISTBOX_SECOND), LB_RESETCONTENT, 0, 0);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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

// Обработчик сообщений для окна "О программе".
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
