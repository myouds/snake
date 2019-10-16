#ifndef FOOD_H
#define FOOD_H

#include "drawable.h"

class Food: public Drawable {
    public:
        Food(Window& win);
        void initCoord();
};

#endif