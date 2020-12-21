#ifndef LAB8_STATE_H
#define LAB8_STATE_H

#include <tlhelp32.h>
#include "Constants.h"

int pCount = 0;
int pSelection = -1;
PROCESSENTRY32 processes[500];


int mCount = 0;
MODULEENTRY32 modules[500];

#endif //LAB8_STATE_H
