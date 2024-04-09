#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

class SharedData {
public:
    template<typename T>
    void init(const std::string& name, T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        data_[name] = value;
    }

    template<typename T>
    T get(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex_);
        try {
            return std::any_cast<T>(data_.at(name));
        }
        catch (const std::bad_any_cast& e) {
            std::cerr << "Error: bad_any_cast in SharedData::get for key " << name << ": " << e.what() << std::endl;
            throw;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: out_of_range in SharedData::get for key " << name << ": " << e.what() << std::endl;
            throw;
        }
    }

    template<typename T>
    void set(const std::string& name, T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        data_[name] = value;
    }

private:
    std::unordered_map<std::string, std::any> data_;
    std::mutex mutex_;
};

class ThreadManager {
public:
    ThreadManager();
    ~ThreadManager();

    template<typename Callable, typename... Args>
    void start(Callable&& func, Args&&... args);

    std::shared_ptr<SharedData> sharedData;

private:
    std::vector<std::thread> threads;
};

#include "ThreadManager.impl.h"

#endif // THREADMANAGER_H
