#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <list>
#include "terminal.h"

class Drawable {
    public:
        Drawable(Window& win);
        ~Drawable();
        std::list<coordinate> coords;
    protected:
        Window& window;
};

#endif