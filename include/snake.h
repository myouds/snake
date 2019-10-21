#ifndef SNAKE_H
#define SNAKE_H
#include "drawable.h"

enum Direction {
    up,
    down,
    left,
    right,
    invalid
};

class Food;

class Snake: public Drawable {
    public:
        Snake(int len, terminal::Window& win);
        bool move();
        Food* chomp(std::list<Food*> food_items);
        bool change_direction(Direction dir);
        static Direction input_to_direction (int input);
    private:
        int length;
        enum Direction direction;
        int speed;
};

#endif