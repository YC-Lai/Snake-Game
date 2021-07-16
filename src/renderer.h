#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>

#include "SDL.h"
#include "snake.h"
#include "game_thread.h"

class Renderer : public GameThread {
   public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(std::shared_ptr<Snake> const snake, SDL_Point const &food, std::vector<SDL_Point> &bugs);
    void UpdateWindowTitle(int score, int fps);

    void setSnake(std::shared_ptr<Snake> const &s);
    void runThread() override;
    void controlRender(); 

    std::shared_ptr<bool> running;

   private:
    std::shared_ptr<Snake> snake;

    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif