#ifndef GAMETHREAD_H
#define GAMETHREAD_H
#include <mutex>
#include <thread>
#include <vector>

/**
 * This ensures the thread and mutex and a thread barrier for the
 * GameObject inherited from this class.
 */
class GameThread {
   public:
    //  desctructor
    ~GameThread();

    // typical behaviour methods
    virtual void runThread() = 0;

   protected:
    std::vector<std::thread> threads;  // holds all threads that have been launched within this object
    static std::mutex _mtxSnake;       // mutex shared by all game objects for protecting the shared snake
    static std::mutex _mtxFood;        // mutex shared by all game objects for protecting the shared food
    static std::mutex _mtxCout;        // mutex shared by all game objects for protecting the shared cout
    static std::mutex _mtxRunning;     // mutex shared by all game objects for protecting the shared running Flag

   private:
};

#endif  // CPP_SNAKE_GAME_CORE_GAME_THREAD_HPP