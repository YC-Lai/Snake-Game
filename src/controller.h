#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include "snake.h"
#include "game_thread.h"

class Controller : public GameThread {
   public:
    void HandleInput() const;

    void setSnake(std::shared_ptr<Snake> const &s);
    void setTargetFrameDuration(std::size_t const &t);
    void runThread() override;
    void controlInput() ; 

    std::shared_ptr<bool> running;

   private:
    std::shared_ptr<Snake> snake;
    std::size_t target_frame_duration;
    void ChangeDirection(Snake::Direction input,
                         Snake::Direction opposite) const;
};

#endif