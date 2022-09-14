// @file thread9.cpp
// g++ -std=c++17 thread9.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library
#include <vector>
#include <mutex>  // New library

// Some shared value
static int shared_value = 0;
std::mutex gLock; // A global lock

void increment_shared_value(){
    // lock_guard follows RAII principles and will
    // release lock after leaving scope.
    // This includes if an exception is thrown.
    std::lock_guard<std::mutex> lockGuard(gLock);
        try{
            shared_value = shared_value + 1;
            throw "Dangerous exception abort";
        }catch(...){
            std::cout << "handle exception by returning from thread\n";
            return;
        }
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



