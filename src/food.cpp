#include "food.h"

#include <iostream>

#include "SDL.h"

void Food::placeFood(std::shared_ptr<Snake> const snake) {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before
        // placing food.
        if (!snake->SnakeCell(x, y)) {
            foodPoint.x = x;
            foodPoint.y = y;
            return;
        }
    }
}

SDL_Point Food::get_food() { return foodPoint; }

