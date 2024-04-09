#include "threadmanager.h"
#include <iostream>

ThreadManager::ThreadManager() : sharedData(std::make_shared<SharedData>()) {}

ThreadManager::~ThreadManager() {
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}
