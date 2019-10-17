#include <unistd.h>
#include "snake.h"
#include "food.h"
#include "terminal.h"

int main(int argc, char **argv){
    int input;
    Direction dir;
    std::list<Food*> food_list;
    /*
     * Need a Window object to display our items
     */
    Window terminal = Window();
    /*
     * Now add a snake and some food to the window
     */
    Snake snake = Snake(3, terminal);
    Food food = Food(terminal);
    /*
     * Add the food to a list that we will use to tell the
     * snake what to eat.
     */
    food_list.push_back(&food);
    /*
     * Main program loop - keep moving the snake
     */
    for(bool go = true; go == true; go = snake.move()) {
        terminal.draw();
        snake.chomp(food_list);
        usleep(100000);
        /*
         * If the user has given some valid input to change
         * direction, change the Snake's direction now
         */
        if ((input = Window::get_input()) != 0) {
            dir = Snake::input_to_direction(input);
            snake.change_direction(dir);
        }
    }
    return 0;
}
