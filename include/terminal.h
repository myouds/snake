#ifndef TERM_WIN_H
#define TERM_WIN_H
#include <list>
#include <thread>

class Drawable;

struct coordinate {
    int x;
    int y;
};

class Window {
    public:
        Window();
        ~Window();
        int get_cols();
        int get_lines();
        void clear_term();
        void draw();
        void register_item(Drawable *item);
        void deregister_item(Drawable *item);
        static int get_input();
    private:
        std::list<Drawable*> drawables;
        static int term_columns;
        static int term_lines;
        static std::atomic_int last_input;
        static void sig_hdl(int sig);
        static void init_size();
        static void watch_input();
        static void input_watcher();
};

#endif