#ifndef LAB6_STATE_H
#define LAB6_STATE_H

#include <windows.h>
#include "Constants.h"


HANDLE Threads[THREAD_COUNT] = {nullptr};
DWORD ThreadIds[THREAD_COUNT] = {0};
bool isSuspended = false;

struct MessageParams {
    explicit MessageParams(int delay, int length) : delay(delay), length(length) {}

    int x = 0;
    int delay, length;
} Messages[THREAD_COUNT] = {
        MessageParams(50, 100),
        MessageParams(100, 100),
        MessageParams(150, 100)
};


#endif //LAB6_STATE_H
