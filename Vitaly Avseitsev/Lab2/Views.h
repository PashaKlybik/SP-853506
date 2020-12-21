#ifndef ENROLL32_VIEWS_H
#define ENROLL32_VIEWS_H

#include <windows.h>
#include "Constants.h"

struct Views {
    HWND listLeft;
    HWND listRight;
    HWND btnAdd;
    HWND btnClear;
    HWND btnToRight;
    HWND btnDelete;
    HWND input;
} views;

HWND CreateButton(const wchar_t name[], const LAYOUT_PARAMS &params, HWND parent, HINSTANCE hinstance, int id) {
    return CreateWindow(
            BUTTON,
            name,
            WS_CHILD,
            params.x, params.y, params.w, params.h,
            parent,
            reinterpret_cast<HMENU>(id),
            hinstance,
            nullptr
    );
}

void InitView(HINSTANCE hinstance, HWND hwnd) {
    views.listLeft = CreateWindow(
            LIST,
            nullptr,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD,
            ListLeft.x, ListLeft.y, ListLeft.w, ListLeft.h,
            hwnd,
            nullptr,
            hinstance,
            nullptr
    );
    ShowWindow(views.listLeft, SW_SHOWNORMAL);
    views.listRight = CreateWindow(
            LIST,
            nullptr,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD,
            ListRight.x, ListRight.y, ListRight.w, ListRight.h,
            hwnd,
            nullptr,
            hinstance,
            nullptr
    );
    ShowWindow(views.listRight, SW_SHOWNORMAL);
    views.btnAdd = CreateButton(L"Add", ButtonAdd, hwnd, hinstance, ADD_ID);
    ShowWindow(views.btnAdd, SW_SHOWNORMAL);
    views.btnClear = CreateButton(L"Clear", ButtonClear, hwnd, hinstance, CLEAR_ID);
    ShowWindow(views.btnClear, SW_SHOWNORMAL);
    views.btnToRight = CreateButton(L"To Right", ButtonToRight, hwnd, hinstance, TO_RIGHT_ID);
    ShowWindow(views.btnToRight, SW_SHOWNORMAL);
    views.btnDelete = CreateButton(L"Delete", ButtonDelete, hwnd, hinstance, DELETE_ID);
    ShowWindow(views.btnDelete, SW_SHOWNORMAL);
    views.input = CreateWindow(
            EDIT,
            L"String",
            WS_CHILD | LBS_WANTKEYBOARDINPUT,
            Input.x, Input.y, Input.w, Input.h,
            hwnd,
            nullptr,
            hinstance,
            nullptr
    );
    ShowWindow(views.input, SW_SHOWNORMAL);
}

#endif //ENROLL32_VIEWS_H
