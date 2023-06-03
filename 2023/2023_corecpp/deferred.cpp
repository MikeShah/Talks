// g++ -g -Wall -std=c++20 deferred.cpp -o prog -lpthread
#include <iostream>
#include <future>

void expensiveComputation(){
    std::cout << "Computing something expensive\n";
}

// Entry point to program
int main(int argc, char* argv[]){

    // Setup a promise/future
    auto lazy = std::async(std::launch::deferred, &expensiveComputation);

    // Try switching flag to true and false and
    // see the different behaviors
    bool flag=true;

    if(flag){
        // Function not called until we 
        // explicitly ask for result.
        lazy.get();
    }


    return 0;
}



