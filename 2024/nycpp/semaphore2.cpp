// NOTE: This example doesn't really work, we need better primtives

// @file semaphore1.cpp 
// g++ -std=c++23 semaphore1.cpp -o prog -lpthread
#include <iostream>
#include <vector>
//#include <print>
#include <thread>   // Include the thread library
#include <semaphore>// semaphore for synchronization

int gCounter =0;
std::binary_semaphore gSem(0);

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

		// Our worker thread is always blocked until 
		// we 'release' or 'signal' that we are ready.
		// 'release' increments our counter, making available one more
		// 'slot' to acquire from the semaphore.
		gSem.release();

		  // Continue executing the main thread
	  	std::cout << std::endl << "gCounter = " << gCounter << std::endl;

		return 0;
}


