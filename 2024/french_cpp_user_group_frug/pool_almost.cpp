// @file pool_almost.cpp
// g++ -std=c++23 pool_almost.cpp -o prog -lpthread
#include <iostream>
#include <thread>   // Include the thread library
#include <vector>
#include <array>
#include <cstring>
#include <functional>

// Global data, or otherwise 'heap' allocated data
// is by default 'shareable' to every thread.
std::array<int,256> shared_global_data;

template <size_t threadcount>
struct ThreadPool{

		ThreadPool(std::function<void(int,int)> func){
				command = func;
		}

		void executeAll(size_t iterations, size_t jobSize){
				size_t count = 0;

				// Execute our '50000' iterations
				while(count < iterations){
						for(size_t i=0; i < threadcount; i++){
							// Assign ahead of time the thread you want to execute
							threads[i] = std::jthread(command, i, jobSize);
						}
						count++;
				}		
		}

		std::function<void(int,int)> command;
		std::array<std::jthread,threadcount> threads;
};


// Entry point to program
int main() {

		// Zero-out memory
		std::memset(shared_global_data.data(), 0, sizeof(int)*shared_global_data.size());

		// Here is our dilligent worker that will execute on some shared memory
		// The 'index' (sometimes abbreviated 'idx' or just 'id') we will use
		// in combination with 'jobSize' -- indicating how many bytes to increment.
		auto AdditionWorker= [](size_t index, size_t jobSize){
				for(size_t i = index*jobSize; i < (index+1) * jobSize; i++){
						shared_global_data[i] += 1;	
				}
		};

		auto threadPool = ThreadPool<4>(AdditionWorker);

		threadPool.executeAll(50000,64);


		// Continue executing the main thread
		std::cout << "Job completed -- in main thread and printing results" << std::endl;
		// Write out data
		for(size_t i=0; i < shared_global_data.size(); i++){
				std::cout << shared_global_data[i] << " ";
		}
		std::cout << std::endl;
		return 0;
}

