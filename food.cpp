#include "food.h"
#include "terminal.h"

Food::Food(Window& win): Drawable(win) {
    initCoord();
}

void Food::initCoord() {
    coordinate coord;
    srand(time(NULL));
    coord.x = rand() % window.get_cols();
    coord.y = rand() % window.get_lines();
    while(!coords.empty()) {
        coords.pop_front();
    }
    coords.push_back(coord);
}