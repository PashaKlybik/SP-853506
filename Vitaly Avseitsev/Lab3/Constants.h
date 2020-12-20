#ifndef ENROLL32_CONSTANTS_H
#define ENROLL32_CONSTANTS_H

#define BUTTON L"button"

#define DRAW_TEXT L"Draw"
#define CLEAR_TEXT L"Clear"


const int WIDTH = 600;
const int HEIGHT = 600;

const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;

#define YELLOW RGB(200 , 200 , 0)
#define GRAY RGB(140 , 140 , 140)
#define DARK_GRAY RGB(40 , 40 , 40)
#define BLACK RGB(0 , 0 , 0)
#define PURPLE RGB(255 , 100 , 120)
#define CIAN RGB(150 , 150 , 240)

struct LAYOUT_PARAMS {
    LAYOUT_PARAMS(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

    int x, y, w, h;
};

const LAYOUT_PARAMS DRAW_PARAMS(150, 500, BUTTON_WIDTH, BUTTON_HEIGHT);
const LAYOUT_PARAMS CLEAR_PARAMS(350, 500, BUTTON_WIDTH, BUTTON_HEIGHT);

const int DRAW_ID = 1003;
const int CLEAR_ID = 1004;

#endif //ENROLL32_CONSTANTS_H
