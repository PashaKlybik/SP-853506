#ifndef ENROLL32_CONSTANTS_H
#define ENROLL32_CONSTANTS_H

#define BUTTON L"button"

#define DRAW_TEXT L"Draw"
#define CLEAR_TEXT L"Clear"

#include <windows.h>

#define BUTTON L"BUTTON"

const int WIDTH = 600;
const int HEIGHT = 300;

const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 20;

const int C_1 = 50;
const int C_2 = 250;

const int ROW_HEIGHT = 30;

const int R_1 = 20;
const int R_2 = R_1 + ROW_HEIGHT;
const int R_3 = R_2 + ROW_HEIGHT;
const int R_4 = R_3 + ROW_HEIGHT;
const int R_5 = R_4 + ROW_HEIGHT;

struct LAYOUT_PARAMS {
    LAYOUT_PARAMS(int x, int y, int id) : x(x), y(y), id(id) {
        w = BUTTON_WIDTH;
        h = BUTTON_HEIGHT;
    }

    LAYOUT_PARAMS(int x, int y, int w, int h) : x(x), y(y), w(w), h(h), id(0) {}

    int x, y, w, h, id;
};

const int GROUP_MARGIN = 10;

const int RED_ID = 1001;
const int GREEN_ID = 1002;
const int BLUE_ID = 1003;

const int SQUARE_ID = 1004;
const int RHOMBUS_ID = 1005;
const int CIRCLE_ID = 1006;
const int STAR_ID = 1007;

const int DRAW_ID = 1008;

const LAYOUT_PARAMS COLORS_GROUP(C_1, R_1 - 20, BUTTON_WIDTH + 2 * GROUP_MARGIN, R_4);
const LAYOUT_PARAMS RED_PARAMS(C_1 + GROUP_MARGIN, R_1, RED_ID);
const LAYOUT_PARAMS GREEN_PARAMS(C_1 + GROUP_MARGIN, R_2, GREEN_ID);
const LAYOUT_PARAMS BLUE_PARAMS(C_1 + GROUP_MARGIN, R_3, BLUE_ID);

const LAYOUT_PARAMS FORM_GROUP(C_2, R_1 - 20, BUTTON_WIDTH + 2 * GROUP_MARGIN, R_5);
const LAYOUT_PARAMS SQUARE_PARAMS(C_2 + GROUP_MARGIN, R_1, SQUARE_ID);
const LAYOUT_PARAMS RHOMBUS_PARAMS(C_2 + GROUP_MARGIN, R_2, RHOMBUS_ID);
const LAYOUT_PARAMS STAR_PARAMS(C_2 + GROUP_MARGIN, R_3, STAR_ID);
const LAYOUT_PARAMS CIRCLE_PARAMS(C_2 + GROUP_MARGIN, R_4, CIRCLE_ID);

const LAYOUT_PARAMS CHECKBOX_PARAMS(C_1, R_5, DRAW_ID);


#endif //ENROLL32_CONSTANTS_H
