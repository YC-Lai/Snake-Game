#include "game.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <thread>

#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(std::make_shared<Snake>(grid_width, grid_height)),
      obstacle(grid_width, grid_height),
      food(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
    food.placeFood(snake);
}

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    auto running = std::make_shared<bool>(true);

    // Setup controller
    controller.setSnake(snake);
    controller.running = running;

    while (*running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        futures.emplace_back(std::async(std::launch::async,
                                        &Controller::HandleInput,
                                        std::ref(controller)));
        futures.emplace_back(
            std::async(std::launch::async, &Game::Update, this));

        std::for_each(futures.begin(), futures.end(),
                      [](std::future<void> &ftr) { ftr.wait(); });

        renderer.Render(snake, food, obstacle);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render
        // cycle takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Game::Update() {
    if (!snake->alive) return;

    snake->Update();

    int new_x = static_cast<int>(snake->head_x);
    int new_y = static_cast<int>(snake->head_y);

    // Check if there's a obstacle over here
    if (obstacle.ObstacleCell(new_x, new_y)) {
        snake->alive = false;
    }

    // Check if there's food over here
    auto foodPoint = food.get_food();
    if (foodPoint.x == new_x && foodPoint.y == new_y) {
        score++;
        std::unique_lock<std::mutex> lockFood(_mtxFood);
        food.placeFood(snake);
        lockFood.unlock();
        // Grow snake and increase speed.
        snake->GrowBody();
        snake->speed += 0.01;
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }