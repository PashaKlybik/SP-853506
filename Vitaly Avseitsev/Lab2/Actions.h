#ifndef ENROLL32_ACTIONS_H
#define ENROLL32_ACTIONS_H

#include <windows.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using std::vector;
using std::wstring;
using std::cout;
using std::endl;

vector<wstring> left, right;

void ToRight(const wchar_t item[]);

int FindRight(int leftIndex);


void Delete(int leftIndex) {
    int rightIndex = FindRight(leftIndex);
    if (rightIndex != -1) {
        right.erase(right.begin() + rightIndex);
    }

    left.erase(left.begin() + leftIndex);
}

bool Add(const wchar_t item[]) {
    wstring str(item);
    auto it = std::find(left.begin(), left.end(), str);
    if (it == left.end()) {
        left.push_back(str);
        return true;
    }
    return false;
}


const wchar_t *ToRight(int from) {
    auto str = left[from];
    auto it = std::find(right.begin(), right.end(), str);
    if (it == right.end()) {
        right.push_back(str);
        return left[from].c_str();
    }
    return nullptr;
}

int FindRight(int leftIndex) {
    wstring str = left.at(leftIndex);
    auto it = std::find(right.begin(), right.end(), str);
    if (it == right.end()) {
        return -1;
    }
    return it - right.begin();
}

void Clear() {
    left.clear();
    right.clear();
}


#endif //ENROLL32_ACTIONS_H
