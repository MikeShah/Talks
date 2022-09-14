// @file async.cpp
// g++ -std=c++17 async.cpp -o prog -lpthread
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Toy example - This will be our 'background thread'
//               that executes asynchronously
bool bufferedFileLoading(){
    size_t bytesLoaded= 0;
    while(bytesLoaded < 20000){
        std::cout << "Loading File..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); 
        bytesLoaded+= 1000;
    }
    return true;    
}

int main() {
    // Launch thread asynchronusly, and this will execute in background
    std::future<bool> backgroundThread = std::async(std::launch::async, 
                                                    bufferedFileLoading);
    // Store status of our future
    std::future_status status;
    // Meanwhile, we have our main thread of execution 
    while(true){
        std::cout << "Main thread running" << std::endl;
        // artificial pause
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
        // Check if our 
        status = backgroundThread.wait_for(std::chrono::milliseconds(1));
        // If our data is ready--do something
        // we'll just terminate for now
        if(status == std::future_status::ready){
            std::cout << "data ready..." << std::endl;
            break;
        }        
    }

    return 0;
}



