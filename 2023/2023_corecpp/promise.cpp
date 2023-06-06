// g++ -g -Wall -std=c++20 promise.cpp -o prog -lpthread
#include <iostream>
#include <future>
#include <thread>

int ComputeSomethingExpensive(){	
		using namespace std::chrono_literals;
		/* really expensive computation... */
		std::this_thread::sleep_for(2000ms);
		std::cout << "Working asynchronously" << std::endl;

		return 42;
}

// Entry point to program
int main(int argc, char* argv[]){

		// std::promise stores a value that will be later acquired
		// asynchronously. It is a 'promise' that gaureentees some
		// value will be available leater.
		// The promise 'pushes' the result to the future when
		// we execute it.
		std::promise<int> myPromise;
	
		// Future waits for a value (i.e. reads)
		// Future is associated with a promise.
		// The type in the promise and future must match (i.e. both are int).
		std::future<int> myFuture = myPromise.get_future();
		// The 'get_future' associates the promise with this future
		// thus 'bundling' them together.

		std::cout << "Do some other work here" << std::endl;

		// Launch a thread which will do some work.
		// Note: We need to 'capture' myPromise here 
		// 		   in order to use it in our lambda.
		// Note: 'myPromise' does not have to be in a thread, 
		//        we could call myPromise.set_value within main, but
		//        we would wait for the function to execute.
		std::thread worker([&myPromise]{
			myPromise.set_value(ComputeSomethingExpensive());
		});

		std::cout << "continue on with our lives" << std::endl;

		myFuture.wait();
		// Note: .get effectively calls '.wait' so this 
		//       is redudant, just use 'get' in this case.
		// 'get blocks' on the future until a result is available. 
		std::cout << "myFuture is: " << myFuture.get() << std::endl;

		// Don't forget to join your thread!
		// Otherwise, consider using jthread
		worker.join();

    return 0;
}
