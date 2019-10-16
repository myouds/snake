#include <iostream>
#include <ncurses.h>
#include <thread>
#include <unistd.h>

void test () {
    for(int i = 0; i < 10; i++) {
        sleep(1);
    }
}

int main(int argc, char **argv) {
    /*initscr();
    move(3, 3);
    waddch(stdscr, 'x');
    move(3, 5);
    waddch(stdscr, 'x');
    getch();
    endwin();*/
    std::thread worker (test);
    worker.join();
}