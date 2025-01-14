// @file thread_safe_queue.cpp 
// g++-11 -std=c++23 thread_safe_queue.cpp -o prog -lpthread
#include <iostream>
#include <vector>
#include <thread>   // Include the thread library
#include <mutex>
#include <queue>
#include <latch>

//std::counting_semaphore tasks(100); // No need to manage counting semaphore.
                                      // This example uses a latch which 'counts down' until 
                                      // finished.

// Thread-Safe namespace for versions of containers.
namespace ThreadSafe{

    // A trivial implementation adding a lock to every operation.
    // This example implements a 'monitor' which is a lock that ensures
    // this data structure can only be accesssed by one thread at a time.
    struct Queue{
        const int& front() const{
            // lock_guard is locked and unlocked only on construction and destruction
            std::lock_guard<std::mutex> guard(mMutex);
            return mQueue.front();
        }

        // Note: As homework you can make a 'push' that takes an rvalue reference to avoid
        //       construction.
        void push(int element){
            std::lock_guard<std::mutex> guard(mMutex);
            mQueue.push(element);
        }

        void pop(){
            std::lock_guard<std::mutex> guard(mMutex);
            mQueue.pop();
        }

        private:
            std::queue<int> mQueue;
            // Lock needed per instance of our queue
            mutable std::mutex mMutex; // Note: We need 'mutable' so we can override 'const' functions
                                       //       and allow the state of the mutex to change.
    };
}

int main() {
        //std::println();
				std::cout << std::endl;

        const int problemSize = 100;
        ThreadSafe::Queue q;
        std::latch jobsToComplete(problemSize);

		// This time create a lambda function
		auto lambda = [&](int x){
            q.push(x);
            // Decrement each time we finish a job just before
            // termination.
            jobsToComplete.count_down();
		};

		// Note: We now have a jthread
		//       No joins in the program
		std::vector<std::jthread> threads;
		// Create a collection of threads
		for(size_t i=0; i < problemSize; ++i){
			threads.push_back(std::jthread(lambda,i));
		} 

        // Block until we have finished all of our jobs
        jobsToComplete.wait();

        for(size_t i=0; i < problemSize; ++i){
//            std::print("{},",q.front());
						std::cout << q.front() << ",";
            q.pop();
        }

		// Continue executing the main thread
//		std::println("\n\nEnd of main thread!");
		std::cout << "\n\nEnd of main thread!" << std::endl;
		return 0;
}
