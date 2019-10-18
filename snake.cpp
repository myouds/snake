#include <ncurses.h>
#include "snake.h"
#include "food.h"

Snake::Snake(int len, Window& win): length(len), Drawable(win) {
    unsigned max_x,
             max_y;
    coordinate coord_tmp;

    max_x = window.get_cols() - 1;
    max_y = window.get_lines() - 1;
    if (max_x > max_y) {
        direction = left;
        coord_tmp.y = max_y / 2;
        for (int i = 0; i < length; i++) {
            coord_tmp.x = max_x - i;
            coords.push_front(coord_tmp);
        }
    }
    else {
        direction = up;
        coord_tmp.x = max_x / 2;
        for (int i = 0; i < length; i++) {
            coord_tmp.y = max_y - i;
            coords.push_front(coord_tmp);
        }
    }
}

bool Snake::move() {
    coordinate coord;
    
    coords.pop_back();
    coord = coords.front();
    switch (direction) {
        case up:
            coord.y--;
            break;
        case down:
            coord.y++;
            break;
        case left:
            coord.x--;
            break;
        case right:
            coord.x++;
            break;
        case invalid:
            break;
    }
    if (coord.x < 0 || coord.x >= window.get_cols())
        return false;
    if (coord.y < 0 || coord.y >= window.get_lines())
        return false;
    for (coordinate c : coords) {
        if (c.x == coord.x && c.y == coord.y) {
            return false;
        }
    }
    coords.push_front(coord);
    return true;
}

bool Snake::change_direction(Direction dir) {
    switch(dir) {
        case invalid:
            return false;
            break;
        case up:
            if (direction == down)
                return false;
            break;
        case down:
            if (direction == up)
                return false;
            break;
        case left:
            if (direction == right)
                return false;
             break;
       case right:
            if (direction == left)
                return false;
            break;
    }
    direction = dir;
    return true;
}

Food* Snake::chomp(std::list<Food*> food_items) {
    Food *ret = NULL;
    coordinate coord;
    coordinate food_coord;

    coord = coords.front();
    for (Food *item: food_items) {
        food_coord = item->coords.front();
        if (coord.x == food_coord.x && coord.y == food_coord.y) {
            /*
             * We've found food! Add another coordinate to the back
             * end of the snake. This will be removed next time the
             * snake moves forward, so the net result will be that
             * nothing is removed from the end, so the snake will
             * grow by 1.
             * It doesn't really matter what this coordinate is, but
             * just in case, make it the same value as the current
             * back end.
             */
            coords.push_back(coords.back());
            length++;
            ret = item;
            /*
             * Tell the Food item to respawn somewhere else
             */
            item->initCoord();
        }
    }
    return ret;
}

Direction Snake::input_to_direction (int input) {
    Direction retval;
    switch (input) {
        case KEY_UP:
            retval = up;
            break;
        case KEY_DOWN:
            retval = down;
            break;
        case KEY_LEFT:
            retval = left;
            break;
        case KEY_RIGHT:
            retval = right;
            break;
        default:
            retval = invalid;
            break;
    }
    return retval;
}
