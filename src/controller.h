#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include "snake.h"

class Controller {
   public:
    void HandleInput(bool &running) const;

    void setSnake(std::shared_ptr<Snake> const &s);

   private:
    std::shared_ptr<Snake> snake;
    void ChangeDirection(Snake::Direction input,
                         Snake::Direction opposite) const;
};

#endif