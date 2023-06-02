// @file thread3.cpp
// g++ -std=c++17 thread3.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library
#include <vector>

int main() {

    // This time create a lambda function
    auto lambda = [](int x){
        std::cout << "thread.get_id:" << std::this_thread::get_id() << std::endl;
        std::cout << "Argument passed in:"   << x << std::endl;
    };
    
    std::vector<std::thread> threads;
	// Create a collection of threads
    for(int i=0; i < 10; i++){
        threads.push_back(std::thread(lambda,i));
        threads[i].join();
    } 

	// Continue executing the main thread
    std::cout << "Hello from the main thread!" << std::endl;

    return 0;
}



