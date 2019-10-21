#include <signal.h>
#include <ncurses.h>
#include "terminal.h"
#include "drawable.h"
#include <list>
#include <thread>

namespace terminal {
    void sig_hdl(int sig) {
        switch(sig) {
            case SIGWINCH:
                endwin();
                refresh();
                get_window().init_size();
                keypad(stdscr, TRUE);
                ;;
            default:
                ;;
        }
    }

    Window::Window() {
        last_input = 0;
        initscr();
        curs_set(0);
        /*
        * Create separate windows for the main game and the score
        * Make them both zero size and position for now - resize
        * will be done by init_size()
        */
        game_scr = newwin(0, 0, 0, 0);
        score_scr = newwin(0, 0, 0, 0);
        init_size();
        signal(SIGWINCH, sig_hdl);
        watch_input();
        clear_term();
    }

    Window::~Window() {
        endwin();
    }

    void Window::init_size() {
        /*
        * getmaxyx() sets its arguments to the vertical and horizontal
        * size of the window - NOT the max x and y coordinates
        */
        getmaxyx(stdscr, term_lines, term_columns);

    }

    int Window::get_cols() {
        return term_columns;
    }

    int Window::get_lines() {
        return term_lines;
    }

    void Window::clear_term() {
        clear();
    }

    void Window::register_item(Drawable *item) {
        drawables.push_back(item);
    }

    void Window::deregister_item(Drawable *item) {
        drawables.remove(item);
    }

    void Window::draw() {
        clear_term();
        for (Drawable *item : drawables) {
            for (coordinate coord : item->coords) {
                move(coord.y, coord.x);
                waddch(stdscr, '*');
            }
        }
        wrefresh(stdscr);
    }

    void Window::input_watcher() {
        keypad(stdscr, TRUE);
        while (1) {
            last_input = getch();
        }
    }

    void Window::watch_input() {
        static bool watching = false;
        if (watching == false) {
            std::thread input_thread (&Window::input_watcher, this);
            input_thread.detach();
            watching = true;
        }
    }

    int Window::get_input() {
        int in = last_input;
        last_input = 0;
        return in;
    }

    Window& get_window() {
        static Window term_window;
        return term_window;
    }
}
