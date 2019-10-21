#ifndef TERM_WIN_H
#define TERM_WIN_H
#include <list>
#include <thread>
#include <ncurses.h>

class Drawable;
struct coordinate {
    int x;
    int y;
};

namespace terminal {
    class Window {
        public:
            Window();
            ~Window();
            void init_size();
            int get_cols();
            int get_lines();
            void clear_term();
            void draw();
            void register_item(Drawable *item);
            void deregister_item(Drawable *item);
            int get_input();
        private:
            ::WINDOW *game_scr;
            ::WINDOW *score_scr;
            std::list<Drawable*> drawables;
            int term_columns;
            int term_lines;
            std::atomic_int last_input;
            void watch_input();
            void input_watcher();
    };
    Window& get_window();
}

#endif