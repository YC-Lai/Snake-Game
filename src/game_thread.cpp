#include "game_thread.h"

#include <algorithm>
#include <iostream>

// std::mutex GameThread::_mtx;
std::mutex GameThread::_mtxSnake;    // mutex shared by all game Threads for
                                     // protecting the shared snake
std::mutex GameThread::_mtxFood;     // mutex shared by all game Threads for
                                     // protecting the shared food
std::mutex GameThread::_mtxCout;     // mutex shared by all game Threads for
                                     // protecting the shared cout
std::mutex GameThread::_mtxRunning;  // mutex shared by all game Threads for
                                     // protecting the shared SDL

GameThread::~GameThread() {
    // set up thread barrier before this Thread is destroyed
    std::for_each(futures.begin(), futures.end(),
                  [](std::future<void> &ftr) { ftr.wait(); });
}