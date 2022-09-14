// @file cv.cpp
// g++ -std=c++17 cv.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library
#include <vector>
#include <chrono>
#include <mutex>  
#include <condition_variable> // New library

std::mutex gLock; // A global lock
std::condition_variable gConditionVariable;

int main() {
    std::cout << "main() starts" << std::endl;

    int result =0; // The result we're tring to compute
    bool notified = false; 
    // This thread reports the result (consumes the result)
    // Could call this a 'consumer' or 'reporter' thread
    std::thread reporter([&]{
        std::unique_lock<std::mutex> lock(gLock);
        // wait here until notified
        if(!notified){ // We need some variable to wait on
            gConditionVariable.wait(lock);
        }
        std::cout << "\tReporter Result = " << result << std::endl;
    });

    // This thread does the work
    std::thread worker([&]{
        std::unique_lock<std::mutex> lock(gLock); 
        // Do our work
        result = 42;
        // Update our variable
        notified = true;
        // artificial pause to show that reporter will indeed wait
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // Output a message
        std::cout << "\twork complete" << std::endl;
        // Notify one thread about a change
        // Could also notify_all
        gConditionVariable.notify_one();
    });

    
    // Don't forget to join!
    reporter.join();
    worker.join();
    std::cout << "main end " << std::endl;
    return 0;
}



