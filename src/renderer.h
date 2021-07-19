#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "SDL.h"
#include "food.h"
#include "game_thread.h"
#include "obstacle.h"
#include "snake.h"

class Renderer : public GameThread {
   public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(std::shared_ptr<Snake> const snake,
                Food &food,
                std::vector<std::shared_ptr<Obstacle>> &obstacles);
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