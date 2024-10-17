// @file semaphore1.cpp 
// g++ -std=c++23 semaphore1.cpp -o prog -lpthread
#include <vector>
#include <chrono>
#include <print>
#include <thread>   // Include the thread library
#include <semaphore>// semaphore for synchronization

std::binary_semaphore gSem(0);

void WorkerThread(int arg){
	// Acquire 'decrements' the counter associated
	// with the semaphore, such that '1' less
	// piece of work can pass by. 
	gSem.acquire();
        size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
		std::println("thread.get_id:{}", tid);
		std::println("Argument passed in:{}", arg);
	gSem.release();
}

int main() {
		// Launch a thread
		std::jthread j(WorkerThread,10);
		// Proceed to do any useful work
		std::println("Hello from the main thread!");

		// Our worker thread is always blocked until 
		// we 'release' or 'signal' that we are ready.
		// 'release' increments our counter, making available one more
		// 'slot' to acquire from the semaphore.
		std::this_thread::sleep_for(std::chrono::seconds(1));
		gSem.release();

		gSem.acquire();
		  // Continue executing the main thread
	  	std::println("Program ending");
		gSem.release();

		return 0;
}


