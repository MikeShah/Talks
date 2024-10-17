// @file team.cpp
// g++ -std=c++23 team.cpp -o prog -lpthread
#include <print>
#include <thread>   // Include the thread library
#include <vector>
#include <array>
#include <cstring>

// Global data, or otherwise 'heap' allocated data
// is by default 'shareable' to every thread.
std::array<int,256> shared_global_data;

// Entry point to program
int main() {

		// Zero-out memory
		std::memset(shared_global_data.data(), 0, sizeof(int)*shared_global_data.size());

		// Here is our dilligent worker that will execute on some shared memory
		// The 'index' (sometimes abbreviated 'idx' or just 'id') we will use
		// in combination with 'jobSize' -- indicating how many bytes to increment.
		auto AdditionWorker= [](size_t index, size_t jobSize){
		//  std::println << "thread.get_id:" << std::this_thread::get_id() << std::endl;			
				for(size_t i = index*jobSize; i < (index+1) * jobSize; i++){
						shared_global_data[i] += 1;	
				}
		};

		// 'threads' vector enables us the ability to push in jthreads -- and execute
		// multiple threads in parallel
		std::vector<std::jthread> threads;
		// Run many iterations of our simulation 
		for(int j=0; j < 5; j++){
				// Create four threads at a time
				// They will 'synchronize' and effectively work as a team of '4' at a time
				for(int i=0; i < 4; i++){
						threads.push_back(std::jthread(AdditionWorker,i,64));
				} 
		}
		std::println("threads.size: {}", threads.size());

        // Ensure all threads have been joined
        for(int i=0; i < threads.size();i++){  threads[i].join();  }

		// Continue executing the main thread
		std::println("Job completed -- in main thread and printing results");
		// Write out data
		for(size_t i=0; i < shared_global_data.size(); i++){
				std::print("[{0:3}] {1:2} ",i,shared_global_data[i]);
                if(i%10==0){std::println();}
		}
		std::println();
		return 0;
}
