#ifndef ENROLL32_CONSTANTS_H
#define ENROLL32_CONSTANTS_H

#define BUTTON L"button"

#include <windows.h>

const int WIDTH = 600;
const int HEIGHT = 600;

const int START_ID = 1001;
const int STOP_ID = 1002;

#define THREAD_COUNT 3
#define MESSAGE_LEN 10

wchar_t Texts[THREAD_COUNT][MESSAGE_LEN] = {
        L"Message 1",
        L"Message 2",
        L"Message 3",
};

#endif //ENROLL32_CONSTANTS_H
