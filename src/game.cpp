#include "game.h"

#include <iostream>
#include <memory>

#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(std::make_shared<Snake>(grid_width, grid_height)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
    PlaceFood();
    PlaceBugs();
}

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    auto running = std::make_shared<bool>(true);
    controller.running = running;

    // Input
    controller.setSnake(snake);
    controller.setTargetFrameDuration(target_frame_duration);
    controller.runThread();

    while (*running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        std::unique_lock<std::mutex> lockSnake(_mtxSnake);
        Update();
        renderer.Render(snake, food, bugs);
        lockSnake.unlock();

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
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

void Game::runThread() {
    // launch control input function in a thread
    threads.emplace_back(std::thread(&Game::Update, this));
}

void Game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake->SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

void Game::PlaceBugs() {
    for (size_t i = 0; i < 3; i++) {
        int x, y;
        SDL_Point bug;
        while (true) {
            x = random_w(engine);
            y = random_h(engine);
            // Check that the location is not occupied by a snake item & food before placing
            // bug.
            if (!snake->SnakeCell(x, y) && food.x != x && food.y != y) {
                bug.x = x;
                bug.y = y;
                bugs.push_back(bug);
                break;
            }
        }
    }
}

void Game::Update() {
    if (!snake->alive) return;

    snake->Update();

    int new_x = static_cast<int>(snake->head_x);
    int new_y = static_cast<int>(snake->head_y);

    // Check if there's a bug over here
    for (auto &bug : bugs) {
        if (bug.x == new_x && bug.y == new_y) {
            snake->alive = false;
        }
    }

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        snake->GrowBody();
        snake->speed += 0.02;
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }