#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <tlhelp32.h>
#include "Views.h"
#include "State.h"

void ShowProcesses() {
    int oldPCount = pCount;
    pCount = 0;
    processes[0].dwSize = sizeof(PROCESSENTRY32);

    HANDLE toolHelp = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    bool result = Process32First(toolHelp, &processes[0]);
    while (result) {
        pCount++;
        processes[pCount].dwSize = sizeof(PROCESSENTRY32);
        result = Process32Next(toolHelp, &processes[pCount]);
    }

    for (int i = 0; i < oldPCount; ++i) {
        SendMessage(processesList, LB_DELETESTRING, 0, 0);
    }
    for (int i = 0; i < pCount; i++) {
        SendMessage(processesList, LB_ADDSTRING, 0, (LPARAM) processes[i].szExeFile);
    }
}

void ProcessSelected(int pos) {
    if (pos < 0) return;

    pSelection = pos;
    int oldCount = mCount;
    mCount = 0;
    modules[0].dwSize = sizeof(MODULEENTRY32);

    auto proc = processes[pos];

    HANDLE toolHelp = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc.th32ProcessID);
    bool result = Module32First(toolHelp, &modules[0]);
    while (result) {
        mCount++;
        modules[mCount].dwSize = sizeof(MODULEENTRY32);
        result = Module32Next(toolHelp, &modules[mCount]);
    }
    CloseHandle(toolHelp);

    for (int i = 0; i < oldCount; ++i) {
        SendMessage(modulesList, LB_DELETESTRING, 0, 0);
    }
    for (int i = 0; i < mCount; ++i)
        SendMessage(modulesList, LB_ADDSTRING, 0, (LPARAM) modules[i].szModule);
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample";

    WNDCLASSW wc = {};
    wc.hInstance = hinstance;
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    wc.lpszMenuName = nullptr;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    RegisterClassW(&wc);
    HWND hwnd = CreateWindowExW(
            0,
            CLASS_NAME,
            L"Sample window title",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
            nullptr,
            nullptr,
            hinstance,
            nullptr
    );

    InitView(hinstance, hwnd);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    ShowProcesses();

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void ShowContextMenu(HWND hwnd, LPARAM lp) {
    if (pSelection != -1) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processes[pSelection].th32ProcessID);
        int pC = GetPriorityClass(hProcess);
        CloseHandle(hProcess);

        auto menu = CreatePopupMenu();
        AppendMenuW(menu, pC == IDLE_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, IDLE_ID, L"Idle");
        AppendMenuW(menu, pC == NORMAL_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, NORMAL_ID, L"Normal");
        AppendMenuW(menu, pC == HIGH_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, HIGH_ID, L"High");
        AppendMenuW(menu, pC == REALTIME_PRIORITY_CLASS ? MF_CHECKED : MF_STRING, RT_ID, L"Real time");
        TrackPopupMenu(menu, TPM_TOPALIGN | TPM_LEFTALIGN, GET_X_LPARAM(lp), GET_Y_LPARAM(lp), 0, hwnd, nullptr);
    }
}

void SetPriority(int priority) {
    if (pSelection != -1) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processes[pSelection].th32ProcessID);
        SetPriorityClass(hProcess, priority);
        CloseHandle(hProcess);
    }
}

LRESULT WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) {
    switch (Message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            switch (LOWORD(wparam)) {
                case PROC_L_ID:
                    if (HIWORD(wparam) == LBN_SELCHANGE) {
                        ProcessSelected(SendMessage(processesList, LB_GETCURSEL, 0, NULL));
                    }
                    break;
                case IDLE_ID:
                    SetPriority(IDLE_PRIORITY_CLASS);
                    break;
                case NORMAL_ID:
                    SetPriority(NORMAL_PRIORITY_CLASS);
                    break;
                case HIGH_ID:
                    SetPriority(HIGH_PRIORITY_CLASS);
                    break;
                case RT_ID:
                    SetPriority(REALTIME_PRIORITY_CLASS);
                    break;
            }
            break;
        case WM_CONTEXTMENU:
            if ((HWND) wparam == processesList) {
                ShowContextMenu(hwnd, lparam);
            }
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}