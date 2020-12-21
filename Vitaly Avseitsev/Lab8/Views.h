#ifndef LAB8_VIEWS_H
#define LAB8_VIEWS_H

#include <windows.h>
#include "Constants.h"

HWND processesList;
HWND modulesList;

void InitView(HINSTANCE hinstance, HWND hwnd) {
    processesList = CreateWindowW(
            LIST,
            nullptr,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD,
            10, 10 , 270 , 560,
            hwnd,
            (HMENU) PROC_L_ID,
            hinstance,
            nullptr
    );
    ShowWindow(processesList , SW_SHOWNORMAL);
    modulesList = CreateWindowW(
            LIST,
            nullptr,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD,
            300, 10 , 270 , 560,
            hwnd,
            nullptr,
            hinstance,
            nullptr
    );
    ShowWindow(modulesList , SW_SHOWNORMAL);
}



#endif //LAB8_VIEWS_H
