#ifndef LAB6_STATE_H
#define LAB6_STATE_H

#include <windows.h>
#include "Constants.h"


HANDLE Threads[THREAD_COUNT] = {nullptr};
DWORD ThreadIds[THREAD_COUNT] = {0};

CRITICAL_SECTION DrawSection;

int *color = new int{RGB(255, 255, 255)};

struct ColorThreadParams {
    ColorThreadParams(int src) : src(src) {}

    int *dest = color;
    int src;
} Colors[THREAD_COUNT]{
        ColorThreadParams(RGB(255, 0, 0)),
        ColorThreadParams(RGB(0, 255, 0)),
        ColorThreadParams(RGB(0, 0, 255))
};


#endif //LAB6_STATE_H
