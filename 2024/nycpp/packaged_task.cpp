// @file packaged_task.cpp 
// g++ -std=c++23 packaged_task.cpp -o prog -lpthread
#include <iostream>
#include <vector>
//#include <print>
#include <thread>   // Include the thread library
#include <semaphore>// semaphore for synchronization
#include <future>

void WorkerThread(int arg){
	// Acquire 'decrements' the counter associated
	// with the semaphore, such that '1' less
	// piece of work can pass by. 
	gSem.acquire();
		std::cout << "thread.id:" << std::this_thread::get_id() << std::endl;
		//std::println("thread.get_id:{}", std::this_thread::get_id());
		//std::println("Argument passed in:{}", arg);
		gCounter++;
	gSem.release();
}

int main() {
		// Launch a thread
		std::vector<std::jthread> js;

		for(size_t i=0; i < 100; ++i){
			js.push_back(std::jthread(WorkerThread,i));
		}
		// Proceed to do any useful work
		std::cout << "Hello from the main thread!" << std::endl;

		  // Continue executing the main thread
	  	std::cout << std::endl << "gCounter = " << gCounter << std::endl;

		return 0;
}


