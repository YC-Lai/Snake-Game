#include "obstacle.h"

#include <iostream>

#include "SDL.h"

void Obstacle::Update() {
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
    obstaclePoint.x = _x;
    obstaclePoint.y = _y;
}

void Obstacle::initPlace() {
    _x = random_w(engine);
    _y = random_h(engine);
    direction = Direction(random_dir(engine));
}

SDL_Point Obstacle::get_obstecle() { return obstaclePoint; }

bool Obstacle::ObstacleCell(int x, int y) {
    if (x == obstaclePoint.x && y == obstaclePoint.y) {
        return true;
    }
    return false;
}