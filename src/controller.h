#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include "snake.h"
#include "game_thread.h"

class Controller : public GameThread {
   public:
    void HandleInput() const;

    void setSnake(std::shared_ptr<Snake> const &s);

    std::shared_ptr<bool> running;

   private:
    std::shared_ptr<Snake> snake;
    void ChangeDirection(Snake::Direction input,
                         Snake::Direction opposite) const;
};

#endif