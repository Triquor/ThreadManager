#include "ThreadManager/threadmanager.h"
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <string>

// Function that increments a counter in a loop
void incrementer(SharedData& sharedData, DWORD pid) {
    int i = 0;

    // Initialize the shared counter named "counter" with 0
    sharedData.init<int>("counter", i);
    while (true) {
        // Display the process ID (PID) for demonstration purposes
        std::cout << "PID: " << pid << std::endl;
        // Sleep
        std::this_thread::sleep_for(std::chrono::microseconds(2));
        i++; // Increment the counter
        // Update the shared counter with the new value of i
        sharedData.set<int>("counter", i);
    }
}

// Function that prints the current value of the counter when it changes
void printer(SharedData& sharedData) {
    int lastPrinted = 0; // To track the last printed value
    while (true) {
        // Sleep
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        // Retrieve the current value of the counter
        int current = sharedData.get<int>("counter");
        // If the current value is different from the last printed value, print it
        if (current != lastPrinted) {
            std::cout << "Counter: " << current << std::endl;
            lastPrinted = current; // Update the last printed value
        }
    }
}

int main() {

    DWORD pid = 1234; // Example pid, not used in any significant way

    // Create an instance of ThreadManager
    ThreadManager threadManager;
    // Start the incrementer function in a new thread, passing the shared data and PID
    threadManager.start(incrementer, pid);
    // Start the printer function in another new thread, passing only the shared data
    threadManager.start(printer);

    return 0;
}
