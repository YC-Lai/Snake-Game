#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <vector>

#include "SDL.h"
#include "controller.h"
#include "food.h"
#include "game_thread.h"
#include "obstacle.h"
#include "renderer.h"
#include "snake.h"

class Game : public GameThread {
   public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller &controller, Renderer &renderer,
             std::size_t target_frame_duration);
    int GetScore() const;
    int GetSize() const;

   private:
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    std::shared_ptr<Snake> snake;
    Food food;

    int score{0};

    void PlaceFood();
    void Update();
};

#endif