// @file semaphore2.cpp 
// g++ -std=c++23 semaphore2.cpp -o prog -lpthread
#include <iostream>
#include <vector>
#include <print>
#include <thread>   // Include the thread library
#include <semaphore>// semaphore for synchronization

int gCounter =0;
std::binary_semaphore gSem(1);

void WorkerThread(int arg){
	// Acquire 'decrements' the counter associated
	// with the semaphore, such that '1' less
	// piece of work can pass by. 
	gSem.acquire();
        size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
		std::println("thread.get_id:{}", tid);
		std::println("Argument passed in:{}", arg);
		gCounter++;
	gSem.release();
}

int main() {
		// Launch a thread
		std::vector<std::jthread> js;
        js.reserve(100);

		for(size_t i=0; i < 100; ++i){
			js.push_back(std::jthread(WorkerThread,i));
		}
		// Proceed to do any useful work
		std::println("Hello from the main thread!");

		// Our worker thread is always blocked until 
		// we 'release' or 'signal' that we are ready.
		// 'release' increments our counter, making available one more
		// 'slot' to acquire from the semaphore.
		gSem.acquire();

		  // Continue executing the main thread
	  	std::println("gCounter = {}",gCounter);
		gSem.release();

		return 0;
}


