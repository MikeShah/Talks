// @file packaged_task.cpp 
//
// Demonstrates packaged_task, which effectively is what you could use to 
// implement your own std::async functions
//
// g++ -std=c++23 packaged_task.cpp -o prog -lpthread
#include <vector>
#include <print>
#include <thread>
#include <chrono>
#include <functional>
#include <future>

// This is the 'work unit' that we'll wrap in a packaged_task later on
int SomeWork(int x, int y){
   std::this_thread::sleep_for(std::chrono::seconds(3));
   return x*x + y*y; 
}

int main() {
		std::println("\nHello from the main thread!");

        // Start up some other work
        std::packaged_task<int()> task(std::bind(SomeWork,1,2));

        // Prepa 
        std::future<int> result = task.get_future();

        // Call the task
        // Needs to be invoked manually, which is a difference between
        // std::aysnc for instance.
        //
        // Note:
        // std::async destructor does block however, so a bit more flexibility
        // with packaged_tasks
        // https://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async
        std::thread myThread(std::move(task));

        std::println("Proceeding to do some work");
        std::println("Proceeding to do some work");
        std::println("Proceeding to do some work");
        std::println("Proceeding to do some work");


        // Blocked here until we get result
        // Note: It's important that we invoke (i.e. call the 'task()' somewhere
        //       before we try to retrieve our future.
        std::println("Got result {}",result.get());

        // Make sure we join our thread
        myThread.join();

        std::println("End of program");


		return 0;
}

