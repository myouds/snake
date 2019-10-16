#include <signal.h>
#include <ncurses.h>
#include "terminal.h"
#include "drawable.h"
#include <iostream>
#include <list>
#include <thread>

int Window::term_columns = 0;
int Window::term_lines = 0;
std::atomic_int Window::last_input(0);

Window::Window() {
    initscr();
    curs_set(0);
    init_size();
    signal(SIGWINCH, Window::sig_hdl);
    Window::watch_input();
    clear_term();
}

Window::~Window() {
    endwin();
}

void Window::sig_hdl(int sig) {
    switch(sig) {
        case SIGWINCH:
            endwin();
            refresh();
            Window::init_size();
            keypad(stdscr, TRUE);
            ;;
        default:
            ;;
    }
}

void Window::init_size() {
    getmaxyx(stdscr, term_lines, term_columns);
    term_lines++;
    term_columns++;
}

int Window::get_cols() {
    return Window::term_columns;
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
        std::thread input_thread (Window::input_watcher);
        input_thread.detach();
        watching = true;
    }
}

int Window::get_input() {
    int in = last_input;
    last_input = 0;
    return in;
}