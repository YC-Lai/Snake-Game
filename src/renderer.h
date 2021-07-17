#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>

#include "SDL.h"
#include "snake.h"
#include "game_thread.h"
#include "obstacle.h"
#include "food.h"

class Renderer : public GameThread {
   public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(std::shared_ptr<Snake> const snake, Food &food, std::vector<Obstacle> &obstacles);
    void UpdateWindowTitle(int score, int fps);

   private:

    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif