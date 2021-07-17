#ifndef GAMETHREAD_H
#define GAMETHREAD_H
#include <mutex>
#include <thread>
#include <future>
#include <vector>

/**
 * This ensures the thread and mutex and a thread barrier for the
 * GameObject inherited from this class.
 */
class GameThread {
   public:
    //  desctructor
    ~GameThread();

   protected:
    std::vector<std::future<void>> futures;  
    static std::mutex _mtxSnake;       
    static std::mutex _mtxFood;       
    static std::mutex _mtxObstacle;        
    static std::mutex _mtxRunning; 

   private:
};

#endif  // CPP_SNAKE_GAME_CORE_GAME_THREAD_HPP