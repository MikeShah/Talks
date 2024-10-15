// @file jthread.cpp 
// g++ -std=c++23 jthread.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library
#include <vector>
#include <print>

int main() {
		// This time create a lambda function
		auto lambda = [](int x){
				std::println("thread.get_id:{}", std::this_thread::get_id());
				std::println("Argument passed in:{}", x);
		};

		// Note: We now have a jthread
		//       No joins in the program
		std::vector<std::jthread> threads;
		// Create a collection of threads
		for(int i=0; i < 10; i++){
				threads.push_back(std::jthread(lambda,i));
		} 

		// Continue executing the main thread
		std::cout << "Hello from the main thread!" << std::endl;

		return 0;
}


