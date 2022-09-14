// @file atomics.cpp
// g++ -std=c++17 atomics.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library
#include <vector>
#include <atomic>  // New library

// Some shared value
static std::atomic<int> shared_value=0;

void increment_shared_value(){
    shared_value ++;
}

int main() {
    std::vector<std::thread> threads;
	// Create a collection of threads
    for(int i=0; i < 1000; i++){
        threads.push_back(std::thread(increment_shared_value));
    } 
    // Join our threads using a ranged-based loop
    // (Our intent is to iterate through all threads in container)
    for(auto& th: threads){
        threads.join();
    } 
	// Retrieve our result
    std::cout << "Result = " << shared_value << std::endl;

    return 0;
}



