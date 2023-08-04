// @file thread5.cpp
// g++ -std=c++17 thread5.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library
#include <vector>

// Some shared value
// A little ugly that it's a static global  but it's a toy example.
static int shared_value = 0;

void increment_shared_value(){
    shared_value = shared_value + 1;
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



