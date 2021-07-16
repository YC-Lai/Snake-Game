#ifndef FOOD_H
#define FOOD_H

#include <random>
#include <vector>
#include <memory>

#include "SDL.h"
#include "snake.h"

class Food {
   public:
    Food(int grid_width, int grid_height)
        : engine(dev()),
          random_w(0, static_cast<int>(grid_width - 1)),
          random_h(0, static_cast<int>(grid_height - 1)) {}

    SDL_Point get_food();
    void placeFood(std::shared_ptr<Snake> const snake);

   private:
    SDL_Point foodPoint;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
};

#endif