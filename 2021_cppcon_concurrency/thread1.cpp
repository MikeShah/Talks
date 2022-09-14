// @file thread1.cpp
// g++ -std=c++17 thread1.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library

// Test function which we'll launch threads from
void test(int x) {
    std::cout << "Hello from our thread!" << std::endl;
    std::cout << "Argument passed in:"   << x << std::endl;
}

int main() {
	// Create a new thread and pass one parameter
    std::thread myThread(&test, 100);
	// Join with the main thread, which is the same as
	// saying "hey, main thread--wait until myThread
	//         finishes before executing further."
    myThread.join();

	// Continue executing the main thread
    std::cout << "Hello from the main thread!" << std::endl;

    return 0;
}
