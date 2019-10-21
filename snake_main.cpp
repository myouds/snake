#include <unistd.h>
#include "snake.h"
#include "food.h"
#include "terminal.h"

int main(int argc, char **argv){
    int input;
    int chomp_cnt = 0;
    Direction dir;
    std::list<Food*> food_list;
    Food *chomped;
    srand(time(NULL));
    /*
     * Need a Window object to display our items
     */
    terminal::Window& terminal = terminal::get_window();
    /*
     * Now add a snake and some food to the window
     * Add the food to a list that we will use to tell the
     * snake what to eat.
     */
    Snake snake = Snake(3, terminal);
    food_list.push_back(new Food(terminal));
    /*
     * Main program loop - keep moving the snake
     */
    for(bool go = true; go == true; go = snake.move()) {
        terminal.draw();
        if ((chomped = snake.chomp(food_list)) != NULL) {
            if (food_list.size() > 1) {
                /*
                 * We have multiple Food objects and one just got chomped
                 * Remove that object now instead of allowing it to move
                 * somewhere else
                 */
                food_list.remove(chomped);
                delete chomped;
                /*
                 * This should be seen as a bonus, so make sure we don't
                 * increment the chomp counter or add any extra Food objects
                 * this time round
                 */
                continue;
            }
            /*
            * Periodically add an extra Food item
            */
            if (++chomp_cnt % 3 == 0) {
                /*
                * Second Food every 3 chomps
                */
                food_list.push_back(new Food(terminal));
                if (chomp_cnt % 5 == 0) {
                    /*
                    * Third food every 15 chomps
                    */
                    food_list.push_back(new Food(terminal));
                }
            }
        }
        usleep(100000);
        /*
         * If the user has given some valid input to change
         * direction, change the Snake's direction now
         */
        if ((input = terminal.get_input()) != 0) {
            dir = Snake::input_to_direction(input);
            snake.change_direction(dir);
        }
    }
    return 0;
}
