#ifndef ENROLL32_CONSTANTS_H
#define ENROLL32_CONSTANTS_H

#define BUTTON L"button"

#define DRAW_TEXT L"Draw"
#define CLEAR_TEXT L"Clear"


const int WIDTH = 600;
const int HEIGHT = 600;

const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;

struct LAYOUT_PARAMS {
    LAYOUT_PARAMS(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

    int x, y, w, h;
};

const LAYOUT_PARAMS DRAW_PARAMS(150, 500, BUTTON_WIDTH, BUTTON_HEIGHT);
const LAYOUT_PARAMS CLEAR_PARAMS(350, 500, BUTTON_WIDTH, BUTTON_HEIGHT);

const int DRAW_ID = 1003;
const int CLEAR_ID = 1004;

#endif //ENROLL32_CONSTANTS_H
