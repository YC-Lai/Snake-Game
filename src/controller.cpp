#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "snake.h"

void Controller::setSnake(std::shared_ptr<Snake> const &s) {
    snake = s;
}

void Controller::setTargetFrameDuration(std::size_t const &t) /*To get the target_frame_duration from the controller*/
{
    target_frame_duration = t;
}

void Controller::runThread() {
    // launch control input function in a thread
    threads.emplace_back(std::thread(&Controller::controlInput, this));
}

/*This is a thread function that is reposible for handling the snake input control*/
void Controller::controlInput() {
    Uint32 title_timestamp = SDL_GetTicks(); /*Record the start time for input control*/

    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;

    while (*running) { /*while the SDL Quit is not pressed, the running flag is always true*/

        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        frame_start = SDL_GetTicks(); /*Record the start time before the controller input*/
        Controller::HandleInput();    /*Call the input control function*/
        frame_end = SDL_GetTicks();   /*Record the end time before the controller input*/

        frame_duration = frame_end - frame_start; /*Calculate the duration for handling the input control*/

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate. to be removed .
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Controller::ChangeDirection(Snake::Direction input,
                                 Snake::Direction opposite) const {
    std::unique_lock<std::mutex> lockSnake(_mtxSnake);
    if (snake->direction != opposite || snake->size == 1) {
        snake->direction = input;
    }
    lockSnake.unlock();
    return;
}

void Controller::HandleInput() const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            *running = false;
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