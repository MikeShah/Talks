// @file thread6.cpp
// g++ -std=c++17 thread6.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library
#include <vector>
# include <mutex>  // New library

// Some shared value
static int shared_value = 0;
std::mutex gLock; // A global lock

void increment_shared_value(){
    gLock.lock();
        shared_value = shared_value + 1;
    gLock.unlock();
}

int main() {
    std::vector<std::thread> threads;
	// Create a collection of threads
    for(int i=0; i < 1000; i++){
        threads.push_back(std::thread(increment_shared_value));
    } 
    // Join our threads
    for(int i=0; i < 1000; i++){
        threads[i].join();
    } 
	// Retrieve our result
    std::cout << "Result = " << shared_value << std::endl;

    return 0;
}



