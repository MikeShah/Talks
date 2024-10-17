// @file simple_cv.cpp
// g++ -std=c++23 simple_cv.cpp -o prog -lpthread
#include <iostream>
#include <tuple>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>

using namespace std::literals::chrono_literals;

// Global state that can be accessed
// (Otherwise could be in a struct/class)
std::mutex              shared_lock_between_producerconsumer;
std::condition_variable cv;
bool               		ready {false};
std::queue<int> 		shared_queue;


// Producers goal is to otherwise 'add' or 'modify' data
static void producer() {

    for(int i=0; i < 5; i++)
    {
        std::this_thread::sleep_for(250ms);
        {
            std::lock_guard<std::mutex> lk {shared_lock_between_producerconsumer};
            // Do some interesting work here
            // Note: We have 'locked' the 'shared' portion of data
            shared_queue.push(i);
        }
        // Something interesting has happened, so notify the conditoinal variable
        // Effectively -- wake all threads
        cv.notify_all();
    }

    {
        std::lock_guard<std::mutex> lk {shared_lock_between_producerconsumer};
        ready = true;
    }
    cv.notify_all();
}

// Consumer thread
// Usual goal to 'consume' data
static void consumer() {
    while (!ready) {
        std::unique_lock<std::mutex> l {shared_lock_between_producerconsumer};
        cv.wait(l, [] { return !shared_queue.empty() || ready; });

        std::cout << "Consuming new value from shared_queue: " << shared_queue.front() << std::endl;
        shared_queue.pop();
    }
}

// Entry point
int main() {

    std::thread t1 {producer};
    std::thread t2 {consumer};
    // Important that we 'join' here and have some control
    t1.join();
    t2.join();
    std::cout << "Completed the task: " << "" << std::endl;
}
