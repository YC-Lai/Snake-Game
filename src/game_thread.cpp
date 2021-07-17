#include "game_thread.h"

#include <algorithm>
#include <iostream>

// This share the same mutex to all inherited classes
std::mutex GameThread::_mtxSnake;
std::mutex GameThread::_mtxFood;
std::mutex GameThread::_mtxObstacle;
std::mutex GameThread::_mtxRunning;

GameThread::~GameThread() {
    // set up thread barrier before this Thread is destroyed
    std::for_each(futures.begin(), futures.end(),
                  [](std::future<void> &ftr) { ftr.wait(); });
}