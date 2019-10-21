#include "drawable.h"

Drawable::Drawable(terminal::Window& win): window(win) {
    window.register_item(this);
}

Drawable::~Drawable() {
    window.deregister_item(this);
}