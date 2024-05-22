// @file async.cpp
// g++ -std=c++23 async.cpp -o prog -lpthread
#include <iostream>
#include <thread>   
#include <vector>
#include <future> // for std::async
#include <chrono>

int main() {

    // This time create a lambda function
    auto lambda = [](int x){
				std::this_thread::sleep_for (std::chrono::seconds(1));
        std::cout << "tid:" << std::this_thread::get_id() << std::endl;
        std::cout << "Argument passed in:"   << x << std::endl;
				return x;
    };
    
    std::vector<std::jthread> threads;
    for(int i=0; i < 10; i++){
        threads.push_back(std::jthread(lambda,i));
				std::cout << "Making progress on iteration " << i << std::endl;
    }

//		std::vector <std::future<int>> async_results(10);
//		for(int i=0; i < 10; i++){
//			async_results[i] = std::async(std::launch::async, lambda, i);
//			std::cout << "Making progress on iteration " << i << std::endl;
//		} 

	// Continue executing the main thread
    std::cout << "Hello from the main thread!" << std::endl;

    return 0;
}



