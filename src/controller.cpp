#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "snake.h"

void Controller::setSnake(std::shared_ptr<Snake> const &s) {
    snake = s;
}

void Controller::ChangeDirection(Snake::Direction input,
                                 Snake::Direction opposite) const {
    if (snake->direction != opposite || snake->size == 1) snake->direction = input;
    return;
}

void Controller::HandleInput(bool &running) const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    ChangeDirection(Snake::Direction::kUp,
                                    Snake::Direction::kDown);
                    break;

                case SDLK_DOWN:
                    ChangeDirection(Snake::Direction::kDown,
                                    Snake::Direction::kUp);
                    break;

                case SDLK_LEFT:
                    ChangeDirection(Snake::Direction::kLeft,
                                    Snake::Direction::kRight);
                    break;

                case SDLK_RIGHT:
                    ChangeDirection(Snake::Direction::kRight,
                                    Snake::Direction::kLeft);
                    break;
            }
        }
    }
}