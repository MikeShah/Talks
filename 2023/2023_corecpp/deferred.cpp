// g++ -g -Wall -std=c++20 deferred.cpp -o prog -lpthread
#include <iostream>
#include <thread>
#include <future>

void expensiveComputation(){
		using namespace std::chrono_literals;
		/* really expensive computation... */
		std::this_thread::sleep_for(2000ms);

    std::cout << "Computing something expensive\n";
}

// Entry point to program
int main(int argc, char* argv[]){

    // Setup a promise/future
    auto lazy = std::async(std::launch::deferred, &expensiveComputation);

		std::cout << "Do some work here" << std::endl;

    // Try switching flag to true and false and
    // see the different behaviors
		bool flag=false;

    if(flag){
        // Function not called until we 
        // explicitly ask for result.
        lazy.get();
    }

		std::cout << "Continuing on with our lives" << std::endl;

    return 0;
}



