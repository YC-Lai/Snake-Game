#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "snake.h"

void Controller::setSnake(std::shared_ptr<Snake> const &s) {
    snake = s;
}

void Controller::ChangeDirection(Snake::Direction input,
                                 Snake::Direction opposite) const {
    std::unique_lock<std::mutex> lockSnake(_mtxSnake);
    if (snake->direction != opposite || snake->size == 1) {
        snake->direction = input;
    }
    lockSnake.unlock();
    std::cout << "ChangeDirection update finish!" << std::endl;
    return;
}

void Controller::HandleInput() const {

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            std::unique_lock<std::mutex> lockRunning(_mtxRunning);
            *running = false;
            lockRunning.unlock();
        } else if (e.type == SDL_KEYDOWN) {
            std::cout << "get key" << std::endl;
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