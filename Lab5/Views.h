#ifndef ENROLL32_VIEWS_H
#define ENROLL32_VIEWS_H

#include <windows.h>
#include "Constants.h"

struct Views {
    HWND red;
    HWND green;
    HWND blue;
    HWND star;
    HWND rhombus;
    HWND square;
    HWND circle;
    HWND draw;
} views;

HWND settings;
HWND canvas;

HWND DrawButton(HINSTANCE hinstance, HWND parent, LAYOUT_PARAMS params, const wchar_t *name, int type) {
    HWND res = CreateWindow(
            BUTTON,
            name,
            WS_CHILD | WS_VISIBLE | type,
            params.x, params.y, params.w, params.h,
            parent,
            reinterpret_cast<HMENU>(params.id),
            hinstance,
            nullptr
    );
    ShowWindow(res, SW_SHOWNORMAL);
    return res;
}

HWND DrawRadiobutton(HINSTANCE hinstance, HWND parent, LAYOUT_PARAMS params, const wchar_t name[], bool isFirst = false) {
    int style = BS_AUTORADIOBUTTON;
    if (isFirst) {
        style = style | WS_GROUP;
    }
    return DrawButton(hinstance, parent, params, name, style);
}

HWND DrawRadioGroup(HINSTANCE hinstance, HWND parent, LAYOUT_PARAMS params, const wchar_t name[]) {
    return DrawButton(hinstance, parent, params, name, BS_GROUPBOX);
}

void InitView(HWND root, HINSTANCE hinstance) {
    DrawRadioGroup(hinstance, root, COLORS_GROUP, L"Color" );
    views.red = DrawRadiobutton(hinstance, root, RED_PARAMS, L"Red", true);
    views.green = DrawRadiobutton(hinstance, root, GREEN_PARAMS, L"Green");
    views.blue = DrawRadiobutton(hinstance, root, BLUE_PARAMS, L"Blue");

    DrawRadioGroup(hinstance, root, FORM_GROUP, L"Shape");
    views.circle = DrawRadiobutton(hinstance, root, CIRCLE_PARAMS, L"Circle", true);
    views.rhombus = DrawRadiobutton(hinstance, root, RHOMBUS_PARAMS, L"Rhombus");
    views.square = DrawRadiobutton(hinstance, root, SQUARE_PARAMS, L"Square");
    views.star = DrawRadiobutton(hinstance, root, STAR_PARAMS, L"Star");

    views.draw = DrawButton(hinstance, root, CHECKBOX_PARAMS, L"Draw", BS_AUTOCHECKBOX);
}


#endif //ENROLL32_VIEWS_H
