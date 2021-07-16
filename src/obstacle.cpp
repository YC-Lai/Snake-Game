#include "obstacle.h"

#include <iostream>

#include "SDL.h"

void Obstacle::placeObstacle() {
    SDL_Point point;

    for (int i = 0; i < grid_width / 2; i++) {
        point.x = i + (grid_width / 4);
        point.y = grid_height / 3;
        obstaclePoints.push_back(point);
    }

    for (int i = 0; i < grid_width / 2; i++) {
        point.x = i + (grid_width / 4);
        point.y = 2 * (grid_height / 3);
        obstaclePoints.push_back(point);
    }
}

std::vector<SDL_Point> Obstacle::get_obstecle() { return obstaclePoints; }

bool Obstacle::ObstacleCell(int x, int y) {
    for (auto const &item : obstaclePoints) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}