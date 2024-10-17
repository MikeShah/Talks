// @file jthread.cpp 
// g++ -std=c++23 jthread.cpp -o prog -lpthread
#include <print>
#include <vector>
#include <thread>   // Include the thread library

int main() {
    // This time create a lambda function
    auto lambda = [](int x){
        size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
        std::println("thread.get_id:{}", tid);
        std::println("Argument passed in:{}", x);
    };

    // Note: We use a 'jthread' this time.
    //       Automatically rejoins on destruction.
    std::vector<std::jthread> threads;
    // Create a collection of threads
    for(int i=0; i < 10; i++){
        threads.push_back(std::jthread(lambda,i));
    } 

    // Continue executing the main thread
    std::println("Hello from the main thread!");

    return 0;
}

