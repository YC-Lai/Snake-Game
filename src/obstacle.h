#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <memory>
#include <random>
#include <vector>

#include "SDL.h"
#include "game_thread.h"

class Obstacle {
   public:
    enum class Direction { Up,
                           Down,
                           Left,
                           Right };

    Obstacle(std::size_t grid_width, std::size_t grid_height)
        : engine(dev()),
          random_dir(0, 3),
          random_w(0, static_cast<int>(grid_width - 1)),
          random_h(0, static_cast<int>(grid_height - 1)) {
        this->grid_width = grid_width;
        this->grid_height = grid_height;
        initPlace();
    }

    SDL_Point get_obstecle();
    bool ObstacleCell(int x, int y);
    void Update();

   private:
    void placeObstacle();
    void initPlace();
    // std::vector<SDL_Point> obstaclePoints;
    SDL_Point obstaclePoint;
    size_t grid_width;
    size_t grid_height;
    float speed{0.03f};
    Direction direction;
    float _x;
    float _y;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_dir;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
};

#endif