#ifndef BUG_H
#define BUG_H

#include <memory>
#include <random>
#include <vector>

#include "SDL.h"
#include "snake.h"

class Bug : public Snake {
   public:
    Bug(int grid_width, int grid_height)
        : Snake(grid_width, grid_height),
          count(new int),
          engine(dev()),
          random_dir(0, 3) {
        *count = 0;
    };
    void Update() override;

   private:
    void UpdateDir();
    std::unique_ptr<int> count;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_dir;
};

#endif