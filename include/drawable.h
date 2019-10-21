#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <list>
#include "terminal.h"

class Drawable {
    public:
        Drawable(terminal::Window& win);
        ~Drawable();
        std::list<coordinate> coords;
    protected:
        terminal::Window& window;
};

#endif