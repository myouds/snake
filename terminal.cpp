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
                get_window().init_size();
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
        start_color();
        signal(SIGWINCH, sig_hdl);
        watch_input();
        clear_term();
        score = 0;
        write_score();
    }

    Window::~Window() {
        endwin();
    }

    void Window::init_size() {
        /*
        * getmaxyx() sets its arguments to the vertical and horizontal
        * size of the window - NOT the max x and y coordinates
        */
        int full_lines;
        int full_columns;
        getmaxyx(stdscr, full_lines, full_columns);
        term_lines = full_lines - 3;
        term_columns = full_columns;
        wresize(game_scr, term_lines, term_columns);
        wresize(score_scr, full_lines - term_lines, full_columns);
        wborder(score_scr, '.', '.', '.', '.', '.', '.', '.', '.');
        mvwin(score_scr, term_lines, 0);
        wrefresh(score_scr);
    }

    int Window::get_cols() {
        return term_columns;
    }

    int Window::get_lines() {
        return term_lines;
    }

    void Window::clear_term() {
        wclear(game_scr);
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
                wmove(game_scr, coord.y, coord.x);
                waddch(game_scr, '*');
            }
        }
        wrefresh(game_scr);
    }

    void Window::increment_score(int num_to_add) {
        score += num_to_add;
        write_score();
    }

    void Window::write_score() {
        mvwprintw(score_scr, 1, 2, "Score: %i", score);
        wrefresh(score_scr);
    }

    void Window::game_over() {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        wattron(game_scr, COLOR_PAIR(1));
        draw();
        wattroff(game_scr, COLOR_PAIR(1));
    }

    void Window::input_watcher() {
        keypad(game_scr, TRUE);
        while (1) {
            last_input = wgetch(game_scr);
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
