// @file thread2.cpp
// g++ -g -Wall -std=c++23 thread2.cpp -o prog -lpthread
#include <print>
#include <thread>   // Include the thread library

int main() {

    // This time create a lambda function 
    auto lambda = [](int x){
        std::println("Hello from our thread!");
        std::println("Argument passed in: {}", x);
    };

    // Create a new thread and pass one parameter
    std::thread myThread(lambda, 100);
    // Join with the main thread, which is the same as
    // saying "hey, main thread--wait until myThread
    //         finishes before executing further."
    myThread.join();

    // Continue executing the main thread
    std::println("Hello from the main thread!"); 

    return 0;
}
