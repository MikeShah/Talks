// @file thread2.cpp
// g++ -std=c++17 thread2.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library

int main() {

    // This time create a lambda function
    auto lambda = [](int x){
        std::cout << "Hello from our thread!" << std::endl;
        std::cout << "Argument passed in:"   << x << std::endl;
    };
    
	// Create a new thread with our lambda this time
    std::thread myThread(lambda,100);
	// Join with the main thread, which is the same as
	// saying "hey, main thread--wait until myThread
	//         finishes before executing further."
    myThread.join();

	// Continue executing the main thread
    std::cout << "Hello from the main thread!" << std::endl;

    return 0;
}
