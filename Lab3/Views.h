#ifndef ENROLL32_VIEWS_H
#define ENROLL32_VIEWS_H

#include <windows.h>
#include "Constants.h"

struct Views {
    HWND draw;
    HWND clear;
} views;

void InitView(HWND root, HINSTANCE hinstance) {

    views.draw = CreateWindow(
            BUTTON,
            DRAW_TEXT,
            BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            DRAW_PARAMS.x, DRAW_PARAMS.y, DRAW_PARAMS.w, DRAW_PARAMS.h,
            root,
            (HMENU) DRAW_ID,
            hinstance,
            nullptr
    );

    views.clear = CreateWindow(
            BUTTON,
            CLEAR_TEXT,
            BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            CLEAR_PARAMS.x, CLEAR_PARAMS.y, CLEAR_PARAMS.w, CLEAR_PARAMS.h,
            root,
            (HMENU) CLEAR_ID,
            hinstance,
            nullptr
    );

}

void DrawView(LPDRAWITEMSTRUCT pDIS) {
    if (pDIS->hwndItem == views.draw) {
        TextOut(pDIS->hDC, pDIS->rcItem.left, pDIS->rcItem.top, DRAW_TEXT, 4);
    } else if (pDIS->hwndItem == views.clear) {
        TextOut(pDIS->hDC, pDIS->rcItem.left, pDIS->rcItem.top, CLEAR_TEXT, 5);
    }
}

#endif //ENROLL32_VIEWS_H
