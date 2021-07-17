#include "obstacle.h"

#include <iostream>

#include "SDL.h"

void Obstacle::Update() {
    direction = Direction(random_dir(engine));
    switch (direction) {
        case Direction::Up:
            _y -= speed;
            break;

        case Direction::Down:
            _y += speed;
            break;

        case Direction::Left:
            _x -= speed;
            break;

        case Direction::Right:
            _x += speed;
            break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    _x = fmod(_x + grid_width, grid_width);
    _y = fmod(_y + grid_height, grid_height);

    placeObstacle();
}

void Obstacle::placeObstacle() {
    // SDL_Point point;
    obstaclePoint.x = _x;
    obstaclePoint.y = _y;
    // obstaclePoints.push_back(point);

    // for (int i = 0; i < grid_width / 8; i++) {
    //     point.x = i + (grid_width / 4);
    //     point.y = grid_height / 3;
    //     obstaclePoints.push_back(point);
    // }

    // for (int i = 0; i < grid_width / 8; i++) {
    //     point.x = i + (grid_width / 4);
    //     point.y = 2 * (grid_height / 3);
    //     obstaclePoints.push_back(point);
    // }
}

void Obstacle::initPlace() {
    _x = random_w(engine);
    _y = random_h(engine);
}

SDL_Point Obstacle::get_obstecle() { return obstaclePoint; }

bool Obstacle::ObstacleCell(int x, int y) {
    // for (auto const &item : obstaclePoints) {
    //     if (x == item.x && y == item.y) {
    //         return true;
    //     }
    // }
    if (x == _x && y == _y) {
        return true;
    }
    return false;
}