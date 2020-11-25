// Lab1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab1.h"

#define MAX_LOADSTRING 100
#define IDM_START 1001
#define IDM_STOP 1002

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS); //IDC_ARROW
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

int TIMER_ID = 1002;

struct POSITION {
    int X;
    int Y;
};

POSITION* POSITIONS;
int LEN = 1000;
int Y_SPACING = 40;
int Y_HIGHT = 500;

int COLS = 20;
int SPEED = 20;

void GeneratePositions(int LEN) {
    POSITIONS = new POSITION[LEN];
    int values_on_column = Y_HIGHT / Y_SPACING;
    COLS = (int)(LEN / values_on_column);

    int per_column_count = LEN / COLS;
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < per_column_count; i++) {
            POSITIONS[j * per_column_count + i].X = j * 10 + 400;
            POSITIONS[j * per_column_count + i].Y = 5 + i*Y_SPACING;
        }
    }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: 
        {
        SetWindowTextA(hWnd, "Миграция муравьёв"); // we set the text of the window title to whatever you want, in this case "a"
        TCHAR menu[] = _T("MENU");
        TCHAR start[] = _T("START");
        TCHAR stop[] = _T("STOP");

        HMENU SX = CreateMenu();
        HMENU SubSX = CreatePopupMenu(); //Create a submenu which appears on hovering to "menu" called "Sub-Menu"
        AppendMenu(SubSX, MF_STRING, IDM_START, start);
        AppendMenu(SubSX, MF_STRING, IDM_STOP, stop);
        AppendMenu(SX, MF_POPUP | MF_STRING, (UINT_PTR)SubSX, menu);
        GeneratePositions(LEN);

        SetMenu(hWnd, SX);
        return 0;
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_START:
                SetTimer(hWnd, TIMER_ID, SPEED, NULL);
                break;
            case IDM_STOP:
                KillTimer(hWnd, TIMER_ID);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
        {
        for (int i = 0; i < LEN; i++) {
            if (POSITIONS[i].Y > Y_HIGHT)
                POSITIONS[i].Y = 5;
            else
                POSITIONS[i].Y += 5;
            int jump = rand()%100;
            if (jump < 30)
                POSITIONS[i].X -= (int)(jump / 5);
            else if (jump > 70)
                POSITIONS[i].X += (int)((100-jump)/ 5);
        }
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            for (int i = 0; i < LEN; i++) {
                TextOut(hdc,
                    POSITIONS[i].X, POSITIONS[i].Y,
                    _T("*"), 1);
            }
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

