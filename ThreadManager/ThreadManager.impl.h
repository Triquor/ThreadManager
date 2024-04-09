#pragma once

#ifndef THREADMANAGER_IMPL_H
#define THREADMANAGER_IMPL_H

template<typename Callable, typename... Args>
void ThreadManager::start(Callable&& func, Args&&... args) {
    auto task = [this, func, &args...]() {
        try {
            func(*sharedData, std::forward<Args>(args)...);
        }
        catch (const std::exception& e) {
            std::cerr << "Exception in thread: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Unknown exception in thread." << std::endl;
        }
        };
    threads.emplace_back(std::move(task));
}

#endif
