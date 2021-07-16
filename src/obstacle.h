#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>

#include "SDL.h"

class Obstacle {
   public:
    Obstacle(int grid_width, int grid_height) {
        this->grid_width = grid_width;
        this->grid_height = grid_height;

        placeObstacle();
    }

    std::vector<SDL_Point> get_obstecle();
    bool ObstacleCell(int x, int y);

   private:
    void placeObstacle();
    std::vector<SDL_Point> obstaclePoints;
    size_t grid_width;
    size_t grid_height;
};

#endif